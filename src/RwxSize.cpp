#include <wx/wx.h>
#include "RwxUtils.h"


void R_finalize_wxSize(SEXP r_obj)
{
    void *ptr = R_ExternalPtrAddr(r_obj);
    wxSize *obj = static_cast<wxSize *>(ptr);
    delete obj;
}

extern "C"
SEXP
R_wxSize_new(SEXP r_width, SEXP r_height, SEXP r_addFinalizer)
{
    int width = asInteger(r_width);
    int height = asInteger(r_height);
    
    R_CFinalizer_t finalizer = NULL;

    wxSize *ans = new wxSize(width, height);

    SEXP r_ans = R_make_wx_Ref(ans, "wxSize");
    if(TYPEOF(r_addFinalizer) == LGLSXP && LOGICAL(r_addFinalizer)[0])
        finalizer = R_finalize_wxSize;
    
    if(finalizer) {
       SEXP tmp = GET_SLOT(r_ans, Rf_install("ref"));
       R_RegisterCFinalizer(tmp, finalizer);
    }
    return(r_ans);
}

extern "C"
SEXP
R_wxSize_GetWidth(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxSize);
    int ans = This->GetWidth();
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxSize_GetHeight(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxSize);
    int ans = This->GetHeight();
    return(ScalarInteger(ans));
}
