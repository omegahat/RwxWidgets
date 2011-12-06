#include <wx/dnd.h>

#include "RwxUtils.h"

class RwxDropSource : public wxDropSource
{

public:
    RwxDropSource() { }

    RwxDropSource(wxDataObject &data, wxWindow *win)
        : wxDropSource(data, win) { }

    virtual wxDragResult DoDragDrop(int flags = wxDrag_CopyOnly);
    virtual bool GiveFeedback(wxDragResult WXUNUSED(effect)) { return false; }

protected:
    SEXP R_DoDragDrop_m, R_GiveFeedback_m;
};

