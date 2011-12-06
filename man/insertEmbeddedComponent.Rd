\name{insertEmbeddedComponent}
\alias{insertEmbeddedComponent}
\title{Put a widget into an HTML window display of a document}
\description{
  This function is typically called within an HTML tag handler
  function when the parser invokes that handler function
  to process an HTML tag/node within a document it is processing.
  When that tag handler creates a widget to put into the document
  in place of that tag, it calls this function to
  position the widget at the correct spot in the rendering
  of the document.

  One provides the widget to be inserted and the parser object
  which is passed in the caller to the tag handler.
  The third argument is not intended to be used unless
  the container has already been cached from earlier calls. It should not be a
  different container from the parsers own one. And caching the value
  is unlikely to lead to any improved efficiency.

  If one returns a widget from the tag handler, the R-tag handler
  mechanism will do the insertion itself, so it is not necessary
  to call this function from within the tag handler, but it does
  give more control.
}
\usage{
insertEmbeddedComponent(w, parser, container = wxHtmlParser_GetContainer(parser))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{w}{the widget object which is to be inserted and displayed in
    the rendered HTML document in the HTML window.
    This wxWindow object should have been created with the
    parser's HTML window as the parent, e.g. \code{parser$GetWindow()}}
  \item{parser}{the \code{wxHtmlParser} object that was passed as the
    third argument in the call to the HTML tag handler function.}
  \item{container}{the wxHtmlContainerCell object associated with the
    parser and the HTML window in which the parser's document is being
    rendered. You should not provide an alternative version of this
    argument.  Use the default value unless you have cached the value
    for some reason.
   }
}
\details{

}
\value{
  The newly created \code{wxHtmlWidgetCell} object
  used to house the widget within the HTML document.
}
\references{\url{http://www.wxwidgets.org/manuals/2.6.3/}}
\author{Duncan Temple Lang}

\seealso{
  \code{\link{wxHtmlTagHandler}}
  \code{\link{wxHtmlParser_AddTagHandler}}
}
\examples{

}
\keyword{IO}
\concept{HTML}
\concept{embedded object}
\concept{interactive document}
