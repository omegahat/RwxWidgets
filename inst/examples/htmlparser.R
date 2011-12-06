#
# Start with a simple display of an HTML document.
# Handle links,
#XXX form submissions and displaying forms.
#
# Then embedded widget inside the HTML document.
#  processor for the HTML parser.


library(RwxWidgets)


OnInit =
function(..., verbose = FALSE)
{

  f =  RFrame("RWxWidgets example",
               as.integer(c(50, 30)),
               as.integer(Size(450, 300)))
  f$Show()
  
 
  h = wxHtmlWindow(f, as.integer(-1), function(src, link) {
                                           href = .Call("R_wxHtmlLinkInfo_GetHref", link)
                                           cat("In link click for", href, "\n")
                                      })

  parser = wxHtmlWindow_GetParser(h)

  # Add a handler for the GUI tag in an HTML document.
  wxHtmlWindow_AddTagHandler(parser,
                             RwxHtmlWinTagHandler("gui",
                                                   function(handler, tag, parser) {
                                                     if(verbose) {
                                                       cat("handling HTML tag gui\n")
                                                       print(wxHtmlTag_GetName(tag))
                                                       print(wxHtmlTag_GetAllParams(tag))
                                                       print(wxHtmlTag_GetParam(tag, "type"))

                                                       print(wxHtmlTag_GetName(wxHtmlTag_GetParent(tag)))

                                                       print(parser)
                                                     }

                                                       data(mtcars)
                                                       g = showDataGrid(mtcars, wxHtmlParser_GetWindow(parser))
                                                       container = wxHtmlParser_GetContainer(parser)
                                                       widgetCell = wxHtmlWidgetCell_new(g)
                                                       wxHtmlContainerCell_InsertCell(container, widgetCell)
                                                       

                                                       TRUE
                                                   }))
 
#  wxHtmlWindow_SetRelatedFrame(h, f, "My Todo List")

 f = c("gui.html", "examples/gui.html")
 if(!any(file.exists(f)))
  stop("Can't find gui.html")  
 f = f[file.exists(f)][1]
  
  wxHtmlWindow_LoadPage(h, f)
#  wxHtmlWindow_SetPage(h, "<html><body>Hi there</body></html>")
 


  # AddFilter - for the types of file.

  # wxInitAllImageHandlers, AddHandler()
  
  # GetParser
  # AddProcessor
  # AddGlobalProcessor

  # OnCellClicked
  # OnLinkClicked

  # OnOpeningURL

}  

app = RApp(OnInit = OnInit, run = TRUE)

  # Initialize the WxWidgets system and run the event loop.
wxEventLoop()
