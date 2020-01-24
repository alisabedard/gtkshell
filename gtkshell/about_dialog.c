/*
   GUIShell
   (c) 2007-2020 Jeffrey Bedard
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
   along with GUIShell; if not, write to the
   Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301  USA
 */

#include "gtkshell.h"

static void setup_about_license(GtkAboutDialog * dialog) {
    gtk_about_dialog_set_license(dialog,
            "http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html");
}

static void setup_logo(GtkAboutDialog * dialog) {
    GtkWidget *image;
    GdkPixbuf *pb;
    image = gtk_image_new_from_file
        (ARDATADIR "/icons/ACE_32.png");
    gtk_widget_show(image);
    pb=gtk_image_get_pixbuf(GTK_IMAGE(image));
    gtk_about_dialog_set_logo(dialog, pb);
    g_object_unref(pb);
}

static GtkDialog *setup_about_fields(GtkAboutDialog * dialog) {
    const gchar *authors[] = GSH_AUTHORS;
    setup_about_license(dialog);
    setup_logo(dialog);
    gtk_about_dialog_set_website(dialog, GSH_WEBSITE);
    gtk_about_dialog_set_authors(dialog, authors);
    gtk_about_dialog_set_comments(dialog, GSH_COMMENTS);
    gtk_about_dialog_set_copyright(dialog, GSH_COPYRIGHT);
    gtk_about_dialog_set_version(dialog, PACKAGE_STRING);

    return GTK_DIALOG(dialog);
}

void gsh_about_dialog() {
    gtk_dialog_run(setup_about_fields
            (GTK_ABOUT_DIALOG(gtk_about_dialog_new())));
    exit(0);
}
