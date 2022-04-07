#include <wx/wx.h>
#include "ProjectMainFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit() { return 0; }
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxFrame* mainFrame = new ProjectMainFrame(NULL);
	mainFrame->Show(true);
	SetTopWindow(mainFrame);
	return true;
}
