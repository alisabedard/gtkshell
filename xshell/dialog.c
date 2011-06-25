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
xshell_message_dialog(XShell * xsh, const char * message)
{
	xsh->gui.widgets->geometry.width=200;
	xsh->gui.widgets->geometry.height=100;
	xshell_floating_button_new(xsh, xsh->gui.widgets, "OK",
		0, 0, 100, 50);
	xshell_floating_button_new(xsh, xsh->gui.widgets, "Cancel",
		100, 0, 100, 50);
	xshell_floating_button_new(xsh, xsh->gui.widgets, message,
		0, 50, 100, 50);
}

void
xshell_handle_dialog_options(XShell * xsh,
	char ** argv, unsigned int * counter)
{
	switch(argv[*counter][2])
	{
	case 'm':
		(*counter)++;
		xshell_message_dialog(xsh, argv[*counter]);
		break;
	default:
		fprintf(stderr, "%s:  Invalid dialog argument specified.",
			argv[0]);
	}
}

