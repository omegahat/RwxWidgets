#include <wx/wx.h>
#include <wx/font.h>

#include "RwxUtils.h"

extern "C" {
 SEXP R_wxFont_new_int(SEXP r_pointSize, SEXP r_family, SEXP r_style, SEXP r_weight, SEXP r_underline, SEXP r_faceName, SEXP r_encoding);
}

SEXP R_wxFont_new_int(SEXP r_pointSize, SEXP r_family, SEXP r_style, SEXP r_weight, 
                       SEXP r_underline, SEXP r_faceName, SEXP r_encoding)
{
  wxFont *ans;
  int pointSize = INTEGER(r_pointSize)[0];
  wxFontFamily family = (wxFontFamily) INTEGER(r_family)[0];
  int style = INTEGER(r_style)[0];
  wxFontWeight weight = (wxFontWeight) INTEGER(r_weight)[0];
  bool underling = LOGICAL(r_underline)[0];
  wxString faceName = R_to_wxString(r_faceName);
  wxFontEncoding encoding = (wxFontEncoding)INTEGER(r_encoding)[0];
  ans = new wxFont(pointSize, family, style, weight, underling, faceName, encoding);

  return(R_make_wxWidget_Ref(ans, "wxFont"));
}
