library(RwxWidgets)

myHTMLHandlers =
function()
{  

init <- character()
callback <- character()

initHandler =
function(handler, tag, parser)
{
  init <<- tag$GetContent(parser)
}
callbackHandler =
function(handler, tag, parser)
{
   callback <<- tag$GetContent(parser)
}

 reset =
  function() {
    init <<- character()
    callback <<- character()
  }

spinCtrlHandler =
function(handler, tag, parser) {
   # go process the sub nodes. Must have </spinctrl>
   reset()
   wxHtmlTagHandler_ParseInner(handler, tag)
   editable = tag$GetParam("editable")

   

   init = ""
   callback = ""

      # have to loop over the children as we may have comments, blank elements, e.g. new lines
      # and so on.
   el = tag$GetChildren(FALSE)   
   while(!is.null(el)) {
     name = tolower(el$GetName())  # they come in as all upper case, e.g. INIT
     print(name)
     if(name == "init")
      init = el$GetContent(parser)
     else if(name == "callback")
      callback = el$GetContent(parser)

     el = el$GetNextSibling()     
   }

   cat(paste("The spinCtrl code was\n editable", editable, "\ninit = ", init, "\ncallback = ", callback, "\n"))

}

 list(spinctrl = spinCtrlHandler, callback = callbackHandler, init = initHandler)
}


htmlViewer("genericHTMLElements.html", 
           tagHandlers = c(htmlTagHandlers(), myHTMLHandlers()),
           run = FALSE, app = NULL)
