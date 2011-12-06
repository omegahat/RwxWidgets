wxListView_GetFirstSelectedItem =
function(this)
{
  .Call("R_wxListView_GetFirstSelectedItem", this)
}

wxListView_GetNextSelectedItem =
function(this, item)
{
  .Call("R_wxListView_GetNextSelectedItem", this, as.numeric(item))
}
