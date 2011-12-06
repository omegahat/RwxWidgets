#include <wx/listbox.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxListBox_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator, SEXP r_name);
    SEXP R_wxListBox_GetSelections(SEXP r_This);
    SEXP R_wxListBox_IsSelected(SEXP r_This, SEXP r_n);
    SEXP R_wxListBox_InsertItems(SEXP r_This, SEXP r_items, SEXP r_pos);

    SEXP R_wxListBox_SetFirstItem_int(SEXP r_This, SEXP r_n);
    SEXP R_wxListBox_SetFirstItem_wxString(SEXP r_This, SEXP r_string);
}

SEXP
R_wxListBox_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
    long style = (long) REAL(r_style)[0];
    wxListBox *ans;
    SEXP r_ans;

#if 0
    int n;
    n = GET_LENGTH(r_choices);
    wxString *choices   = (wxString *) calloc(n, sizeof(wxString)); //XX R_alloc
    for(int i = 0; i < n ; i++) {
        choices[i] = wxString(CHAR(STRING_ELT(r_choices, i)), wxConvUTF8);
    }
    ans = new wxListBox(parent, id, wxDefaultPosition, wxDefaultSize, n, choices, style);
#else
    wxArrayString choices = RcharacterToArrayString(r_choices);
    ans = new wxListBox(parent, id, wxDefaultPosition, wxDefaultSize, choices, style);
#endif

    r_ans = R_make_wxWidget_Ref(ans, "wxListBox");

    return(r_ans);
}

SEXP R_wxListBox_InsertItems(SEXP r_This, SEXP r_items, SEXP r_pos)
{
    DECLARE_RWX_REF(This, wxListBox);
    SEXP r_ans = R_NilValue;
    wxArrayString items;

    int pos = INTEGER(r_pos)[0];

    items = RcharacterToArrayString(r_items);

    This->InsertItems(items, pos);

    return(r_ans);
}

SEXP 
R_wxListBox_IsSelected(SEXP r_This, SEXP r_n)
{
    DECLARE_RWX_REF(This, wxListBox);
    int n = INTEGER(r_n)[0];
    bool ans;
    ans = This->IsSelected(n);
    return(ScalarLogical(ans));
}

SEXP 
R_wxListBox_GetSelections(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxListBox);
    int count;
    wxArrayInt ans;
    SEXP r_ans = R_NilValue;

    count = This->GetSelections(ans);

    r_ans = wxArrayIntToR(ans);
    return(r_ans);
}

extern "C"
SEXP 
R_wxListBox_Set(SEXP r_This, SEXP r_choices)
{
    DECLARE_RWX_REF(This, wxListBox);
    wxArrayString choices;
    choices = RcharacterToArrayString(r_choices);
    This->Set(choices);
    return(R_NilValue);
}







