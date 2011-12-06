#include <wx/wx.h>
#include "RwxConverters.h"

#include "Rinternals.h"
#include "Rdefines.h"

SEXP
convert_wxSize_to_R(wxSize &sz)
{
  SEXP r_ans;

  PROTECT(r_ans = NEW_INTEGER(2));

  INTEGER(r_ans)[0] = sz.GetWidth();
  INTEGER(r_ans)[1] = sz.GetHeight();

  UNPROTECT(1);

  return(r_ans);
}

