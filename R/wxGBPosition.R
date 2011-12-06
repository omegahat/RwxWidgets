setGeneric("wxGBPosition",
           function(row = 1, col = 1)
             standardGeneric("wxGBPosition"))

setMethod("wxGBPosition",
           c("numeric", "numeric"),
           function(row = 1, col = 1)
              .Call("R_wxGBPosition_new_int_int", as.integer(row), as.integer(col)))


setMethod("wxGBPosition",
           c("missing", "missing"),
           function(row = 1, col = 1)
              .Call("R_wxGBPosition_new"))

