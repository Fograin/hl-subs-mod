// ======================================
// Ingame message using custom font
// Written by: Fograin92
// Based on: Subtitles code by Buzzer
// ======================================

#ifndef _INSAVED_H
#define _INSAVED_H
using namespace vgui;

class CSavedMSGTextPanel : public TextPanel
{
public:
	CSavedMSGTextPanel(const char* text,int x,int y,int wide,int tall) : TextPanel(text, x, y, wide, tall)
	{
		m_fBirthTime = 0;
		m_fHoldTime = 0;
		msgAfterDeath = NULL;
	}

	virtual void paintBackground();
	virtual void paint();

	float m_fBirthTime;
	float m_fHoldTime;
//	int bkalpha;
	client_textmessage_t *msgAfterDeath;
};


class CSavedMSG : public Panel
{
public:
    CSavedMSG();
	void AddMessage( client_textmessage_t *tempMessage );
	void Initialize();
	
	
protected:
	virtual void paintBackground();

//protected:
public: // hacks..
	Panel *m_pLayer;
	CSavedMSGTextPanel *m_pCur;
	CSavedMSGTextPanel *m_pWait;


	float layerpos; // float version of layer's y-coordinate
	float lasttime;
	float m_fCurStartTime;
};

void CSavedMSGMessageAdd( client_textmessage_t *tempMessage );
void CSavedMSGInit();

#endif // _INSAVED_H