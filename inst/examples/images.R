library(RwxWidgets)
wxInit()
wxNullBitmap = getWxNullBitmap()

#imageNames = list.files("~/pal2", full.names = TRUE)[1:3]
imageNames = list.files("~", pattern = "\.png", full.names = TRUE)
images = wxImageList()
sapply(imageNames, function(filename) images$Add(wxBitmap(filename, wxBITMAP_TYPE_PNG)))


f = RFrame("PNG Example", size = c(600, 300))
sz = wxBoxSizer(wxHORIZONTAL)
sz$SetSizeHints(f)
f$SetSizer(sz)

li = wxListCtrl(f) 
li$SetImageList(images, wxIMAGE_LIST_NORMAL)

sz$Add(li, 1, c(wxEXPAND, wxALL))

sapply(seq(along = imageNames),
        function(i) {
	    li$InsertItem(i - 1, basename(imageNames[i]), i-1)
        })


f$Show()
wxEventLoop()$Run()

