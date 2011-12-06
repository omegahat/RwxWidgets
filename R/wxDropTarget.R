RwxTextDropTarget =
function(OnDropText = NULL, OnEnter = NULL, OnDragOver = NULL)
{
  if(!is.null(OnDropText) && !is.function(OnDropText)) # allow C/C++ routine.
    stop("OnDropText must be a function")

  if(!is.null(OnEnter) && !is.function(OnEnter)) # allow C/C++ routine.
    stop("OnEnter must be a function")  
  
  .Call("R_RwxTextDropTarget", OnDropText, OnEnter, OnDragOver)
}

wxDropTarget_SetDataObject =
function()
{

}  


wxDropSource =
function(data, win, doDragDrop = TRUE)
{
  .Call("R_wxDropSource", data, win, as.logical(doDragDrop))
}
