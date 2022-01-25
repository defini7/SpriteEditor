#include "cMain.h"
#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
	EVT_MENU(10001,	cMain::OnMenuNew)
	EVT_MENU(10002, cMain::OnMenuOpen)
	EVT_MENU(10003, cMain::OnMenuSave)
	EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "github.com/defini7 - Sprite Editor", wxPoint(30,30), wxSize(800, 600))
{
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	m_MenuBar->Append(menuFile, "File");

	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

	wxColour palette[16];
	palette[0] = wxColour(0, 0, 0);
	palette[1] = wxColour(0, 0, 128);
	palette[2] = wxColour(0, 128, 0);
	palette[3] = wxColour(0, 128, 128);
	palette[4] = wxColour(128, 0, 0);
	palette[5] = wxColour(128, 0, 128);
	palette[6] = wxColour(128, 128, 0);
	palette[7] = wxColour(192, 192, 192);
	palette[8] = wxColour(128, 128, 128);
	palette[9] = wxColour(0, 0, 255);
	palette[10] = wxColour(0, 255, 0);
	palette[11] = wxColour(0, 255, 255);
	palette[12] = wxColour(255, 0, 0);
	palette[13] = wxColour(255, 0, 255);
	palette[14] = wxColour(255, 255, 0);
	palette[15] = wxColour(255, 255, 255);

	for (int i = 0; i < 16; i++)
	{
		wxButton* colour_b = new wxButton(m_ToolBar, 10100 + i, "", wxDefaultPosition, wxSize(40, 24), 0);
		colour_b->SetBackgroundColour(palette[i]);
		colour_b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
		m_ToolBar->AddControl(colour_b);
	}

	wxButton* alpha_b = new wxButton(m_ToolBar, 10100 + 16, "ALPHA", wxDefaultPosition, wxDefaultSize, 0);
	alpha_b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
	
	m_ToolBar->AddControl(alpha_b);

	m_ToolBar->Realize();

}

cMain::~cMain()
{
	delete m_ToolBar;
}

void cMain::OnMenuNew(wxCommandEvent& evt)
{
	m_nSpriteWidth = wxGetNumberFromUser("Select a width of sprite", "", "Sprite options", m_nSpriteWidth, 1L, 100L, this, wxDefaultPosition);
	m_nSpriteHeight = wxGetNumberFromUser("Select a height of sprite", "", "Select height of sprite", m_nSpriteHeight, 1L, 100L, this, wxDefaultPosition);

	if (m_nSpriteWidth < 0 || m_nSpriteHeight < 0)
		m_nSpriteWidth = 16, m_nSpriteHeight = 16;

	cEditorFrame* f = new cEditorFrame(this, "Edit sprite");

	f->New(m_nSpriteWidth, m_nSpriteHeight);
	f->Show();

	evt.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	wxFileDialog dlg(this, "Open Sprite file", "", "", ".spr Files (*.spr)|.spr", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		cEditorFrame* f = new cEditorFrame(this, dlg.GetPath());
		f->Open(dlg.GetPath());
		f->Show();
	}
	evt.Skip();
}

void cMain::OnMenuSave(wxCommandEvent& evt)
{
	if (GetActiveChild() != nullptr)
	{
		wxFileDialog dlg(this, "Save Sprite file", "", "", ".spr Files (*spr)|*.spr", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK)
			((cEditorFrame*)GetActiveChild())->Save(dlg.GetPath());
	}
}

void cMain::OnMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void cMain::OnSelectColour(wxCommandEvent& evt)
{
	int colour = evt.GetId() - 10100;

	if (GetActiveChild() != nullptr)
		((cEditorFrame*)GetActiveChild())->SetColour(colour);
}
