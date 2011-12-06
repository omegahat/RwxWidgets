#include <wx/wx.h>
#include <wx/dnd.h>

#if wxUSE_DRAG_AND_DROP

#include "RwxUtils.h"

extern SEXP wxDragResultToR(wxDragResult);

extern "C"
SEXP
R_wxDropSource(SEXP r_data, SEXP r_win, SEXP r_DoDragDrop)
{
    DECLARE_RWX_REF(win, wxWindow);
    wxDataObject *data;
    data = (wxDataObject*) R_get_wxWidget_Ref(r_data, NULL); /*XXX fixme - have to be able to find a match without the class information. Perhaps do a proper dynamic_cast. */  

    wxDropSource *src = new wxDropSource(*data, win);
    if(LOGICAL(r_DoDragDrop)[0]) {
        wxDragResult ans = src->DoDragDrop(wxDrag_CopyOnly);
        delete src;
        switch(ans) {
        case wxDragError: 
        {
            PROBLEM "error in drag and drop"
                ERROR;
            break;
        }
        case wxDragNone: 
        {
            PROBLEM "drop source didn't acept the data"
                WARN;
            break;
        }
        default:
            break;
        }
        return(wxDragResultToR(ans));
        //return(ScalarInteger(ans)); /*XXX put the name on this, i.e. make it an enum */
    } else {
        return(R_make_wx_Ref(src, "wxDropSource"));
    }
}

#endif
