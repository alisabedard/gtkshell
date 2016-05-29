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

#include "gtkshell.h"

extern struct GDLEnvironment *gsh_guidl_env;

static void delete_dictionary(struct ARTupleVector *dict)
{
	if (dict)
		$(dict, delete);
}

static void delete_contents(struct GDLDictionaries *dictionaries)
{
	delete_dictionary(dictionaries->widget);
	delete_dictionary(dictionaries->option);
	delete_dictionary(dictionaries->dialog);
}

static void gsh_delete_GDLDictionaries(struct GDLDictionaries *dictionaries)
{
	delete_contents(dictionaries);
	g_free(dictionaries);
}

static void initialize_member_fields(struct GDLDictionaries *dictionaries)
{
#define NULLIFY(dict) dictionaries->dict=NULL
	NULLIFY(widget);
	NULLIFY(dialog);
	NULLIFY(option);
}

static void setup_GDLDictionaries(struct GDLDictionaries *dictionaries)
{
	initialize_member_fields(dictionaries);
	/* Set up methods.  */
	dictionaries->delete = &gsh_delete_GDLDictionaries;
}

struct GDLDictionaries *gsh_new_GDLDictionaries()
{
	struct GDLDictionaries *dictionaries;

	dictionaries = g_malloc(sizeof(struct GDLDictionaries));
	setup_GDLDictionaries(dictionaries);

	return dictionaries;
}

void
gsh_guidl_generic_item(gchar * item, gchar * argument,
		       struct ARTupleVector *dict)
{
	$(gsh_guidl_env, add, $(dict, find, item), argument);
	g_free(item);
}
