#include "RwxDirTraverser.h"

extern "C"
SEXP
R_RwxDirTraverser_new(SEXP OnFile, SEXP OnDir, SEXP OnError)
{
   RwxDirTraverser *ans = new RwxDirTraverser(OnFile, OnDir, OnError);
   return(R_make_wx_Ref(ans, "RwxDirTraverser"));
}

wxDirTraverseResult
RwxDirTraverser::OnFile(const wxString &filename)
{
    if(!R_OnFile_m) {
        PROBLEM "no method for OnFile in RwxDirTraverser"
            ERROR;
    }


    SEXP e, r_ans;
    wxDirTraverseResult ans;

    PROTECT(e = allocVector(LANGSXP, 3));
    SETCAR(e, R_OnFile_m);
    SEXP This = R_make_wx_Ref(this, "RwxDirTraverser");
    SETCAR(CDR(e), This);
    SETCAR(CDR(CDR(e)), wxStringToR(filename));

    r_ans = Rf_eval(e, R_GlobalEnv);
    ans = (wxDirTraverseResult) INTEGER(r_ans)[0];
    UNPROTECT(1);

    return(ans);
}


wxDirTraverseResult
RwxDirTraverser::OnDir(const wxString &filename)
{
    if(!R_OnDir_m) {
        PROBLEM "no method for OnFile in RwxDirTraverser"
            ERROR;
    }


    SEXP e, r_ans;
    wxDirTraverseResult ans;

    PROTECT(e = allocVector(LANGSXP, 3));
    SETCAR(e, R_OnDir_m);
    SEXP This = R_make_wx_Ref(this, "RwxDirTraverser");
    SETCAR(CDR(e), This);
    SETCAR(CDR(CDR(e)), wxStringToR(filename));

    r_ans = Rf_eval(e, R_GlobalEnv);
    ans = (wxDirTraverseResult) INTEGER(r_ans)[0];
    UNPROTECT(1);

    return(ans);
}



wxOpenErrorTraverseResult 
RwxDirTraverser::OnOpenError(const wxString& openerrorname)
{
    if(!R_OnOpenError_m) {
        return(wxDirTraverser::OnOpenError(openerrorname));
    }


    SEXP e, r_ans;
    wxDirTraverseResult ans;

    PROTECT(e = allocVector(LANGSXP, 3));
    SETCAR(e, R_OnOpenError_m);
    SEXP This = R_make_wx_Ref(this, "RwxDirTraverser");
    SETCAR(CDR(e), This);
    SETCAR(CDR(CDR(e)), wxStringToR(openerrorname));

    r_ans = Rf_eval(e, R_GlobalEnv);
    ans = (wxOpenErrorTraverseResult) INTEGER(r_ans)[0];
    UNPROTECT(1);

    return(ans);
}




#if 0
extern "C" 
SEXP
R_RwxTextDropTarget_RsetOnDropText_method(SEXP r_target, SEXP fun)
{
    RwxTextDropTarget *target = (RwxTextDropTarget *) R_get_wxWidget_Ref(r_target, "RwxTextDropTarget");    
    return(target->R_setOnDropText_method(fun));
}
#endif
