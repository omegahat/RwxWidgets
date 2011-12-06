#if wxUSE_DRAG_AND_DROP

#include <wx/wx.h>
#include <wx/dnd.h>
#include "RwxUtils.h"
#include "RwxEnums.h"

extern "C"
SEXP
R_test_wxDragResult_enum()
{
    return(wxDragResultToR(wxDragMove));
}

#endif
