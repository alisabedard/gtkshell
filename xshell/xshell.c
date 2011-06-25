/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
  antiright@gmail.com

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

static void
setup_xshell_gui_layout(XShellGUILayout * layout)
{
	layout->row_count=0;
	layout->column_count=0;
	layout->max_row_count=XSH_ROWS_PER_COLUMN;
	layout->widget_width=XSH_WIDGET_WIDTH;
}

static void
setup_xshell_gui(XShellGUI * gui)
{
	gui->widgets=NULL;
	gui->widget_count=0;
	setup_xshell_gui_layout(&(gui->layout));
}

static void
setup_xshell(XShell * xsh)
{
	xsh->options=0;
	setup_xshell_gui(&(xsh->gui));
}

static void
delete_widgets(XWidget * head)
{
	XWidget * iter;

	iter=head;
	while(iter)
	{
		XWidget * next;

		next=iter->next;
		free(iter);
		iter=next;
	}
}

static void
cleanup(XShell * xsh)
{
	Display * dpy;

	dpy=xsh->gui.display;
	delete_widgets(xsh->gui.widgets);
	xsh_free_font(xsh);
	XFreeGC(dpy, xsh->gui.gc);
	XCloseDisplay(dpy);
}

static void
show_main_window(XShell * xsh)
{
	XShellGUI * gui = &(xsh->gui);
	Window toplevel=gui->widgets->window;
	Display * dpy = gui->display;

	toplevel=xsh->gui.widgets->window;
	XMapSubwindows(dpy, toplevel);
	XMapWindow(dpy, toplevel);
}

static void
setup_main_window(XShell * xsh)
{
	XShellGUI * gui = &(xsh->gui);
	Display * dpy = gui->display;
	int screen = DefaultScreen(dpy);
	const int x=DisplayWidth(dpy, screen)/3;
	const int y=DisplayHeight(dpy, screen)/3;


	/* Main window.  */
	xshell_XWidget_new(xsh, NULL, x, y, 100, 100);
	gui->gc=XSH_SETUP_GC(dpy, gui->widgets->window);
	XSH_SET_COLOR(dpy, gui->gc, 0xae, 0xb2, 0xc3);
	xsh_set_font(xsh, "-misc-fixed-medium-r-*-*-14-*-*-*-*-*-*-*");
}

static void
apply_toplevel_geometry(XShell * xsh)
{
	XShellGUI * gui = &(xsh->gui);

	XMoveResizeWindow(xsh->gui.display, xsh->gui.widgets->window,
		xsh->gui.widgets->geometry.x,
		xsh->gui.widgets->geometry.y,
		gui->widgets->geometry.width,
		gui->widgets->geometry.height);
}

int
main(int argc, char ** argv)
{
	XShell xsh;

	if(argc<=1)
		xsh_show_usage_and_exit();
	setup_xshell(&xsh);
	if(!(xsh.gui.display=XOpenDisplay(NULL)))
	{
		fprintf(stderr, "%s:  ERROR:  cannot open display\n",
			argv[0]);
		exit(1);
	}
	setup_main_window(&xsh);
	xsh_parse_arguments(&xsh, argc, argv);
	xsh_layout_widgets(&xsh);
	apply_toplevel_geometry(&xsh);
	show_main_window(&xsh);
	xsh_event_loop(&xsh);
	cleanup(&xsh);

	return 0; 
}


