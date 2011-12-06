wxListBox =
function(parent, id, pos = wxDefaultPosition, size = wxDefaultSize, choices, style = 0,
         validator = NULL, name = "listBox")
{
  .Call("R_wxListBox_new", parent, as.integer(id), pos, size, as.character(choices),
                            as.numeric(bitlist(style)), validator, name)
}

wxListBox_IsSelected =
function(this, n)
{
  .Call("R_wxListBox_IsSelected", this, as.integer(n))
}

wxListBox_GetSelections = wxChoice_GetSelections =
function(this)
{
  .Call("R_wxListBox_GetSelections", this)
}

wxListBox_SetSelections =
function(this, vals)
{
  warning("not implemented in wxWidgets")
   #XXX getWxClassInfo() is not including wxControlWithContainers for some reason.
  tmp = .Call("R_wxControlWithItems_cast", this)
  sapply(vals, function(i) wxControlWithItems_Select(tmp, i))
}

wxListBox_InsertItems =
function(this, items, pos)
{
  .Call("R_wxListBox_InsertItems", this, as.character(items), pos)
}  

wxListBox_Set =
function(this, choices)
{
  .Call("R_wxListBox_Set", this, as.character(choices))
}  
