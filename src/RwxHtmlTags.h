#include <wx/html/htmlwin.h>
#include "RwxUtils.h"
#include "RwxClass.h"


/*
  This is an implementation of a dynamic HTML tag parser
  that can be added to the HTML parser to handle special/user-derfined
  tags.
*/

class RwxHtmlWinTagHandler : public wxHtmlWinTagHandler, R_wxClass
{
 public:
    /* */
    RwxHtmlWinTagHandler(const char *tagNames, SEXP r_handler) {
	tags = wxString(tagNames, wxConvUTF8);
        handler = r_handler;
	R_PreserveObject(handler);
    }

    wxString GetSupportedTags() {
        return(tags);
    };

    bool HandleTag(const wxHtmlTag& varib);

    void RParseInner(const wxHtmlTag &tag) {
	ParseInner(tag);
    }

protected:
    wxString tags;
    SEXP handler;
};
