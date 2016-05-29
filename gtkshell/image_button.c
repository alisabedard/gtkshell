/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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

static inline guint gsh_icon_size_to_pixels(const guint icon_size)
{
	switch (icon_size) {
	case 1:
		return 16;
	case 2:
		return 18;
	case 0:
	case 3:
	case 4:
		return 24;
	case 5:
		return 32;
	case 6:
		return 48;
	default:		/* in case icon_size was specified in pixels */
		return icon_size;
	}
}

/* Get an image from the antiright icon distribution or the GTK stock
   icon set.  */
GtkWidget *gsh_get_image(const gchar * name, const guint icon_size)
{
	const guint sz = gsh_icon_size_to_pixels(icon_size);
	GtkWidget *image = NULL;
	{
		GdkPixbuf *pix;
#define CHKPIX if(pix) goto imagenew
#define LOADPB(n) gdk_pixbuf_new_from_file_at_size(n,sz,sz,NULL)
		pix = LOADPB(name);
		CHKPIX;
		{
			gchar *prefixed_name =
			    g_strconcat(ARDATADIR "/icons/", name, NULL);
			pix = LOADPB(prefixed_name);
			g_free(prefixed_name);
		}
		CHKPIX;
		{
			GtkIconInfo *inf;

			if ((inf =
			     gtk_icon_theme_lookup_icon
			     (gtk_icon_theme_get_default(), name, sz, 0))) {
				pix = LOADPB(gtk_icon_info_get_filename(inf));
				gtk_icon_info_free(inf);
			}
		}
 imagenew:
		if (pix) {
			image = gtk_image_new_from_pixbuf(pix);
			g_object_unref(pix);

			return image;
		}
	}
	if ((image = gtk_image_new_from_stock(name, icon_size)))
		return image;
	else
		return gtk_image_new_from_stock("gtk-execute", icon_size);
}

void gsh_image_button(struct GSH *gsh, char *command, char *name)
{
	GtkWidget *image;

	$(gsh, add.button, command);
	image = gsh_get_image((const gchar *)name, gsh->icon_size);
	if (image) {
		GtkWidget *parent = gsh->rows->v;
		GtkWidget *button = gsh->widgets.button;
		gtk_widget_show(image);
		if (!GTK_IS_MENU(parent) /* && !GTK_IS_TOOLBAR(parent)) */ ) {
			gtk_button_set_image(GTK_BUTTON(button), image);
			if (GSH_FLAG(GSH_NO_RELIEF))
				gtk_button_set_relief(GTK_BUTTON(button),
						      GTK_RELIEF_NONE);
		} else {	/* is menu-related */

			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM
						      (button), image);
		}
	}
}
