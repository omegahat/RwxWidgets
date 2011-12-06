#include <wx/checkbox.h>
#include "RwxUtils.h"

extern "C" {
SEXP R_wxCheckBox_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_validator, SEXP r_name);
SEXP  R_wxCheckBox_IsChecked(SEXP r_check);
SEXP R_wxCheckBox_SetValue(SEXP r_check, SEXP r_value);
SEXP R_wxCheckBox_GetValue(SEXP r_check);
}

SEXP
R_wxCheckBox_new(SEXP r_parent, SEXP r_id, SEXP r_label, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxString label = R_to_wxString(r_label);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    long style = (long) REAL(r_style)[0];
    const wxValidator &validator = wxDefaultValidator;
    const wxString name = R_to_wxString(r_name);    

    wxCheckBox *ans = new wxCheckBox(parent, id, label, pos, size, style, validator, name);
    return(R_make_wxWidget_Ref(ans, "wxCheckBox"));
}

SEXP 
R_wxCheckBox_IsChecked(SEXP r_check) 
{
    DECLARE_RWX_REF(check, wxCheckBox);
    bool ans = check->IsChecked();
    return(ScalarLogical(ans));
}

SEXP 
R_wxCheckBox_SetValue(SEXP r_check, SEXP r_value) 
{
    DECLARE_RWX_REF(check, wxCheckBox);
    bool value = LOGICAL(r_value)[0];
    check->SetValue(value);
    return(R_NilValue);
}    


SEXP 
R_wxCheckBox_GetValue(SEXP r_check) 
{
    DECLARE_RWX_REF(check, wxCheckBox);
    bool ans = check->GetValue();
    return(ScalarLogical(ans));
}
