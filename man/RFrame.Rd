\name{RFrame}
\alias{RFrame}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ ~~function to do ... ~~ }
\description{
  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
RFrame(title = "R-wxWidgets", pos = Point(50, 100), size = Size(400, 300), id = -1, OnQuit = NULL)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{title}{ ~~Describe \code{title} here~~ }
  \item{pos}{ ~~Describe \code{pos} here~~ }
  \item{size}{ ~~Describe \code{size} here~~ }
  \item{id}{ ~~Describe \code{id} here~~ }
  \item{OnQuit}{ ~~Describe \code{OnQuit} here~~ }
}
\details{
  ~~ If necessary, more details than the description above ~~
}
\value{
  ~Describe the value returned
  If it is a LIST, use
  \item{comp1 }{Description of 'comp1'}
  \item{comp2 }{Description of 'comp2'}
  ...
}
\references{ ~put references to the literature/web site here ~ }
\author{ ~~who you are~~ }
\note{ ~~further notes~~ 

 ~Make other sections like Warning with \section{Warning }{....} ~
}
\seealso{ ~~objects to See Also as \code{\link{help}}, ~~~ }
\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function (title = "R-wxWidgets", pos = Point(50, 100), size = Size(400, 
    300), id = -1, OnQuit = NULL) 
{
    if (!is.null(OnQuit)) 
        OnQuit = as.function(OnQuit)
    if (is(size, "numeric")) 
        size = as.integer(size)
    if (is(pos, "numeric")) 
        pos = as.integer(pos)
    ans = .Call("R_RwxFrame_new", as.character(title), pos, size, 
        as.integer(id), OnQuit)
    if (length(OnQuit) && is.function(OnQuit)) 
        ans$AddCallback(wxEVT_CLOSE_WINDOW, OnQuit)
    ans
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
