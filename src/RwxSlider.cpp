#include <wx/slider.h>

#include "RwxUtils.h"

extern "C" {

  SEXP R_wxSlider_GetValue(SEXP r_this);
  SEXP R_wxSlider_SetValue(SEXP r_this, SEXP r_value);
  SEXP R_wxSlider_SetThumbLength(SEXP r_this, SEXP r_len);

  SEXP R_wxSlider_GetMin(SEXP r_this);
  SEXP R_wxSlider_GetMax(SEXP r_this);  
  SEXP R_wxSlider_GetPageSize(SEXP r_this);  
  SEXP R_wxSlider_SetMin(SEXP r_this, SEXP r_value);
  SEXP R_wxSlider_SetMax(SEXP r_this, SEXP r_value);
  SEXP R_wxSlider_SetPageSize(SEXP r_this, SEXP r_value);

}

extern "C"
SEXP
R_wxSlider_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_min, SEXP r_max, SEXP r_pos, SEXP r_size, SEXP r_style)
{
  wxWindow *parent;
  wxWindowID id;
  wxSlider *ans;
  SEXP r_ans;
  int value, min, max;
  long style;
  wxPoint pos = wxDefaultPosition;
  wxSize size = wxDefaultSize;

  parent = (wxWindow *) R_get_wxWidget_Ref(r_parent, NULL);
  id = INTEGER(r_id)[0];

  value = INTEGER(r_value)[0];
  min = INTEGER(r_min)[0];
  max = INTEGER(r_max)[0];

  style = (long) REAL(r_style)[0];

  if(GET_LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);
  if(GET_LENGTH(r_size)) size = R_to_wxSize(r_size);

  ans = new wxSlider(parent, id, value, min, max, pos, size, style);

  r_ans = R_make_wxWidget_Ref(ans, "wxSlider");
  
  return(r_ans);
}

SEXP
R_wxSlider_GetValue(SEXP r_this)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans;

  value = slider->GetValue();
  ans = ScalarInteger(value);

  return(ans);
}

SEXP 
R_wxSlider_SetValue(SEXP r_this, SEXP r_value)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetValue(value);

  return(ans);
}


SEXP 
R_wxSlider_SetThumbLength(SEXP r_this, SEXP r_len)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int len;
  SEXP ans = R_NilValue;

  len = INTEGER(r_len)[0];
  slider->SetThumbLength(len);

  return(ans);
}


SEXP
R_wxSlider_GetMin(SEXP r_this)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans;

  value = slider->GetMin();
  ans = ScalarInteger(value);

  return(ans);
}


SEXP
R_wxSlider_SetMin(SEXP r_this, SEXP r_value)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetMin(value);

  return(ans);
}

SEXP
R_wxSlider_GetMax(SEXP r_this)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans;

  value = slider->GetMax();
  ans = ScalarInteger(value);

  return(ans);
}


SEXP
R_wxSlider_SetMax(SEXP r_this, SEXP r_value)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetMax(value);

  return(ans);
}


SEXP
R_wxSlider_GetPageSize(SEXP r_this)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans;

  value = slider->GetPageSize();
  ans = ScalarInteger(value);

  return(ans);
}


SEXP
R_wxSlider_SetPageSize(SEXP r_this, SEXP r_value)
{
  wxSlider *slider = GET_RWX_REF(r_this, wxSlider);
  int value;
  SEXP ans = R_NilValue;

  value = INTEGER(r_value)[0];
  slider->SetPageSize(value);

  return(ans);
}

