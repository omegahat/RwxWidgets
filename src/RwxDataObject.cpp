#include <wx/wx.h>
#include <wx/dataobj.h>

#include "RwxUtils.h"

extern "C" 
SEXP
R_wxTextDataObject(SEXP r_data)
{
    SEXP r_ans;
    wxTextDataObject *ans;
    wxString data = R_to_wxString(r_data);
    ans = new wxTextDataObject(data);
    return(R_make_wx_Ref(ans, "wxTextDataObject"));
}
