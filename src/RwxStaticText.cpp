#include <wx/stattext.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxStaticText_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name);
    SEXP R_wxStaticText_Wrap(SEXP r_This, SEXP r_width);
}




SEXP
R_wxStaticText_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos,
                   SEXP r_size, SEXP r_style, SEXP r_name)

{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxString label= R_to_wxString(r_label);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    long style = (long) REAL(r_style)[0];
    const wxString name = R_to_wxString(r_name);

    wxStaticText *ans = new wxStaticText(parent, id, label, pos, size, style, name);

    return(R_make_wxWidget_Ref(ans, "wxStaticText"));
}

extern "C"
SEXP 
R_wxStaticText_Wrap(SEXP r_This, SEXP r_width)
{
    DECLARE_RWX_REF(This, wxStaticText);
    int width = INTEGER(r_width)[0];
    This->Wrap(width);
    return(R_NilValue);
}


extern "C"
SEXP 
R_wxStaticText_SetLabel(SEXP r_This, SEXP r_label)
{
    DECLARE_RWX_REF(This, wxStaticText);
    wxString label = R_to_wxString(r_label);
    This->SetLabel(label);
    return(R_NilValue);
}


extern "C"
SEXP 
R_wxStaticText_GetLabel(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxStaticText);
    wxString ans;
    SEXP r_ans;
    ans = This->GetLabel();
    r_ans = wxStringToR(ans);
    return(r_ans);
}


