library(RwxWidgets)
library(bitops)

h = htmlFormTagHandlers()

f = c("form.html", "examples/form.html")
if(!any(file.exists(f)))
 stop("Can't find form.html")  
f = f[file.exists(f)][1]

htmlViewer(f, tagHandlers = h, run = TRUE)


