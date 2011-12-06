RwxDirTraverser =
function(OnFile = NULL, OnDir = NULL, OnOpenError = NULL)
{
   .Call("R_RwxDirTraverser_new", OnFile, OnDir, OnOpenError)
}

wxDir =
function(dir = character())
{
  .Call("R_wxDir_new", as.character(dir))
}  


wxDir_Traverse =
function(this, sink, filespec = "", flags = wxDIR_DEFAULT)
{
   flags = bitlist(flags)
   .Call("R_wxDir_Traverse", this, sink, as.character(filespec), flags)
}    


   

