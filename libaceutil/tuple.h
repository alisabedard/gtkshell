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

#ifndef AR_TUPLE_H
#define AR_TUPLE_H

struct ARTupleVector
{
	GHashTable * __hash;
	void (*add)(struct ARTupleVector *, const gchar *, const gchar *);
	const gchar * (*find)(struct ARTupleVector *, const gchar *);
	void (*delete)(struct ARTupleVector *);
};

typedef struct ARTupleVector ARTupleVector;

struct ARTupleVector *
ar_new_ARTupleVector();

#endif /* AR_TUPLE_H */

