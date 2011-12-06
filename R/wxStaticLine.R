wxStaticLine =
function(parent, id = wxID_ANY, pos = wxDefaultPosition, size = wxDefaultSize,
             style = wxLI_HORIZONAL, name = "staticLine")
{
  style = as.numeric(bitlist(style))
  size = as(size, "RwxSize")
  pos = as(pos, "RwxPoint")
  
  .Call("R_wxStaticLine_new", parent, as.integer(id), pos, size, style, as.character(name))
}  
