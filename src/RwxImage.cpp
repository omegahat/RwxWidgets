#include <wx/wx.h>
#include <wx/image.h>

#include "RwxUtils.h"


extern "C"
SEXP
R_wxImage_new_wxString_wxString_int(SEXP r_name, SEXP r_mimetype, SEXP r_index)
{
    wxString name = R_to_wxString(r_name);
    wxString mimetype = R_to_wxString(r_mimetype);
    int index = INTEGER(r_index)[0];

    wxImage *ans;

    ans = new wxImage(name, mimetype, index);
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}


extern "C"
SEXP
R_wxImage_new_wxString_long_int(SEXP r_name, SEXP r_type, SEXP r_index)
{
    wxString name = R_to_wxString(r_name);
    long type = (long) REAL(r_type)[0];
    int index = INTEGER(r_index)[0];

    wxImage *ans;

    ans = new wxImage(name, type, index);
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}

#if 1

extern "C"
SEXP
R_wxImage_LoadFile_wxString_long_int(SEXP r_image, SEXP r_name, SEXP r_type, SEXP r_index)
{
    DECLARE_RWX_REF(image, wxImage);
    wxString name = R_to_wxString(r_name);
    long type = (long) REAL(r_type)[0];
    int index = INTEGER(r_index)[0];

    bool ans = image->LoadFile(name, type, index);

    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxImage_LoadFile_wxString_wxString_int(SEXP r_image, SEXP r_name, SEXP r_mimetype, SEXP r_index)
{
    DECLARE_RWX_REF(image, wxImage);
    wxString name = R_to_wxString(r_name);
    wxString mimetype = R_to_wxString(r_mimetype);
    int index = INTEGER(r_index)[0];

    bool ans = image->LoadFile(name, mimetype, index);

    return(ScalarLogical(ans));
}
#endif


extern "C"
SEXP
R_wxImage_Rotate(SEXP r_image, SEXP r_angle, SEXP r_rotationCentre, 
                 SEXP r_interpolating, SEXP r_offsetAfterRotation)
{
    DECLARE_RWX_REF(image, wxImage);
    double angle = REAL(r_angle)[0];
    wxPoint rotationCenter;
    bool interpolating = LOGICAL(r_interpolating)[0];
    wxPoint *offsetAfterRotation = NULL;
    wxImage *ans, tmp;

    rotationCenter = R_to_wxPoint(r_rotationCentre);

    tmp = image->Rotate(angle, rotationCenter, interpolating, offsetAfterRotation);
    ans = new wxImage(tmp);
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}


extern "C"
SEXP
R_wxImage_Rescale(SEXP r_image, SEXP r_width, SEXP r_height)
{
    DECLARE_RWX_REF(image, wxImage);
    int width, height;
    width = INTEGER(r_width)[0];
    height = INTEGER(r_height)[0];

    (void) image->Rescale(width, height); //XX hard to determine programmatically. Has a reference.
    return(r_image);
}


extern "C"
SEXP
R_wxImage_Scale(SEXP r_image, SEXP r_width, SEXP r_height)
{
    DECLARE_RWX_REF(image, wxImage);
    int width, height;
    width = INTEGER(r_width)[0];
    height = INTEGER(r_height)[0];

    wxImage *ans, tmp;

    tmp = image->Scale(width, height);
    ans = new wxImage(tmp);
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}



extern "C"
SEXP
R_wxImage_Ok(SEXP r_image)
{
    DECLARE_RWX_REF(image, wxImage);

    bool ans = image->Ok();

    return(ScalarLogical(ans));
}

extern "C"
SEXP
R_wxImage_GetSubImage(SEXP r_image, SEXP r_rect)
{
    DECLARE_RWX_REF(image, wxImage);
    wxRect rect;
    rect = R_to_wxRect(r_rect);
    
    wxImage *ans, tmp;

    tmp = image->GetSubImage(rect);
    ans = new wxImage(tmp);
    return(R_make_wxWidget_Ref(ans, "wxImage"));
}



extern "C"
SEXP
R_wxImage_ConvertToBitmap(SEXP r_image)
{

    const DECLARE_RWX_REF(image, wxImage);
    wxBitmap *ans = new wxBitmap(*image);
    
    return(R_make_wxWidget_Ref(ans, "wxBitmap"));
#if wxMINOR_VERSION < 8
#else
    PROBLEM "not supported in wxWidgets 2.8 ..."
        ERROR;
    return(R_NilValue);
#endif
}

