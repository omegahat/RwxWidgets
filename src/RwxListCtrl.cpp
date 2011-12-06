#include <wx/listctrl.h>

#include "RwxUtils.h"

extern "C" 
SEXP
R_wxListCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, 
                 SEXP r_style, SEXP r_validator, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    
    long style = (long) REAL(r_style)[0];
    const wxValidator &validator = wxDefaultValidator;
    const wxString name = R_to_wxString(r_name);

    if(LENGTH(r_size))
        size = R_to_wxSize(r_size);
    if(LENGTH(r_pos))
        pos = wxPoint(INTEGER(r_pos)[0], INTEGER(r_pos)[1]);

    wxListCtrl *ans = new wxListCtrl(parent, id, pos, size, style, validator, name);
    return(R_make_wxWidget_Ref(ans, "wxListCtrl"));

}

extern "C"
SEXP 
R_wxListCtrl_InsertItem_long_wxString(SEXP r_list, SEXP r_index, SEXP r_label)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    
    long index = (long) REAL(r_index)[0];
    wxString label = R_to_wxString(r_label);
    long ans = list->InsertItem(index, label);
    return(ScalarReal(ans));
}

extern "C"
SEXP 
R_wxListCtrl_InsertItem_long_int(SEXP r_list, SEXP r_index, SEXP r_imageIndex)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    
    long index = (long) REAL(r_index)[0];
    int  imageIndex =  INTEGER(r_imageIndex)[0];

    long ans = list->InsertItem(index, imageIndex);

    return(ScalarReal(ans));
}

extern "C"
SEXP 
R_wxListCtrl_InsertItem_long_wxString_int(SEXP r_list, SEXP r_index, SEXP r_label, SEXP r_imageIndex)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    
    long index = (long) REAL(r_index)[0];
    wxString label = R_to_wxString(r_label);
    int  imageIndex =  INTEGER(r_imageIndex)[0];

    long ans = list->InsertItem(index, label, imageIndex);

    return(ScalarReal(ans));
}

extern "C"
SEXP 
R_wxListCtrl_SetItem_long_int_wxString_int(SEXP r_list, SEXP r_index, SEXP r_col, SEXP r_label, SEXP r_imageIndex)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    
    long index = (long) REAL(r_index)[0];
    int col = INTEGER(r_col)[0];
    wxString label = R_to_wxString(r_label);
    int  imageIndex =  INTEGER(r_imageIndex)[0];

    long ans = list->SetItem(index, col, label, imageIndex);

    return(ScalarReal(ans));
}




extern "C"
SEXP 
R_wxListCtrl_SetImageList(SEXP r_list, SEXP r_imageList, SEXP r_which)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    DECLARE_RWX_REF(imageList, wxImageList); 
       
    int which = INTEGER(r_which)[0];

    list->SetImageList(imageList, which);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxListCtrl_AssignImageList(SEXP r_list, SEXP r_imageList, SEXP r_which)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    DECLARE_RWX_REF(imageList, wxImageList); 
       
    int which = INTEGER(r_which)[0];

    list->AssignImageList(imageList, which);
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxListCtrl_ClearAll(SEXP r_list)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    list->ClearAll();
    return(R_NilValue);
}

extern "C"
SEXP 
R_wxListCtrl_GetItem(SEXP r_list, SEXP r_id)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    wxListItem item;
    long id = (long) REAL(r_id)[0];
    item.SetId(id);
    bool tmp = list->GetItem(item);
    if(!tmp) {
        PROBLEM "failed in call to wxListCtrl_GetItem"
            ERROR;
    }
        
    wxListItem *ans = new wxListItem(item);
    SEXP r_ans = R_make_wxWidget_Ref(ans, "wxListItem");
    return(r_ans);
}


extern "C"
SEXP 
R_wxListCtrl_InsertColumn_long_wxString_int_int(SEXP r_list, SEXP r_col, SEXP r_heading,
                                                SEXP r_format, SEXP r_width)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    long col = (long) REAL(r_col)[0];
    wxString heading = R_to_wxString(r_heading);
    int format = INTEGER(r_format)[0];
    int width = INTEGER(r_width)[0];

    long ans = list->InsertColumn(col, heading, format, width);
    return(ScalarReal(ans));
}


extern "C"
SEXP 
R_wxListCtrl_SetColumnWidth(SEXP r_list, SEXP r_col, SEXP r_width)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    int col = INTEGER(r_col)[0];
    int width = INTEGER(r_width)[0];

    bool ans = list->SetColumnWidth(col, width);
    return(ScalarLogical(ans));
}


extern "C"
SEXP 
R_wxListCtrl_SetItemImage(SEXP r_list, SEXP r_item, SEXP r_image)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    long item = (long) REAL(r_item)[0];
    int image = INTEGER(r_image)[0];

    bool ans = list->SetItemImage(item, image);
    return(ScalarLogical(ans));
}

extern "C"
SEXP 
R_wxListCtrl_SetItemBackgroundColour(SEXP r_list, SEXP r_item, SEXP r_col)
{
    DECLARE_RWX_REF(list, wxListCtrl); 
    long item = (long) REAL(r_item)[0];
    DECLARE_RWX_REF(col, wxColour);

    list->SetItemBackgroundColour(item, *col);
    return(R_NilValue);
}

