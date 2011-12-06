wxCheckBox =
function(parent, id = -1, label, pos = wxDefaultPosition, size = wxDefaultSize, style = 0, validator = NULL, name = "")
{
 .Call("R_wxCheckBox_new", parent, as.integer(id), as.character(label), pos,
                           size, as.numeric(bitlist(style)), validator, as.character(name))
}

wxCheckBox_IsChecked =
function(this)
{
  .Call("R_wxCheckBox_IsChecked", this)
}

wxCheckBox_GetValue =
function(this)
{
  .Call("R_wxCheckBox_GetValue", this)
}

wxCheckBox_SetValue =
function(this, value)
{
  .Call("R_wxCheckBox_SetValue", this, as.logical(value))
}
    
