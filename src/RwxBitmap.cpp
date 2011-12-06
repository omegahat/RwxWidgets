#include <wx/wx.h>
#include <wx/image.h>
#include <wx/bitmap.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_get_wxNullBitmap()
{
    wxBitmap *ans = &wxNullBitmap;
    return(R_make_wxWidget_Ref(ans, "wxBitmap"));
}

extern "C"
SEXP
R_wxBitmap_new_wxString_long(SEXP r_name, SEXP r_type)
{
    const wxString name = R_to_wxString(r_name);
    wxBitmapType type = (wxBitmapType) asInteger(r_type);
    wxBitmap *ans;

    ans = new wxBitmap(name,  type);  /* XXX we need the wxBitmapType case here or we get the wrong constructor!!!
                                                        At least on my Linux box. Gcc 4.1.0 20060304 (Red Hat 4.1.0-3) */
    return(R_make_wxWidget_Ref(ans, "wxBitmap"));
}

extern "C"
SEXP
R_test_wxBitmap()
{
    wxBitmap *ans = new wxBitmap(wxT("/home/duncan/pal2/icon0.png"), wxBITMAP_TYPE_PNG);
    return(R_make_wxWidget_Ref(ans, "wxBitmap"));

}

extern "C"
SEXP
R_wxBitmap_GetWidth(SEXP r_bitmap)
{
    DECLARE_RWX_REF(bitmap, wxBitmap);
    int ans = bitmap->GetWidth();
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxBitmap_GetHeight(SEXP r_bitmap)
{
    DECLARE_RWX_REF(bitmap, wxBitmap);
    int ans = bitmap->GetHeight();
    return(ScalarInteger(ans));
}

extern "C"
SEXP
R_wxBitmap_GetDepth(SEXP r_bitmap)
{
    DECLARE_RWX_REF(bitmap, wxBitmap);
    int ans = bitmap->GetDepth();
    return(ScalarInteger(ans));
}


extern "C"
SEXP
R_wxBitmap_ConvertToImage(SEXP r_bitmap)
{
    DECLARE_RWX_REF(bitmap, wxBitmap);
    wxImage *ans, tmp;
    tmp = bitmap->ConvertToImage();
    ans = new wxImage(tmp);
    
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}
