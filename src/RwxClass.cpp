#include "RwxClass.h"

SEXP 
R_wxClass::invoke(SEXP fun, SEXP arg1, SEXP arg2)
{
    SEXP e;
    SEXP ans = NULL;

    PROTECT(e = allocVector(LANGSXP, 3));
    SETCAR(e, fun);
    SETCAR(CDR(e), arg1);
    SETCAR(CDR(CDR(e)), arg2);

    int errorOccurred;

    ans = R_tryEval(e, R_GlobalEnv, &errorOccurred);
    UNPROTECT(1);
    if(errorOccurred)
        ans = NULL;
    return(ans);
}


SEXP 
R_wxClass::invoke(SEXP fun, SEXP arg1, SEXP arg2, SEXP arg3)
{
    SEXP e;
    SEXP ans = NULL;

    PROTECT(e = allocVector(LANGSXP, 4));
    SETCAR(e, fun);
    SETCAR(CDR(e), arg1);
    SETCAR(CDR(CDR(e)), arg2);
    SETCAR(CDR(CDR(CDR(e))), arg3);

    int errorOccurred;

    ans = R_tryEval(e, R_GlobalEnv, &errorOccurred);
    UNPROTECT(1);
    if(errorOccurred)
        ans = NULL;

    return(ans);
}



SEXP 
R_wxClass::invoke(SEXP fun, SEXP arg1)
{
    SEXP e;
    SEXP ans = NULL;

    PROTECT(e = allocVector(LANGSXP, 2));
    SETCAR(e, fun);
    SETCAR(CDR(e), arg1);

    int errorOccurred;

    ans = R_tryEval(e, R_GlobalEnv, &errorOccurred);

    UNPROTECT(1);
    if(errorOccurred)
        ans = NULL;

    return(ans);
}


