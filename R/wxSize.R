wxSize =
function(width, height, .addFinalizer = TRUE)
{
  if(missing(height) && length(width) == 2)
    height = width[2]

  .Call("R_wxSize_new", as.integer(width), as.integer(height), .addFinalizer)
}  

wxSize_GetWidth =
function(this)
  .Call("R_wxSize_GetWidth", this)

wxSize_GetHeight =
function(this)
  .Call("R_wxSize_GetHeight", this)


setAs("numeric", "RwxSize",
      function(from) {

        if(length(from) == 1)
          from = rep(from, 2)

        wxSize(from[1], from[2])
      })

