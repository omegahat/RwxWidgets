#include <wx/wx.h>
#include <wx/html/htmlwin.h>

#include <wx/image.h>

extern "C" 
void R_try()
{
    wxInitialize(); 
    wxInitAllImageHandlers();  
    wxString title(wxT("My title"));
    wxFrame *f = new wxFrame((wxWindow *)NULL,  wxID_ANY, title);

    wxHtmlWindow *h = new wxHtmlWindow(f, wxID_ANY);

    f->Show(true);
}

