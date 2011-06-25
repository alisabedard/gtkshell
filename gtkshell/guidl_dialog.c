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

/* Set the dictionary to use for this definition file.  */
#include "gtkshell.h"

extern struct GDLEnvironment *gsh_guidl_env;


static void
setup_dictionary ()
{
  ARTupleVector * dict;

  dict = ARNEW (ar, ARTupleVector);
  /* Begin adding mappings between keys and values.  */
#define DEF(a, b) GSH_GUIDL_DEFINE(dict, a, b)
  DEF ("file", "-df");
  DEF ("font", "-dF");
  DEF ("about", "-da");
  DEF ("folder", "-dd");
  DEF ("create folder", "-dD");
  DEF ("save", "-ds");
  DEF ("color", "-dc");
  DEF ("info", "-di");
  DEF ("warning", "-dw");
  DEF ("error", "-de");
#define DICT gsh_guidl_env->dictionaries->dialog
  DICT=dict;
}

/* Generate public function to access these definitions.  */
GSH_GUIDL_ITEM_FUNC (dialog, DICT);
