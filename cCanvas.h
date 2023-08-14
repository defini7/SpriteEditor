#pragma once

#include "wx/wx.h"
#include "wx/vscroll.h"

class cCanvas : public wxHVScrolledWindow
{
public:
	cCanvas(wxWindow *parent);
	virtual ~cCanvas();

private:
	int m_nPixelSize = 8;
	unsigned char* m_pSprite = nullptr;
	wxColour m_palette[16];

public:
	void SetPixelSize(int n);
	void SetSpriteData(int rows, int columns, unsigned char* pSprite);
	void SetColour(int c);

	int m_nColour = 0;

private:

	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	void OnMouseLeftDown(wxMouseEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

