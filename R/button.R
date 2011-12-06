wxButton =
function(parent, id = wxID_ANY, label, pos = wxDefaultPosition, size = wxDefaultSize, clickHandler = NULL, name = "")
{
  .Call("R_wxButton_new", parent, as.integer(id), as.character(label), pos, size, clickHandler, as.character(name))
}

wxButton_GetLabel =
function(this)
{
  .Call("R_wxButton_GetLabel", this)
}  


wxButton_SetLabel =
function(this, label)
{
  .Call("R_wxButton_SetLabel", this, as.character(label))
}  
