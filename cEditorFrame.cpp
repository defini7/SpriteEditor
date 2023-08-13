#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
	EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()

cEditorFrame::cEditorFrame(wxMDIParentFrame* parent, const wxString& sName) : wxMDIChildFrame(parent, wxID_ANY, sName)
{
	m_Canvas = new cCanvas(this);

	m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32);
}

cEditorFrame::~cEditorFrame()
{
	delete[] m_pSprite;
	delete m_sprData;
}

void cEditorFrame::SetColour(int c)
{
	m_Canvas->m_nColour = c;
}

bool cEditorFrame::Save(const wxString& sFileName)
{
	for (int i = 0; i < m_sprData->nWidth; i++)
		for (int j = 0; j < m_sprData->nHeight; j++)
		{
			short colour = m_pSprite[j * m_sprData->nHeight + i];

			if (colour == 16)
			{
				m_sprData->SetColour(i, j, 0);
				m_sprData->SetGlyph(i, j, L' ');
			}
			else
			{
				m_sprData->SetColour(i, j, colour);
				m_sprData->SetGlyph(i, j, 0x2588);
			}
		}

	return m_sprData->Save(sFileName.wc_str());
}

bool cEditorFrame::Open(const wxString& sFileName)
{
	m_sprData = new Sprite();

	if (m_sprData->Load(sFileName.wc_str()))
	{
		delete[] m_pSprite;
		m_pSprite = new unsigned char[m_sprData->nWidth * m_sprData->nHeight]{ 0 };

		for (int i = 0; i < m_sprData->nWidth; i++)
			for (int j = 0; j < m_sprData->nHeight; j++)
			{
				short glyph = m_sprData->GetGlyph(i, j);
				short colour = m_sprData->GetColour(i, j);

				m_pSprite[j * m_sprData->nWidth + i] = (glyph == L' ') ? 16 : colour & 0x000F;
			}

		m_Canvas->SetSpriteData(m_sprData->nHeight, m_sprData->nWidth, m_pSprite);

		return true;
	}

	return false;
}

bool cEditorFrame::New(int r, int c)
{
	delete[] m_pSprite;

	m_pSprite = new unsigned char[r * c]{ 0 };
	m_Canvas->SetSpriteData(r, c, m_pSprite);

	m_sprData = new Sprite(c, r);

	return true;
}

void cEditorFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
	m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());
	evt.Skip();
}
