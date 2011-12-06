.onAttach =
function(lib, pkg)
{
   # Two initialization methods. Use init although
   # we were also using wxInitialize interactively in tests.
   #  .Call("R_wxWidgets_wxInitialize");
  # .Call("R_wxWidgets_init", "R");
}

wxEntry =
  #
  # At present, can only be called once as this does the initialization and runs the loop.
  # We will separate these two steps later on.
function(args = "Rwx")
{
   doEntryStart = FALSE  
   .Call("R_wxWidgets_init", args, as.logical(doEntryStart))
}  

wxInit =
function(addEventHandler = TRUE)
{
  .Call("R_wxWidgets_wxInitialize")
  if(addEventHandler) {
    if(Sys.info()["sysname"] == "Darwin" && Sys.getenv("R_GUI_APP_VERSION") == "") {
        if(!require(CarbonEL))
          warning("Cannot load the package CarbonEL. Please install it to get event handling.")
    } else {
        if(is.loaded("addGtkEventHandler")) {
          cat("registered Gtk event handler\n")
          .C("addGtkEventHandler")
          if(is.loaded("gdk_flush"))
            .C("gdk_flush")
        } else
          warning("Cannot add event handler")
   }
  }
}  
