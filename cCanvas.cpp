#include "cCanvas.h"

#include "wx/dcmemory.h"
#include "wx/dcclient.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(cCanvas, wxHVScrolledWindow)
	EVT_PAINT(cCanvas::OnPaint)
	EVT_LEFT_DOWN(cCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

cCanvas::cCanvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
	SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_palette[0] = wxColour(0, 0, 0);
	m_palette[1] = wxColour(0, 0, 128);
	m_palette[2] = wxColour(0, 128, 0);
	m_palette[3] = wxColour(0, 128, 128);
	m_palette[4] = wxColour(128, 0, 0);
	m_palette[5] = wxColour(128, 0, 128);
	m_palette[6] = wxColour(128, 128, 0);
	m_palette[7] = wxColour(192, 192, 192);
	m_palette[8] = wxColour(128, 128, 128);
	m_palette[9] = wxColour(0, 0, 255);
	m_palette[10] = wxColour(0, 255, 0);
	m_palette[11] = wxColour(0, 255, 255);
	m_palette[12] = wxColour(255, 0, 0);
	m_palette[13] = wxColour(255, 0, 255);
	m_palette[14] = wxColour(255, 255, 0);
	m_palette[15] = wxColour(255, 255, 255);
}

cCanvas::~cCanvas()
{
}

void cCanvas::SetPixelSize(int n)
{
	m_nPixelSize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh();
}

void cCanvas::SetSpriteData(int rows, int columns, unsigned char* pSprite)
{
	m_pSprite = pSprite;
	this->SetRowColumnCount(rows, columns);
}

void cCanvas::SetColour(int c)
{
	m_nColour = c;
}

wxCoord cCanvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(m_nPixelSize);
}

wxCoord cCanvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(m_nPixelSize);
}

void cCanvas::OnDraw(wxDC& dc)
{
	dc.Clear();

	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	wxPosition s = GetVisibleBegin();
	wxPosition e = GetVisibleEnd();

	pen.SetStyle(wxPENSTYLE_LONG_DASH);
	pen.SetColour(wxColour(200, 200, 200));
	dc.SetPen(pen);

	for (int x = s.GetCol(); x < e.GetCol(); x++)
		for (int y = s.GetRow(); y < e.GetRow(); y++)
		{
			int colour = m_pSprite[y * this->GetColumnCount() + x];

			if (colour < 16)
			{
				brush.SetColour(m_palette[colour]);
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else
			{
				brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
				brush.SetColour(wxColour(0, 0, 0));
			}

			dc.SetBrush(brush);
			dc.DrawRectangle(x * m_nPixelSize, y * m_nPixelSize, m_nPixelSize, m_nPixelSize);
		}

	dc.SetBrush(brush);
}

void cCanvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

void cCanvas::OnMouseLeftDown(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();
	m_pSprite[(evt.GetY() / m_nPixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / m_nPixelSize + s.GetCol())] = m_nColour;
	this->Refresh(false);
	evt.Skip();
}
