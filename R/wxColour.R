
setAs("character", "wxColour",
       function(from) {
           .Call("R_wxGetColour", toupper(from))
       })
