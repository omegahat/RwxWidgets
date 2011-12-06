#include <wx/spinbutt.h>
#include "RwxUtils.h"

extern "C" {

   SEXP R_wxSpinButton_new(SEXP r_parent, SEXP r_id, SEXP r_style, SEXP r_name);

   SEXP R_wxSpinButton_GetMax(SEXP r_this);
   SEXP R_wxSpinButton_GetMin(SEXP r_this);
   SEXP R_wxSpinButton_GetValue(SEXP r_this);
   SEXP R_wxSpinButton_SetRange(SEXP r_this, SEXP r_min, SEXP r_max);
   SEXP R_wxSpinButton_SetValue(SEXP r_this, SEXP r_value);
}


SEXP
R_wxSpinButton_new(SEXP r_parent, SEXP r_id, SEXP r_style, SEXP r_name)
{
  wxWindow *parent;
  wxWindowID id;
  wxSpinButton *ans;
  SEXP r_ans;
  wxString name;
  long style;

  style = (long) REAL(r_style)[0];

  ans = new wxSpinButton(parent, id, wxDefaultPosition, wxDefaultSize, style, name);
  r_ans = R_make_wxWidget_Ref(ans, "wxSpinButton");

  return(r_ans);
}


SEXP
R_wxSpinButton_GetMax(SEXP r_this)
{
  wxSpinButton *btn = GET_RWX_REF(r_this, wxSpinButton);
  int value;
  SEXP ans;

  value = btn->GetMax();
  ans = ScalarInteger(value);

  return(ans);
}

SEXP
R_wxSpinButton_GetMin(SEXP r_this)
{
  wxSpinButton *btn = GET_RWX_REF(r_this, wxSpinButton);
  int value;
  SEXP ans;

  value = btn->GetMin();
  ans = ScalarInteger(value);

  return(ans);
}


SEXP
R_wxSpinButton_GetValue(SEXP r_this)
{
  wxSpinButton *btn = GET_RWX_REF(r_this, wxSpinButton);
  int value;
  SEXP ans;

  value = btn->GetValue();
  ans = ScalarInteger(value);

  return(ans);
}


SEXP
R_wxSpinButton_SetRange(SEXP r_this, SEXP r_min, SEXP r_max)
{
  wxSpinButton *btn = GET_RWX_REF(r_this, wxSpinButton);
  int min, max;
  SEXP ans = R_NilValue;

  min = INTEGER(r_min)[0];
  max = INTEGER(r_max)[0];

  btn->SetRange(min, max);

  return(ans);
}

SEXP 
R_wxSpinButton_SetValue(SEXP r_this, SEXP r_value)
{
  wxSpinButton *slider = GET_RWX_REF(r_this, wxSpinButton);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetValue(value);

  return(ans);
}

