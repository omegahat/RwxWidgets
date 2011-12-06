#include <wx/treectrl.h>

#include "RwxUtils.h"

SEXP
wxTreeItemId_to_R(wxTreeItemId id)
{
    return(R_make_wx_Ref(new wxTreeItemId(id), "wxTreeItemId"));
}

extern "C"
SEXP 
R_wxTreeCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, 
                 SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
    long style =  (long) REAL(r_style)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize; 
    const wxValidator *validator = &wxDefaultValidator;
    wxString name = R_to_wxString(r_name);

    if(GET_LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);
    if(GET_LENGTH(r_size)) size = R_to_wxSize(r_size);

    wxTreeCtrl *ans = new wxTreeCtrl(parent, id, pos, size, style, *validator, name);
    SEXP r_ans = R_make_wxWidget_Ref(ans, "wxTreeCtrl");
    return(r_ans);
}

extern "C"
SEXP 
R_wxTreeCtrl_AddRoot(SEXP r_tree, SEXP r_text, SEXP r_image, SEXP r_selImage, SEXP r_data)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    wxString text = R_to_wxString(r_text);    
    int image = INTEGER(r_image)[0];
    int selImage = INTEGER(r_selImage)[0];
    wxTreeItemData *data = NULL;//XXX

    wxTreeItemId tmp = tree->AddRoot(text, image, selImage, data);
    return(wxTreeItemId_to_R(tmp));
}



extern "C"
SEXP 
R_wxTreeCtrl_AppendItem(SEXP r_tree, SEXP r_parent, SEXP r_text, SEXP r_image, SEXP r_selImage, SEXP r_data)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(parent, wxTreeItemId);
    wxString text = R_to_wxString(r_text);    
    int image = INTEGER(r_image)[0];
    int selImage = INTEGER(r_selImage)[0];
    wxTreeItemData *data = NULL;//XXX

    wxTreeItemId tmp = tree->AppendItem(*parent, text, image, selImage, data);
/*
    wxGenericTreeItem *duncan = static_cast< wxGenericTreeItem *> (tree->AppendItem(*parent, text, image, selImage, data));
*/
    SEXP r_ans = wxTreeItemId_to_R(tmp);

    return(r_ans);
}


extern "C"
SEXP 
R_wxTreeCtrl_InsertItem(SEXP r_tree, SEXP r_parent, SEXP r_previous, SEXP r_text, 
                        SEXP r_image, SEXP r_selImage, SEXP r_data)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(parent, wxTreeItemId);
    DECLARE_RWX_REF(previous, wxTreeItemId);
    wxString text = R_to_wxString(r_text);    
    int image = INTEGER(r_image)[0];
    int selImage = INTEGER(r_selImage)[0];
    wxTreeItemData *data = NULL;//XXX

    wxTreeItemId tmp = tree->InsertItem(*parent, *previous, text, image, selImage, data);
    return(wxTreeItemId_to_R(tmp));
}


extern "C"
SEXP 
R_wxTreeCtrl_AssignImageList(SEXP r_tree, SEXP r_imageList)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(imageList, wxImageList);

    tree->AssignImageList(imageList);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_AssignButtonsImageList(SEXP r_tree, SEXP r_imageList)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(imageList, wxImageList);

    tree->AssignButtonsImageList(imageList);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_SetImageList(SEXP r_tree, SEXP r_imageList)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(imageList, wxImageList);

    tree->SetImageList(imageList);

    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_EnsureVisible(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    tree->EnsureVisible(*item);
    return(R_NilValue);
}


extern "C"
SEXP 
R_wxTreeCtrl_ScrollTo(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    tree->ScrollTo(*item);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_Toggle(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    tree->Toggle(*item);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_Expand(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    tree->Expand(*item);
    return(R_NilValue);
}


extern "C"
SEXP 
R_wxTreeCtrl_Collapse(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    tree->Collapse(*item);
    return(R_NilValue);
}



extern "C"
SEXP 
R_wxTreeItemId_IsOk(SEXP r_item)
{
    DECLARE_RWX_REF(item, wxTreeItemId);
    bool ans = item->IsOk();
    return(ScalarLogical(ans));
}



extern "C"
SEXP 
R_wxTreeCtrl_GetItemText(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);

    if(!item->IsOk()) {
        PROBLEM "wxTreeItemId is not valid"
            ERROR
    }

    wxString ans = tree->GetItemText(*item);

    return(wxStringToR(ans));
}


extern "C"
SEXP 
R_wxTreeCtrl_GetItemParent(SEXP r_tree, SEXP r_item)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);

    wxTreeItemId tmp = tree->GetItemParent(*item);
    return(wxTreeItemId_to_R(tmp));
}


extern "C"
SEXP 
R_wxTreeCtrl_SetItemImage(SEXP r_tree, SEXP r_item, SEXP r_index, SEXP r_which)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    int index = INTEGER(r_index)[0];
    wxTreeItemIcon which = (wxTreeItemIcon) INTEGER(r_which)[0];

    tree->SetItemImage(*item, index, which);

    return(R_NilValue);
}

#if 0
// Deprecated
extern "C"
SEXP 
R_wxTreeCtrl_SetItemSelectedImage(SEXP r_tree, SEXP r_item, SEXP r_index)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    int index = INTEGER(r_index)[0];

    tree->SetItemSelectedImage(*item, index);

    return(R_NilValue);
}
#endif

extern "C"
SEXP 
R_wxTreeCtrl_SetItemBackgroundColour(SEXP r_tree, SEXP r_item, SEXP r_colour)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    const wxColour *colour = wxRED;
    if(GET_LENGTH(r_colour))
        colour = (const wxColour *) R_get_wxWidget_Ref(r_colour, "wxColour");

    tree->SetItemBackgroundColour(*item, *colour);

    return(R_NilValue);
}

extern "C"
SEXP 
R_wxTreeCtrl_SetItemTextColour(SEXP r_tree, SEXP r_item, SEXP r_colour)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    DECLARE_RWX_REF(item, wxTreeItemId);
    const wxColour *colour = wxBLUE;
    if(GET_LENGTH(r_colour))
        colour = (const wxColour *) R_get_wxWidget_Ref(r_colour, "wxColour");

    tree->SetItemTextColour(*item, *colour);

    return(R_NilValue);
}


extern "C"
SEXP 
R_wxTreeCtrl_HitTest(SEXP r_tree, SEXP r_point)
{
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    wxPoint point = R_to_wxPoint(r_point);
    int flags;
    wxTreeItemId ans = tree->HitTest(point, flags);
    SEXP r_ans, r_names;

    PROTECT(r_ans = NEW_LIST(2));
    PROTECT(r_names = NEW_CHARACTER(2));
    SET_VECTOR_ELT(r_ans, 0, wxTreeItemId_to_R(ans));
    SET_VECTOR_ELT(r_ans, 1, ScalarInteger(flags));
    SET_STRING_ELT(r_names, 0, mkChar(".result"));
    SET_STRING_ELT(r_names, 1, mkChar("flags"));
    SET_NAMES(r_ans, r_names);
    UNPROTECT(2);
    return(r_ans);
}






extern "C"
SEXP 
R_wxTreeEvent_mine(SEXP r_event, SEXP r_tree)
{
    DECLARE_RWX_REF(event, wxTreeEvent);
    DECLARE_RWX_REF(tree, wxTreeCtrl);
    wxTreeItemId item = event->GetItem();

    wxString ans = tree->GetItemText(item);
    return(wxStringToR(ans));
}





extern "C"
SEXP 
R_wxTreeEvent_GetItem(SEXP r_event)
{
    DECLARE_RWX_REF(event, wxTreeEvent);
    wxTreeItemId tmp = event->GetItem();

    wxTreeItemId *ans = new wxTreeItemId(tmp);
    return(R_make_wx_Ref(ans, "wxTreeItemId"));
}


extern "C"
SEXP 
R_wxNotifyEvent_Allow(SEXP r_event)
{
    DECLARE_RWX_REF(event, wxNotifyEvent);
    event->Allow();
    return(R_NilValue);
}

extern "C"
SEXP
R_wxTreeCtrl_GetSelections(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxTreeCtrl);
    int i, n;
    wxArrayTreeItemIds els;

    n = This->GetSelections(els);

    if(n == 0)
        return(R_NilValue);

    SEXP r_ans;
    PROTECT(r_ans = NEW_LIST(n));
    for(i = 0 ;  i < n ; i++) {
        SET_VECTOR_ELT(r_ans, i, wxTreeItemId_to_R(els[i]));
    }
    return(r_ans);
}
