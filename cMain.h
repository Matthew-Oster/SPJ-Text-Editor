#pragma once
#include "wx/wx.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/gdicmn.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	void OnMenuHello(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);
	void OnMenuAbout(wxCommandEvent& evt);

	void OnMenuCopy(wxCommandEvent& evt);
	void OnMenuCut(wxCommandEvent& evt);
	void OnMenuPaste(wxCommandEvent& evt);

	void OnBold(wxCommandEvent& evt);
	void OnItalic(wxCommandEvent& evt);
	void OnUnderline(wxCommandEvent& evt);
	void OnFontChange(wxCommandEvent& evt);
	void OnSizeChange(wxCommandEvent& evt);
	void OnColourChange(wxCommandEvent& evt);

	void OnSave(wxCommandEvent& evt);
	void OnSaveAs(wxCommandEvent& evt);
	void OnOpen(wxCommandEvent& evt);

	void SetControlDisplayValues(wxCommandEvent& evt);

public:	
	wxRichTextCtrl* m_txt1 = nullptr;

	wxMenuBar* menuBar = nullptr;
	wxToolBar* toolBar = nullptr;
	wxButton* toolBarButtons[3];
	wxChoice* fontChoice = nullptr;
	wxChoice* fontSize = nullptr;
	wxChoice* colourChoice = nullptr;

	wxString filename = "";

	wxDECLARE_EVENT_TABLE();

private:
	void setupMenuBar();
	void setupToolBar();

};

enum {
	ID_Hello = 1,
	ID_SELECT_SIZE = 2,
	ID_RT = 3
};

