#include <wx/wx.h>

#include <Rinternals.h>
#include <Rdefines.h>

#include <wx/event.h>

SEXP
R_MakeList(int n, ...)
{
    SEXP *tmp, ans;
    va_list ap;
    int i;

    tmp = (SEXP *) R_alloc(n, sizeof(SEXP));
    va_start(ap, n);
    for(i = 0; i< n;i++) {
        tmp[i] = va_arg(ap, SEXP);
        PROTECT(tmp[i]);
    }
    va_end(ap);
    PROTECT(ans = NEW_LIST(n));
    for(i = 0; i< n;i++) 
        SET_VECTOR_ELT(ans, i, tmp[i]);
    UNPROTECT(n+1);
    return(ans);
}


extern "C"
SEXP
R_getVersionInfo()
{
    SEXP ans;
    ans = R_MakeList(4,
                ScalarInteger(wxMAJOR_VERSION),
                ScalarInteger(wxMINOR_VERSION),
                ScalarInteger(wxRELEASE_NUMBER),
                ScalarInteger(wxSUBRELEASE_NUMBER));
//                mkString(wxVERSION_STRING));

    return(ans);
}


extern "C"
SEXP
R_get_wxEVT_SCROLL_CHANGED()
{
    int status;
    status = wxEVT_COMMAND_SCROLLBAR_UPDATED;
    return(ScalarInteger(status));
}
