///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Project.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bFrame;
	bFrame = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bMainView;
	bMainView = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bView1;
	bView1 = new wxBoxSizer(wxVERTICAL);

	_viewTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bView1->Add(_viewTop, 1, wxEXPAND | wxALL, 5);

	_viewFront = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bView1->Add(_viewFront, 1, wxEXPAND | wxALL, 5);


	bMainView->Add(bView1, 3, wxEXPAND, 5);

	wxBoxSizer* bView2;
	bView2 = new wxBoxSizer(wxVERTICAL);

	_viewPerspective = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bView2->Add(_viewPerspective, 1, wxEXPAND | wxALL, 5);

	_viewRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bView2->Add(_viewRight, 1, wxEXPAND | wxALL, 5);


	bMainView->Add(bView2, 3, wxEXPAND, 5);

	_shapeList = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	bMainView->Add(_shapeList, 2, wxALL | wxEXPAND, 5);


	bFrame->Add(bMainView, 2, wxEXPAND, 5);

	wxBoxSizer* bConsole;
	bConsole = new wxBoxSizer(wxVERTICAL);

	_consoleOutput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	bConsole->Add(_consoleOutput, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxEXPAND, 5);

	wxBoxSizer* bPrompt;
	bPrompt = new wxBoxSizer(wxHORIZONTAL);

	_promptChar = new wxStaticText(this, wxID_ANY, wxT(">"), wxDefaultPosition, wxDefaultSize, 0);
	_promptChar->Wrap(-1);
	bPrompt->Add(_promptChar, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	_promptField = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	bPrompt->Add(_promptField, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


	bConsole->Add(bPrompt, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);


	bFrame->Add(bConsole, 1, wxEXPAND, 5);


	this->SetSizer(bFrame);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::MainFrameOnClose));
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::MainFrameOnPaint));
	_promptField->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::_promptFieldOnTextEnter), NULL, this);
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::MainFrameOnClose));
	this->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::MainFrameOnPaint));
	_promptField->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::_promptFieldOnTextEnter), NULL, this);

}
