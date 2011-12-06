.First.lib = .onLoad =
function(...)
{
  # print(getLoadedDLLs())
  if(FALSE && is.loaded("addGtkEventHandler")) {
     cat("registered Gtk event handler\n")
     .C("addGtkEventHandler")
  }
}  
