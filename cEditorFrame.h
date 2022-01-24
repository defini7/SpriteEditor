#pragma once
#include "wx/wx.h"
#include "cCanvas.h"

class Sprite
{
public:
	Sprite()
	{

	}

	Sprite(int w, int h)
	{
		Create(w, h);
	}

	Sprite(std::wstring sFile)
	{
		if (!Load(sFile))
			Create(8, 8);
	}

	int nWidth = 0;
	int nHeight = 0;

private:
	short* m_Glyphs = nullptr;
	short* m_Colours = nullptr;

	void Create(int w, int h)
	{
		nWidth = w;
		nHeight = h;
		m_Glyphs = new short[w * h];
		m_Colours = new short[w * h];
		for (int i = 0; i < w * h; i++)
		{
			m_Glyphs[i] = L' ';
			m_Colours[i] = 0;
		}
	}

public:
	void SetGlyph(int x, int y, short c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Glyphs[y * nWidth + x] = c;
	}

	void SetColour(int x, int y, short c)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return;
		else
			m_Colours[y * nWidth + x] = c;
	}

	short GetGlyph(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return L' ';
		else
			return m_Glyphs[y * nWidth + x];
	}

	short GetColour(int x, int y)
	{
		if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
			return 0;
		else
			return m_Colours[y * nWidth + x];
	}

	short SampleGlyph(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);
		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return L' ';
		else
			return m_Glyphs[sy * nWidth + sx];
	}

	short SampleColour(float x, float y)
	{
		int sx = (int)(x * (float)nWidth);
		int sy = (int)(y * (float)nHeight - 1.0f);
		if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
			return 0;
		else
			return m_Colours[sy * nWidth + sx];
	}

	bool Save(std::wstring sFile)
	{
		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"wb");
		if (f == nullptr)
			return false;

		fwrite(&nWidth, sizeof(int), 1, f);
		fwrite(&nHeight, sizeof(int), 1, f);
		fwrite(m_Colours, sizeof(short), nWidth * nHeight, f);
		fwrite(m_Glyphs, sizeof(short), nWidth * nHeight, f);

		fclose(f);

		return true;
	}

	bool Load(std::wstring sFile)
	{
		delete[] m_Glyphs;
		delete[] m_Colours;
		nWidth = 0;
		nHeight = 0;

		FILE* f = nullptr;
		_wfopen_s(&f, sFile.c_str(), L"rb");
		if (f == nullptr)
			return false;

		std::fread(&nWidth, sizeof(int), 1, f);
		std::fread(&nHeight, sizeof(int), 1, f);

		Create(nWidth, nHeight);

		std::fread(m_Colours, sizeof(short), nWidth * nHeight, f);
		std::fread(m_Glyphs, sizeof(short), nWidth * nHeight, f);

		std::fclose(f);
		return true;
	}
};

class cEditorFrame : public wxMDIChildFrame
{
public:
	cEditorFrame(wxMDIParentFrame* parent, wxString sName);
	~cEditorFrame();

	void SetColour(int c);
	bool Save(wxString sFileName);
	bool Open(wxString sFileName);
	bool New(int r, int c);

private:
	cCanvas *m_Canvas = nullptr;
	wxStatusBar *m_StatusBar = nullptr;
	wxSlider *m_ZoomSlider = nullptr;

	Sprite spr;
	unsigned char* m_pSprite = nullptr;

	void OnZoomChange(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

