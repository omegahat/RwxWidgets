#
# Start with a simple display of an HTML document.
# Handle links,
#XXX form submissions
#
# Then embedded widget inside the HTML document.
#  processor for the HTML parser.


library(RwxWidgets)

OnInit =
function(...)
{
  f =  RFrame("RWxWidgets example",
               as.integer(c(50, 30)),
               as.integer(Size(450, 300)))
  f$Show();
 

 link = function(src, link) {
       cat("In link click", wxHtmlLinkInfo_GetHref(link), "\n");
       # print(src)
       # print(link)
      }
  
  h = wxHtmlWindow(f, as.integer(-1)) #, link)

print(getWxClassInfo(h))

  
#XXX wxHtmlWindow_SetRelatedFrame(h, f, "My Todo List")

 f = c("form.html", "examples/form.html")
 if(!any(file.exists(f)))
  stop("Can't find form.html")  
 f = f[file.exists(f)][1]
  
  wxHtmlWindow_LoadPage(h, f)
#  wxHtmlWindow_SetPage(h, "<html><body>Hi there</body></html>")
 


  # AddFilter - for the types of file.

  # wxInitAllImageHandlers, AddHandler()
  
  # GetParser - see htmlparser.R
  # AddProcessor
  # AddGlobalProcessor

  # OnCellClicked
  # OnLinkClicked

  # OnOpeningURL

}  

app = RApp(OnInit = OnInit, run = TRUE)

  # Initialize the WxWidgets system and run the event loop.
#wxEventLoop()

