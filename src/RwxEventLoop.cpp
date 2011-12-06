#include <wx/wx.h>
#include <wx/evtloop.h>

#include "RwxUtils.h"

#ifndef NO_WX_EVENT_LOOP

/* Attempt to force the instantiation of the class and its vtable, etc. */
static void
foo(void) {
   wxEventLoop dummy;
   dummy.Run();
}

extern "C" {
    SEXP R_wxEventLoop_Dispatch(SEXP r_eventloop);
    SEXP R_wxEventLoop_GetActive();
    SEXP R_wxEventLoop_SetActive(SEXP r_eventloop);
    SEXP R_wxEventLoop_Pending(SEXP r_eventloop);
    SEXP R_wxEventLoop_Dispatch(SEXP r_eventloop);
    SEXP R_wxEventLoop_Run(SEXP r_eventloop);
    SEXP R_wxEventLoop_Exit(SEXP r_eventloop, SEXP r_rc);
    SEXP R_wxEventLoop_new();
};


SEXP
R_wxEventLoop_new()
{
    wxEventLoop *ans;
    ans = new wxEventLoop();
    return(R_make_wx_Ref(ans, "wxEventLoop"));
}
#if 0
#endif

SEXP 
R_wxEventLoop_GetActive()
{
    SEXP r_ans;
    wxEventLoop *ans = wxEventLoop::GetActive();
    return(R_make_wx_Ref(ans, "wxEventLoop"));
}

SEXP 
R_wxEventLoop_SetActive(SEXP r_eventloop)
{
    DECLARE_RWX_REF(eventloop, wxEventLoop);
    wxEventLoop::SetActive(eventloop);
    return(R_NilValue);
}


SEXP 
R_wxEventLoop_Pending(SEXP r_eventloop)
{
    DECLARE_RWX_REF(eventloop, wxEventLoop);
    return(ScalarLogical(eventloop->Pending()));
}

SEXP 
R_wxEventLoop_Dispatch(SEXP r_eventloop)
{
    DECLARE_RWX_REF(eventloop, wxEventLoop);
    return(ScalarLogical(eventloop->Dispatch()));
}


SEXP 
R_wxEventLoop_Run(SEXP r_eventloop)
{
    DECLARE_RWX_REF(eventloop, wxEventLoop);
    return(ScalarInteger(eventloop->Run()));
}

SEXP 
R_wxEventLoop_Exit(SEXP r_eventloop, SEXP r_rc)
{
    DECLARE_RWX_REF(eventloop, wxEventLoop);
    int rc = INTEGER(r_rc)[0];
    eventloop->Exit(rc);
    return(R_NilValue);
}

#else
static int _x;
#endif /* NO_WX_EVENT_LOOP */
