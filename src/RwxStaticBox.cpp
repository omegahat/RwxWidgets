#include <wx/wx.h>
#include <wx/statbox.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_wxStaticBox_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, 
                 SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    const wxString label = R_to_wxString(r_label);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    
    long style = (long) REAL(r_style)[0];
    const wxString name = R_to_wxString(r_name);

    if(LENGTH(r_size))
        size = R_to_wxSize(r_size);
    if(LENGTH(r_pos))
        pos = wxPoint(INTEGER(r_pos)[0], INTEGER(r_pos)[1]);

    wxStaticBox *ans = new wxStaticBox(parent, id, label, pos, size, style, name);
    return(R_make_wxWidget_Ref(ans, "wxStaticBox"));

}

