# THis is intended to show how to deal with two wxStaticBoxSizer()
# objects in a frame. If we add them both to the frame, then they go on
# top of each other. Instead, we create two panels and associate each
# sizer with one of these and then we add the panels to the frame
# via a sizer for that frame. So it is more indirect, but logical.

library(RwxWidgets)

f = function(this)
{

  f = RFrame("StaticBoxSizer example",
             size = c(400, 400))

  topSizer = wxBoxSizer(wxHORIZONTAL)

  p1 = wxPanel(f)

     sz = wxStaticBoxSizer(wxHORIZONTAL, p1, "My Example Label")

    btn = wxButton(p1, wxID_ANY, label = "Hit me")
    sz$Add(btn)
  
    p1$SetSizer(sz)
    sz$SetSizeHints(p1)

  p2 = wxPanel(f)

     sz = wxStaticBoxSizer(wxHORIZONTAL, p2, "A different label")

    btn = wxButton(p2, wxID_ANY, label = "Hit me")
    sz$Add(btn)
  
    p2$SetSizer(sz)
    sz$SetSizeHints(p2)

  topSizer$Add(p1, 1, wxEXPAND)
  topSizer$Add(p2, 1, wxEXPAND)
  f$SetSizer(topSizer)
  topSizer$SetSizeHints(f)  
  
  f$Show()
  
}

RApp(OnInit = f, run = TRUE)
