#include <wx/filedlg.h>

#include "RwxUtils.h"

class RwxFileDialog : public wxFileDialog /* ,
                      public RwxDynamicClass
					  */
{

protected:
    SEXP R_OnOK_m;

public:

    RwxFileDialog(wxWindow *parent, const wxString &message, const wxString &defaultDir, const wxString &defaultFile,
                  const wxString & wildcard, long style, const wxPoint &pos = wxDefaultPosition,
                  SEXP OnOK_m = NULL) 
	:   wxFileDialog(parent, message, defaultDir, defaultFile, wildcard, style, pos),
            R_OnOK_m(OnOK_m) 
    {
	if(R_OnOK_m)
	    R_PreserveObject(R_OnOK_m);
    }

    virtual void OnOK(wxCommandEvent &event);
/*
    void OnApply(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);
*/
};
