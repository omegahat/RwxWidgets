wxControlWithItems_GetSelection =
function(this)
  .Call("R_wxControlWithItems_GetSelection", this)


wxControlWithItems_Select =
function(this, n)
  .Call("R_wxControlWithItems_Select", this, as.integer(n))

wxControlWithItems_SetSelection =
function(this, n)
  .Call("R_wxControlWithItems_Select", this, as.integer(n))
