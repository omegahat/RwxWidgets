#include <wx/control.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxControl_SetLabel(SEXP r_This, SEXP r_label)
{
    DECLARE_RWX_REF(This, wxControl);
    wxString label = R_to_wxString(r_label);
    This->SetLabel(label);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxControl_GetLabel(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxControl);
    wxString ans;
    ans = This->GetLabel();
    SEXP r_ans = wxStringToR(ans);
    return(r_ans);
}
