#include <wx/gbsizer.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxGBPosition_new()
{
    wxGBPosition *ans;
    ans = new wxGBPosition();
    return(R_make_wx_Ref((void *) ans, "wxGBPosition"));
}


extern "C"
SEXP
R_wxGBPosition_new_int_int(SEXP r_row, SEXP r_col)
{
    wxGBPosition *ans;
    int row = INTEGER(r_row)[0];
    int col = INTEGER(r_col)[0];
    ans = new wxGBPosition(row, col);
    return(R_make_wx_Ref(ans, "wxGBPosition"));
}

extern "C"
SEXP
R_wxGBPosition_SetRow(SEXP r_gbposition, SEXP r_row)
{
    DECLARE_RWX_REF(gbposition, wxGBPosition);
    int row = INTEGER(r_row)[0];
    gbposition->SetRow(row);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxGBPosition_SetCol(SEXP r_gbposition, SEXP r_row)
{
    DECLARE_RWX_REF(gbposition, wxGBPosition);
    int row = INTEGER(r_row)[0];
    gbposition->SetCol(row);
    return(R_NilValue);
}




