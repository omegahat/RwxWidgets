#include <wx/sizer.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxSizerItem_IsWindow(SEXP r_sizerItem)
{
    DECLARE_RWX_REF(sizerItem, wxSizerItem);
    bool ans = sizerItem -> IsWindow();
    return(ScalarLogical(ans));
}

extern "C"
SEXP
R_wxSizerItem_IsSizer(SEXP r_sizerItem)
{
    DECLARE_RWX_REF(sizerItem, wxSizerItem);
    bool ans = sizerItem -> IsSizer();
    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxSizerItem_IsSpacer(SEXP r_sizerItem)
{
    DECLARE_RWX_REF(sizerItem, wxSizerItem);
    bool ans = sizerItem -> IsSpacer();
    return(ScalarLogical(ans));
}

extern "C"
SEXP
R_wxSizerItem_GetWindow(SEXP r_sizerItem)
{
    DECLARE_RWX_REF(sizerItem, wxSizerItem);
    wxWindow *ans = sizerItem ->GetWindow();
    return(R_make_wxWidget_Ref(ans, "wxWindow", true));
}

extern "C"
SEXP
R_wxSizerItem_GetSizer(SEXP r_sizerItem)
{
    DECLARE_RWX_REF(sizerItem, wxSizerItem);
    wxSizer *ans = sizerItem ->GetSizer();
    return(R_make_wxWidget_Ref(ans, "wxSizer"));
}

