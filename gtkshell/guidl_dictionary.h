/*
  GUIShell
  (c) 2007 Jeffrey Bedard
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

#ifndef GSH_GUIDL_DICTIONARY_H
#define GSH_GUIDL_DICTIONARY_H

struct GDLDictionaries {
	struct ARTupleVector *widget;
	struct ARTupleVector *dialog;
	struct ARTupleVector *option;
	void (*delete) (struct GDLDictionaries *);
};

#define GSH_GUIDL_CHECK_DICTIONARY(dict, setup)\
{\
	if(!dict)\
		setup();\
}

#define GSH_GUIDL_DEFINE(dict, a, b)\
	$(dict, add, (gchar *)a, (gchar *)b)

#define GSH_GUIDL_ITEM(item, arg, dict, setup)\
{\
	GSH_GUIDL_CHECK_DICTIONARY(dict, setup);\
	gsh_guidl_generic_item(item, arg, dict);\
}

#define GSH_GUIDL_ITEM_FUNC(type, dict)\
void gsh_guidl_ ##type (gchar * item, gchar * arg)\
{\
	GSH_GUIDL_ITEM(item, arg, dict, setup_dictionary);\
}

#define GSH_GUIDL_ITEM_HEAD(type)\
void gsh_guidl_ ##type (gchar * item, gchar * arg);

struct GDLDictionaries *gsh_new_GDLDictionaries();

void
gsh_guidl_generic_item(gchar * item, gchar * argument,
		       struct ARTupleVector *dict);

#endif /* GSH_GUIDL_DICTIONARY_H */
