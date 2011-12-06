# This is an experiment to see if we can avoid creating an application.
# And the answer is yes.
# This illustrates how we can
#  a) switch between R's event loop and wxWidget's and not
#  b) create multiple top-level windows as if they were apps
#     rather than just having a single wxApp.
#
# This now illustrates how to integrate the R and wxEvent event loops on Linux/Unix
# i.e. with gtk. We use the same approach we used in RGtk/RGtk2 of adding the
# X11 file descriptor to the R event loop.  This doesn't handle timers and.

# If addGtkEventHandler

olibrary(RwxWidgets)
wxInit()
autoEventLoop = FALSE

init = function(loop) {
    # We don't need the loop passed in here
    # as we can get it via wxEventLoop_GetActive.

  cat("Creating GUI\n")
  f = RFrame("Event loop test", size = c(400, 400))
  sz = wxBoxSizer(wxHORIZONTAL)
  
  b = wxButton(f, wxID_ANY, "Break Loop")
      b$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                     function(ev) {
                       if(!autoEventLoop) {
                         l = wxEventLoop_GetActive()
                         print(l) # is it the same as the original loop we were passed?
                         wxEventLoop_Exit(loop)
                       } else
                         cat("No explicit event loop running from wxWidgets\n")
                })
  sz$Add(b, 1, wxEXPAND)

  b = wxButton(f, wxID_ANY, "Sample")
  b$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                function(ev) {
                  print(sample(1:6, 1))
                })  
  sz$Add(b, 1, wxEXPAND)

  f$SetSizer(sz)
  sz$SetSizeHints(f)
  
  f$Show()
  TRUE
}


# If this routine is available, invoke it and
# the event loop will be andled automatically for us.
# Note that we do want to call gdk_flush periodically
# 
if(is.loaded("addGtkEventHandler")) {
  .C("addGtkEventHandler")
  autoEventLoop = TRUE
  init(eloop)
  .C("gdk_flush")
} else {
 eloop = wxEventLoop()
 init(eloop)  
 wxEventLoop_Run(eloop)
}

