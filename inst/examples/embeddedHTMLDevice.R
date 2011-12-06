library(RwxWidgets)

htmlRdeviceHandler =
  function(handler, tag, parser) {
     library(RwxDevice)
     win = wxHtmlParser_GetWindow(parser)   
     canvas = RwxCanvas(win, size = c(400, 400))
     asWxDevice(canvas)
     insertEmbeddedComponent(canvas, parser)
     txt = tag$GetContent(parser)
     eval(parse(text = txt))
     TRUE
  }

htmlButtonHandler =
function(handler, tag, parser)
{
     win = wxHtmlParser_GetWindow(parser)   
     b = wxButton(win, wxID_ANY, tag$GetParam("label"))
     e = parse(text = tag$GetContent(parser))
     b$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                    function(ev) {
                       eval(e)
                    })

     insertEmbeddedComponent(b, parser)     
     TRUE
 }  

 f = c("device.html", "examples/device.html")
 if(!any(file.exists(f)))
  stop("Can't find device.html")  
 f = f[file.exists(f)][1]

htmlViewer(f,
           tagHandlers = c(htmlTagHandlers(),
                           Rdevice = htmlRdeviceHandler,
                           button = htmlButtonHandler),
           run = TRUE)

