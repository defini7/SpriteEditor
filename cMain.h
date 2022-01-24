#pragma once

#include "wx/wx.h"
#include "wx/numdlg.h"

class cMain : public wxMDIParentFrame
{
public:
	cMain();
	~cMain();

	void OnSelectColour(wxCommandEvent& evt);

private:
	wxToolBar* m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);

	long lSpriteWidth = -1, lSpriteHeight = -1;

	wxDECLARE_EVENT_TABLE();
};

