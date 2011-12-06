\name{processHTMLParameters}
\alias{processHTMLParameters}
\title{Convert the single string of attributes from an HTML node into a named
      character vector}
\description{

  When processing an HTML tag, one can fetch all the
  parameters from the wxWidgets \code{wxHtmlTag} object
  as a single string. This  function breaks that string
  into separate name=value pairs and then
  returns the result as a named character vector
  for more convenient use in R.

  This arises in an HTML tag handler function which is
  registered to convert a node into some content in the rendered
  document.

  The function \code{wxHtmlTag_GetAllParams} now has a
  \code{split} argument which, if \code{TRUE},
  calls this function to return the parameters already
  separated. So  one can use either this function
  or \code{wxHtmlTag_GetAllParams}.
}
\usage{
processFormParameters(tag)
}
\arguments{
  \item{tag}{the \code{wxHtmlTag} object whose attributes/parameters are
    to be .}
}
\details{
 The parameters are returned as a comma-separated list.
}
\value{

}
\references{\url{http://www.wxwidgets.org/manuals/2.6.3/wx_wxhtmltag.html#wxhtmltag}}
\author{Duncan Temple Lang}
\seealso{
  \code{wxHtmlTag_GetAllParams}
  \code{wxHtmlTagHandler}
  \code{wxHtmlParser_AddTagHandler}
}
\examples{

}

\keyword{IO}
\concept{HTML parsing}
