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

#ifndef XSHELL_H
#define XSHELL_H

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#ifdef DEBUG
#define XMSG(msg) fprintf(stderr, "%s:%d:  %s\n", __FILE__, __LINE__, msg);
#else /* not DEBUG */
#define XMSG(msg)		/* unused */
#endif /* DEBUG */

#include "xshell_struct.h"

#include "widget.h"
#include "button.h"
#include "text.h"
#include "arguments.h"
#include "events.h"
#include "decoration.h"
#include "layout.h"
#include "font.h"
#include "color.h"
#include "dialog.h"

#define SYSTEM(command)\
	 if(system(command))\
	 	fprintf(stderr, "ERROR:  %s\n", command);

#endif /* XSHELL_H */
