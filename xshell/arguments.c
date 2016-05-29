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

void xsh_show_usage_and_exit()
{
	fprintf(stderr, "Usage: xshell [-[a[]o[[r rows]n[g X+Y]]]"
		" BUTTON] ...\n");
	exit(1);
}

static void add_label(XShell * xsh, const char *label_text)
{
	xshell_button_new(xsh, xsh->gui.widgets, label_text);
	xsh->gui.last_widget->events.button_press = NULL;
}

static void handle_add_options(XShell * xsh, char **argv, unsigned int *counter)
{
	XShellGUI *gui = &(xsh->gui);
	XShellGUILayout *layout = &(gui->layout);

	switch (argv[*counter][2]) {
	case 'l':		/* Label.  */
		(*counter)++;
		add_label(xsh, argv[(*counter)]);
		break;

	case 'r':		/* Add a column.  */
		xsh->gui.layout.column_count++;
		xsh->gui.layout.row_count = 0;
		break;

	case 't':		/* Field.  */
		(*counter)++;
		xshell_text_new(xsh, xsh->gui.widgets, 0,
				(*counter) * 16, 1, argv[*counter]);
		break;
	case 'T':		/* Text Area.  */
		(*counter)++;
		xsh->gui.layout.max_row_count *= 2;
		xshell_text_new(xsh, xsh->gui.widgets, 0,
				(*counter) * 16,
				layout->max_row_count - layout->row_count,
				argv[*counter]);
		break;
	}
}

static void set_override_redirect(XShell * xsh)
{
	XSetWindowAttributes attr;

	attr.override_redirect = True;
	XUnmapWindow(xsh->gui.display, xsh->gui.widgets->window);
	XChangeWindowAttributes(xsh->gui.display, xsh->gui.widgets->window,
				CWOverrideRedirect, &attr);
	XMapRaised(xsh->gui.display, xsh->gui.widgets->window);
}

static void set_geometry(XShell * xsh, const char *geometry_string)
{
	XWindowAttributes *geometry = &(xsh->gui.widgets->geometry);
	XParseGeometry(geometry_string,
		       &(geometry->x), &(geometry->y),
		       (unsigned int *)&(geometry->width),
		       (unsigned int *)&(geometry->height));
}

static void
handle_option_options(XShell * xsh, char **argv, unsigned int *counter)
{
	switch (argv[*counter][2]) {
	case 'g':
		set_geometry(xsh, argv[++(*counter)]);
		break;
	case 'n':
		set_override_redirect(xsh);
		break;
	case 'r':
		(*counter)++;
		xsh->gui.layout.max_row_count = atoi(argv[*counter]);
		printf("%d\n", xsh->gui.layout.max_row_count);
		break;
	}
}

static void handle_options(XShell * xsh, char **argv, unsigned int *counter)
{
	switch (argv[*counter][1]) {
	case '-':		/* Handle GNU long options.  */
		xsh_show_usage_and_exit();
		break;
	case 'a':		/* Add options.  */
		handle_add_options(xsh, argv, counter);
		break;
	case 'd':
		xshell_handle_dialog_options(xsh, argv, counter);
		break;
	case 'h':
		xsh_show_usage_and_exit();
		break;
	case 'o':
		handle_option_options(xsh, argv, counter);
		break;
	case 't':		/* test area */
		{
		}
		break;
	default:
		xsh_show_usage_and_exit();
	}
}

static void handle_argument(XShell * xsh, char **argv, unsigned int *counter)
{
	if (argv[*counter][0] == '-')
		handle_options(xsh, argv, counter);
	else
		xshell_button_new(xsh, xsh->gui.widgets, argv[*counter]);
}

void xsh_parse_arguments(XShell * xsh, int argc, char **argv)
{
	unsigned int counter;

	for (counter = 1; counter < (unsigned int)argc; counter++) {
		handle_argument(xsh, argv, &counter);
	}
}
