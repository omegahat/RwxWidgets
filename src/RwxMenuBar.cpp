#include <wx/menu.h>
#include "RwxUtils.h"

extern "C" {
 SEXP R_wxMenuBar_new(SEXP r_style);
 SEXP R_wxMenuBar_Append(SEXP r_This, SEXP r_menu, SEXP r_title);
}


SEXP 
R_wxMenuBar_new(SEXP r_style)
{
  wxMenuBar *ans;
  SEXP r_ans;
  long style = (long) REAL(r_style)[0];

  ans = new wxMenuBar(style);

  r_ans = R_make_wxWidget_Ref(ans, "wxMenuBar");  

  return(r_ans);
}

SEXP 
R_wxMenuBar_Append(SEXP r_This, SEXP r_menu, SEXP r_title)
{
    DECLARE_RWX_REF(This, wxMenuBar);
    DECLARE_RWX_REF(menu, wxMenu);
    wxString title;
    bool ans;
    SEXP r_ans;
    
    title = wxString(CHAR(STRING_ELT(r_title, 0)), wxConvUTF8);

    ans = This->Append(menu, title);

    r_ans = ScalarLogical(ans);

    return(r_ans);
}


