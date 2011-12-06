library(RwxWidgets)
# source("showDist.R")
# My version
showDist = function(dist, sampleSize = 10, stat = mean, whichDev = dev.cur())
{
  browser()
  print(dist)
  plot(runif(10))
}


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



myHTMLHandlers =
  function(myEnv = new.env(),
           Rdevice = htmlRdeviceHandler, 
           init = htmlInitHandler)
{
  myEnv$env = myEnv  # put a reference to myEnv into itself so we can refer to it in code. circular reference.

  environment(Rdevice) = myEnv
  environment(init) = myEnv

  list( Rdevice = Rdevice, init = init,
        listbox = function(handler, tag, parser) {
           eval(parse(text = tag$GetContent(parser)), myEnv) # myEnv not env
        })
} 

htmlViewer("in2.html", 
           tagHandlers = c(htmlTagHandlers(), myHTMLHandlers()),
           run = TRUE)

