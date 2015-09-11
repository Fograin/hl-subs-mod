// makevfont.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileimage.h"
#include "vfontdata.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define TYPEFACE_NAME_MAX_LEN 32

bool CreateVFont(
	char *pOutFile,
	char *pFontName,
	int pointSize,
	double charRot,
	int fontWeight,
	bool bItalic,
	bool bUnderline,
	bool bStrikeout,
	bool bSmoothed,
	bool bPrintable)
{
	int rotTenths, charsStart;
	double rotRadians, rotSinNNeg, rotCosNNeg;
	HFONT hFont, hOldFont;
	int i;
	char theChar;
	SIZE charSize;
	int bitmapCharWidth, bitmapFontWidth, bitmapCharHeight;
	HDC hDC, hMemDC;
	bool bRet;
	RECT rc, rcChar;
	COLORREF TextColor, OldTextColor;
	int BkMode, OldBkMode;
	HBITMAP hBitmap, hOldBitmap;
	BITMAPINFOHEADER *pbmheader;
	BITMAPINFO tempbmi;
	BITMAPINFO *pbmi;
	unsigned char *bits;
	int nScans;
	FileImage fileImage;
	FILE *fp;

	rotTenths = (int)(charRot * 10.0);
	charsStart = bPrintable ? 32 : 0;
	rotRadians = charRot * M_PI / 180.0;
	rotSinNNeg = fabs(sin(rotRadians));
	rotCosNNeg = fabs(cos(rotRadians));

	hFont = hOldFont = NULL;
	hDC = hMemDC = NULL;
	TextColor = OldTextColor = 0x00FFFFFF;
	BkMode = OldBkMode = TRANSPARENT;
	hBitmap = hOldBitmap = NULL;
	pbmi = NULL;
	bRet = true;


	printf ( "Creating font \"%s\"...\n", pOutFile );

	// Make the font.
	hFont = CreateFont(
		pointSize, 
		0, 
		rotTenths, 
		rotTenths, 
		fontWeight, 
		bItalic, 
		bUnderline, 
		bStrikeout, 
		DEFAULT_CHARSET, 
		OUT_TT_PRECIS, 
		CLIP_DEFAULT_PRECIS | CLIP_LH_ANGLES, 
		PROOF_QUALITY, 
		VARIABLE_PITCH | FF_DONTCARE, 
		pFontName);
	
	if(!hFont)
	{
		printf("ERROR: CreateFont failed!\n");
		goto HANDLE_ERROR;
	}

	hDC		= GetDC(NULL);
	hMemDC	= CreateCompatibleDC(hDC);
	if(!hMemDC)
	{
		printf("ERROR: CreateCompatibleDC failed!\n");
		goto HANDLE_ERROR;
	}
	hOldFont = (HFONT)SelectObject(hMemDC, hFont);

		OldTextColor = SetTextColor(hMemDC, TextColor);
		OldBkMode = SetBkMode(hMemDC, BkMode);

		// Figure out the biggest character.
		bitmapCharWidth = bitmapCharHeight = 0;
		for(i = charsStart; i < NUM_VFONT_CHARS; i++)
		{
			theChar = (char)i;
			if(!GetTextExtentPoint32(hMemDC, &theChar, 1, &charSize))
			{
				printf("ERROR: GetTextExtentPoint32 failed!\n");
				goto HANDLE_ERROR;
			}

			if(charSize.cx > bitmapCharWidth)
				bitmapCharWidth = charSize.cx;

			if(charSize.cy > bitmapCharHeight)
				bitmapCharHeight = charSize.cy;
		}

		// Let's temporarily save the char width value here for the pending height calculation.
		bitmapFontWidth = bitmapCharWidth;

		bitmapCharWidth = (int)(bitmapCharWidth * rotCosNNeg + bitmapCharHeight * rotSinNNeg);
		bitmapCharHeight = (int)(bitmapFontWidth * rotSinNNeg + bitmapCharHeight * rotCosNNeg);
		
		// We get 1 pixel of padding because neighbours characters must not overlap each other.
		bitmapCharWidth++;

		bitmapFontWidth = bitmapCharWidth * NUM_VFONT_CHARS;

		// Now check if our bitmap font can be saved as a PCX/TGA file.
		if(bitmapCharHeight > USHRT_MAX || bitmapFontWidth > USHRT_MAX)
		{
			printf("ERROR: Bitmap is too large!\n");
			goto HANDLE_ERROR;
		}

		// Setup our bitmap.
		hBitmap	= CreateBitmap(bitmapFontWidth, bitmapCharHeight, 1, bSmoothed ? 32 : 1, NULL); 
		if(!hBitmap)
		{
			printf("ERROR: CreateBitmap failed!\n");
			goto HANDLE_ERROR;
		}
		hOldBitmap	= (HBITMAP)SelectObject(hMemDC, hBitmap);

		// Fill the background.
		rc.left = rc.top = 0;
		rc.right = bitmapFontWidth;
		rc.bottom = bitmapCharHeight;
		FillRect( hMemDC, &rc, (HBRUSH)GetStockObject( BLACK_BRUSH ) );

		// Draw characters in.
		for(i = charsStart; i < NUM_VFONT_CHARS; i++)
		{
			if(i != '\t')
			{
				// Draw the letter in the appropriate slot.
				rcChar.left = i * bitmapCharWidth + 1; // 1-pixel border for the padding
				rcChar.top = 0;
				rcChar.right = (i+1) * bitmapCharWidth;
				rcChar.bottom = bitmapCharHeight;
				theChar = (char)i;
				DrawText(hMemDC, &theChar, 1, &rcChar, DT_NOPREFIX | DT_LEFT | DT_NOCLIP);
			}
		}

		// Get the bits out.
		memset(&tempbmi, 0, sizeof(BITMAPINFO));
		pbmheader = ( BITMAPINFOHEADER * )&tempbmi;

		pbmheader->biSize	= sizeof( BITMAPINFOHEADER );
		pbmheader->biWidth	= bitmapFontWidth;
		pbmheader->biHeight	= -bitmapCharHeight; 
		pbmheader->biPlanes	= 1;
		pbmheader->biBitCount = 32;
		pbmheader->biCompression = BI_RGB;

		// Figure out how many bytes to allocate and setup a buffer.
		nScans = GetDIBits(hMemDC, hBitmap, 0, bitmapCharHeight, NULL, &tempbmi, DIB_RGB_COLORS);
		pbmi = ( BITMAPINFO * )malloc( sizeof ( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD ) + pbmheader->biSizeImage );
		memcpy( pbmi, &tempbmi, sizeof( BITMAPINFO ) );
		bits = ( unsigned char * )pbmi + sizeof( BITMAPINFOHEADER ) + 2 * sizeof( RGBQUAD );
		
		// Read the bits in.
		nScans = GetDIBits(hMemDC, hBitmap, 0, bitmapCharHeight, bits, pbmi, DIB_RGB_COLORS);
		if(nScans == 0)
		{
			printf("ERROR: GetDIBits failed!\n");
			goto HANDLE_ERROR;
		}
		
	
		// Save as a PCX/TGA file.
		fp = fopen(pOutFile, "wb");
		if(!fp)
		{
			printf("ERROR: fopen(\"%s\", \"wb\") failed!\n", pOutFile);
			goto HANDLE_ERROR;
		}

		fileImage.m_Width = bitmapFontWidth;
		fileImage.m_Height = bitmapCharHeight;
		fileImage.m_pData = (unsigned char*)bits;
		Save32BitTGA(fp, &fileImage);
		fileImage.Clear();
		
		fclose(fp);

		printf ( "Successfully completed.\n" );

	goto CLEANUP;


HANDLE_ERROR:;
	bRet = false;


CLEANUP:;
	if(hMemDC)
	{
		if(hOldBitmap)
			SelectObject(hMemDC, hOldBitmap);

		SetBkMode(hMemDC, OldBkMode);
		SetTextColor(hMemDC, OldTextColor);

		if(hOldFont)
			SelectObject(hMemDC, hOldFont);

		DeleteDC(hMemDC);
	}

	if(hBitmap)
	{
		DeleteObject(hBitmap);
	}

	if(hFont)
	{
		DeleteObject(hFont);
	}

	if(pbmi)
	{
		free(pbmi);
	}

	return true;
}

int main(int argc, char* argv[])
{
	char fontName[TYPEFACE_NAME_MAX_LEN];
	int pointSize, fontWeight;
	double charRot;
	bool bItalic, bUnderline, bStrikeout, bSmoothed, bPrintable;
	int i;


	// Setup defaults.
	strcpy(fontName, "Arial");
	pointSize = 0; // Using the system default font size (according to MSDN)
	fontWeight = FW_MEDIUM;
	charRot = 0.0;
	bItalic = bUnderline = bStrikeout = bSmoothed = bPrintable = false;


	printf("makevfont.exe version 1.2 (%s) by Valve & Vit_amiN\n", __DATE__ );


	// Read parameters in.
	for (i=1 ; i<argc ; i++)
	{
		if (!strcmp(argv[i],"-font"))
		{
			if (i >= argc - 1)
			{
				printf( "ERROR: No font name specified!\n" );
				return -1;
			}
			i++;
			strncpy( fontName, argv[i], TYPEFACE_NAME_MAX_LEN );
			fontName[TYPEFACE_NAME_MAX_LEN - 1] = '\0';
		}
		else if (!strcmp(argv[i],"-pointsize"))
		{
			if (i >= argc - 1)
			{
				printf( "ERROR: No point size specified!\n" );
				return -1;
			}
			i++;
			pointSize = atoi( argv[i] );
		}
		else if (!strcmp(argv[i],"-rotation"))
		{
			if (i >= argc - 1)
			{
				printf( "ERROR: No rotation angle specified!\n" );
				return -1;
			}
			i++;
			charRot = atof( argv[i] );
		}
		else if (!strcmp(argv[i],"-bold"))
		{
			fontWeight = FW_HEAVY;
		}
		else if (!strcmp(argv[i],"-weight"))
		{
			if (i >= argc - 1)
			{
				printf( "ERROR: No font weight specified!\n" );
				return -1;
			}
			i++;
			fontWeight = atoi( argv[i] );
		}
		else if (!strcmp(argv[i],"-italic"))
		{
			bItalic = true;
		}
		else if (!strcmp(argv[i],"-underline"))
		{
			bUnderline = true;
		}
		else if (!strcmp(argv[i],"-strikeout"))
		{
			bStrikeout = true;
		}
		else if (!strcmp(argv[i],"-smoothed"))
		{
			bSmoothed = true;
		}
		else if (!strcmp(argv[i],"-printable-only"))
		{
			bPrintable = true;
		}
		else if ( argv[i][0] == '-' )
		{
			printf("ERROR: Unknown option \"%s\"!\n", argv[i]);
			return -1;
		}
		else
			break;
	}

	if ( i != argc - 1 )
	{
		printf("\nCorrect usage:\nmakevfont [-font \"fontname\"] [-pointsize size] [-rotation deg] [-bold | -weight wt] [-italic] [-underline] [-strikeout] [-smoothed] [-printable-only] \"outfile\"\n");
		return -1;
	}

	CreateVFont(
		argv[argc-1],
		fontName,
		pointSize,
		charRot,
		fontWeight,
		bItalic,
		bUnderline,
		bStrikeout,
		bSmoothed,
		bPrintable);

	return 0;
}
