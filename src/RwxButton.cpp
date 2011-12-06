#include <wx/button.h>
#include "RwxUtils.h"
#include "RwxButton.h"

#include "RwxEvents.h"

extern "C" {
SEXP
R_wxButton_new(SEXP r_parent,
                SEXP r_id,
                SEXP r_label,
                SEXP r_pos,
                SEXP r_size,
                SEXP clickHandler,
                SEXP r_name
               );

SEXP R_wxButton_GetLabel(SEXP r_this);
SEXP R_wxButton_SetLabel(SEXP r_this, SEXP str);

}



SEXP
R_wxButton_new(SEXP r_parent,
                SEXP r_id,
                SEXP r_label,
                SEXP r_pos,
                SEXP r_size,
               SEXP clickHandler,
               SEXP r_name
               )
{

  wxWindow *parent;
  wxWindowID id;
  wxButton *ans;
  wxString label;
  wxString name;
  SEXP r_ans;

  parent = (wxWindow *) R_get_wxWidget_Ref(r_parent, NULL);
  id = INTEGER(r_id)[0];
  label = wxString(CHAR(STRING_ELT(r_label, 0)), wxConvUTF8);
  name = R_to_wxString(r_name);

/* Both approaches work. */
#define USE_RAW_BUTTON 1

#ifdef USE_RAW_BUTTON
  R_wxButton *rans;
  ans = new wxButton(parent, id, label, wxDefaultPosition, wxDefaultSize, (long) 0, wxDefaultValidator, name);
#else
  ans = rans = new R_wxButton(parent, id, label);
#endif

  if(Rf_length(clickHandler)) {


    /* The following is a test to see if we have to have the handler within
        the widget hierarchy. It appears we do. */
#ifndef USE_RAW_BUTTON
       rans->setClickHandler(clickHandler);
       rans->Connect(rans->GetId(), wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, 
  	 	     wxCommandEventHandler(R_wxButton::clicked));
#else

       R_wxEventHandler *handler = new R_wxEventHandler(clickHandler);

       ans->Connect(ans->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
                      wxEventHandler(R_wxEventHandler::invoke), NULL, handler);
#if 0
       handler->Connect(ans->GetId(), wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, 
                         wxEventHandler(R_wxEventHandler::invoke));
#endif
#endif

  }


  r_ans = R_make_wxWidget_Ref(ans, "RwxButton");

  return(r_ans);
}

void 
R_wxButton::clicked(wxCommandEvent &ev)
{
  SEXP e;
  int errorOccurred;

  PROTECT(e = allocVector(LANGSXP, 2));
  SETCAR(e, clickHandler);
  SETCAR(CDR(e), R_NilValue);

  R_tryEval(e, R_GlobalEnv, &errorOccurred);
 
}

SEXP 
R_wxButton_GetLabel(SEXP r_this)
{
  wxButton *b = GET_RWX_REF(r_this, wxButton);
  wxString str;
  SEXP ans;

  str = b->GetLabel();
  ans = wxStringToR(str);

  return(ans);
}

SEXP 
R_wxButton_SetLabel(SEXP r_this, SEXP r_str)
{
  wxButton *b = GET_RWX_REF(r_this, wxButton);
  wxString str = wxString(CHAR(STRING_ELT(r_str, 0)), wxConvUTF8);

  b->SetLabel(str);

  return(R_NilValue);
}
