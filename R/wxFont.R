# wxFont(int pointSize, wxFontFamily family, int style, wxFontWeight weight, const bool underline = false, const wxString& faceName = "", wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
#wxFont(const wxSize& pixelSize, wxFontFamily family, int style, wxFontWeight weight, const bool underline = false, const wxString& faceName = "", wxFontEncoding encoding = wxFONTENCODING_DEFAULT)

setGeneric("wxFont",
            function(pointSize, family, style, weight, underline = FALSE, faceName = "", encoding = wxFONTENCODING_DEFAULT)
               standardGeneric("wxFont"))

setMethod('wxFont', c("numeric"),
          function(pointSize, family, style, weight, underline = FALSE, faceName = "", encoding = wxFONTENCODING_DEFAULT) {
            #XXX fix the enums
             family = as.integer(family)
             weight = as.integer(weight)
             underline = as.logical(underline)
             faceName = as.character(faceName) # if wxString pointer, don't coerce.
             encoding = as.integer(encoding)
            .Call("R_wxFont_new_int", as.integer(pointSize), family, as.integer(style)[0], weight, underline, faceName, encoding)
          })

setMethod('wxFont', c("wxSize"),
          function(pointSize, family, style, weight, underline = FALSE, faceName = "", encoding = wxFONTENCODING_DEFAULT) {
            #XXX fix the enums
             family = as.integer(family)
             weight = as.integer(weight)
             underline = as.logical(underline)
             faceName = as.character(faceName) # if wxString pointer, don't coerce.
             encoding = as.integer(encoding)
            .Call("R_wxFont_new_wxSize", pointSize, family, as.integer(style)[0], weight, underline, faceName, encoding)
          })
  


wxWindow_SetFont =
function(this, font)
{
   .Call("R_wxWindow_SetFont", this, font)
}
