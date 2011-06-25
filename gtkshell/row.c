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

#include "gtkshell.h"

static void
GSHRows_new (struct GSHRows *this)
{
  GtkWidget *h = this->h;
  GSH * gsh = (GSH *)this->gsh;
  /* reset row counter */
  this->current = 0;
  /* create a new column */
  this->v = gtk_vbox_new(FALSE, 0);
  if(G_UNLIKELY(GSH_FLAG(GSH_NO_EXPAND)))
    GSHCA_TIGHT(h, this->v);
  else
    GSHCA(h, this->v);
  /* This is necessary as geometry would get messed up otherwise.  */
  gtk_widget_show_all(h); 
}

static void
GSHRows_check (struct GSHRows *this)
{
  if ((this->current >= this->total) || !(this->v))
    $ (this, new);
}

static void
GSHRows_delete (struct GSHRows *rows)
{
#define KILLWIDGET(x) if(GTK_IS_WIDGET(x)) gtk_widget_destroy(x)
  KILLWIDGET(rows->v);
  KILLWIDGET(rows->h);
  arfree (rows);
}

struct GSHRows *
gsh_new_GSHRows (GSH * gsh)
{
  struct GSHRows *this;

  this = armalloc (sizeof (struct GSHRows));
  /* setup methods */
  this->delete = &GSHRows_delete;
  this->new = &GSHRows_new;
  this->check = &GSHRows_check;
  this->gsh=gsh;
  /* Use an arbitrary, though reasonable, initial number of rows.  */
  this->total = 8;
  GSH_CREATE (this->h, hbox, FALSE, 0);
  $(this, new);

  return this;
}



