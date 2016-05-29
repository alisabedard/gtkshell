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

#ifndef GSH_GTKSHELL_H
#define GSH_GTKSHELL_H

#include <gtk/gtk.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_VTE
#include <vte/vte.h>
#endif /* HAVE_VTE */
#include <unistd.h>
#include <signal.h>

#ifdef HAVE_PANEL_APPLET
#include <panel-applet.h>
#endif /* HAVE_PANEL_APPLET */

#include "../libaceutil/library.h"

#ifndef YYFILE
#include "y.tab.h"
#endif /* not YYFILE */

#include "macros.h"

#include "row_struct.h"
#include "updated.h"
#include "update_manager_struct.h"

#include "gsh.h"

#include "module_includes.h"

void gsh_GSH(GSH * gsh);

GSH *gsh_new_GSH();

#endif /* ! GSH_GTKSHELL_H */
