RwxDialog =
function(parent, id = wxID_ANY, title, pos = wxDefaultPosition, size = wxDefaultSize,
             style = wxDEFAULT_DIALOG_STYLE, name = "RwxDialog")  
{
  style = bitlist(style)
  .Call("R_RwxDialog_new", parent, as.integer(id),  as.character(title),
               pos, size, style, as.character(name))
}
