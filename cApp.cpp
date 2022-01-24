#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
	delete wxFrame;
}

bool cApp::OnInit()
{
	wxFrame = new cMain();
	wxFrame->Show();
	return true;
}


