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

#include "gtkshell.h"

/* GTK Scrolled Window Set */
#define GSWS(item, window, ...)\
	gtk_scrolled_window_set_##item(GTK_SCROLLED_WINDOW(window),\
		__VA_ARGS__)
static void
gsh_setup_scrolled_window (struct GSH *gsh)
{
  GtkWidget *scrolled_window;
  GtkWidget *window = gsh->widgets.window;

  scrolled_window = gsh->widgets.scrolled_window
    = gtk_scrolled_window_new (NULL, NULL);
  GSWS (shadow_type, scrolled_window, GTK_SHADOW_OUT);
  GSWS (policy, scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  GSHCA (window, scrolled_window);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW
					 (scrolled_window), gsh->rows->h);
  gtk_widget_show (scrolled_window);
}

static void
setup_framed (struct GSH *gsh)
{
  GtkWidget *frame;

  frame = gtk_frame_new (NULL);
  GSHCA (gsh->widgets.window, frame);
  GSHCA (frame, gsh->rows->h);
  gtk_widget_show (frame);
}

void
gsh_setup_base_container (struct GSH *gsh)
{
#define GWA gsh->widgets.app
#define FRAME GWA.frame
  if (FRAME)
    {				/* setup app mode frame */
      GSHCA (FRAME, gsh->rows->h);
      gsh->rows->h = GWA.row;
    }
  if (GSH_FLAG (GSH_SCROLL))
    gsh_setup_scrolled_window (gsh);
  else if (!GSH_FLAG (GSH_NO_BASE_FRAME))
    setup_framed (gsh);
  else
    {
      GtkWidget *window = gsh->widgets.window;
      GtkWidget *row = gsh->rows->h;
      GSHCA (window, row);
    }
}
