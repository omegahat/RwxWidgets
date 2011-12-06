#include <wx/wx.h>
#include <wx/html/htmlwin.h>

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,
    Minimal_Back,
    Minimal_Forward,

    // controls start here (the numbers are, of course, arbitrary)
    Minimal_Text = 1000,
};

IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// `Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // Create the main application window
    MyFrame *frame = new MyFrame( _("wxHtmlWindow testing application"),
        wxDefaultPosition, wxSize(640, 480) );

    // Show it and tell the application that it's our main window
    // @@@ what does it do exactly, in fact? is it necessary here?
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

wxHtmlWindow *html;

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
{

    CreateStatusBar(2);

    html = new wxHtmlWindow(this);
    html -> SetRelatedFrame(this, _("wxHTML Demo: '%s'"));

    html -> SetRelatedStatusBar(1);

    html -> LoadPage(wxT("start.htm"));
}


#include <wx/image.h>

extern "C" 
void R_start(void)
{
  char *argv[] = {"R"};
  int argc = sizeof(argv)/sizeof(argv[0]);

  wxInitAllImageHandlers();
  wxEntry(argc, argv);
}
