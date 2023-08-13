#pragma once

#include "wx/wx.h"

class cDialogDimensions : public wxDialog
{
public:
	cDialogDimensions(wxWindow* parent);
	~cDialogDimensions();

	int GetSpriteWidth();
	int GetSpriteHeight();

private:
	wxStaticText* m_lblWidth;
	wxTextCtrl* m_txtWidth;
	wxStaticText* m_lblHeight;
	wxTextCtrl* m_txtHeight;

};

