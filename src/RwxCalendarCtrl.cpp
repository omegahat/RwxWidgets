#include <wx/calctrl.h>
#include "RwxUtils.h"

extern "C"
SEXP
R_wxCalendarCtrl_new(SEXP r_parent, SEXP r_id, SEXP r_date,
                     SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
    long style = (long) REAL(r_style)[0];
    const wxString name = R_to_wxString(r_name);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    

    DECLARE_RWX_REF(date, wxDateTime);
    
    if(LENGTH(r_size)) size = R_to_wxSize(r_size);
    if(LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);

    wxCalendarCtrl *ans = new wxCalendarCtrl(parent, id, *date, pos, size, style, name);
    return(R_make_wxWidget_Ref(ans, "wxCalendarCtrl"));
}

extern "C"
SEXP
R_wxCalendarCtrl_GetDate(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxCalendarCtrl);
    wxDateTime *ans;
    ans = new wxDateTime( This->GetDate() );
    return(R_make_wx_Ref(ans, "wxDateTime"));
}

extern "C"
SEXP
R_wxCalendarCtrl_SetDate(SEXP r_This, SEXP r_date)
{
    DECLARE_RWX_REF(This, wxCalendarCtrl);
    DECLARE_RWX_REF(date, wxDateTime);

    This->SetDate(*date);
    return(R_NilValue);
}



