#include <wx/radiobut.h>
#include "RwxUtils.h"

extern "C" {
SEXP R_wxRadioButton_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_validator, SEXP r_name);
SEXP R_wxRadioButton_SetValue(SEXP r_check, SEXP r_value);
SEXP R_wxRadioButton_GetValue(SEXP r_check);
}

SEXP
R_wxRadioButton_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxString label = R_to_wxString(r_label);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    long style = (long) REAL(r_style)[0];
    const wxValidator &validator = wxDefaultValidator;
    const wxString name = R_to_wxString(r_name);    

    wxRadioButton *ans = new wxRadioButton(parent, id, label, pos, size, style, validator, name);
    return(R_make_wxWidget_Ref(ans, "wxRadioButton"));
}


SEXP 
R_wxRadioButton_SetValue(SEXP r_check, SEXP r_value) 
{
    DECLARE_RWX_REF(check, wxRadioButton);
    bool value = LOGICAL(r_value)[0];
    check->SetValue(value);
    return(R_NilValue);
}    


SEXP 
R_wxRadioButton_GetValue(SEXP r_check) 
{
    DECLARE_RWX_REF(check, wxRadioButton);
    bool ans = check->GetValue();
    return(ScalarLogical(ans));
}
