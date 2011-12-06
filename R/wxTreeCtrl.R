wxTreeCtrl =
function(parent, id, pos = wxDefaultPosition, size = wxDefaultSize,
           style = wxTR_HAS_BUTTONS, validator = NULL, name = "treeCtrl")
{
  style = bitlist(style)
  size = as(size, "RwxSize")
  pos = as(pos, "RwxPoint")
  
  .Call("R_wxTreeCtrl_new", parent, as.integer(id), pos, size, style, validator, as.character(name))
}

wxTreeCtrl_AddRoot   =
function(this, text, image = -1, selImage = -1, data = NULL)
{
  .Call("R_wxTreeCtrl_AddRoot", this, as.character(text), as.integer(image), as.integer(selImage), data)
}

wxTreeCtrl_AppendItem   =
function(this, parent, text, image = -1, selImage = -1, data = NULL)  
  .Call("R_wxTreeCtrl_AppendItem", this, as(parent, "wxTreeItemId"), as.character(text),
                                as.integer(image), as.integer(selImage), data)


wxTreeCtrl_InsertItem   =
function(this, parent, previous, text, image = -1, selImage = -1, data = NULL)  
  .Call("R_wxTreeCtrl_InsertItem", this,
                                as(parent, "wxTreeItemId"),
                                as(previous, "wxTreeItemId"),
                                as.character(text),
                                as.integer(image), as.integer(selImage), data)

wxTreeCtrl_AssignButtonsImageList =
  function(this, imageList)
    .Call("R_wxTreeCtrl_AssignButtonsImageList", this, as(imageList, "wxImageList"))

wxTreeCtrl_AssignImageList =
  function(this, imageList)
    .Call("R_wxTreeCtrl_AssignImageList", this, as(imageList, "wxImageList"))

wxTreeCtrl_SetImageList =
  function(this, imageList)
    .Call("R_wxTreeCtrl_AssignImageList", this, as(imageList, "wxImageList"))


wxTreeCtrl_SetItemBackgroundColour =
  function(this, item, colour)
    .Call("R_wxTreeCtrl_SetItemBackgroundColour", this, as(item, "wxTreeItemId"), as(colour, "wxColour"))

wxTreeCtrl_SetItemTextColour =
  function(this, item, colour)
    .Call("R_wxTreeCtrl_SetItemTextColour", this, as(item, "wxTreeItemId"), as(colour, "wxColour"))


wxTreeCtrl_EnsureVisible = 
  function(this, item)
    .Call("R_wxTreeCtrl_EnsureVisible", this, as(item, "wxTreeItemId"))

wxTreeCtrl_ScrollTo = 
  function(this, item)
    .Call("R_wxTreeCtrl_ScrollTo", this, as(item, "wxTreeItemId"))

wxTreeCtrl_Collapse = 
  function(this, item)
    .Call("R_wxTreeCtrl_Collapse", this, as(item, "wxTreeItemId"))

wxTreeCtrl_Expand = 
  function(this, item)
    .Call("R_wxTreeCtrl_Expand", this, as(item, "wxTreeItemId"))

wxTreeCtrl_Toggle = 
  function(this, item)
    .Call("R_wxTreeCtrl_Toggle", this, as(item, "wxTreeItemId"))

wxTreeCtrl_GetItemText = 
  function(this, item)
    .Call("R_wxTreeCtrl_GetItemText", this, as(item, "wxTreeItemId"))


wxTreeCtrl_GetItemParent = 
  function(this, item)
    .Call("R_wxTreeCtrl_GetItemParent", this, as(item, "wxTreeItemId"))


wxTreeCtrl_SetItemImage = 
  function(this, item, image, which = wxTreeItemIcon_Normal)
    .Call("R_wxTreeCtrl_SetItemImage", this, as(item, "wxTreeItemId"), as.integer(image),
                     which)  #XXX


wxTreeCtrl_HitTest = 
  function(this, point)
    .Call("R_wxTreeCtrl_HitTest", this, point)


if(FALSE) {
wxTreeCtrl_SetItemSelectedImage = 
  function(this, item, image)
    .Call("R_wxTreeCtrl_SetItemSelectedImage", this, as(item, "wxTreeItemId"), as.integer(image))
}

wxTreeCtrl_GetSelections =
  function(this)
    .Call("R_wxTreeCtrl_GetSelections", this)


#########################

wxTreeItemId_IsOk =
function(this)
  .Call("R_wxTreeItemId_IsOk", this)

###################
wxTreeEvent_GetItem =
  function(ev)
   .Call("R_wxTreeEvent_GetItem", ev)

