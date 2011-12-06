wxDialog =
function(parent, id = wxID_ANY, title, pos = wxDefaultPosition, size = wxDefaultSize,
             style = wxDEFAULT_DIALOG_STYLE, name = "dialog")  
{
  style = as.numeric(bitlist(style))
  .Call("R_wxDialog_new", parent, as.integer(id),  as.character(title),
                          pos, size, style, as.character(name))
}
