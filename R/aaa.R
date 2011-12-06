cumBitOr = bitlist =
function(...)
{
  x = unlist(list(...))
  if(length(x) == 1)
    return(x)

  ans = x[1]
  for(i in 2:length(x)) {
    ans = bitOr(ans, x[i])
  }
  ans
}



wxDefaultPosition = as.integer(c(200, 220))
wxDefaultSize = as.integer(c(400, 400))

