setGeneric("wxBitmap",
           function(data, type, width, height, depth) {
             standardGeneric("wxBitmap")
           })

setMethod("wxBitmap", c("character", "numeric"),
           function(data, type, width, height, depth) {
             .Call("R_wxBitmap_new_wxString_long", data, as.numeric(type))
           })


wxBitmap_GetWidth =
  function(this)
  .Call("R_wxBitmap_GetWidth", this)

wxBitmap_GetHeight =
  function(this)
  .Call("R_wxBitmap_GetHeight", this)

wxBitmap_GetDepth =
  function(this)
  .Call("R_wxBitmap_GetDepth", this)

getWxNullBitmap =
function()
 .Call("R_get_wxNullBitmap")


wxBitmap_ConvertToImage =
function(this)
  .Call("R_wxBitmap_ConvertToImage", this)

setAs("wxBitmap", "wxImage",
       function(from) {
         wxBitmap_ConvertToImage(from)
       })

