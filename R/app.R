# The OnInit is a method, not an event
# so we override it via an explicitt field in our
# C++ R class.
RApp =
function(OnInit = NULL, runEventLoop = FALSE)
{
  app = .Call("R_RwxApp_new", OnInit)

  if(runEventLoop)
    wxEntry()

  app
}

# 
#   wxEnum cannot be virtual as we need an instance in the prototype for
setClass("wxEnum", contains = "integer", prototype = structure(integer(1), names = ""))
setMethod("show", "wxEnum", function(object) { show(structure(as(object, "integer"), names = names(object)))})


wxDragResultValues =
  structure(c(wxDragError, wxDragNone, wxDragCopy, wxDragMove, wxDragLink, wxDragCancel),
            names = c("wxDragError", "wxDragNone", "wxDragCopy", "wxDragMove", "wxDragLink", "wxDragCancel"),
            class = c("wxDragResultEnumValues", "EnumValues"))

setClass("wxDragResult", contains = "wxEnum", prototype = new("wxEnum"))
setAs("numeric", "wxDragResult",
       function(from) {
          i = match(from, wxDragResultValues)
          if(is.na(i))
            stop("not a valid wxDragResult value")
          ans = new("wxDragResult", wxDragResultValues[i])
          names(ans) = names(wxDragResultValues)[i]
          ans
       })

setAs("character", "wxDragResult",
       function(from) {
          i = pmatch(from, names(wxDragResultValues))
          if(is.na(i))
            stop("not a valid wxDragResult value")
          ans = new("wxDragResult", wxDragResultValues[i])
          names(ans) = names(wxDragResultValues)[i]
          ans          
       })




setClass("ExternalPtr", representation(ref = "externalptr"))
setClass("C++ExternalPtr", contains = "ExternalPtr")

# Rationalize the naming scheme here.
setClass("wxObject", contains = "C++ExternalPtr")
setClass("wxGenericObject", contains = "wxObject")  # when we don't know what type it is
                                                    # or don't have explicitly defined for it.
                                                    # should we keep the class information around
                                                    # or even for all wxObject instances.
                                                    # Should we keep the name of the class that we know it is
                                                    # at least, e.g. wxCommandEvent eventhough we know it is more specific.
setClass("wxNonDynamicObject", representation(classes = "character"), contains = "wxObject")


setClass("wxEventLoop", contains = "C++ExternalPtr")

setClass("RwxObject", contains = "wxObject")
setClass("RwxApp", contains = "RwxObject")


setClass("wxDC",  contains = "wxObject")


setClass("wxEvtHandler",  contains = "wxObject")

setClass("wxEvent", contains = "wxObject")
setClass("wxCommandEvent", contains = "wxEvent")
setClass("wxCloseEvent", contains = "wxEvent")
setClass("wxPaintEvent", contains = "wxEvent")

setClass("wxMoveEvent", contains = "wxEvent")

setClass("wxScrollEvent", contains = "wxCommandEvent")


setClass("wxStatusBar", contains = "wxObject")
setClass("RwxStatusBar", contains = "wxStatusBar")



setClass("wxWindow",  contains = "wxObject")

setClass("wxMenuBar", contains = "wxWindow")
setClass("wxMenu", contains = "wxEvtHandler")
setClass("wxMenuItem", contains = "wxObject")

setClass("wxButton", contains = "wxWindow")
setClass("RwxButton", contains = "wxButton")


setClass("wxSizerItem",  contains = "wxObject")


setClass("wxListItem",  contains = "RwxObject")

setClass("wxFrame", contains = "wxWindow")
setClass("RwxFrame", contains = "wxFrame")

setClass("wxSizer",  contains = "RwxObject")
setClass("wxGridSizer", contains = "wxSizer")
setClass("wxFlexGridSizer", contains = "wxSizer")
setClass("wxGridBagSizer", contains = "wxSizer")


setClass("wxSizerItem", contains = "wxObject")

setClass("wxBoxSizer", contains = "wxSizer")
setClass("wxStaticBoxSizer", contains = "wxBoxSizer")

setClass("RwxEventHandler", contains = "RwxObject")

setClass("wxGrid", contains = "wxWindow")
setClass("wxHtmlWindow", contains = "wxWindow")
setClass("RwxHtmlWindow", contains = "wxHtmlWindow")

setClass("wxTextCtrl", contains = "wxWindow")
setClass("wxNotebook", contains = "wxWindow")
setClass("wxNotebookPage", contains = "wxWindow")

#XXsetClass("RwxTextCtrl", contains = "wxTextCtrl")

setClass("wxPanel", contains = "wxWindow")


setClass("wxControl", contains = "wxWindow")
setClass("wxControlWithItems", contains = "wxControl")



setClass("wxRadioButton", contains = "wxControl")
setClass("wxCheckBox", contains = "wxControl")
setClass("wxSpinCtrl", contains = "wxControl")
setClass("wxRadioBox", contains = "wxControl")
setClass("wxSplitterWindow", contains = "wxWindow")
setClass("wxListBox", contains = "wxControlWithItems")
setClass("wxChoice", contains = "wxControlWithItems")

setClass("wxListCtrl", contains = "wxControl")
setClass("wxStaticBox", contains = "wxControl")
setClass("wxStaticText", contains = "wxControl")

setClass("wxToolBar", contains = "wxControl")

setClass("wxTreeCtrl", contains = "wxControl")

setClass("wxTreeItemId", contains = "C++ExternalPtr")

setClass("wxToolBarTool", contains =  "wxObject")

setClass("wxComboBox", contains = "wxControlWithItems")


setClass("wxStaticLine", contains = "wxControl")
setClass("wxCalendarCtrl", contains = "wxControl")



setClass("wxTopLevelWindow", contains = "wxWindow")
setClass("wxDialog", contains = "wxTopLevelWindow")


setClass("wxFileDialog", contains = "wxDialog")
setClass("RwxFileDialog", contains = "wxFileDialog") # by hand.

setClass("wxMultiChoiceDialog", contains = "wxDialog")
setClass("wxSingleChoiceDialog", contains = "wxDialog")

setClass("RwxDialog", contains = "wxDialog") 

setClass("wxSlider", contains = "wxWindow")


setClass("wxDirTraverser", contains = "C++ExternalPtr")
setClass("RwxDirTraverser", contains = "wxDirTraverser")

setClass("wxDir", contains = "C++ExternalPtr")


setClass("wxGBPosition", contains = "C++ExternalPtr")
setClass("wxGBSpan", contains = "C++ExternalPtr")

setAs("numeric", 'wxGBPosition',
         function(from) {
            if(length(from) < 2)
              stop("Need two values for an wxGBPosition")

            wxGBPosition(from[1], from[2])
          })

setAs("numeric", 'wxGBSpan',
         function(from) {
            # if(length(from) < 2)
            #  stop("Need two values for an wxGBSpan")

            if(length(from) == 1)
              from = c(from, from)
            
            wxGBSpan(from[1], from[2])
          })


setClass("wxDropTarget", contains = "C++ExternalPtr")
setClass("RwxDropTarget", contains = "wxDropTarget")
setClass("wxTextDropTarget", contains = "wxDropTarget")
setClass("RwxTextDropTarget", contains = "wxTextDropTarget")

setClass("wxDropSource", contains = "C++ExternalPtr")

setClass("wxDataObject", contains = "C++ExternalPtr")
setClass("wxTextDataObject", contains = "wxDataObject")


setClass("wxDateTime", contains = "C++ExternalPtr")


# Is this an wxObject.
setClass("wxHtmlLinkInfo", contains = "wxNonDynamicObject",
               prototype = list(classes = c("wxHtmlLinkInfo", "wxObject")))

setAs("wxObject", "wxHtmlLinkInfo",
      function(from) {
        .Call("R_wxHtmlLinkInfo_cast", from)
      })


setClass("wxHtmlWinParser", contains = "wxObject")

setClass("wxHtmlTag", contains = "wxObject")
setClass("wxHtmlParser", contains = "wxObject")


setClass("wxHtmlContainerCell", contains = "wxObject")
setClass("wxHtmlCell", contains = "wxObject")
setClass("wxHtmlWidgetCell", contains = "wxObject")
setClass("wxHtmlWordCell",  contains = "wxHtmlCell")


setClass("RwxHtmlWinTagHandler", "wxObject")

setClass("wxGDIObject", contains = "wxObject")
setClass("wxFont", contains = "wxGDIObject")


setClass("wxEvent", contains = "wxObject")
setClass("wxKeyEvent", contains = "wxEvent")
setClass("wxCommandEvent", contains = "wxEvent")
setClass("wxMouseEvent", contains = "wxEvent")

setClass("wxDateEvent", contains = "wxCommandEvent")
setClass("wxCalendarEvent", contains = "wxDateEvent")

setClass("wxNotifyEvent", contains = "wxCommandEvent")
setClass("wxListEvent", contains = "wxNotifyEvent")
setClass("wxTreeEvent", contains = "wxNotifyEvent")






setClass("wxGDIObject", contains = "wxObject")
setClass("wxBitmap", contains = "wxGDIObject")
setClass("wxIcon", contains = "wxBitmap")


setClass("wxImage", contains = "wxObject")
setClass("wxImageList", contains = "wxObject")

setClass("wxPoint",  "C++ExternalPtr")
setClass("wxSize",  "C++ExternalPtr")
setClass("wxString", "C++ExternalPtr")


setClass("wxColour",  "C++ExternalPtr")

setClass("wxGBSpan", contains = "C++ExternalPtr")
setClass("wxGBSposition", contains = "C++ExternalPtr")


# Here we want to allow a user to specify either a C++ level
# object or an R vector as a value for a parameter and
# we will deal with it in the C++ code.
# The idea is not to create a C++ object from R, pass it to C++
# and then garbage collect it. Although this is fine too.
# In the R code for a function taking a wxSize object, we can have either
# approach:
#    size = as(size, "wxSize")
# to create an instance of the  C++ wxSize class.
# Alternatively, we can have
#    size = as(size, "RwxSize")
# which will accept size = c(10, 30) or
#                   size = wxSize(10, 30)
# And in the corresponding C++ code, we have
#   wxSize size = R_to_wxSize(r_size)

setClassUnion("RwxSize", c("numeric", "wxSize"))
setClassUnion("RwxPoint", c("numeric", "wxPoint"))
setClassUnion("RwxString", c("character", "wxString"))

setAs("numeric", "wxSize",
        function(from) {
          from = as.integer(from)
          .Call("R_wxSize_new", from[1], from[2], TRUE)
        })


makeActiveBinding("wxTheApp", function(id) .Call("R_wxApp_wxTheApp"), .GlobalEnv) #XXX

wxApp_MainLoop =
 function(app = wxTheApp)
{
  .Call("R_wxAppBase_MainLoop", app)
}
