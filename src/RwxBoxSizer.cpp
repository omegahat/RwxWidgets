#include <wx/sizer.h>
#include "RwxUtils.h"

extern "C" {
 SEXP R_wxBoxSizer_new(SEXP r_orient);
 SEXP R_wxBoxSizer_GetOrientation(SEXP r_sizer);
 SEXP R_wxSizer_Add_wxWindowp_int_int_int_wxObjectp(SEXP r_this, SEXP r_window, SEXP r_proportion, SEXP r_flag, SEXP r_border,
                                                    SEXP r_userData);
 SEXP R_wxSizer_Add_wxWindowp_wxSizerFlags(SEXP r_this, SEXP r_window, SEXP r_flags);
}


SEXP R_wxBoxSizer_new(SEXP r_orient)
{
  wxBoxSizer *sizer;
  int orient = INTEGER(r_orient)[0];
  SEXP r_ans;

  sizer = new wxBoxSizer(orient);
  r_ans = R_make_wxWidget_Ref(sizer, "wxBoxSizer");  

  return(r_ans);
}


SEXP 
R_wxBoxSizer_GetOrientation(SEXP r_sizer)
{
    DECLARE_RWX_REF(sizer, wxBoxSizer);
    SEXP r_ans;
    int ans;

    ans =  sizer->GetOrientation();

    PROTECT(r_ans = ScalarInteger(ans));
    SET_NAMES(r_ans, mkString(ans == wxVERTICAL ? "VERTICAL" : "HORIZONTAL"));
    UNPROTECT(1);
    
    return(r_ans);
}


SEXP
R_wxSizer_Add_wxWindowp_wxSizerFlags(SEXP r_this, SEXP r_window, SEXP r_flags)
{
    SEXP ans = R_NilValue;
//XXX
    return(ans);
}


SEXP
R_wxSizer_Add_wxWindowp_int_int_int_wxObjectp(SEXP r_sizer, SEXP r_window, SEXP r_proportion, SEXP r_flag, SEXP r_border,
                                     SEXP r_userData)
{
    DECLARE_RWX_REF(sizer, wxSizer);
    DECLARE_RWX_REF(window, wxWindow);
    int proportion = INTEGER(r_proportion)[0];
    int flag = INTEGER(r_flag)[0];
    int border = INTEGER(r_border)[0];
    wxObject *userData = NULL; //XXX
    
    sizer->Add(window, proportion, flag, border, userData);

    return(R_NilValue);
}
