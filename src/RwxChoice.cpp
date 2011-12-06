#include <wx/wx.h>

#include "RwxUtils.h"

extern "C" {
   SEXP R_wxChoice_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator, SEXP r_name);
}


SEXP
R_wxChoice_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_choices, SEXP r_style, SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
    long style = (long) REAL(r_style)[0];
    wxChoice *ans;
    SEXP r_ans;

#if 0
    int n;
    n = GET_LENGTH(r_choices);
    wxString *choices   = (wxString *) calloc(n, sizeof(wxString)); //XX R_alloc
    for(int i = 0; i < n ; i++) {
        choices[i] = wxString(CHAR(STRING_ELT(r_choices, i)), wxConvUTF8);
    }
    ans = new wxChoice(parent, id, wxDefaultPosition, wxDefaultSize, n, choices, style);
#else
    wxArrayString choices = RcharacterToArrayString(r_choices);
    ans = new wxChoice(parent, id, wxDefaultPosition, wxDefaultSize, choices, style);
#endif

    r_ans = R_make_wxWidget_Ref(ans, "wxChoice");

    return(r_ans);
}
