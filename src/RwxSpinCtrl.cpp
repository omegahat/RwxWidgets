#include <wx/spinctrl.h>
#include "RwxUtils.h"

extern "C" {

   SEXP R_wxSpinCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_style, 
                         SEXP r_min, SEXP r_max, SEXP r_initial, SEXP r_name);

   SEXP R_wxSpinCtrl_GetMax(SEXP r_this);
   SEXP R_wxSpinCtrl_GetMin(SEXP r_this);
   SEXP R_wxSpinCtrl_GetValue(SEXP r_this);
   SEXP R_wxSpinCtrl_SetRange(SEXP r_this, SEXP r_min, SEXP r_max);
   SEXP R_wxSpinCtrl_SetValue(SEXP r_this, SEXP r_value);
}


SEXP
R_wxSpinCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_style,
                 SEXP r_min, SEXP r_max, SEXP r_initial, SEXP r_name)
{
  wxWindowID id;
  wxSpinCtrl *ans;
  int min, max, initial;
  SEXP r_ans;
  wxString name;
  wxString value;
  long style;

  DECLARE_RWX_REF(parent, wxWindow);
  id = (wxWindowID) INTEGER(r_id)[0];
  value = R_to_wxString(r_value);
  style = (long) REAL(r_style)[0];
  min = INTEGER(r_min)[0];
  max = INTEGER(r_max)[0];
  initial = INTEGER(r_initial)[0];
  name = R_to_wxString(r_name);

  ans = new wxSpinCtrl(parent, id, value, wxDefaultPosition, wxDefaultSize, style, 
                       min, max, initial, name);
  r_ans = R_make_wxWidget_Ref(ans, "wxSpinCtrl");
  
  return(r_ans);
}


SEXP
R_wxSpinCtrl_GetMax(SEXP r_this)
{
  wxSpinCtrl *btn = GET_RWX_REF(r_this, wxSpinCtrl);
  int value;
  SEXP ans;

  value = btn->GetMax();
  ans = ScalarInteger(value);

  return(ans);
}

extern "C"
SEXP
R_wxSpinCtrl_GetMin(SEXP r_this)
{
  wxSpinCtrl *btn = GET_RWX_REF(r_this, wxSpinCtrl);
  int value;
  SEXP ans;

  value = btn->GetMin();
  ans = ScalarInteger(value);

  return(ans);
}


extern "C"
SEXP
R_wxSpinCtrl_GetValue(SEXP r_this)
{
  wxSpinCtrl *btn = GET_RWX_REF(r_this, wxSpinCtrl);
  int value;
  SEXP ans;

  value = btn->GetValue();
  ans = ScalarInteger(value);

  return(ans);
}


extern "C"
SEXP
R_wxSpinCtrl_SetRange(SEXP r_this, SEXP r_min, SEXP r_max)
{
  wxSpinCtrl *btn = GET_RWX_REF(r_this, wxSpinCtrl);
  int min, max;
  SEXP ans = R_NilValue;

  min = INTEGER(r_min)[0];
  max = INTEGER(r_max)[0];

  btn->SetRange(min, max);

  return(ans);
}

extern "C"
SEXP 
R_wxSpinCtrl_SetValue_int(SEXP r_this, SEXP r_value)
{
  wxSpinCtrl *slider = GET_RWX_REF(r_this, wxSpinCtrl);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetValue(value);

  return(ans);
}


extern "C"
SEXP 
R_wxSpinCtrl_SetValue_wxString(SEXP r_this, SEXP r_value)
{
  wxSpinCtrl *slider = GET_RWX_REF(r_this, wxSpinCtrl);
  int value;
  SEXP ans = R_NilValue;
 // wxString value = R_to_wxString(r_value);
 value = INTEGER(r_value)[0];

  slider->SetValue(value);

  return(ans);
}

