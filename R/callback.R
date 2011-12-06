wxEvtHandler_AddCallback =
function(this, eventType, fun, ...,
         objId = this$GetId(), computeEventClass = TRUE,
         .extraArgs = list(...))
{
  eventType = as.integer(eventType)
  objId = as.integer(objId)
  fun = as.function(fun)

  args = list(...)

  if(length(args)) {
    i = agrep("objId", names(args))
    if(length(i)) 
      warning("You possibly mis-spelled ", names(...)[i],
               "incorrectly and meant 'objId'. If you don't seem to catch any events on this callback, that is probably your problem.")
  }
  
  .Call("R_Rwx_Connect", this, objId, eventType, fun, NULL, NULL, .extraArgs, as.logical(computeEventClass))
}  
