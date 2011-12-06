#include <wx/wx.h>
#include <wx/icon.h>

#include "RwxUtils.h"


extern "C"
SEXP
R_wxIcon_new_wxString_wxBitmapType_int_int(SEXP r_name, SEXP r_type, SEXP r_desiredWidth, SEXP r_desiredHeight)
{

    wxString name = R_to_wxString(r_name);
    wxBitmapType type = (wxBitmapType) INTEGER(r_type)[0];
    int desiredWidth = INTEGER(r_desiredWidth)[0];
    int desiredHeight = INTEGER(r_desiredHeight)[0];

    wxIcon *ans;

    ans = new wxIcon(name, type, desiredWidth, desiredHeight);

    return(R_make_wxWidget_Ref(ans, "wxIcon"));
}


extern "C"
SEXP
R_wxIcon_LoadFile(SEXP r_icon, SEXP r_name, SEXP r_type)
{
    DECLARE_RWX_REF(icon, wxIcon);
    wxString name = R_to_wxString(r_name);
    wxBitmapType type = (wxBitmapType) INTEGER(r_type)[0];

    bool ans = icon->LoadFile(name, type);

    return(ScalarLogical(ans));
}

extern "C"
SEXP
R_wxIcon_Ok(SEXP r_icon)
{
    DECLARE_RWX_REF(icon, wxIcon);

    bool ans = icon->Ok();

    return(ScalarLogical(ans));
}
