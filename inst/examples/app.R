library(RwxWidgets)

init =
  function(app) {
    f = RFrame("My frame")
    f$Show()
    TRUE
  }
RApp(init, run = TRUE)
