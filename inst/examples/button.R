library(RwxWidgets) 
wxInit()

# Define a function that will be called by the RApp class when it
# needs to bring up the "main" window.

OnInit <-
function(this)  # , cmdLineParser)
{
 cat("<R:OnInit>\n")
 f <- RFrame("RWxWidgets example",
              as.integer(c(50, 30)),
              as.integer(Size(450, 300)),
              OnQuit = function(event) cat("[R:::OnQuit]\n")
   #    ,     OnAbout = function(event) MessageBox("An example of RwxWidgets")
         )

 myFrame <<- f

 f$CreateStatusBar()
 f$SetStatusText("An example of R-wxWidgets events")

     # Can't use dynamic RTTI mechanism to create wxBoxSizer?
 sizer = wxBoxSizer(wxHORIZONTAL)

 callbacks =
  list("Hit me" = function(event, extra, second) {
                       cat("Reacting to the button being clicked\n")
                       .Call("R_wxEventHandler_Disconnect", connections[[1]])
                      },
       "Again, hit me" = function(event, extra, second) {
                             cat("A different reaction\n")
                             plot(rnorm(100), col = "red", main = "100 Random N(0,1)", ylim = c(-4, 4))
                       })

 buttons = lapply(names(callbacks),
                     function(label) {
                                 # This really should  be f and not sizer as sizer is not a wxWindow.
                        wxButton(f, wxID_ANY, label)
                     })
 
 sapply(buttons, 
         function(btn) 
             sizer$Add(btn, 0))

 print(sapply(buttons, wxWindow_GetId))  # or function(btn) btn$GetId())

 if(TRUE) {
   cat("Adding callbacks\n")
     # These connections allow us to disconnect.
   connections <<-
      lapply(seq(along = callbacks),
              function(i)
                 buttons[[i]]$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED, callbacks[[i]], "Extra argument", "And another")
                 # buttons[[i]]$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED, callbacks[[i]], i)
             )
 }

   # Now add the sizer with the buttons to the wxFrame.

 f$SetSizer(sizer)
 sizer$SetSizeHints(f)
        
 if(FALSE) {
   cat("Class info for wxFrame\n")
   print(getWxClassInfo(f))

   cat("Class info for wxButton\n")
   print(getWxClassInfo("wxButton"))
 }
 
 cat("</R:OnInit>\n")

  f$Show()

 cat("Children of top-level frame\n")
 kids = f$GetChildren()
 print(kids)

 TRUE
}  

   # Create the running App.
if(exists("use_wx_app") && use_wx_app) {
  app = RApp(OnInit = OnInit, run = TRUE)
} else
  OnInit()

