#include <wx/combobox.h>
#include "RwxUtils.h"

extern "C" {

SEXP
R_wxComboBox_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_pos,
                 SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator,
                 SEXP r_name);

    SEXP R_wxComboBox_GetValue(SEXP r_combo);
    SEXP R_wxComboBox_SetSelection(SEXP r_combo, SEXP r_from, SEXP r_to);
};

SEXP
R_wxComboBox_new(SEXP r_parent, SEXP r_id, SEXP r_value, SEXP r_pos,
                 SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator,
                 SEXP r_name)

{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxString value = R_to_wxString(r_value);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    int n;
    long style = (long) REAL(r_style)[0];
    const wxValidator &validator = wxDefaultValidator;
    const wxString name = R_to_wxString(r_name);

#if 1
    wxArrayString choices;
    RtowxArrayString(r_choices, choices);

    wxComboBox *ans = new wxComboBox(parent, id, value, pos, size, choices, style, validator, name);
#else
    wxString *choices   = (wxString *) R_alloc(n, sizeof(wxString));
    for(int i = 0; i < n ; i++) {
        const char *tmp = CHAR(STRING_ELT(r_choices, i));
        choices[i] = wxString(tmp, wxConvUTF8);
    }
    wxComboBox *ans = new wxComboBox(parent, id, value, pos, size, n, choices, style, validator, name);
#endif


    // free the strings.

    return(R_make_wxWidget_Ref(ans, "wxComboBox"));
}

extern "C"
SEXP
R_wxComboBox_GetValue(SEXP r_combo)
{
    DECLARE_RWX_REF(combo, wxComboBox);
    wxString ans = combo->GetValue();

    SEXP r_ans = wxStringToR(ans);
    return(r_ans);
}


extern "C"
SEXP
R_wxComboBox_SetValue(SEXP r_combo, SEXP r_text)
{
    DECLARE_RWX_REF(combo, wxComboBox);
    wxString text =R_to_wxString(r_text);
    combo->SetValue(text);
    return(R_NilValue);
}



extern "C"
SEXP 
R_wxComboBox_SetSelection(SEXP r_combo, SEXP r_from, SEXP r_to)
{
        DECLARE_RWX_REF(combo, wxComboBox);
        long from = (long) REAL(r_from)[0];
        long to = (long) REAL(r_to)[0];
        combo->SetSelection(from, to);

        return(R_NilValue);
}
