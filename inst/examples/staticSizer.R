library(RwxWidgets)


f = function(this)
{

  f = RFrame("StaticBoxSizer example",
             size = c(400, 400))

  sz = wxStaticBoxSizer(wxHORIZONTAL, f, "My Example Label")

  btn = wxButton(f, wxID_ANY, label = "Hit me")
  sz$Add(btn)
  
  f$SetSizer(sz)
  sz$SetSizeHints(f)
  
  f$Show()
  
}

RApp(OnInit = f, run = TRUE)
