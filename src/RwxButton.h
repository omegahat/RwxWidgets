#include "RwxUtils.h"
#include <wx/button.h>

#include <stdio.h>

class R_wxButton : public wxButton {

 public:
  R_wxButton(): wxButton() {};
  R_wxButton(wxWindow *parent, 
             wxWindowID id,
             const wxString& label = wxEmptyString,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long int style = 0,
             const wxValidator& validator = wxDefaultValidator,
             const wxString& name = wxButtonNameStr)
    : wxButton(parent, id, label, pos, size, style, validator, name) {};

  virtual void setClickHandler(SEXP fun) {
    fprintf(stderr, "setting button handler\n");
    clickHandler = fun;
    R_PreserveObject(clickHandler);
  }

 void clicked(wxCommandEvent &ev);

 protected :
  SEXP clickHandler;

 private:
  DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(R_wxButton, wxButton)
     EVT_BUTTON(wxEVT_COMMAND_BUTTON_CLICKED, R_wxButton::clicked)
END_EVENT_TABLE()

