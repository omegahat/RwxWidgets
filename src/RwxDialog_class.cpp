#include "RwxDialog.h"

extern "C"
SEXP
R_RwxDialog_new(SEXP r_parent, SEXP r_id, SEXP r_title, SEXP r_pos, SEXP r_size,
                SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF_NULL_OK(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    
    long style = (long) REAL(r_style)[0];
    const wxString title = R_to_wxString(r_title);
    const wxString name = R_to_wxString(r_name);

    if(LENGTH(r_size))
        size = R_to_wxSize(r_size);
    if(LENGTH(r_pos))
        pos = R_to_wxPoint(r_pos);


    RwxDialog *ans = new RwxDialog(parent, id, title, pos, size, style, name);
    SEXP r_ans = R_make_wxWidget_Ref(dynamic_cast<wxObject *>(ans), "RwxDialog");
    return(r_ans);
}


void 
RwxDialog::CreateControls(void)
{
#if 0 // XXX This not in the wxDialog class. Suggested it is in Chap 9 of the wxWidgets book.
    if(!R_CreateControls_m) {
        wxDialog::CreateControls();
        return;
    }
#endif

    SEXP e;
    PROTECT(e = allocVector(LANGSXP, 2));
    SETCAR(e, R_CreateControls_m);
    SETCAR(CDR(e), R_make_wxWidget_Ref(this, "RwxDialog"));

    (void) Rf_eval(e, REnv());

    UNPROTECT(1);
}
   
bool 
RwxDialog::TransferDataToWindow(void)
{
    if(!R_TransferDataToWindow_m)
        return(wxDialog::TransferDataToWindow());

    SEXP e;
    PROTECT(e = allocVector(LANGSXP, 2));
    SETCAR(e, R_TransferDataFromWindow_m);
    SETCAR(CDR(e), R_make_wxWidget_Ref(this, "RwxDialog"));

    SEXP r_ans = Rf_eval(e, REnv());

    PROTECT(r_ans);

    bool ans;
    if(TYPEOF(r_ans) == LGLSXP)
        ans =  LOGICAL(r_ans)[0];
    else
        ans = GET_LENGTH(r_ans) > 0;

    UNPROTECT(2);
    return(ans);
}

bool 
RwxDialog::TransferDataFromWindow(void)
{
    if(!R_TransferDataFromWindow_m)
        return(wxDialog::TransferDataFromWindow());

    SEXP e;
    PROTECT(e = allocVector(LANGSXP, 2));
    SETCAR(e, R_TransferDataFromWindow_m);
    SETCAR(CDR(e), R_make_wxWidget_Ref(this, "RwxDialog"));

    SEXP r_ans = Rf_eval(e, REnv());

    PROTECT(r_ans);

    bool ans;
    if(TYPEOF(r_ans) == LGLSXP)
        ans =  LOGICAL(r_ans)[0];
    else
        ans = GET_LENGTH(r_ans) > 0;

    UNPROTECT(2);
    return(ans);
}

