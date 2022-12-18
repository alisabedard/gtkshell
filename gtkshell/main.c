/*
  GUIShell
  (c) 2002-2010 Alisa Bedard
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

int main(int argc, char **argv)
{
	GSH *gsh;

#ifdef LIBGC
	GC_INIT();
#endif /* LIBGC */
	gtk_init(&argc, &argv);
	gsh = g_newa(GSH, 1);
	gsh_GSH(gsh);
	$(gsh, parse, (const gint)argc, (const gchar **)argv);
	$(gsh, finalize);
#ifdef LIBGC
	GC_gcollect();
#endif /* LIBGC */
	gtk_main();		/* application main loop  */
	$(gsh, delete);

	return 0;
}
