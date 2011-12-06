#include <wx/wx.h>
#include <wx/colour.h>

#include "RwxUtils.h"

extern "C"
SEXP
R_wxGetColour(SEXP r_which)
{
    if(TYPEOF(r_which) != STRSXP) {
        PROBLEM "non-character value passed to R_wxGetColour"
            ERROR;
    }
        
    const char *tmp =  CHAR(STRING_ELT(r_which, 0));
    const wxColour *col;

    if(strcmp(tmp, "RED") == 0) {
        col = wxRED;
    } else if(strcmp(tmp, "BLACK") == 0) {
        col = wxBLACK;
    } else if(strcmp(tmp, "WHITE") == 0) {
        col = wxWHITE;
    } else if(strcmp(tmp, "GREEN") == 0) {
        col = wxGREEN;
    } else if(strcmp(tmp, "BLUE") == 0) {
        col = wxBLUE;
    } else if(strcmp(tmp, "CYAN") == 0) {
        col = wxCYAN;
    } else if(strcmp(tmp, "LIGHT_GREY") == 0) {
        col = wxLIGHT_GREY;
    } else  {
        PROBLEM "couldn't interpret color name %s", tmp
            WARN
        return(R_NilValue);
    }

    return(R_make_wxWidget_Ref(col, "wxColour"));
}
