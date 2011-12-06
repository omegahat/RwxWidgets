#include <wx/html/htmlwin.h>
#include "RwxUtils.h"
#include "RwxClass.h"

class R_wxHtmlWindow : public wxHtmlWindow,
                       public R_wxClass
{
  public:

    R_wxHtmlWindow(wxWindow *parent, wxWindowID id,
		   SEXP OnLinkClicked = NULL, 
                    const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
		   long style = wxHW_DEFAULT_STYLE, const wxString &name = _T("htmlWindow") )
	: wxHtmlWindow(parent, id, pos, size,style, name) {
	         setOnLinkClicked(OnLinkClicked);
          }

     void setOnLinkClicked(SEXP OnLinkClicked) {
 	         R_OnLinkClicked = OnLinkClicked;
		 if(Rf_length(R_OnLinkClicked))
		     R_PreserveObject(R_OnLinkClicked);
     }

     virtual void OnLinkClicked(const wxHtmlLinkInfo &link);

  protected:
    SEXP R_OnLinkClicked;

};


