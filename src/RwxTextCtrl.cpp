#include <wx/textctrl.h>

#include "RwxUtils.h"

extern "C" {
    SEXP R_wxTextCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_style, SEXP r_name, SEXP r_size);
 SEXP R_wxTextCtrl_AppendText(SEXP r_textctrl, SEXP r_text);
 SEXP R_wxTextCtrl_Clear(SEXP r_textctrl, SEXP r_text);
 SEXP R_wxTextCtrl_GetInsertionPoint(SEXP r_textctrl);
 SEXP R_wxTextCtrl_GetLineLength(SEXP r_textctrl, SEXP r_line);
 SEXP R_wxTextCtrl_GetLineText(SEXP r_textctrl, SEXP r_line);
 SEXP R_wxTextCtrl_GetNumberOfLines(SEXP r_textctrl);
 SEXP R_wxTextCtrl_GetRange(SEXP r_textctrl, SEXP r_from, SEXP r_to);
 SEXP R_wxTextCtrl_GetStringSelection(SEXP r_textctrl);
 SEXP R_wxTextCtrl_GetValue(SEXP r_textctrl);
 SEXP R_wxTextCtrl_LoadFile(SEXP r_textctrl, SEXP r_filename);
 SEXP R_wxTextCtrl_SetEditable(SEXP r_textctrl, SEXP r_editable);
 SEXP R_wxTextCtrl_SetMaxLength(SEXP r_textctrl, SEXP r_maxlen);
 SEXP R_wxTextCtrl_SetValue(SEXP r_textctrl, SEXP r_value);
 SEXP R_wxTextCtrl_WriteText(SEXP r_textctrl, SEXP r_value);
 SEXP R_wxTextCtrl_IsMultiLine(SEXP r_textctrl);
}

SEXP R_wxTextCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_style, SEXP r_name, SEXP r_size)
{
 SEXP r_ans;
 wxWindow *parent = GET_RWX_REF(r_parent, wxWindow);
 wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
 wxString name = wxString(CHAR(STRING_ELT(r_name, 0)), wxConvUTF8);
 wxString value;
 wxSize sz = wxDefaultSize;
 long style = 0;
 wxTextCtrl *ans;

#if 1
 if(LENGTH(r_size))
     sz = R_to_wxSize(r_size);
#endif

 if(GET_LENGTH(r_value))
     value = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);
 else
     value = wxT("");


 if(GET_LENGTH(r_style))
     style = (long) REAL(r_style)[0];


 ans = new wxTextCtrl(parent, id, value, wxDefaultPosition, sz, style, wxDefaultValidator, name);
 r_ans = R_make_wxWidget_Ref(ans, "wxTextCtrl");

 return(r_ans);
}

SEXP R_wxTextCtrl_AppendText(SEXP r_textctrl, SEXP r_text)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;

  wxString str =  wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);

  textctrl->AppendText(str);
  return(r_ans);
}

SEXP 
R_wxTextCtrl_Clear(SEXP r_textctrl, SEXP r_text)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;

  textctrl->Clear();

  return(r_ans);
}

SEXP 
R_wxTextCtrl_GetInsertionPoint(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  long ans;

  ans = textctrl->GetInsertionPoint();
  r_ans = ScalarReal(ans);

  return(r_ans);
}


SEXP 
R_wxTextCtrl_GetLineLength(SEXP r_textctrl, SEXP r_line)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  long line = (long) REAL(r_line)[0];
  int ans;

  ans = textctrl->GetLineLength(line);
  r_ans = ScalarInteger(ans);

  return(r_ans);
}


SEXP 
R_wxTextCtrl_IsMultiLine(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  bool ans;
  ans = textctrl->IsMultiLine();
  r_ans = ScalarLogical(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_GetLineText(SEXP r_textctrl, SEXP r_line)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  long line = (long) REAL(r_line)[0];
  wxString ans;


  ans = textctrl->GetLineText(line);
  r_ans = wxStringToR(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_GetNumberOfLines(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  int ans;

  ans = textctrl->GetNumberOfLines();
  r_ans = ScalarInteger(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_GetRange(SEXP r_textctrl, SEXP r_from, SEXP r_to)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  long from, to;
  wxString ans;

  ans = textctrl->GetRange(from, to);
  r_ans = wxStringToR(ans);

  return(r_ans);
}


SEXP R_wxTextCtrl_GetStringSelection(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  wxString ans;

  ans = textctrl->GetStringSelection();
  r_ans = wxStringToR(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_GetValue(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  wxString ans;

  ans = textctrl->GetValue();
  r_ans = wxStringToR(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_LoadFile(SEXP r_textctrl, SEXP r_filename)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  wxString filename = wxString(CHAR(STRING_ELT(r_filename, 0)), wxConvUTF8);
  bool ans;

  ans = textctrl->LoadFile(filename);
  r_ans = ScalarLogical(ans);

  return(r_ans);
}

SEXP R_wxTextCtrl_SetEditable(SEXP r_textctrl, SEXP r_editable)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  bool editable = LOGICAL(r_editable)[0];

  textctrl->SetEditable(editable);

  return(r_ans);
}

SEXP R_wxTextCtrl_SetMaxLength(SEXP r_textctrl, SEXP r_maxlen)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  long maxlen = (long) REAL(r_maxlen)[0];

  textctrl->SetMaxLength(maxlen);

  return(r_ans);
}

SEXP R_wxTextCtrl_SetValue(SEXP r_textctrl, SEXP r_value)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  wxString value = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);

  textctrl->SetValue(value);

  return(r_ans);
}

SEXP R_wxTextCtrl_WriteText(SEXP r_textctrl, SEXP r_value)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);
  SEXP r_ans = R_NilValue;
  wxString value = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);

  textctrl->WriteText(value);

  return(r_ans);
}


extern "C"
SEXP 
R_wxTextCtrl_SetInsertionPoint(SEXP r_textctrl, SEXP r_pos)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);

  SEXP r_ans = R_NilValue;
  long pos = (long) asReal(r_pos);;
  textctrl->SetInsertionPoint(pos);

  return(r_ans);
}


extern "C"
SEXP 
R_wxTextCtrl_SetInsertionPointEnd(SEXP r_textctrl)
{
  DECLARE_RWX_REF(textctrl, wxTextCtrl);

  SEXP r_ans = R_NilValue;
  textctrl->SetInsertionPointEnd();

  return(r_ans);
}

