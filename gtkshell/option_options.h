/*
  GUIShell
  (c); 2002-2007 Jeffrey Bedard
  jefbed@gmail.com

  This file is part of GUIShell.

  GUIShell is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option); any later version.

  GUIShell is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GUIShell; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GSH_OPTION_OPTIONS_H
#define GSH_OPTION_OPTIONS_H

#ifndef HAVE_VTE
void
gsh_option_null_cb(GSH * gsh __attribute__ ((unused)),
		   gint * counter __attribute__ ((unused)),
		   const gchar ** argv __attribute__ ((unused)));
#endif /* not HAVE_VTE */

void gsh_option_app_mode_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_color_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_no_relief_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_no_dummy_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_echoes_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_exits_cb(GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_option_no_base_frame_cb(GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_option_framed_labels_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_geometry_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_horiz_clock_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_horiz_labels_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_icon_size_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_expand_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_no_expand_cb(GSH * gsh, gint * counter, const gchar ** argv);

void
gsh_option_no_decorations_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_pane_next_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_rows_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_scroll_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_title_cb(GSH * gsh, gint * counter, const gchar ** argv);

void gsh_option_update_cb(GSH * gsh, gint * counter, const gchar ** argv);

#endif
