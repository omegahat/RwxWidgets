wxRadioButton =
function(parent, id, label, pos = wxDefaultPosition, size = wxDefaultSize, style = 0, validator = NULL, name = "radioButton")
{
  .Call("R_wxRadioButton_new", parent, as.integer(id), as.character(label), pos, size, as.numeric(bitlist(style)), validator, name)
}

wxRadioButton_SetValue =
function(this, value)
{
  .Call("R_wxRadioButton_SetValue", this, as.logical(value))
}

wxRadioButton_GetValue =
function(this)
{
  .Call("R_wxRadioButton_GetValue", this)
}  
