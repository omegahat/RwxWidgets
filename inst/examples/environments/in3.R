library(RwxWidgets)
# source("showDist.R")
# My version
showDist = function(dist, sampleSize = 10, stat = mean, whichDev = dev.cur())
{
  print(dist)
  print(sampleSize)
  print(stat)
  plot(runif(10))
}


myHTMLHandlers =
function()
{
  htmlRdeviceHandler =
  function(handler, tag, parser) {
     library(RwxDevice)
     win = wxHtmlParser_GetWindow(parser)
     canvas = RwxCanvas(win, size = c(400, 400))
     asWxDevice(canvas)
     tname = tag$GetParam("name")
     if ( tname != "") 
       assign(tname, dev.cur(),  env)

     insertEmbeddedComponent(canvas, parser)
     txt = tag$GetContent(parser)
     if(nchar(txt) > 0)
       eval(parse(text = txt), env) 
  }

  htmlInitHandler =
  function(handler, tag, parser)
  {
     initCode = tag$GetContent(parser)
     env$parser = parser  # make the parser available for other handlers.
     f = parse(text = initCode)
     eval(f, env) 
  }

  env = environment(htmlInitHandler)
   
  list( Rdevice = Rdevice, init = init,
        listbox = function(handler, tag, parser) {
           eval(parse(text = tag$GetContent(parser)), env) # myEnv not env
        })
} 

htmlViewer("in3.html", 
           tagHandlers = c(htmlTagHandlers(), myHTMLHandlers()),
           run = TRUE)

