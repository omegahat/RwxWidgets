wxID_ANY=as.integer(-1)

wxHORIZONTAL = as.integer(4)
wxVERTICAL = as.integer(8)


 wxVSCROLL  =  as.integer(0x80000000)
 wxHSCROLL  =  as.integer(0x40000000)
 wxCAPTION  =  as.integer(0x20000000)

wxSP_3DSASH = as.integer(0x0100)
wxSP_3DBORDER = as.integer(0x0200)
wxSP_BORDER = as.integer(0x0200)
wxSP_3D = as.integer(0x0300) # bitOr(wxSP_3DSASH, wxSP_3DBORDER)

wxTAB_TRAVERSAL = as.integer(0x000800000)

wxPROCESS_ENTER = as.integer(0x0400)
 wxPASSWORD = as.integer(0x0800)
 wxTE_NO_VSCROLL = as.integer(0x0002)
 wxTE_AUTO_SCROLL = as.integer(0x0008)
 wxTE_READONLY = as.integer(0x0010)
 wxTE_MULTILINE = as.integer(0x0020)
 wxTE_PROCESS_TAB = as.integer(0x0040)
 wxTE_LEFT = as.integer(0x0000)
 wxTE_RICH = as.integer(0x0080)
 wxTE_PROCESS_ENTER = as.integer(0x0400)
 wxTE_PASSWORD = as.integer(0x0800)
 wxTE_AUTO_URL = as.integer(0x1000)
 wxTE_NOHIDESEL = as.integer(0x2000)
 wxTE_CENTER = wxALIGN_CENTER_HORIZONTAL
 wxTE_RIGHT = wxALIGN_RIGHT
 wxTE_CENTRE = wxTE_CENTER
 wxTE_DONTWRAP = wxHSCROLL
 wxTE_CHARWRAP = as.integer(0x4000)
 wxTE_WORDWRAP = as.integer(0x0001)
 wxTE_BESTWRAP = as.integer(0x0000)
 wxTE_LINEWRAP = wxTE_CHARWRAP
 wxTE_RICH2 = as.integer(0x8000)
 wxTE_CAPITALIZE = wxTE_RICH2
 wxTE_CAPITALIZE = as.integer(0)




wxLB_SORT      =     as.integer(0x0010)
 wxLB_SINGLE   =     as.integer(0x0020)
 wxLB_MULTIPLE =     as.integer(0x0040)
 wxLB_EXTENDED  =    as.integer(0x0080)
 wxLB_OWNERDRAW =    as.integer(0x0100)
 wxLB_NEEDED_SB =    as.integer(0x0200)
 wxLB_ALWAYS_SB =    as.integer(0x0400)
 wxLB_HSCROLL   =    wxHSCROLL
 wxLB_INT_HEIGHT =   as.integer(0x0800)


exEVT_GRID_COL_SIZE = as.integer(1589)

wxEVT_GRID_CELL_LEFT_CLICK = as.integer(1580)
wxEVT_GRID_CELL_RIGHT_CLICK = as.integer(1581)
wxEVT_GRID_CELL_LEFT_DCLICK = as.integer(1582)
wxEVT_GRID_CELL_RIGHT_DCLICK = as.integer(1583)
wxEVT_GRID_LABEL_LEFT_CLICK = as.integer(1584)
wxEVT_GRID_LABEL_RIGHT_CLICK = as.integer(1585)
wxEVT_GRID_LABEL_LEFT_DCLICK = as.integer(1586)
wxEVT_GRID_LABEL_RIGHT_DCLICK = as.integer(1587)
wxEVT_GRID_ROW_SIZE = as.integer(1588)
wxEVT_GRID_COL_SIZE = as.integer(1589)
wxEVT_GRID_RANGE_SELECT = as.integer(1590)
wxEVT_GRID_CELL_CHANGE = as.integer(1591)
wxEVT_GRID_SELECT_CELL = as.integer(1592)
wxEVT_GRID_EDITOR_SHOWN = as.integer(1593)
wxEVT_GRID_EDITOR_HIDDEN = as.integer(1594)
wxEVT_GRID_EDITOR_CREATED = as.integer(1595)
wxEVT_GRID_CELL_BEGIN_DRAG = as.integer(1596)

wxSP_ARROW_KEYS = as.integer(0x1000)

wxNOT_FOUND = -1


wxDEFAULT_DIALOG_STYLE = bitlist(wxCAPTION, wxSYSTEM_MENU, wxCLOSE_BOX)
wxCHOICEDLG_STYLE = bitlist(wxDEFAULT_DIALOG_STYLE, wxOK , wxCANCEL , wxCENTRE)
