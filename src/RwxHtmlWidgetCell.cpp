#include <wx/html/htmlcell.h>
#include "RwxUtils.h"

extern "C" {
  SEXP R_wxHtmlWidgetCell_new(SEXP r_wnd, SEXP r_w);
}


SEXP
R_wxHtmlWidgetCell_new(SEXP r_wnd, SEXP r_w)
{
  wxWindow *wnd = GET_RWX_REF(r_wnd, wxWindow);
  int w = INTEGER(r_w)[0];

  wxHtmlWidgetCell *ans = new wxHtmlWidgetCell(wnd, w);
  SEXP r_ans = R_make_wxWidget_Ref(ans, "wxHtmlWidgetCell");
  return(r_ans);
}
