#pragma once
#include "wx/wx.h"
#include "wx/richtext/richtextxml.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	
	virtual bool OnInit();

private:
	cMain* m_frame1 = nullptr;
};

