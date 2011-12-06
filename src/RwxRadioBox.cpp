#include <wx/wx.h>
#include <wx/radiobox.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxRadioBox_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_point, SEXP r_size, SEXP r_choices,
                          SEXP r_majorDimension, SEXP r_style, SEXP r_validator, SEXP r_name);
    SEXP R_wxRadioBox_GetStringSelection(SEXP r_This);                           
    SEXP R_wxRadioBox_GetSelection(SEXP r_This);                           
}

SEXP 
R_wxRadioBox_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_point, SEXP r_size, SEXP r_choices,
                       SEXP r_majorDimension, SEXP r_style, SEXP r_validator, SEXP r_name)
{

    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = INTEGER(r_id)[0];
    wxString label = R_to_wxString(r_label);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    int majorDimension = INTEGER(r_majorDimension)[0];
    long style = (long) REAL(r_style)[0];
    const wxValidator &validator = wxDefaultValidator;
    wxString name = R_to_wxString(r_name);

    wxArrayString choices = RcharacterToArrayString(r_choices);
    wxRadioBox *ans = new wxRadioBox(parent, id, label, pos, size, choices, majorDimension,  style, validator, name);

    SEXP r_ans = R_make_wxWidget_Ref(ans, "wxListBox");

    return(r_ans);
}


SEXP
R_wxRadioBox_GetStringSelection(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxRadioBox);
    wxString ans;
    ans = This->GetStringSelection();
    return(wxStringToR(ans));
}                           

SEXP 
R_wxRadioBox_GetSelection(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxRadioBox);
    int ans;
    ans = This->GetSelection();
    return(ScalarInteger(ans));
}                           

SEXP 
R_wxRadioBox_GetLabel(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxRadioBox);
    wxString ans;
    ans = This->GetLabel();

    return(wxStringToR(ans));
}                           


SEXP 
R_wxRadioBox_SetLabel(SEXP r_This, SEXP r_label)
{
    DECLARE_RWX_REF(This, wxRadioBox);

    wxString label = R_to_wxString(r_label);
    This->SetLabel(label);

    return(R_NilValue);
}                           
