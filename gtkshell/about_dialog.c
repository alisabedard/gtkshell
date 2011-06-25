/*
  GUIShell
  (c) 2007-2010 Jeffrey Bedard
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

#define GADS(i, v) gtk_about_dialog_set_##i(dialog, v)
static void
setup_about_license (GtkAboutDialog * dialog)
{
  gchar *text;
  GADS(license, text=antiright_read_named_file(GSH_LICENSE_FILE));
  g_free (text);
}

static void
setup_logo (GtkAboutDialog * dialog)
{
  GtkWidget *image;

  gtk_widget_show(image 
                  = gtk_image_new_from_file 
                  (ARDATADIR "/icons/ACE_32.png"));
    {
      GdkPixbuf *pb;

      GADS(logo, pb=gtk_image_get_pixbuf(GTK_IMAGE(image)));
      g_object_unref(pb);
    }
}

static GtkDialog *
setup_about_fields (GtkAboutDialog *dialog)
{
  const gchar *authors[] = GSH_AUTHORS;
  //setup_authors_field (dialog);
  setup_about_license (dialog);
  setup_logo (dialog);
  GADS(website, GSH_WEBSITE);
  GADS(authors, authors);
  GADS(comments, GSH_COMMENTS);
  GADS(copyright, GSH_COPYRIGHT);
  GADS(version, PACKAGE_STRING);

  return GTK_DIALOG(dialog);
}

void
gsh_about_dialog ()
{
  gtk_dialog_run ( setup_about_fields 
                  ( GTK_ABOUT_DIALOG ( gtk_about_dialog_new ()))); 
  exit(0);
}

