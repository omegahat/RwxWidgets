library(RwxWidgets)

tags =
  list(
"gui" =  function(handler, tag, parser, verbose = FALSE) {
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
          },
  OBJECT = function(handler, tag, parser) {
     cat("In OBJECT handler\n")
     FALSE
  }
 )


f = c("gui.html", "examples/gui.html")
if(!any(file.exists(f)))
  stop("Can't find gui.html")  
f = f[file.exists(f)][1]
htmlViewer(f, function(src, link) {
                                           href = .Call("R_wxHtmlLinkInfo_GetHref", link)
                                           cat("In link click for", href, "\n")
                                      },
            tags, run = TRUE)
