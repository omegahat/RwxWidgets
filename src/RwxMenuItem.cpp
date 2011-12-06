#include <wx/wx.h>
#include <wx/menuitem.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_wxMenuItem_new(SEXP r_parentMenu, SEXP r_id, SEXP r_text, SEXP r_helpString, SEXP r_kind, SEXP r_subMenu)
{
    DECLARE_RWX_REF_NULL_OK(parentMenu, wxMenu);
    int id = INTEGER(r_id)[0];
    wxString text = R_to_wxString(r_text);
    wxString helpString = R_to_wxString(r_helpString);
    wxItemKind kind = (wxItemKind) INTEGER(r_kind)[0];
    wxMenu *subMenu = NULL;
    if(GET_LENGTH(r_subMenu))
        subMenu = (wxMenu *) R_get_wxWidget_Ref(r_subMenu, "wxMenu");
    
    wxMenuItem *ans = new wxMenuItem(parentMenu, id, text, helpString, kind, subMenu);
    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));

}

extern "C"
SEXP
R_wxMenuItem_GetId(SEXP r_menuItem)
{
    DECLARE_RWX_REF(menuItem, wxMenuItem);
    int ans = menuItem->GetId();
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxMenuItem_GetText(SEXP r_menuItem)
{
    DECLARE_RWX_REF(menuItem, wxMenuItem);
    wxString ans = menuItem->GetText();
    SEXP r_ans = wxStringToR(ans);
    return(r_ans);
}

extern "C"
SEXP
R_wxMenuItem_SetBitmap(SEXP r_menuItem, SEXP r_bmp)
{
    DECLARE_RWX_REF(menuItem, wxMenuItem);
    DECLARE_RWX_REF(bmp, wxBitmap);
    menuItem->SetBitmap(*bmp);
    return(R_NilValue);
}


#if 0 /* Windows only */
extern "C"
SEXP
R_wxMenuItem_SetBitmaps(SEXP r_menuItem, SEXP r_bmp, SEXP r_unchecked)
{
    DECLARE_RWX_REF(menuItem, wxMenuItem);
    DECLARE_RWX_REF(bmp, wxBitmap);
    DECLARE_RWX_REF(unchecked, wxBitmap);
    menuItem->SetBitmaps(*bmp, *unchecked);
    return(R_NilValue);
}
#endif
