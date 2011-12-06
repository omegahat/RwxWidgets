#include <wx/wx.h>
#include <wx/datetime.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_wxDateTime_GetTicks(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxDateTime);
    time_t ans = This->GetTicks();
    return(ScalarReal(ans));
}

extern "C"
SEXP
R_wxDateTime_IsLaterThan(SEXP r_This, SEXP r_other)
{
    DECLARE_RWX_REF(This, wxDateTime);
    DECLARE_RWX_REF(other, wxDateTime);
    bool ans = This->IsLaterThan(*other);
    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxDateTime_new_size_t(SEXP r_timet)
{
    time_t timet = (time_t) REAL(r_timet)[0];
    wxDateTime *ans = new wxDateTime(timet);
    return(R_make_wx_Ref(ans, "wxDateTime"));
}

extern "C" 
SEXP
R_get_wxDefaultDateTime()
{
    return(R_make_wx_Ref((void *) const_cast<wxDateTime *>(&wxDefaultDateTime), "wxDateTime"));
}
