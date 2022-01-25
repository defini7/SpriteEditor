#include "cApp.h"

IMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	m_frame = new cMain();
	return m_frame->Show();
}
