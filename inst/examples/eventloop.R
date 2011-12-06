library(RwxWidgets)
#.Call("R_wxWidgets_wxInitialize")
#source("examples/button.R")

init = function(app) {
  cat("Creating GUI\n")
  print(app)
  f = RFrame("Event loop test", size = c(400, 400))
  b = wxButton(f, wxID_ANY, "Break Loop")
  b$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                function(ev) {
                   mapp = .Call("R_wxApp_wxTheApp")
                   print(mapp)
                  .Call("R_wxApp_ExitMainLoop", app)
                })
#  f$Add(b)
  f$Show()
  TRUE
#  FALSE
}

myApp = RApp(OnInit = init, run = FALSE)
wxEventLoop()

cat("Exited the event loop\n")

app = .Call("R_wxApp_wxTheApp")
print(app)

#XXX app at this point is NULL so we fail in the next steps.

#.Call("R_wxAppBase_MainLoop", myApp)


eloop = wxEventLoop()

init(app)
wxEventLoop_Run(eloop)



