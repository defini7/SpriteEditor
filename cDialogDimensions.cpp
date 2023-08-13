#include "cDialogDimensions.h"

cDialogDimensions::cDialogDimensions(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "New Sprite")
{
	m_lblWidth = new wxStaticText(this, wxID_ANY, "Enter Width");
	m_txtWidth = new wxTextCtrl(this, wxID_ANY, "");
	m_lblHeight = new wxStaticText(this, wxID_ANY, "Enter Height");
	m_txtHeight = new wxTextCtrl(this, wxID_ANY, "");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->AddSpacer(5);
	sizer->Add(m_lblWidth, 0, wxSTRETCH_NOT | wxRIGHT | wxALIGN_CENTER);

	sizer->AddSpacer(5);
	sizer->Add(m_txtWidth, 0, wxSTRETCH_NOT | wxRIGHT | wxALIGN_CENTER);

	sizer->AddSpacer(5);
	sizer->Add(m_lblHeight, 0, wxSTRETCH_NOT | wxRIGHT | wxALIGN_CENTER);

	sizer->AddSpacer(5);
	sizer->Add(m_txtHeight, 0, wxSTRETCH_NOT | wxRIGHT | wxALIGN_CENTER);

	sizer->AddSpacer(5);
	sizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxRIGHT);

	sizer->AddSpacer(5);
	this->SetSizerAndFit(sizer);
}

cDialogDimensions::~cDialogDimensions()
{
	this->Close();
}

int cDialogDimensions::GetSpriteWidth()
{
	int nWidth;

	if (!m_txtWidth->GetValue().ToInt(&nWidth))
		nWidth = 16;

	return (nWidth > 0) ? nWidth : 16;
}

int cDialogDimensions::GetSpriteHeight()
{
	int nHeight;

	if (!m_txtHeight->GetValue().ToInt(&nHeight))
		nHeight = 16;

	return (nHeight > 0) ? nHeight : 16;
}
