wxEventLoop  =
function()
{
  .Call("R_wxEventLoop_new")
}  


wxEventLoop_Run  =
function(loop = wxEventLoop())
{
  .Call("R_wxEventLoop_Run", loop)
}  


wxEventLoop_Exit  =
function(loop = wxEventLoop_GetActive(), returnCode = 0)
{
  .Call("R_wxEventLoop_Exit", loop, as.integer(returnCode))
}  



wxEventLoop_Pending  =
function(loop)
{
  .Call("R_wxEventLoop_Pending", loop)
}

wxEventLoop_Dispatch  =
function(loop)
{
  .Call("R_wxEventLoop_Dispatch", loop)
}  


wxEventLoop_GetActive  =
function()
{
  .Call("R_wxEventLoop_GetActive")
}  


wxEventLoop_SetActive  =
function(loop)
{
  .Call("R_wxEventLoop_SetActive", loop)
}  
