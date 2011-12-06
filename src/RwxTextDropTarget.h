#include <wx/wx.h>
#include <wx/dnd.h>

#include "RwxUtils.h"

class RwxTextDropTarget : public wxTextDropTarget
{

protected:
     SEXP R_OnDropText_m;
     SEXP R_OnEnter_m;
     SEXP R_OnDragOver_m;

public:
    RwxTextDropTarget() : wxTextDropTarget(), R_OnDropText_m(NULL) { }

    RwxTextDropTarget(SEXP OnDropText, SEXP OnEnter, SEXP OnDragOver) : wxTextDropTarget() {
	if(GET_LENGTH(OnDropText))
	    R_PreserveObject(R_OnDropText_m = Rf_duplicate(OnDropText));
	else
	    R_OnDropText_m = NULL;
	if(GET_LENGTH(OnEnter))
 	    R_PreserveObject(R_OnEnter_m = Rf_duplicate(OnEnter));
	else
	    R_OnEnter_m = NULL;
	if(GET_LENGTH(OnDragOver))
 	    R_PreserveObject(R_OnDragOver_m = Rf_duplicate(OnDragOver));
	else
	    R_OnDragOver_m = NULL;
    }


    virtual bool OnDropText(wxCoord x, wxCoord y, const wxString &text);
    virtual wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
    virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
/*
    bool OnDrop(wxCoord x, wxCoord y);
    wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
    bool GetData();
*/

    SEXP R_setOnDropText_method(SEXP m) {
	SEXP old = R_OnDropText_m;
	R_OnDropText_m = m;
	R_ReleaseObject(m);
	return(old);
    }
};
