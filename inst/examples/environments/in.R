library(RwxWidgets)
# source("showDist.R")
# My version
showDist = function(dist, whichDev = dev.cur())
{
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
     if ( tname != "") {
         # why not simply
       assign(tname, dev.cur(),  myEnv)
        # eval(parse(text = paste(tname, "<<- dev.cur()" )), myEnv) #XXX need to tell eval() where to do the evaluation.

       # Recall also that we could assign canvas to a variable in myEnv and allow the
       # R code doing plots to use canvas$plot(..) or get the device number from the object.
     }

     insertEmbeddedComponent(canvas, parser)
     txt = tag$GetContent(parser)
     eval(parse(text = txt), myEnv) # tell eval relative to which environment.
  }

htmlInitHandler =
function(handler, tag, parser)
{
     initCode = tag$GetContent(parser)
     f = parse(text = initCode) 
     eval(f, myEnv)  #XXX env = myEnv
 }

htmlListBoxHandler =
function(handler, tag, parser)
{
     c = tag$GetParam("choices")
            # If you want to get the variable, use get(c)
            # but you don't even need this as the code will find the
            # variable choices
     cList = eval(parse(text = c), myEnv)  
     win = wxHtmlParser_GetWindow(parser)   
     lb = wxListBox(win, wxID_ANY, wxLB_SINGLE, choices = choices) # cList)
     insertEmbeddedComponent(lb, parser)

# Prepare the code to reassign the value of the variable 
# when the listbox is changed - note we add one because of the 0-based
# indexing in wxWidgets.

     f = parse(text = tag$GetContent(parser))
     lbcb = function(ev) {
               obj = ev$GetEventObject()
               lbv = obj$GetSelections()
               assign('listbox_value', lbv + 1, myEnv)
               eval(f, myEnv)
            }
#     environment(lbcb) = parent.frame()
     print("I am in the list box HTML handler")

     lb$AddCallback(wxEVT_COMMAND_LISTBOX_SELECTED, lbcb)
}  



myHTMLHandlers =
  function(myEnv = new.env(),
           Rdevice = htmlRdeviceHandler, 
           listbox = htmlListBoxHandler, 
           init = htmlInitHandler)
{

  myEnv$xx = 200
  myEnv$curDist = "Normal"
  myEnv$choices = c('Normal','Uniform', 'Beta', 'Exponential')



  myEnv$myEnv = myEnv  # put a reference to myEnv into itself so we can refer to it in code. circular reference.
  
            # Create an environment for the call backs to share 
  print("I am in myHandlers and myEnv is:")
  print(myEnv)

  environment(Rdevice) = myEnv
  environment(init) = myEnv
  environment(listbox) = myEnv

  list( Rdevice = Rdevice, init = init, listbox = listbox)
} 

htmlViewer("in.html", 
           tagHandlers = c(htmlTagHandlers(), myHTMLHandlers()),
           run = TRUE)

