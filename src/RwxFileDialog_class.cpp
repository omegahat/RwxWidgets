#include "RwxFileDialog.h"

extern "C" {
SEXP
R_RwxFileDialog_new(SEXP r_parent, SEXP r_message, SEXP r_defaultDir, SEXP r_defaultFile,
                    SEXP r_wildcard, SEXP r_style, SEXP r_pos,
                    SEXP OnOK_m);

}

SEXP
R_RwxFileDialog_new(SEXP r_parent, SEXP r_message, SEXP r_defaultDir, SEXP r_defaultFile,
                    SEXP r_wildcard, SEXP r_style, SEXP r_pos,
                    SEXP OnOK_m)
{
    RwxFileDialog *ans;
    wxWindow *parent = GET_RWX_REF(r_parent, wxWindow);
    wxString message = R_to_wxString(r_message);
    wxString defaultDir = R_to_wxString(r_defaultDir);
    wxString defaultFile = R_to_wxString(r_defaultFile);
    wxString wildcard = R_to_wxString(r_wildcard);
    long style = (long) REAL(r_style)[0];
    wxPoint pos = wxDefaultPosition;

    if(GET_LENGTH(r_pos) >= 2 && TYPEOF(r_pos) == INTSXP)
        pos = wxPoint(INTEGER(r_pos)[0], INTEGER(r_pos)[1]);

    ans = new RwxFileDialog(parent, message, defaultDir, defaultFile, wildcard, style, pos, OnOK_m == R_NilValue ? NULL : OnOK_m);
    return(R_make_wxWidget_Ref(ans, "RwxFileDialog"));    
}

void RwxFileDialog::OnOK(wxCommandEvent &event)
{
    if(R_OnOK_m != NULL) {
        SEXP e;
        int errorOccurred = 0;
        PROTECT(e = allocVector(LANGSXP, 2));
        SETCAR(e, R_OnOK_m);
        SETCAR(CDR(e),  createDynamicRwxReference(&event));
        (void) R_tryEval(e, R_GlobalEnv, &errorOccurred);
        UNPROTECT(1);

        return;
    }
#if 0 //XXX not in 2.8 and probably not used anyway
    wxFileDialog::OnOK(event);
#endif
}



#if 0
void RwxFileDialog::OnApply(wxCommandEvent &event)
{
    SEXP fun;
    fun = RwxDynamicClass::lookupMethod("OnApply");
    if(fun) {
        
        return;
    }

    wxFileDialog::OnApply(event);
}

void RwxFileDialog::OnCancel(wxCommandEvent &event)
{
    SEXP fun;
    fun = RwxDynamicClass::lookupMethod("OnCancel");

    wxFileDialog::OnCancel(event);
}
#endif


