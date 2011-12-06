#include <wx/panel.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxPanel_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name);
}

SEXP
R_wxPanel_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;

    long style = (long) REAL(r_style)[0];
    wxString name = R_to_wxString(r_name);
    wxPanel *ans;

    size = R_to_wxSize(r_size);
    pos = R_to_wxPoint(r_pos);

    ans = new wxPanel(parent, id, pos, size, style, name);

    return(R_make_wxWidget_Ref(ans, "wxPanel"));
}


