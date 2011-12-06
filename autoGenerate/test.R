library(RGCCTranslationUnit)
tu = parseTU("wx.cpp.tu")

tp = resolveType(tu[["12175"]], tu)
getNativeDeclaration("me", tp, "me")
