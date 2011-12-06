#include <wx/listctrl.h>
#include "RwxUtils.h"

#if 0
extern "C"
SEXP 
R_wxListView_GetFirstSelectedItem(SEXP r_list)
{

    DECLARE_RWX_REF(list, wxListView); 
    long index = list->GetFirstSelectedItem();
    return(ScalarReal(index));
}


extern "C"
SEXP 
R_wxListView_GetNextSelectedItem(SEXP r_list, SEXP r_item)
{

    DECLARE_RWX_REF(list, wxListView); 
    long item = REAL(r_item)[0];
    long index = list->GetNextSelectedItem(item);
    return(ScalarReal(index));
}
#endif
