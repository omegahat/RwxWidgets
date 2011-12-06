wxDialog_ShowModal =
function(this)
{  
  .Call("R_wxDialog_ShowModal", this)
}


wxDialog_EndModal =
function(this, code)
{  
  .Call("R_wxDialog_EndModal", this, as.integer(code))
}

