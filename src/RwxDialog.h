#include <wx/dialog.h>
#include "RwxUtils.h"

#include "RwxObject.h"

class RwxDialog : public wxDialog 
		  /* public RwxObject */
{

public:
    SEXP REnv() { return(R_GlobalEnv); }// if we don't extend RwxObject.

    RwxDialog() {
       R_TransferDataToWindow_m =  R_TransferDataFromWindow_m =  R_CreateControls_m = NULL;
    };
    RwxDialog(wxWindow *parent, wxWindowID id = wxID_ANY,
                const wxString&  title = wxT("R Dialog"),
                const wxPoint  &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
  	        long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU,
  	        const wxString &name = wxT("RwxDialog")
	) :  wxDialog(parent, id, title, pos, size, style, name)
      {
       R_TransferDataToWindow_m =  R_TransferDataFromWindow_m =  R_CreateControls_m = NULL;
      };

#if 0
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY,
                const wxString&  title = wxT("R Dialog"),
                const wxPoint  &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize,
                long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU
              );
#endif

    virtual void CreateControls();   
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();

protected:
    SEXP R_TransferDataToWindow_m, R_TransferDataFromWindow_m,
  	 R_CreateControls_m;

#if 0
private:
    DECLARE_DYNAMIC_CLASS(RwxDialog)
#endif

};

