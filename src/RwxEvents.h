#include "RwxUtils.h"
#include <wx/event.h>
#include <wx/window.h>

#include "Rinternals.h"


class R_wxEventHandler : public wxEvtHandler {

 public:
    R_wxEventHandler(SEXP fun, SEXP args = NULL) : addEventClass(true) {
        expr = NULL;
	SetCallback(fun, args);
   }

    R_wxEventHandler(SEXP fun, bool computeEventClass) : addEventClass(computeEventClass) {
        expr = NULL;
	SetCallback(fun, NULL);
   }


   R_wxEventHandler(SEXP fun, int id, wxEventType eventType, wxEvtHandler *widget, SEXP args = NULL, bool computeEventClass = true) 
      : addEventClass(computeEventClass) 
  {
      expr = NULL;
      SetCallback(fun, args);
      this->id = id;
      this->eventType = eventType;
      this->widget = widget;
  };

 ~R_wxEventHandler() {
     if(expr) {
	 R_ReleaseObject(expr);
	 expr = NULL;
     }
 }

  void SetCallback(SEXP fun, SEXP args = NULL) {
	  if(expr == NULL) {
	      int i, n;
	      // do we need to copy/duplicate these arguments and fun objects. 
	      // No as we preserve the expression that contains them.
	      n = args != NULL ? LENGTH(args) : 0;
	      // allocate for the function, the event and the n args.
	      expr = allocVector(LANGSXP, 2 + n);
	      R_PreserveObject(expr);
	      if(n > 0) {
		  SEXP ptr = CDR(CDR(expr));
		  for(i = 0; i < n; i++) {
		      SETCAR(ptr, VECTOR_ELT(args, i));
		      ptr = CDR(ptr);
		  }
	      }
	  } 
	  SETCAR(expr, fun);
  }

  void invoke(wxEvent& ev); 
 
  void Disconnect();

 protected:
      SEXP expr;
      int id;
      wxEventType eventType;
      wxEvtHandler *widget;
      bool addEventClass;
};
