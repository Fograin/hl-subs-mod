// ======================================
// Ingame message using custom font
// Written by: Fograin92
// Based on: Subtitles code by Buzzer
// ======================================

#ifndef _INGAMEMSG_H
#define _INGAMEMSG_H
using namespace vgui;

class CIngameMSGTextPanel : public TextPanel
{
public:
	CIngameMSGTextPanel(const char* text,int x,int y,int wide,int tall) : TextPanel(text, x, y, wide, tall)
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


class CIngameMSG : public Panel
{
public:
    CIngameMSG();
	void AddMessage( client_textmessage_t *tempMessage );
	void Initialize();
	
	
protected:
	virtual void paintBackground();

//protected:
public: // hacks..
	Panel *m_pLayer;
	CIngameMSGTextPanel *m_pCur;
	CIngameMSGTextPanel *m_pWait;


	float layerpos; // float version of layer's y-coordinate
	float lasttime;
	float m_fCurStartTime;
};

void CIngameMSGMessageAdd( client_textmessage_t *tempMessage );
void IngameMSGInit();

#endif // _INGAMEMSG_H