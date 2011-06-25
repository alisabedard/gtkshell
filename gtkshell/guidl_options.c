/*
  GUIShell
  (c) 2007 Jeffrey Bedard
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

#include "gtkshell.h"

extern struct GDLEnvironment *gsh_guidl_env;


static void
setup_dictionary ()
{
  ARTupleVector *dict;

  dict= ARNEW (ar, ARTupleVector);
#define DEF(a, b) GSH_GUIDL_DEFINE(dict, a, b);
  DEF ("framed labels", "-of");
  DEF ("undecorated", "-on");
  DEF ("exit on activate", "-oe");
  DEF ("horizontal labels", "-oh");
  DEF ("scrolled", "-os");
  DEF ("no fill", "-ol");
  DEF ("fill", "-oL");
  DEF ("geometry", "-og");
  DEF ("title", "-oT");
  DEF ("terminal font", "-otf");
  DEF ("terminal width", "-otw");
  DEF ("terminal height", "-oth");
  DEF ("terminal transparent", "-ott");
  DEF ("terminal not transparent", "-otT");
  DEF ("rows", "-or");
  DEF ("update frequency", "-ou");
  DEF ("application", "-oa");
  DEF ("icon size", "-oi");
  DEF ("pane next", "-op");
  DEF ("check commands", "-oC");
  DEF ("horizontal clock", "-oH");
#define DICT gsh_guidl_env->dictionaries->option
  DICT=dict;
}

GSH_GUIDL_ITEM_FUNC (option, DICT);
