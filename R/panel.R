wxPanel =
function(parent, id = wxID_ANY, pos = wxDefaultPosition, size = wxDefaultSize, style = wxTAB_TRAVERSAL, name = "panel")
{
  style = as.numeric(bitlist(style)) # style is long, will bitlist truncate with integers?XXX
  size = as(size, "RwxSize")
  pos = as(pos, "RwxSize")
  
  .Call("R_wxPanel_new", parent, as.integer(id), pos, size, style, name)
}  



