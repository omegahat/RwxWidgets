#include <wx/gbsizer.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxGBSpan_new()
{
    wxGBSpan *ans;
    ans = new wxGBSpan();
    return(R_make_wx_Ref(ans, "wxGBSpan"));
}


extern "C"
SEXP
R_wxGBSpan_new_int_int(SEXP r_row, SEXP r_col)
{
    wxGBSpan *ans;
    int row = INTEGER(r_row)[0];
    int col = INTEGER(r_col)[0];
    ans = new wxGBSpan(row, col);
    return(R_make_wx_Ref(ans, "wxGBSpan"));
}

extern "C"
SEXP
R_wxGBSpan_SetRowspan(SEXP r_gbspan, SEXP r_row)
{
    DECLARE_RWX_REF(gbspan, wxGBSpan);
    int row = INTEGER(r_row)[0];
    gbspan->SetRowspan(row);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxGBSpan_SetColspan(SEXP r_gbspan, SEXP r_row)
{
    DECLARE_RWX_REF(gbspan, wxGBSpan);
    int row = INTEGER(r_row)[0];
    gbspan->SetColspan(row);
    return(R_NilValue);
}
