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

#include "library.h"


static void
ar_delete_ARTupleVector(struct ARTupleVector * vector)
{
#if !defined(WIN32) & !defined(CYGWIN)
	g_hash_table_remove_all(vector->__hash);
#endif
	g_hash_table_destroy(vector->__hash);
	arfree(vector);
}

static void
ar_add_ARTupleVector(struct ARTupleVector * vector,
		     const gchar * key, const gchar * value)
{
	g_hash_table_insert(vector->__hash, (gpointer)key, (gpointer)value);
}

static const gchar *
ar_find_ARTupleVector(struct ARTupleVector * vector,
		      const gchar * term)
{
	return (const gchar *)g_hash_table_lookup(vector->__hash, 
						  (gconstpointer)term);
}

struct ARTupleVector *
ar_new_ARTupleVector()
{
	struct ARTupleVector * vector;

	vector=armalloc(sizeof(struct ARTupleVector));
	vector->__hash=g_hash_table_new(&g_str_hash, &g_str_equal);
	vector->add=&ar_add_ARTupleVector;
	vector->find=&ar_find_ARTupleVector;
	vector->delete=&ar_delete_ARTupleVector;

	return vector;
}

