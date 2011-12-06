#include <wx/menu.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxMenu_new(SEXP r_title, SEXP r_style)
{
    wxString title = R_to_wxString(r_title);
    long style = (long) REAL(r_style)[0];

    wxMenu *ans = new wxMenu(title, style);
    return(R_make_wxWidget_Ref(ans, "wxMenu"));
}


extern "C"
SEXP
R_wxMenu_AppendSeparator(SEXP r_menu)
{
    DECLARE_RWX_REF(menu, wxMenu);
    wxMenuItem *ans = menu->AppendSeparator();

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}


extern "C"
SEXP
R_wxMenu_AppendCheckItem(SEXP r_menu, SEXP r_id, SEXP r_item, SEXP r_helpString)
{
    DECLARE_RWX_REF(menu, wxMenu);

    int id = INTEGER(r_id)[0];
    wxString item = R_to_wxString(r_item);
    wxString helpString = R_to_wxString(r_helpString);

    wxMenuItem *ans = menu->AppendCheckItem(id, item, helpString);

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}


extern "C"
SEXP
R_wxMenu_AppendRadioItem(SEXP r_menu, SEXP r_id, SEXP r_item, SEXP r_helpString)
{
    DECLARE_RWX_REF(menu, wxMenu);

    int id = INTEGER(r_id)[0];
    wxString item = R_to_wxString(r_item);
    wxString helpString = R_to_wxString(r_helpString);

    wxMenuItem *ans = menu->AppendRadioItem(id, item, helpString);

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}


extern "C"
SEXP
R_wxMenu_Append_int_wxString_wxString_wxItemKind(SEXP r_menu, SEXP r_id, SEXP r_item, SEXP r_helpString, SEXP r_kind)
{
    DECLARE_RWX_REF(menu, wxMenu);

    int id = INTEGER(r_id)[0];
    wxString item = R_to_wxString(r_item);
    wxString helpString = R_to_wxString(r_helpString);
    wxItemKind kind = (wxItemKind) INTEGER(r_kind)[0];

    wxMenuItem *ans = menu->Append(id, item, helpString, kind);

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}


extern "C"
SEXP
R_wxMenu_Append_int_wxString_wxMenu_wxString(SEXP r_menu, SEXP r_id, SEXP r_item, SEXP r_subMenu, SEXP r_helpString)
{
    DECLARE_RWX_REF(menu, wxMenu);

    int id = INTEGER(r_id)[0];
    wxString item = R_to_wxString(r_item);
    DECLARE_RWX_REF(subMenu, wxMenu);
    wxString helpString = R_to_wxString(r_helpString);

    wxMenuItem *ans = menu->Append(id, item, subMenu, helpString);

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}


extern "C"
SEXP
R_wxMenu_Append_wxMenuItem(SEXP r_menu, SEXP r_menuItem)
{
    DECLARE_RWX_REF(menu, wxMenu);
    DECLARE_RWX_REF(menuItem, wxMenuItem);

    wxMenuItem *ans = menu->Append(menuItem);

    return(R_make_wxWidget_Ref(ans, "wxMenuItem"));
}





extern "C"
SEXP
R_wxMenu_Delete_wxMenuItem(SEXP r_menu, SEXP r_item)
{
    DECLARE_RWX_REF(menu, wxMenu);
    DECLARE_RWX_REF(item, wxMenuItem);
    menu->Delete(item);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxMenu_Delete_int(SEXP r_menu, SEXP r_id)
{
    DECLARE_RWX_REF(menu, wxMenu);
    int id = INTEGER(r_id)[0];
    menu->Delete(id);
    return(R_NilValue);
}


extern "C"
SEXP
R_wxMenu_Enable(SEXP r_menu, SEXP r_id, SEXP r_enable)
{
    DECLARE_RWX_REF(menu, wxMenu);
    int id = INTEGER(r_id)[0];
    bool enable = LOGICAL(r_enable)[0];
    menu->Enable(id, enable);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxMenu_Check(SEXP r_menu, SEXP r_id, SEXP r_check)
{
    DECLARE_RWX_REF(menu, wxMenu);
    int id = INTEGER(r_id)[0];
    bool check = LOGICAL(r_check)[0];
    menu->Check(id, check);
    return(R_NilValue);
}


