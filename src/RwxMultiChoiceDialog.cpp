#include <wx/wx.h>
#include <wx/choicdlg.h>
#include "RwxUtils.h"


extern "C"
SEXP
R_wxMultiChoiceDialog_new(SEXP r_parent, SEXP r_message, SEXP r_caption,
                          SEXP r_choices, SEXP r_style, SEXP r_pos)
{
    DECLARE_RWX_REF_NULL_OK(parent, wxWindow);
    wxString message = R_to_wxString(r_message);
    wxString caption = R_to_wxString(r_caption);
    long style = (long) REAL(r_style)[0];
    wxPoint pos = wxDefaultPosition; 

    if(GET_LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);

    wxArrayString choices;
    RtowxArrayString(r_choices, choices);

    wxMultiChoiceDialog *ans = new wxMultiChoiceDialog(parent, message, caption, choices, style, pos);
    return(R_make_wxWidget_Ref(ans, "wxMultiChoiceDialog"));
}

extern "C"
SEXP 
R_wxMultiChoiceDialog_GetSelections(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxMultiChoiceDialog);
    wxArrayInt ans;
    SEXP r_ans = R_NilValue;

    ans = This->GetSelections();

    r_ans = wxArrayIntToR(ans);
    return(r_ans);
}




extern "C"
SEXP
R_wxSingleChoiceDialog_new(SEXP r_parent, SEXP r_message, SEXP r_caption,
                          SEXP r_choices, SEXP r_style, SEXP r_pos)
{
    DECLARE_RWX_REF_NULL_OK(parent, wxWindow);
    wxString message = R_to_wxString(r_message);
    wxString caption = R_to_wxString(r_caption);
    long style = (long) REAL(r_style)[0];
    wxPoint pos = wxDefaultPosition; 

    if(GET_LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);

    wxArrayString choices;
    RtowxArrayString(r_choices, choices);

    wxSingleChoiceDialog *ans = new wxSingleChoiceDialog(parent, message, caption, choices, NULL, style, pos);
    return(R_make_wxWidget_Ref(ans, "wxSingleChoiceDialog"));
}


extern "C"
SEXP 
R_wxSingleChoiceDialog_GetSelection(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxSingleChoiceDialog);
    int ans;
    SEXP r_ans = R_NilValue;

    ans = This->GetSelection();

    r_ans = ScalarInteger(ans);
    return(r_ans);
}
