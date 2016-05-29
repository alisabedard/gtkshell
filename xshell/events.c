/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
  jefbed@gmail.com

  This file is part of GUIShell.

  GUIShell is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  GUIShell is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GUIShell; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "xshell.h"

#ifndef DEBUG_EVENTS
#undef XMSG
#define XMSG
#endif /* not DEBUG_EVENTS */

#define XSH_EVENT(iter, event)\
{\
	if(iter->events.event)\
		(iter->events.event)(iter);\
}

#ifdef DEBUG_EVENTS
unsigned int xsh_expose_count = 0;
unsigned int xsh_configure_count = 0;
#endif /* DEBUG_EVENTS */

static void select_event(XWidget * iter, XEvent * event)
{
	iter->events.event = event;
	switch (event->type) {
	case Expose:
		if (event->xexpose.count < 1)
			XSH_EVENT(iter, expose);
		break;
	case KeyPress:
		XSH_EVENT(iter, key_press);
		break;
	case ButtonPress:
		XSH_EVENT(iter, button_press);
		break;
	case ButtonRelease:
		XSH_EVENT(iter, button_release);
		break;
	};
}

static void xshell_foreach_XWidget(XWidget * head, XEvent * event)
{
	XWidget *iter;

	iter = head;
	while (iter) {
		/* Only process event if it occurs on a particular window.  */
		if (event->xany.window != iter->window) {
			iter = iter->next;
			continue;
		}
		select_event(iter, event);
		iter = iter->next;
	}
}

void xsh_event_loop(XShell * xsh)
{
	XEvent event;
	Display *dpy = xsh->gui.display;

	for (dpy = xsh->gui.display;; XNextEvent(dpy, &event)) {
		switch (event.type) {
		case ConfigureNotify:
#ifdef DEBUG_EVENTS
			XMSG("ConfigureNotify");
#endif /* DEBUG_EVENTS */
			xsh->gui.widgets->geometry.width =
			    event.xconfigure.width;
			if (event.xany.window == xsh->gui.widgets->window)
				xsh->gui.widgets->geometry.height =
				    event.xconfigure.height;
			xsh_layout_widgets(xsh);
			break;
		case DestroyNotify:
			exit(0);
			break;
		default:
			xshell_foreach_XWidget(xsh->gui.widgets, &event);
		}
	}
}
