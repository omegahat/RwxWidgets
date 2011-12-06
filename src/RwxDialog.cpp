#include <wx/dialog.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxDialog_ShowModal(SEXP r_dialog);
    SEXP R_wxDialog_EndModal(SEXP r_dialog, SEXP r_code);

    SEXP R_wxDialog_GetAffirmativeId(SEXP r_dialog);
}

SEXP
R_wxDialog_ShowModal(SEXP r_dialog)
{
    DECLARE_RWX_REF(dialog, wxDialog);
    int ans = dialog->ShowModal();
    return(ScalarInteger(ans));
}

SEXP
R_wxDialog_EndModal(SEXP r_dialog, SEXP r_code)
{
    DECLARE_RWX_REF(dialog, wxDialog);
    int code = INTEGER(r_code)[0];
    dialog->EndModal(code);
    return(R_NilValue);
}

SEXP 
R_wxDialog_GetAffirmativeId(SEXP r_dialog)
{
    DECLARE_RWX_REF(dialog, wxDialog);
    int ans = dialog->GetAffirmativeId();
    return(ScalarInteger(ans));
}
