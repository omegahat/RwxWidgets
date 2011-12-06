#include <wx/wx.h>
#include <wx/dir.h>

#include "RwxUtils.h"


extern "C" 
SEXP
R_wxDir_new(SEXP r_dir)
{
    wxString dir;
    wxDir *ans;

    if(GET_LENGTH(r_dir)) {
        dir = R_to_wxString(r_dir);
        ans = new wxDir(dir);
    } else 
        ans = new wxDir();

    return(R_make_wx_Ref(ans, "wxDir"));
}

extern "C" 
SEXP
R_wxDir_Traverse(SEXP r_dir, SEXP r_traverser, SEXP r_filespec, SEXP r_flags)
{
    DECLARE_RWX_REF(dir, wxDir);
    wxDirTraverser * traverser = (wxDirTraverser *) R_get_wxWidget_Ref(r_traverser, NULL);
    wxString filespec = R_to_wxString(r_filespec);
    int flags = INTEGER(r_flags)[0];

    size_t ans = dir->Traverse(*traverser, filespec, flags);
    return(ScalarReal(ans));
}
