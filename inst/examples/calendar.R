library(RwxWidgets)
wxInit()

f = RFrame( size = c(50, 50))
cal = wxCalendarCtrl(f)
f$SetSizer(sz <- wxBoxSizer(wxHORIZONTAL))
sz$Add(cal, 1, wxEXPAND)
cal$SetSize(50, 50)
f$SetSizer(sz)
sz$SetSizeHints(f)
f$Show()

print(f$GetChildren())

#wxEventLoop()$Run()
