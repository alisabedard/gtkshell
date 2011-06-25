/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
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

#ifndef GSH_OPTIONS_H
#define GSH_OPTIONS_H

#include "gtkshell.h"

#ifdef DEBUG
#define GSH_COUNT(argc, counter) \
{\
	(*counter)++;\
	g_assert((*counter) <= argc);\
}
#else /* not DEBUG */
#define GSH_COUNT(argc, counter) \
{\
	(*counter)++;\
}
#endif /* DEBUG */

void
gsh_handle_switch_argument (GSH * gsh, const gchar ** argv, gint * counter);

#endif /* not GSH_OPTIONS_H */
