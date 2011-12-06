#include <wx/wx.h>
#include <wx/imaglist.h>

#include "RwxUtils.h"

extern "C" 
SEXP
R_wxImageList_new()
{
    wxImageList *ans = new wxImageList();
    return(R_make_wxWidget_Ref(ans, "wxImageList"));
}


extern "C" 
SEXP
R_wxImageList_new_int_int(SEXP r_width, SEXP r_height, SEXP r_mask, SEXP r_initialCount)
{
    int width = INTEGER(r_width)[0];
    int height = INTEGER(r_height)[0];
    bool mask = LOGICAL(r_mask)[0];
    int initialCount = INTEGER(r_initialCount)[0];
    
    wxImageList *ans = new wxImageList(width, height, mask, initialCount);
    return(R_make_wxWidget_Ref(ans, "wxImageList"));
}


extern "C"
SEXP
R_wxImageList_Add_wxBitmap_wxBitmap(SEXP r_imageList, SEXP r_bitmap, SEXP r_mask)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    DECLARE_RWX_REF(bitmap, wxBitmap);
    DECLARE_RWX_REF(mask, wxBitmap);

    int ans = imageList->Add(*bitmap, *mask);
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxImageList_Add_wxBitmap_wxColour(SEXP r_imageList, SEXP r_bitmap, SEXP r_maskColour)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    DECLARE_RWX_REF(bitmap, wxBitmap);
    DECLARE_RWX_REF(maskColour, wxColour);

    int ans = imageList->Add(*bitmap, *maskColour); 
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxImageList_Add_wxIcon(SEXP r_imageList, SEXP r_icon)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    DECLARE_RWX_REF(icon, wxIcon);

    int ans = imageList->Add(*icon);
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxImageList_GetImageCount(SEXP r_imageList)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    int ans = imageList->GetImageCount();
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxImageList_GetBitmap(SEXP r_imageList, SEXP r_index)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    int index = INTEGER(r_index)[0];
    wxBitmap tmp, *ans;
    tmp = imageList->GetBitmap(index);
    ans = new wxBitmap(tmp);

    return(R_make_wxWidget_Ref(ans, "wxBitmap"));
}


extern "C"
SEXP
R_wxImageList_GetSize(SEXP r_imageList, SEXP r_itemIndex)
{
    DECLARE_RWX_REF(imageList, wxImageList);
    int itemIndex = INTEGER(r_itemIndex)[0];
    int w, h;
    bool ans = imageList->GetSize(itemIndex, w, h);
    if(!ans)
        return(NEW_INTEGER(0));

    SEXP r_ans, r_names;
    PROTECT(r_ans = NEW_INTEGER(2));
    INTEGER(r_ans)[0] = w;
    INTEGER(r_ans)[1] = h;
    PROTECT(r_names = NEW_CHARACTER(2));
    SET_STRING_ELT(r_names, 0, mkChar("width"));
    SET_STRING_ELT(r_names, 1, mkChar("height"));
    SET_NAMES(r_ans, r_names);
    UNPROTECT(2);

    return(r_ans);
}

