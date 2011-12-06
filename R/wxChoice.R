wxDefaultValidator = NULL

wxChoice =
function(parent, id, pos = wxDefaultPosition, size = wxDefaultSize, choices, style = 0,
           validator = wxDefaultValidator, name = "choice")
{
  .Call("R_wxChoice_new", parent, as.integer(id), pos, size, as.character(choices), bitlist(style), validator, as.character(name))
}  
