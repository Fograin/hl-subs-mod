// ==================================================
// Ingame message using custom font
// $effect 4 = ID for "Saved..." message
// Written by: Fograin92
// Based on: Subtitles code by Buzzer
// ==================================================

#include "hud.h"
#include "cl_util.h"
#include "const.h"
#include "entity_types.h"
#include "cdll_int.h"
#include "vgui_TeamFortressViewport.h"
#include "vgui_MSG_Saved.h"
#include "VGUI_TextImage.h"

cvar_t *SavedMSG_enabled;

Font* FontFromMessageY(const char* &ptext)
{
	char fontname[64] = "Default Text";
	if (ptext != NULL && ptext[0] != 0)
	{
		if (ptext[0] == '@')
		{
			// get font name
			ptext++;
			ptext = gEngfuncs.COM_ParseFile((char*)ptext, fontname);
			ptext+=2;
		}
	}

	CSchemeManager *pSchemes = gViewPort->GetSchemeManager();
	SchemeHandle_t hTextScheme = pSchemes->getSchemeHandle( fontname );
	return pSchemes->getFont( hTextScheme );
}


void CSavedMSGMessageAdd( client_textmessage_t *tempMessage )
{
	if (!SavedMSG_enabled->value)
		return;

	if (gViewPort && gViewPort->m_pSavedMSG)
	{
		gViewPort->m_pSavedMSG->AddMessage( tempMessage );
	}
	else
		gEngfuncs.Con_Printf("Subtitle error: CSavedMSG or ViewPort is not constructed!\n");
}

void CSavedMSGInit()
{
	SavedMSG_enabled = gEngfuncs.pfnRegisterVariable( "MSG_Saved", "1", 0 );
}

void CSavedMSGTextPanel::paintBackground()
{
	float fade = 0.2;
	float time = gEngfuncs.GetClientTime();

	int r, g, b, a;
	getFgColor(r, g, b ,a);

	if (m_fBirthTime && (m_fBirthTime + fade > time))
	{
		float alpha = (time - m_fBirthTime) / fade;
		setFgColor( r, g, b, 255 - (alpha * 255));
		return;
	}

	if (gViewPort && gViewPort->m_pSavedMSG) // hm..
	{
		if (gViewPort->m_pSavedMSG->m_pCur == this)
		{
			float dietime = gViewPort->m_pSavedMSG->m_fCurStartTime + m_fHoldTime;
			if (dietime - fade < time)
			{
				float alpha = (dietime - time) / fade;
				setFgColor( r, g, b, 255 - (alpha * 255));
				return;
			}
		}
	}

	setFgColor( r, g, b, 0 );
}

void CSavedMSGTextPanel::paint()
{
	int mr, mg, mb, ma;
	int ix, iy;
	getFgColor(mr, mg, mb, ma);
	getTextImage()->getPos(ix, iy);
	getTextImage()->setPos(ix+1, iy+1);
	getTextImage()->setColor( Color(0, 0, 0, ma) );
	getTextImage()->doPaint(this);
	getTextImage()->setPos(ix, iy);
	getTextImage()->setColor( Color(mr, mg, mb, ma) );
	getTextImage()->doPaint(this);
}

CSavedMSG::CSavedMSG() : Panel(XRES(5), YRES(5), XRES(630), YRES(470))
{	
	m_pLayer = new Panel;
	m_pLayer->setParent(this);
	m_pLayer->setPaintBackgroundEnabled(false); // Disable layer background
	setVisible(false);
	m_pCur = NULL;
	m_pWait = NULL;
	lasttime = 0;
	layerpos = 0;
}

void CSavedMSG::Initialize()
{
	m_pLayer->removeAllChildren();
	setVisible(false);
	m_pCur = NULL;
	m_pWait = NULL;
	lasttime = 0;
	layerpos = 0;
}

void CSavedMSG::AddMessage( client_textmessage_t *msg )
{
	Initialize(); // Fograin92: We say "GTFO" to the last message

	float time = gEngfuncs.GetClientTime();
	float holdtime = msg->holdtime;	
	const char *pText = msg->pMessage;
	client_textmessage_t *postMsg = NULL;
	Font *pFont = FontFromMessageY(pText);

	// Fograin92: Give us enough place to render shit
	m_pLayer->setSize(ScreenWidth-msg->x, ScreenHeight-msg->y);

	int new_X, new_Y;
	CSavedMSGTextPanel *text = new CSavedMSGTextPanel(pText, msg->x, msg->y, ScreenWidth-msg->x, ScreenHeight-msg->y );
	text->setParent( m_pLayer );
	text->setFont(pFont);
	text->msgAfterDeath = postMsg;
	text->setFgColor(msg->r1, msg->g1, msg->b1, 0);
	text->m_fHoldTime = holdtime;

	new_X = 0;
	new_Y = 0;
	text->getTextImage()->getTextSize( new_X, new_Y );	// Fograin92: We need this to get correct position from titles.txt

	// Fix the X position
	if(msg->x == -1)
		new_X =  (ScreenWidth - new_X) / 2;
	else
	{
		if ( msg->x < 0 )
			new_X = (1.0 + msg->x) * ScreenWidth - new_X;
		else 
			new_X = msg->x * ScreenWidth;
	}

	if ( new_X + new_X > ScreenWidth )
		new_X = ScreenWidth - new_X;
	else if ( new_X < 0 )
		new_X = 0;

	// Fix the Y position
	if(msg->y == -1)
		new_Y =  (ScreenHeight - new_Y) / 2;  
	else
	{
		// Alight bottom?
		if ( msg->y < 0 )
			new_Y = (1.0 + msg->y) * ScreenHeight - new_Y;	// Alight bottom
		else // align top
			new_Y = msg->y * ScreenHeight;
	}

	if ( new_Y + new_Y > ScreenHeight )
		new_Y = ScreenHeight - new_Y;
	else if ( new_Y < 0 )
		new_Y = 0;

	m_pLayer->setPos(new_X, new_Y);

	text->m_fBirthTime = time;
	m_fCurStartTime = time;
	m_pCur = text;
	m_pWait = NULL;
	text->setVisible(true);
	setVisible(true);
}

void CSavedMSG::paintBackground()
{	
	float curtime = gEngfuncs.GetClientTime();
	if (lasttime == 0) lasttime = curtime;
	float deltatime = curtime - lasttime;

	if (!SavedMSG_enabled->value)
	{
		Initialize();
		return;
	}

	// GTFO from the screen
	if (m_fCurStartTime + m_pCur->m_fHoldTime <= curtime)
	{
		Initialize();
		return;
	}
}