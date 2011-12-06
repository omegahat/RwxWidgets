#include <wx/filedlg.h>
#include "RwxUtils.h"

extern "C" 
{
    SEXP R_wxFileDialog_new(SEXP r_parent, SEXP r_message, SEXP r_dir, SEXP r_file, SEXP r_wildcard, SEXP r_style, SEXP r_pos);
    SEXP R_wxFileDialog_GetPath(SEXP r_dialog);
}

SEXP
R_wxFileDialog_new(SEXP r_parent, SEXP r_message, SEXP r_dir, SEXP r_file, SEXP r_wildcard, SEXP r_style, SEXP r_pos)
{
    DECLARE_RWX_REF_NULL_OK(parent, wxWindow);
    wxString message;
    wxString dir, file, wildcard;
    long style = 0;
    wxPoint pos = wxDefaultPosition;
    wxFileDialog *ans;
    SEXP r_ans = R_NilValue;

    style = (long) REAL(r_style)[0];
    message = wxString(CHAR(STRING_ELT(r_message, 0)), wxConvUTF8);
    dir = wxString(CHAR(STRING_ELT(r_dir, 0)), wxConvUTF8);
    file = wxString(CHAR(STRING_ELT(r_file, 0)), wxConvUTF8);
    wildcard = wxString(CHAR(STRING_ELT(r_wildcard, 0)), wxConvUTF8);
       
    ans = new wxFileDialog(parent, message, dir, file, wildcard, style, pos);

    r_ans = R_make_wxWidget_Ref(ans, "wxFileDialog");

    return(r_ans);
}

/*
 Manual and more knowledgable than the basic interface
 as it can figure out the style being used and determine
 whether GetPaths or GetPath is to be used.
*/
SEXP
R_wxFileDialog_GetPath(SEXP r_dialog)
{
  DECLARE_RWX_REF(dialog, wxFileDialog);
  SEXP r_ans = R_NilValue;

  if(dialog->GetStyle() & wxMULTIPLE) {
      wxArrayString ans;
      dialog->GetPaths(ans);
      r_ans = wxStringArrayToR(ans);
  } else {
      wxString ans = dialog->GetPath();
      r_ans = wxStringToR(ans);
  }

  return(r_ans);
}


