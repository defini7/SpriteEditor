#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	virtual ~cApp();

private:
	cMain* m_frame = nullptr;

public:
	virtual bool OnInit();
};

