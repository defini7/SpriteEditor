#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
	EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()

cEditorFrame::cEditorFrame(wxMDIParentFrame* parent, wxString sName) : wxMDIChildFrame(parent, wxID_ANY, sName)
{
	m_Canvas = new cCanvas(this);

	m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32);
}

cEditorFrame::~cEditorFrame()
{
	delete[] m_pSprite;
	delete m_StatusBar;
}

void cEditorFrame::SetColour(int c)
{
	m_Canvas->m_nColour = c;
}

bool cEditorFrame::Save(wxString sFileName)
{
	for (int i = 0; i < spr.nWidth; i++)
		for (int j = 0; j < spr.nHeight; j++)
		{
			short colour = m_pSprite[j * spr.nHeight + i];

			if (colour == 16)
			{
				spr.SetColour(i, j, 0);
				spr.SetGlyph(i, j, L' ');
			}
			else
			{
				spr.SetColour(i, j, colour);
				spr.SetGlyph(i, j, 0x2588);
			}
		}

	return spr.Save(sFileName.wc_str());
}

bool cEditorFrame::Open(wxString sFileName)
{
	if(!spr.Load(sFileName.wc_str()))
		return false;
	else
	{
		delete[] m_pSprite;
		m_pSprite = new unsigned char[spr.nWidth * spr.nHeight]{ 0 };

		for (int i = 0; i < spr.nWidth; i++)
			for (int j = 0; j < spr.nHeight; j++)
			{
				wchar_t glyph = spr.GetGlyph(i, j);
				short colour = spr.GetColour(i, j);

				if (glyph == L' ')
					m_pSprite[j * spr.nWidth + i] = 16;
				else
					m_pSprite[j * spr.nWidth + i] = colour & 0x000F;
			}

		m_Canvas->SetSpriteData(spr.nHeight, spr.nWidth, m_pSprite);
		return true;
	}
}

bool cEditorFrame::New(int r, int c)
{
	delete[] m_pSprite;

	m_pSprite = new unsigned char[r * c]{ 0 };
	m_Canvas->SetSpriteData(r, c, m_pSprite);

	spr = Sprite(c, r);

	return false;
}

void cEditorFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
	m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());
	evt.Skip();
}
