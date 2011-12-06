#include <wx/wx.h>
#include <wx/html/htmlwin.h>

#include <wx/image.h>

class MyApp : public wxApp 
{
public:
    virtual bool OnInit() {
        wxString title(wxT("My title"));
        wxFrame *f = new wxFrame((wxWindow *)NULL,  wxID_ANY, title);

        wxHtmlWindow *h = new wxHtmlWindow(f, wxID_ANY);

        f->Show(true);
        return(true);
    }
}

IMPLEMENT_APP(MyApp)
