library(RwxWidgets)

wxRB_SINGLE = as.integer(8)
#
# The goal of this "example" is to test the idea of creating
# radio buttons that are not in a group but that act as one.
# We want  to be able to have a collection of related radio buttons
# be located in different parent widgets and to manage them ourselves
# to turn


#
# We can find 
#
#
start =
function(app)
{

  win = RFrame("Test of Single Radio Buttons")

  vsizer = wxBoxSizer(wxVERTICAL)

  create =
  function(win, vsizer, two = FALSE, single = TRUE, style = 0, useCheckBox = FALSE) {
    sz = wxBoxSizer(wxHORIZONTAL)

    fixedStyle = !missing(style)
    grp = radioButtonGroup()
    sapply(letters[1:6],
           function(i) {
             if(!fixedStyle) {
               style = if(two && i == "d") wxRB_GROUP else 0
               if(single)
                 style = c(wxRB_SINGLE, style)
             } else {
               win = wxPanel(win, wxID_ANY)
             }

             if(useCheckBox) {
                 w = wxCheckBox(win, wxID_ANY, i)
             } else
                 w = wxRadioButton(win, wxID_ANY, i, style = style)
             
             grp$add(w, i)
             sz$Add(if(fixedStyle) win else w)
             if(fixedStyle)
               w$SetValue(FALSE)

           })

    if(useCheckBox)
      grp$set(6)
    vsizer$Add(sz)
  }


  checkBoxGroups =
    # Setup 3 different groups of within mutually exclusive buttons
    #  (A, B, C), (d, e) and "Single" by itself to test the boundary
    # condition of just one element.
    # This tests that the groups do behave independently of each other.
  function(win) {
    sz = wxBoxSizer(wxHORIZONTAL)
    sapply(list(LETTERS[1:3], letters[4:5], "Single"),
           function(labels) {
             grp = radioButtonGroup()
             sapply(labels, function(id) {
                             w = wxCheckBox(win, wxID_ANY, id)
                             grp$add(w)
                             sz$Add(w)
                           })
             grp$set(length(labels)) # last one is set.
           })
    vsizer$Add(sz)
  }

  create(win, vsizer)  # one large group style = 0 for all buttons
  create(win, vsizer, TRUE, FALSE) # two groups (a, b, c) & (d, e, f)
  create(win, vsizer, TRUE, TRUE)  # two groups and everything single
  create(win, vsizer, style = c(wxRB_GROUP, wxRB_SINGLE))  # put each button in its own panel.
  create(win, vsizer, style = 0)  # put each button in its own panel but with default style  

  create(win, vsizer, useCheckBox = TRUE)  # use a single collection of 6 checkboxes that are mutually exclusive

  checkBoxGroups(win)         # 3 groups of independent checkboxes each group though is mutually exclusive within the group.

  
  win$SetSizer(vsizer)
  vsizer$SetSizeHints(win)         
    
  win$Show()

  TRUE
}


if(FALSE) {
  RApp(OnInit = start, run = TRUE)
  wxEventLoop()
} else
  start()


