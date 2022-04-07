///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
private:

protected:
	wxPanel* _viewTop;
	wxPanel* _viewFront;
	wxPanel* _viewPerspective;
	wxPanel* _viewRight;
	wxTextCtrl* _shapeList;
	wxTextCtrl* _consoleOutput;
	wxStaticText* _promptChar;
	wxTextCtrl* _promptField;

	// Virtual event handlers, overide them in your derived class
	virtual void MainFrameOnClose(wxCloseEvent& event) { event.Skip(); }
	virtual void MainFrameOnPaint(wxPaintEvent& event) { event.Skip(); }
	virtual void _promptFieldOnTextEnter(wxCommandEvent& event) { event.Skip(); }


public:

	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Prosty edytor grafiki 3D"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(640, 480), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainFrame();

};

