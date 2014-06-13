// ======================================
// Ingame message using custom font
// Written by: Fograin92
// Based on: Subtitles code by Buzzer
// ======================================

#ifndef _INCREDS_H
#define _INCREDS_H
using namespace vgui;

class CCreditsMSGTextPanel : public TextPanel
{
public:
	CCreditsMSGTextPanel(const char* text,int x,int y,int wide,int tall) : TextPanel(text, x, y, wide, tall)
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


class CCreditsMSG : public Panel
{
public:
    CCreditsMSG();
	void AddMessage( client_textmessage_t *tempMessage );
	void Initialize();
	
	
protected:
	virtual void paintBackground();

//protected:
public: // hacks..
	Panel *m_pLayer;
	CCreditsMSGTextPanel *m_pCur;
	CCreditsMSGTextPanel *m_pWait;


	float layerpos; // float version of layer's y-coordinate
	float lasttime;
	float m_fCurStartTime;
};

void CCreditsMSGMessageAdd( client_textmessage_t *tempMessage );
void CCreditsMSGInit();

#endif // _INCREDS_H