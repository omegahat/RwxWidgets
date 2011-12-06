wxDefaultDateTime =
function()
  .Call("R_get_wxDefaultDateTime")

wxDateTime =
function(time)
  .Call("R_wxDateTime_new", as.numeric(time))

wxDateTime_GetTicks =
function(time)
  .Call("R_wxDateTime_GetTicks", time)

wxDateTime_IsLaterThan =
function(time, other)
  .Call("R_wxDateTime_IsLaterThan", time, other)


setAs("wxDateTime", "POSIXct",
       function(from) {
          v = from$GetTicks()
          class(v) = c("POSIXt", "POSIXct")
          v
        })

setAs("POSIXct", "wxDateTime",
       function(from) {
          wxDateTime(as.numeric(from))
        })

