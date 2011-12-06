#ifdef USE_GTK_EVENTS

#define USE_GLIB_EVENT_LOOP 1

#  include <gtk/gtk.h>
#  include <gdk/gdkx.h>

#ifdef USE_GLIB_EVENT_LOOP

#include <glib.h>

void
R_gtk_eventHandler(void *userData)
{
    GMainContext *ctxt;
    gdk_flush();
    /* This uses glib */
    ctxt = g_main_context_default();
    while (g_main_context_pending(ctxt))
	g_main_context_iteration(ctxt, FALSE);
}


#else /* USE_GLIB_EVENT_LOOP */

#  include <gtk/gtk.h>
#  include <gdk/gdkx.h>

void
R_gtk_eventHandler(void *userData)
{
    gdk_flush();
    while (gtk_events_pending())
	gtk_main_iteration();
}
#endif




#include <R_ext/eventloop.h>

#ifdef __cplusplus
extern "C" {
#endif
void
addGtkEventHandler()
{
#ifndef G_OS_WIN32
    {
    InputHandler *h;
    h = addInputHandler(R_InputHandlers, ConnectionNumber(GDK_DISPLAY()),
                         R_gtk_eventHandler, -1);
    }
#endif
}
#ifdef __cplusplus
}
#endif

#endif /* USE_GTK_EVENTS */

