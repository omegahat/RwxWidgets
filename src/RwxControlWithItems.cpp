#include <wx/wx.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxControlWithItems_GetSelection(SEXP r_This);
    SEXP R_wxControlWithItems_Select(SEXP r_This, SEXP r_n);
    SEXP R_wxControlWithItems_cast(SEXP r_obj);
}

SEXP 
R_wxControlWithItems_GetSelection(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxControlWithItems);

    int ans = This->GetSelection();
    return(ScalarInteger(ans));
}

SEXP 
R_wxControlWithItems_Select(SEXP r_This, SEXP r_n)
{
    DECLARE_RWX_REF(This, wxControlWithItems);
    int n = INTEGER(r_n)[0];
    This->Select(n);
    return(R_NilValue);
}

SEXP 
R_wxControlWithItems_cast(SEXP r_obj)
{
   void *ptr = R_get_wxWidget_Ref(r_obj, NULL);
   wxControlWithItems *ans = wxDynamicCast(ptr, wxControlWithItems);
   if(!ans) {
       PROBLEM "object is not a legitimate wxControlWithItems pointer"
       ERROR;
   }
   return(R_make_wxWidget_Ref(ans, "wxControlWithItems"));
}
