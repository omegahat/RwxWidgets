setGeneric("wxImage",
            function(name, type = wxBITMAP_TYPE_INDEX, index = -1) 
              standardGeneric("wxImage")
          )

setMethod("wxImage", c("character", "character"),
          function(name, type, index = -1) {
            .Call("R_wxImage_new_wxString_wxString_int", name, type, as.integer(index))
          })

setMethod("wxImage", c("character", "numeric"),
          function(name, type, index = -1) {
            .Call("R_wxImage_new_wxString_long_int", name, as.numeric(type), as.integer(index))
          })

setGeneric("wxImage_LoadFile",
           function(this, name, type= wxBITMAP_TYPE_ANY, index = -1) {
             standardGeneric("wxImage_LoadFile")
           })

setMethod("wxImage_LoadFile",
          c("wxImage", "character", "numeric"),
function(this, name, type = wxBITMAP_TYPE_ANY, index = -1)
{
  .Call("R_wxImage_LoadFile", as.character(name), as.numeric(type), as.integer(index))
})

setMethod("wxImage_LoadFile",
          c("wxImage", "character", "character"),
function(this, name, type = wxBITMAP_TYPE_ANY, index = -1)
{
  .Call("R_wxImage_LoadFile", name, type, as.integer(index))
})

wxImage_Rotate =
function(this, angle, rotationCentre, interpolating = TRUE, offsetAfterRotation = NULL)
{
  .Call("R_wxImage_Rotate", this, as.numeric(angle), rotationCentre, as.logical(interpolating), offsetAfterRotation)
}

wxImage_Rescale =
function(this, width, height)
{
  .Call("R_wxImage_Rescale", this, as.integer(width), as.integer(height))
}


wxImage_Scale =
function(this, width, height)
{
  .Call("R_wxImage_Scale", this, as.integer(width), as.integer(height))
}




wxImage_Ok =
function(this)
{
 .Call("R_wxImage_Ok", this)  
}


wxImage_ConvertToBitmap =
function(this)
  .Call("R_wxImage_ConvertToBitmap", this)

setAs("wxImage", "wxBitmap",
       function(from) {
         wxImage_ConvertToBitmap(from)
       })
