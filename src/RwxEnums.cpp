#include <wx/wx.h>
#include <wx/dnd.h>

#include "RwxUtils.h"


#if wxUSE_DRAG_AND_DROP
static const wxDragResult wxDragResult_values[] = {
    wxDragError, wxDragNone, wxDragCopy, wxDragMove, wxDragLink, wxDragCancel
};

static const char * const wxDragResult_names[] = {
    "wxDragError", "wxDragNone", "wxDragCopy", "wxDragMove", "wxDragLink", "wxDragCancel"
};

SEXP
wxDragResultToR(wxDragResult val)
{
    int n = sizeof(wxDragResult_values)/sizeof(wxDragResult_values[0]), i;

    for(i = 0; i < n ; i++) {
        if(wxDragResult_values[i] == val) {
            SEXP klass, ans;
            PROTECT(klass = MAKE_CLASS("wxDragResult"));
            PROTECT(ans = NEW(klass));
            INTEGER(ans)[0] = (int) val;
            SET_NAMES(ans, mkString(wxDragResult_names[i]));
            UNPROTECT(2);
            return(ans);
        }
    }
    PROBLEM "no match for %d in wxDragResult", (int) val
        ERROR;
    return(R_NilValue);
}

#endif

