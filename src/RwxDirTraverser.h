#include <wx/wx.h>
#include <wx/dir.h>

#include "RwxUtils.h"

//XXX had to do this manually as the docs and the code are out of sync.
typedef wxDirTraverseResult wxOpenErrorTraverseResult;


class RwxDirTraverser : public wxDirTraverser {

public:
    RwxDirTraverser(SEXP OnFile, SEXP OnDir, SEXP OnOpenError = NULL) {
	if(OnFile && GET_LENGTH(OnFile) && TYPEOF(OnFile) == CLOSXP)
	    R_PreserveObject(R_OnFile_m = Rf_duplicate(OnFile));

	if(OnFile && GET_LENGTH(OnDir) && TYPEOF(OnDir) == CLOSXP)
	    R_PreserveObject(R_OnDir_m = Rf_duplicate(OnDir));

	if(OnOpenError && GET_LENGTH(OnOpenError) && TYPEOF(OnOpenError) == CLOSXP)
	    R_PreserveObject(R_OnOpenError_m = Rf_duplicate(OnOpenError));
    }

    wxDirTraverseResult OnFile(const wxString &filename);
    wxDirTraverseResult OnDir(const wxString &filename);
    wxOpenErrorTraverseResult OnOpenError(const wxString& openerrorname);

protected:
    SEXP R_OnDir_m, R_OnFile_m, R_OnOpenError_m;
};
