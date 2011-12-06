#if wxUSE_DRAG_AND_DROP

#include "RwxTextDropTarget.h"

#include <Rinternals.h>

extern "C"
SEXP
R_RwxTextDropTarget(SEXP OnDropText, SEXP OnEnter, SEXP OnDragOver)
{
    RwxTextDropTarget *ans =  new RwxTextDropTarget(OnDropText, OnEnter, OnDragOver);
    return(R_make_wx_Ref(ans, "RwxTextDropTarget"));
}

bool
RwxTextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString &text)
{
    if(!R_OnDropText_m)
        return(false);

    SEXP e, r_ans, p;
    bool ans;

//XXX check
    PROTECT(e = allocVector(LANGSXP, 5));
    SETCAR(e, R_OnDropText_m);   p = CDR(e);
    SETCAR(p, R_make_wx_Ref(this, "RwxTextDropTarget")); p = CDR(p);
    SETCAR(p, ScalarInteger(x));  p = CDR(p);
    SETCAR(p, ScalarInteger(y));  p = CDR(p);
    SETCAR(p, wxStringToR(text));

    r_ans = Rf_eval(e, R_GlobalEnv);
    if(TYPEOF(r_ans) == LGLSXP)
        ans = LOGICAL(r_ans)[0];
    else
        ans = Rf_length(r_ans) > 0;

    UNPROTECT(1);

    return(ans);
}


static wxDragResult
invoke(SEXP fun, wxTextDropTarget *This, wxCoord x, wxCoord y, wxDragResult def)
{
    SEXP e, r_ans, p;
    wxDragResult ans;

    PROTECT(e = p = allocVector(LANGSXP, 5)); 
    SETCAR(e, fun);  p = CDR(p);
    SETCAR(p, R_make_wx_Ref(This, "RwxTextDropTarget"));  p = CDR(p);
    SETCAR(p, ScalarInteger(x)); p = CDR(p);
    SETCAR(p, ScalarInteger(y)); p = CDR(p);
    SETCAR(p, ScalarInteger(def));  //XX make an enum

    r_ans = Rf_eval(e, R_GlobalEnv);
    if(TYPEOF(r_ans) == INTSXP)
        ans = (wxDragResult) LOGICAL(r_ans)[0];
    else if(TYPEOF(r_ans) == REALSXP)
        ans = (wxDragResult) REAL(r_ans)[0];
    else
        ans = def;

    UNPROTECT(1);

    return(ans);
}

wxDragResult
RwxTextDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
    if(!R_OnEnter_m)
        return(def);
    return(invoke(R_OnEnter_m, this, x, y, def));
}


wxDragResult
RwxTextDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if(!R_OnDragOver_m)
        return(def);
    return(invoke(R_OnDragOver_m, this, x, y, def));
}




extern "C" 
SEXP
R_RwxTextDropTarget_RsetOnDropText_method(SEXP r_target, SEXP fun)
{
    RwxTextDropTarget *target = (RwxTextDropTarget *) R_get_wxWidget_Ref(r_target, "RwxTextDropTarget");    
    return(target->R_setOnDropText_method(fun));
}


#endif
