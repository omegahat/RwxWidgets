\name{radioButtonGroup}
\alias{radioButtonGroup}
\title{Create an R object to manage a group of associated radio buttons}
\description{
  This function creates an R-level management structure for handling
  wxWidgets radio buttons that share state, i.e. that are mutually
  exclusive.
  There are facilities in wxWidgets to do this, but they put a
  constraint on the layout and ordering of the buttons and so we need
  our own.
  The idea is relatively simple. One creates a group and then
  adds radio buttons to it.  These are added via the
  \code{add} function returned as part of the group object.
  We typically add these by name and so can recover them later.
  When a radio button in this group is selected, the others are
  deselected. Additionally, if the group was created with a callback
  function (the \code{callback} argument), then that callback is invoked
  when a button is selected.  It is passed the
  radio button that was selected and its name and any additional
  arguments
  passed in the call to \code{radioButtonGroup} via the \Sdots parameter.
}
\usage{
radioButtonGroup(callback = NULL, ..., elements = list(), currentValue = NA)
}
\arguments{
  \item{callback}{ a function that accepts at least 2 arguments, the
    radio button that was just selected and its \dQuote{name} as given
    via a call to \code{add}.  Any values passed to the
    \code{radioButtonGroup} function call via \Sdots are also passed on
    to the callback.
  }
  \item{\dots}{additional arguments that are passed on to
    \code{callback} when a radio button is set by the user or programmatically.} 
  \item{elements}{a list of the radio button objects/widgets.  This is
    an argument so that one can create the radio buttons before creating
    the radio group.  Typically, one creates the group and explicitly adds
     the radio buttons via a call to \code{add}.}
  \item{currentValue}{which of the radio buttons is set. This is a
    character string or integer identifying the element of the
    \code{elements} list.}
}
\value{
  A list of class \code{RadioButtonGroup}
  whose elements are functions that allow one to modify and query the
  state of the radio group.
  \item{add}{}
  \item{set}{}
  \item{remove}{}
  \item{getSelected}{}
  \item{getValue}{}  
}
\references{wxWidgets documentation. http://www.wxwidgets.org/manuals/2.6}
\author{Duncan Temple Lang}

\seealso{
  \url{http://www.wxwidgets.org/manuals/2.6/wx_wxradiobox.html#wxradiobox}{wxRadioButton},
  \url{http://www.wxwidgets.org/manuals/2.6/wx_wxradiobox.html#wxradiobutton}{wxRadioBox}.  
}
\examples{
 # see examples/embeddedDevice.R
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{programming}
\keyword{interface}
\concept{GUI}

