library(RwxWidgets)
wxInit()

f =  RFrame("RWxWidgets example",
              as.integer(c(50, 30)),
              as.integer(200, 100))

sz = wxBoxSizer(wxHORIZONTAL)
p = wxPanel(f, size = c(200, 200))
sz$Add(p, 1, wxEXPAND)
f$SetSizer(sz)
sz$SetSizeHints(f)
p$AddCallback(wxEVT_LEFT_DOWN, function(...) cat("down\n"))

#sub = wxFrame(f)
#f$Add(sub)
#sub$AddCallback(wxEVT_PAINT, function(...) cat("painting\n"))
f$Show()

eloop = wxEventLoop()
wxEventLoop_Run(eloop)
