#include <wx/sizer.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxStaticBoxSizer_new(SEXP r_orient, SEXP r_parent, SEXP r_label);
}


SEXP 
R_wxStaticBoxSizer_new(SEXP r_orient, SEXP r_parent, SEXP r_label)
{
  wxWindow *parent;
  parent = (wxWindow *) R_get_wxWidget_Ref(r_parent, NULL);
  int orient = INTEGER(r_orient)[0];
  wxString label = R_to_wxString(r_label);

  wxStaticBoxSizer *ans = new wxStaticBoxSizer(orient, parent, label);
  SEXP r_ans = R_make_wxWidget_Ref(ans, "wxStaticBoxSizer");

  return(r_ans);
}
