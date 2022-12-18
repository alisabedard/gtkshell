/*
  GUIShell
  (c) 2002-2007 Alisa Bedard
  alisabedard@gmail.com

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

static void draw_label(XWidget * shell)
{
	XShell *xsh;
	const char *label = shell->data;

	xsh = (XShell *) shell->xsh;
	XDrawString(xsh->gui.display, shell->window, xsh->gui.gc,
		    3, 12, label, strlen(label));
}

static void expose(XWidget * button)
{
	draw_label(button);
}

static void button_press(XWidget * button)
{
	XSHButtonData *data;

	XMSG("PRESSED");
	data = (XSHButtonData *) button->data;
	SYSTEM(data->command);
}

static void key_press(XWidget * button)
{
	button_press(button);
}

static void configure(XWidget * button)
{
	expose(button);
}

static void setup_events(XWidget * button)
{
	button->events.expose = &expose;
	button->events.configure = &configure;
	button->events.key_press = &key_press;
	button->events.button_press = &button_press;
}

void
xshell_shell_new(XShell * xsh, XWidget * parent, int x, int y,
		 const char *command)
{
	XWidget *button;
	XSHButtonData *data;
	char *label;

	xshell_XWidget_new(xsh, parent, x, y, 100, 16);
	button = xsh->gui.last_widget;
	data = malloc(sizeof(XSHButtonData));
	data->command = (char *)command;
	label = strchr(command, '#');
	if (label) {
		data->label = label + 1;
	} else {
		data->label = (char *)command;
	}
	button->data = data;
	setup_events(button);
}
