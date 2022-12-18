/*
  GUIShell
  (c) 2002-2007 Alisa Bedard
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

#ifndef GSH_COLOR_H
#define GSH_COLOR_H

#define GSH_FALLBACK_COLOR "black"
#define GSH_FALLBACK_BGCOLOR "#aeb2c3"
#define GSH_FALLBACK_FGCOLOR GSH_FALLBACK_COLOR

void
gsh_widget_set_color(GtkWidget * widget,
		     const gchar * color_string, bool is_fg_color);

#endif /* ! GSH_COLOR_H */
