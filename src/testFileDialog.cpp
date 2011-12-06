#include "TestFileDialog.h"

#include "RwxUtils.h"

extern "C"
SEXP
R_TestFileDialog(SEXP r_parent)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxTestFileDialog *ans;
    ans = new wxTestFileDialog(parent);


    SEXP r_ans = R_make_wxWidget_Ref(ans, "wxFileDialog");
    return(r_ans);
}

#include <stdio.h>
void 
wxTestFileDialog::OnOK(wxCommandEvent &ev)
{
    fprintf(stderr, "OnOk in wxTestFileDialog\n");fflush(stderr);
#if wxMINOR_VERSION < 8
    wxFileDialog::OnOK(ev);
#endif
}
