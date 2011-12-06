wxTextCtrl =
function(parent, value = character(), style = 0, name = "wxTextCtrl", id = wxID_ANY, size = wxDefaultSize)
{
   style = bitlist(style)
   size = as(size, "RwxSize")

   .Call("R_wxTextCtrl_new", parent, as.integer(id), as.character(value), as.numeric(style), as.character(name), size)
}  

wxTextCtrl_Clear =
function(this)
  .Call("R_wxTextCtrl_Clear", this)


wxTextCtrl_IsMultiLine =
function(this)
  .Call("R_wxTextCtrl_IsMultiLine", this)


wxTextCtrl_AppendText =
function(this, text)
  .Call("R_wxTextCtrl_AppendText", this, as.character(text))

wxTextCtrl_GetNumberOfLines =
function(this)
  .Call("R_wxTextCtrl_GetNumberOfLines", this)


wxTextCtrl_GetValue =
function(this)
  .Call("R_wxTextCtrl_GetValue", this)

wxTextCtrl_SetValue =
function(this, text)
  .Call("R_wxTextCtrl_SetValue", this, as.character(text))


wxTextCtrl_SetEditable =
function(this, editable)
  .Call("R_wxTextCtrl_SetEditable", this, as.logical(editable))

wxTextCtrl_LoadFile =
function(this, fileName)
{
  if(!file.exists(fileName))
    stop("No such file") # What about URIs
  
  .Call("R_wxTextCtrl_LoadFile", this, path.expand(fileName))
}


wxTextCtrl_SetInsertionPoint =
function(this, pos)
{
  .Call("R_wxTextCtrl_SetInsertionPoint", this, as.numeric(pos))
}  

wxTextCtrl_SetInsertionPointEnd =
function(this)
{
  .Call("R_wxTextCtrl_SetInsertionPointEnd", this)
}  
