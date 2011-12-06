#include <wx/grid.h> /* For testing the event identifier. */

#include "RwxEvents.h"
#include "Rdefines.h"

extern "C" {
    SEXP R_Rwx_Connect(SEXP r_obj,
                       SEXP r_winid,
                       SEXP r_eventType,
                       SEXP fun,
                       SEXP r_routine,
                       SEXP eventSink,
                       SEXP r_args, SEXP r_computeEventClass
                      );

    SEXP R_wxEventHandler_Disconnect(SEXP r_handler);
    SEXP R_wxEvent_Skip(SEXP r_event, SEXP r_skip);
    SEXP R_wxEvent_GetEventObject(SEXP r_event);
    SEXP R_wxKeyEvent_MetaDown(SEXP r_event);
    SEXP R_wxKeyEvent_ControlDown(SEXP r_event);
    SEXP R_wxKeyEvent_GetKeyCode(SEXP r_event);

    SEXP ResumePropagation(SEXP r_event, SEXP r_propogationLevel);
    SEXP StopPropagation(SEXP r_event);
}


SEXP
/*
 Create an R object which is a reference to this object
 (make certain there is no finalizer)
 and get the class information
*/
createDynamicRwxReference(wxEvent *ev, const char *tagName)
{
   SEXP ref, ans, e;

   PROTECT(e = allocVector(LANGSXP, 2));
   SETCAR(e, Rf_install("wxObject"));
   SETCAR(CDR(e), ref = R_MakeExternalPtr((void *) ev, Rf_install(tagName), R_NilValue));      
   ans = Rf_eval(e, R_GlobalEnv);
   UNPROTECT(1);

   return(ans);
}


void
R_wxEventHandler::invoke(wxEvent &ev)
{
  if(this->expr == NULL || Rf_length(this->expr) == 0) {
    fprintf(stderr, "no handler function in R_wxEventHandler\n");
    fflush(stderr);
    return;
  }

  int errorOccurred;
  SEXP rev;

  if(addEventClass) 
      rev = createDynamicRwxReference(&ev);
  else 
      rev = R_MakeExternalPtr((void *) &ev, Rf_install("wxEvent"), R_NilValue);
  SETCAR(CDR(expr), rev);

  (void) R_tryEval(expr, R_GlobalEnv, &errorOccurred);
  if(errorOccurred) {
      PROBLEM "an error occurred in a callback"
          WARN;
  }
}



SEXP
R_Rwx_Connect(SEXP r_obj,
              SEXP r_winid,
              SEXP r_eventType,
              SEXP fun,
              SEXP r_routine,
              SEXP eventSink,
              SEXP r_args,
              SEXP r_computeEventClass
             )
{
  wxEvtHandler *obj = (wxEvtHandler *) R_get_wxWidget_Ref(r_obj, NULL);
  wxWindow *w = (wxWindow *) R_get_wxWidget_Ref(r_obj, NULL);

  int winid = INTEGER(r_winid)[0], lastId;
  wxEventType eventType = (wxEventType) INTEGER(r_eventType)[0];

  SEXP r_ans;

  /*  routine = (wxObjectEventFunction) R_ExternalPtrAddr(routine); */

  R_wxEventHandler *handler = new R_wxEventHandler(fun, winid, eventType, obj, r_args, LOGICAL(r_computeEventClass)[0]);

  if(GET_LENGTH(r_winid) > 1) {
      lastId = INTEGER(r_winid)[1];
      w->Connect(winid, lastId, eventType, 
                 wxEventHandler(R_wxEventHandler::invoke), 
                 NULL, handler);
  } else {
      w->Connect(winid, eventType, 
                 wxEventHandler(R_wxEventHandler::invoke), 
                 NULL, handler);
  }
  r_ans = R_make_wxWidget_Ref(handler, "RwxEventHandler");

  return(r_ans);
}

SEXP
R_wxEventHandler_Disconnect(SEXP r_handler)
{
    SEXP ans;
    R_wxEventHandler *handler = (R_wxEventHandler*) R_get_wxWidget_Ref(r_handler, "RwxEventHandler");
    handler->Disconnect();
 
    ans = ScalarLogical(TRUE);
    return(ans);
}

void
R_wxEventHandler::Disconnect()
{
    if(!widget) {
       PROBLEM  "Can't diconnect event handler as insufficient information stored when connecting, e.g. widget"
           ERROR;
    }
    widget->Disconnect(id, eventType, wxEventHandler(R_wxEventHandler::invoke), NULL, this);
}


SEXP
R_wxEvent_Skip(SEXP r_event, SEXP r_skip)
{
  DECLARE_RWX_REF(event, wxEvent);
  bool skip = LOGICAL(r_skip)[0];
  event->Skip(skip);
  return(R_NilValue);
}


SEXP
R_wxEvent_GetEventObject(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxEvent);
  wxObject *ans;

  ans = event->GetEventObject();
  return(R_make_wxWidget_Ref(ans, "wxObject"));
}

extern "C"
SEXP
R_wxEvent_GetId(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxEvent);
  wxObject *ans;

  int id = event->GetId();
  return(ScalarInteger(id));
}

SEXP
R_wxKeyEvent_MetaDown(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxKeyEvent);
  bool ans;
  ans = event->MetaDown();
  return(ScalarLogical(ans));
}


SEXP
R_wxKeyEvent_ControlDown(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxKeyEvent);
  bool ans;
  ans = event->ControlDown();
  return(ScalarLogical(ans));
}

SEXP
R_wxKeyEvent_GetKeyCode(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxKeyEvent);
  int ans;
  ans = event->GetKeyCode();
  return(ScalarInteger(ans));
}


SEXP
StopPropagation(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxKeyEvent);
  int ans;
  ans = event->StopPropagation();
  return(ScalarInteger(ans));
}

SEXP
ResumePropagation(SEXP r_event, SEXP r_propogationLevel)
{
  DECLARE_RWX_REF(event, wxKeyEvent);
  int propogationLevel = INTEGER(r_propogationLevel)[0];
  event->ResumePropagation(propogationLevel);
  return(R_NilValue);
}


extern "C"
SEXP
R_wxCommandEvent_GetString(SEXP r_event)
{
  DECLARE_RWX_REF(event, wxCommandEvent);

  wxString ans = event->GetString();
  SEXP r_ans = wxStringToR(ans);
  return(r_ans);
}
