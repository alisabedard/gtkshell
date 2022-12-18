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

#include "gtkshell.h"

extern struct GDLEnvironment *gsh_guidl_env;

static void setup_dictionary()
{
	ARTupleVector *dict;

	dict = ARNEW(ar, ARTupleVector);
#define DEF(a, b) GSH_GUIDL_DEFINE(dict, a, b)
	DEF("label", "-al");
	DEF("prompt", "-at");
	DEF("terminal", "-as");
	DEF("window", "-aw");
	DEF("separator", "-aS");
	DEF("updating label", "-aul");
	DEF("updating progress", "-aup");
	DEF("row", "-ar");
	DEF("viewer", "-ae");
	DEF("text", "-aT");
	DEF("system label", "-acl");
	DEF("system button", "-acb");
	DEF("vertical pane", "-ab");
	DEF("command shell", "-aC");
	DEF("clock applet", "-aAc");
	DEF("app menu", "-aAm");
	DEF("embedded", "-aX");
#define DICT gsh_guidl_env->dictionaries->widget
	DICT = dict;
}

GSH_GUIDL_ITEM_FUNC(widget, DICT);
