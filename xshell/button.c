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
draw_label(XShell * xsh, XWidget * button)
{
	XSHButtonData * data = (XSHButtonData *)button->data;
	const char * label=data->label;
	XShellGUI * gui = &(xsh->gui);
	Display * dpy = gui->display;
	GC gc = gui->gc;

	XSH_SET_COLOR(dpy, gc, 0, 0, 0);
	XDrawString(dpy, button->window, gc, XSH_FONT_WIDTH(xsh), 
		XSH_FONT_HEIGHT(xsh)-XSH_WIDGET_PADDING, 
		label, strlen(label));
}

static void
expose(XWidget * button)
{
#ifdef XSH_DECORATE
	if(button->events.button_press)
		xsh_decorate(button, XSH_DECOR_OUT);
	else /* for label  */
		xsh_decorate(button, XSH_DECOR_FLAT);
#endif /* XSH_DECORATE */
	draw_label((XShell *)(button->xsh), button);
}

static Bool
special_command(const char * command)
{
	if(!strcmp(command, "Exit___"))
		exit(0);
	else
		return False;
	return True;
}

static void
button_press(XWidget * button)
{
	XSHButtonData * data=(XSHButtonData *)button->data;
	const char * command=data->command;

	XMSG("PRESSED");
	data=(XSHButtonData *)button->data;
#ifdef XSH_DECORATE
	xsh_decorate(button, XSH_DECOR_IN);
#endif /* XSH_DECORATE */
	draw_label((XShell *)(button->xsh), button);
	if(!special_command(command))
		SYSTEM(command);
}

static void
button_release(XWidget * button)
{
	expose(button);
}

static void
configure(XWidget * button)
{
	expose(button);
}


static void
setup_button_events(XWidget * button)
{
	button->events.expose=&expose;
	button->events.configure=&configure;
	button->events.key_press=NULL;
	button->events.button_press=&button_press;
	button->events.button_release=&button_release;
}

/* The result must be freed.  */
static char *
setup_label(const char * command)
{
	char * label;

	label=strdup(command);
	/* Start label after comment character, if any.  */
	label=strchr(label, '#')?label+1:(char*)label;
	{
		/* Replace underscore characters in label with spaces.  */
		char * iter=label;
		while((iter=strchr(iter, '_')))
			iter[0]=' ';
	}

	return label;
}

void
xshell_floating_button_new(XShell * xsh, XWidget * parent, 
	const char * command, int x, int y, 
	unsigned int width, unsigned int height)
{
	XWidget * button;
	XSHButtonData * data;

	xshell_XWidget_new(xsh, parent, x, y, width, height);
	button=xsh->gui.last_widget;
	button->data=data=malloc(sizeof(XSHButtonData));
	data->label=setup_label(data->command=(char *)command);
	setup_button_events(button);
}

void
xshell_button_new(XShell * xsh, XWidget * parent, const char * command)
{
	XShellGUILayout *layout=&(xsh->gui.layout);

	xshell_floating_button_new(xsh, parent, command,
		XSH_WIDGET_WIDTH*layout->column_count, 
		XSH_WIDGET_HEIGHT*layout->row_count,
		XSH_WIDGET_WIDTH, XSH_WIDGET_HEIGHT);
	if(++(layout->row_count) > layout->max_row_count)
	{
		layout->column_count++; 
		layout->row_count=0;
	}
}

