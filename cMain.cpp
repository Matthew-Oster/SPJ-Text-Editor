#include "cMain.h"
#include "wx/file.h"
#include "wx/dir.h"
#include "wx/filefn.h"
#include "wx/wfstream.h"
#include <iostream>
#include <string>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_MENU(ID_Hello, OnMenuHello)
	EVT_MENU(wxID_EXIT, OnMenuExit)
	EVT_MENU(wxID_ABOUT, OnMenuAbout)
	EVT_MENU(wxID_COPY, OnMenuCopy)
	EVT_MENU(wxID_CUT, OnMenuCut)
	EVT_MENU(wxID_PASTE, OnMenuPaste)
	EVT_MENU(wxID_SAVE, OnSave)
	EVT_MENU(wxID_SAVEAS, OnSaveAs)
	EVT_MENU(wxID_OPEN, OnOpen)
	EVT_BUTTON(wxID_BOLD, OnBold)
	EVT_BUTTON(wxID_ITALIC, OnItalic)
	EVT_BUTTON(wxID_UNDERLINE, OnUnderline)
	EVT_CHOICE(wxID_SELECT_FONT, OnFontChange)
	EVT_CHOICE(ID_SELECT_SIZE, OnSizeChange)
	EVT_CHOICE(wxID_SELECT_COLOR, OnColourChange)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SPJ's Text Editor", wxPoint(30, 30), wxSize(1000, 800)) {

	m_txt1 = new wxRichTextCtrl(this, wxID_ANY, "", wxPoint(220, 10), wxSize(800, 600), wxTE_MULTILINE | wxTE_LEFT | wxTE_RICH2);

	for (int i = 0; i < 2; i++) toolBarButtons[i] = nullptr;

	setupMenuBar();
	SetMenuBar(menuBar);

	CreateStatusBar();
	setupToolBar();

	wxRichTextAttr newDefault;
	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);
	wxFont newFont(8, wxFONTFAMILY_DEFAULT, newDefault.GetFontStyle(),
		newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Arial");
	m_txt1->SetFont(newFont);

	wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);
	boxSizer->Add(m_txt1, 1, wxEXPAND | wxALL);
	boxSizer->SetSizeHints(this);
	SetSizer(boxSizer);
	
}

cMain::~cMain() {
}


void cMain::OnMenuHello(wxCommandEvent& evt) {
	wxLogMessage("Hello World!");
}

void cMain::OnMenuExit(wxCommandEvent& evt) {
	Close(true);
	evt.Skip();
}

void cMain::OnMenuAbout(wxCommandEvent& evt) {
	wxMessageBox("Welcome to SPJ's Text Editor! Its kinda barebones at the moment.", "About SPJ's Text Editor", wxOK | wxICON_INFORMATION);
}

void cMain::OnMenuCopy(wxCommandEvent& evt) {
	m_txt1->Copy();
}

void cMain::OnMenuCut(wxCommandEvent& evt) {
	m_txt1->Cut();
}

void cMain::OnMenuPaste(wxCommandEvent& evt) {
	m_txt1->Paste();
}

void cMain::OnBold(wxCommandEvent& evt){
	
	m_txt1->SetFocus();

	wxRichTextAttr newDefault;
	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);
	//setupTextAttr(newDefault);

	if ((newDefault.GetFontWeight() & wxFONTWEIGHT_BOLD) != wxFONTWEIGHT_BOLD)
		newDefault.SetFontWeight(wxFONTWEIGHT_BOLD);
	else newDefault.SetFontWeight(wxFONTWEIGHT_NORMAL);

	m_txt1->SetDefaultStyle(newDefault);
	m_txt1->ApplyBoldToSelection();
}

void cMain::OnItalic(wxCommandEvent& evt){

	m_txt1->SetFocus();

	wxRichTextAttr newDefault;
	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);

	if ((newDefault.GetFontStyle() & wxFONTSTYLE_ITALIC) != wxFONTSTYLE_ITALIC) 
		newDefault.SetFontStyle(wxFONTSTYLE_ITALIC);
	else newDefault.SetFontStyle(wxFONTSTYLE_NORMAL);

	m_txt1->SetDefaultStyle(newDefault);
	m_txt1->ApplyItalicToSelection();
}

void cMain::OnUnderline(wxCommandEvent& evt){

	m_txt1->SetFocus();

	wxRichTextAttr newDefault;
	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);

	if (!newDefault.GetFontUnderlined()) newDefault.SetFontUnderlined(true);
	else newDefault.SetFontUnderlined(false);

	m_txt1->SetDefaultStyle(newDefault);
	m_txt1->ApplyUnderlineToSelection();

}

void cMain::OnFontChange(wxCommandEvent& evt)
{
	m_txt1->SetFocus();

	int choice = fontChoice->GetSelection();
	wxRichTextAttr newDefault;

	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);

	switch (choice) {
	case 1:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_DEFAULT, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Arial");
		newDefault.SetFont(newFont);
		break;
	}
	case 2:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_DECORATIVE, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Garamond");
		newDefault.SetFont(newFont);
		break;
	}
	case 3:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_ROMAN, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Times New Roman");
		newDefault.SetFont(newFont);
		break;
	}
	case 4:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_SCRIPT, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Coronet");
		newDefault.SetFont(newFont);
		break;
	}
	case 5:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_SWISS, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Helvetica");
		newDefault.SetFont(newFont);
		break;
	}
	case 6:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_MODERN, newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Courier");
		newDefault.SetFont(newFont);
		break;
	}
	case 7:
	{
		wxFont newFont(newDefault.GetFontSize(), wxFONTFAMILY_TELETYPE, newDefault.GetFontStyle(), 
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), "Consolas");
		newDefault.SetFont(newFont);
		break;
	}
	default:
	{
		return;
	}
	}

	m_txt1->SetDefaultStyle(newDefault);
}

void cMain::OnSizeChange(wxCommandEvent& evt)
{
	m_txt1->SetFocus();
	
	int choice = fontSize->GetSelection();
	wxRichTextAttr newDefault;

	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);

	switch (choice) {
	case 1:
	{
		wxFont newFont(2, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 2:
	{
		wxFont newFont(4, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 3:
	{
		wxFont newFont(8, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 4:
	{
		wxFont newFont(16, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 5:
	{
		wxFont newFont(32, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 6:
	{
		wxFont newFont(48, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	case 7:
	{
		wxFont newFont(64, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetFontSize(newFont.GetPointSize());
		break;
	}
	default:
	{
		return;
	}
	}
	m_txt1->SetDefaultStyle(newDefault);
}

void cMain::OnColourChange(wxCommandEvent& evt)
{
	m_txt1->SetFocus();

	int choice = colourChoice->GetSelection();

	wxRichTextAttr newDefault;
	m_txt1->GetStyle(m_txt1->GetInsertionPoint(), newDefault);
	
	switch (choice) {
	case 1:
	{
		wxFont newFont(2, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxBLACK);
		break;
	}
	case 2:
	{
		wxFont newFont(4, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxBLUE);
		break;
	}
	case 3:
	{
		wxFont newFont(8, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxCYAN);
		break;
	}
	case 4:
	{
		wxFont newFont(16, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxGREEN);
		break;
	}
	case 5:
	{
		wxFont newFont(32, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxYELLOW);
		break;
	}
	case 6:
	{
		wxFont newFont(48, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxLIGHT_GREY);
		break;
	}
	case 7:
	{
		wxFont newFont(64, newDefault.GetFontFamily(), newDefault.GetFontStyle(),
			newDefault.GetFontWeight(), newDefault.GetFontUnderlined(), newDefault.GetFontFaceName());
		newDefault.SetTextColour(*wxRED);
		break;
	}
	default:
	{
		return;
	}
	}

	m_txt1->SetDefaultStyle(newDefault);
	
}

void cMain::OnSave(wxCommandEvent& evt)
{
	if (filename == "")
		OnSaveAs(evt); //file needs a name
	else
		m_txt1->SaveFile(filename);
}

void cMain::OnSaveAs(wxCommandEvent& evt) {

	wxFileDialog dlg(this, "Save .xml file", "", "", "XML files (*.xml) | *.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (dlg.ShowModal() == wxID_CANCEL)
		return; //user cancelled operation

	filename = dlg.GetFilename();
	m_txt1->SaveFile(filename, wxRICHTEXT_TYPE_XML);
}

void cMain::OnOpen(wxCommandEvent& evt)
{

	wxFileDialog dlg(this, "Open .txt file", "", "", "XML files (*.xml) | *.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() == wxID_CANCEL)
		return; //user cancelled operation

	filename = dlg.GetFilename();
	m_txt1->LoadFile(filename, wxRICHTEXT_TYPE_XML);

}

void cMain::setupMenuBar()
{
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello!\tCtrl-H", "Welcome to SPJ's Text Editor!");
	menuFile->AppendSeparator();
	//Save, Load ect.
	menuFile->Append(wxID_SAVE);
	menuFile->Append(wxID_SAVEAS);
	menuFile->Append(wxID_OPEN);
	menuFile->Append(wxID_EXIT);

	wxMenu* menuEdit = new wxMenu;
	menuEdit->Append(wxID_COPY);
	menuEdit->Append(wxID_CUT);
	menuEdit->Append(wxID_PASTE);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");

	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuHelp, "&Help");
}


void cMain::setupToolBar() {
	toolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY | wxTB_TEXT);

	toolBarButtons[0] = new wxButton(toolBar, wxID_BOLD, "Bold", wxDefaultPosition, wxSize(40, 24), 0);
	toolBar->InsertControl(0, toolBarButtons[0], "bold");

	toolBarButtons[1] = new wxButton(toolBar, wxID_ITALIC, "Italic", wxDefaultPosition, wxSize(40, 24), 0);
	toolBar->InsertControl(1, toolBarButtons[1], "italic");

	toolBarButtons[2] = new wxButton(toolBar, wxID_UNDERLINE, "Underline", wxDefaultPosition, wxSize(60, 24), 0);
	toolBar->InsertControl(2, toolBarButtons[2], "underline");

	// Add font choices into a string array to pass to wxChoice constructor
	wxString fonts[8] = {"Font Choice", "Arial", "Garamond", "Times New Roman", "Coronet", "Helvetica", "Courier", "Consolas"}; 
	wxArrayString fontArr;
	
	for (int i = 0; i < 8; i++)
		fontArr.Add(fonts[i]);

	fontChoice = new wxChoice(toolBar, wxID_SELECT_FONT, wxDefaultPosition, wxSize(110, 24), fontArr, 0, wxDefaultValidator, "Font");
	
	for (int i = 0; i < 8; i++)
		fontChoice->SetString(i, fonts[i]);

	fontChoice->SetSelection(0);
	toolBar->InsertControl(3, fontChoice, "font");
	toolBar->InsertSeparator(3);

	// Add font sizes into a string array to pass to wxChoice constructor
	wxString sizes[8] = { "Font Size", "2pt", "4pt", "8pt", "16pt", "32pt", "48pt", "64pt" };
	wxArrayString sizeArr;

	for (int i = 0; i < 8; i++)
		sizeArr.Add(sizes[i]);

	fontSize = new wxChoice(toolBar, ID_SELECT_SIZE, wxDefaultPosition, wxSize(110, 24), sizeArr, 0, wxDefaultValidator, "Size");
	
	for (int i = 0; i < 8; i++)
		fontSize->SetString(i, sizes[i]);

	fontSize->SetSelection(0);
	toolBar->InsertControl(4, fontSize, "size");

	wxString colors[8] = { "Color", "Black", "Blue", "Cyan", "Green", "Yellow", "Light Grey", "Red" };
	wxArrayString colorArr;

	for (int i = 0; i < 8; i++)
		colorArr.Add(colors[i]);

	colourChoice = new wxChoice(toolBar, wxID_SELECT_COLOR, wxDefaultPosition, wxSize(60, 24), colorArr, 0, wxDefaultValidator, "Color");
	colourChoice->SetSelection(0);
	toolBar->InsertControl(6, colourChoice, "color");

	toolBar->Realize();
}