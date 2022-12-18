/*
  GUIShell
  (c) 2007 Alisa Bedard
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

#ifndef GSH_TERMINAL_H
#define GSH_TERMINAL_H
#ifdef HAVE_VTE

#include "terminal_struct.h"

#define GSH_DEFAULT_SHELL "/bin/sh"

GSHTerminal *gsh_new_GSH_Terminal(GSH * gsh);

#endif /* HAVE_VTE */
#endif /* not GSH_TERMINAL_H */
