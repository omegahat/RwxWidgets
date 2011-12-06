#include <wx/toolbar.h>
#include <wx/tbarbase.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_wxToolBar_AddTool_int_wxString_wxBitmap_wxString_wxItemKind(SEXP r_toolbar, SEXP r_id, SEXP r_label, SEXP r_bitmap, SEXP r_helpString, SEXP r_kind)
{
    DECLARE_RWX_REF(toolbar, wxToolBar);
    int id = INTEGER(r_id)[0];
    wxString label = R_to_wxString(r_label);
    DECLARE_RWX_REF(bitmap, wxBitmap);
    wxString helpString = R_to_wxString(r_helpString);
    wxItemKind kind = (wxItemKind) INTEGER(r_kind)[0];

    wxToolBarToolBase *ans;
    ans = toolbar->AddTool(id, label, *bitmap, helpString, kind);

    SEXP r_ans = R_make_wxWidget_Ref(ans, "wxToolBarTool");

    return(r_ans);
}


extern "C"
SEXP
R_wxToolBar_Realize(SEXP r_toolbar)
{
    DECLARE_RWX_REF(toolbar, wxToolBar);
    bool ans = toolbar->Realize();
    return(ScalarLogical(ans));
}
