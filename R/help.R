if(!isGeneric("?")) {
  setGeneric("?", function (e1, e2) standardGeneric("?"))
  setMethod("?", c("ANY", "ANY"), get("?", "package:utils"))
}

# obj?"Show"
setMethod("?", c("wxObject", "ANY"), function(e1, e2) cat("Help for", class(e1), deparse(e2), "\n"))

setMethod("?", c("wxObject", "character"), function(e1, e2) cat("Help for ", class(e1), "::", e2, "\n", sep = ""))

# ?obj
setMethod("?", c("wxObject", "missing"), function(e1, e2) cat("Help for class", class(e1), "\n"))
