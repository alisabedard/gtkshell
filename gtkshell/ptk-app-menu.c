/*
* ptk-app-menu.c
*
* Description: Generate menu from desktop files according to the spec on freedesktop.org
*
*
* Author: Hong Jen Yee (PCMan) <pcman.tw (AT) gmail.com>, (C) 2006
*
* Copyright: GNU Lesser General Public License Version 2
*
*/
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

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <alloca.h>
#include "gtkshell.h"

//#include "misc.h" /* Misc functions for lxpanel */

GQuark PTK_APP_MENU_ITEM_ID = 0;
#define ICON_SIZE        GTK_ICON_SIZE_SMALL_TOOLBAR

GtkWidget *ptk_app_menu_new();

static const char desktop_ent[] = "Desktop Entry";
static const char app_dir_name[] = "applications";

typedef struct _CatInfo {
	char *title;
	char *directory_file;
	char *icon;
	const char **sub_cats;
} CatInfo;

typedef struct _PtkAppMenuItem {
	char *name;
	char *icon;
	char *exec;
} PtkAppMenuItem;

static const char *development_cats[] = {
	"Development",
	"Building",
	"Debugger",
	"IDE",
	"GUIDesigner",
	"Profiling",
	"RevisionControl",
	"Translation",
	"WebDevelopment",
	"ProjectManagement",
	NULL
};

static const char *office_cats[] = {
	"Office",
	"Dictionary",
	"Chart",
	"Calendar",
	"Email",
	"ContactManagement",
	"Database",
	"Finance",
	"PDA",
	"Presentation",
	"Spreadsheet",
	"WordProcessor",
	"Publishing",
	"FlowChart",
	NULL
};

static const char *graphics_cats[] = {
	"Graphics",
	"2DGraphics",
	"3DGraphics",
	"VectorGraphics",
	"RasterGraphics",
	"Viewer",
	"Scanning",
	"OCR",
	"Photography",
	NULL
};

static const char *network_cats[] = {
	"Network",
	"Dialup",
	"Email",
	"WebBrowser",
	"InstantMessaging",
	"IRCClient",
	"FileTransfer",
	"News",
	"P2P",
	"RemoteAccess",
	"Telephony",
	"TelephonyTools",
	"VideoConference",
	"HamRadio",
	"Chat",
	NULL
};

static const char *settings_cats[] = {
	"Settings",
	"DesktopSettings",
	"HardwareSettings",
	"Accessibility",
	"Printing",
	NULL
};

static const char *system_cats[] = {
	"System",
	"Core",
	"Security",
	"PackageManager",
	"Emulator",
	"FileManager",
	"TerminalEmulator",
	"Filesystem",
	"Monitor",
	"Security",
	NULL
};

static const char *audiovideo_cats[] = {
	"AudioVideo",
	"Audio",
	"Video",
	"Mixer",
	"Sequencer",
	"Tuner",
	"TV",
	"AudioVideoEditing",
	"Player",
	"Recorder",
	"DiscBurning",
	"Music",
	NULL
};

static const char *game_cats[] = {
	"Game",
	"Games",
	"Amusement",
	"ActionGame",
	"AdventureGame",
	"Adventure",
	"ArcadeGame",
	"BoardGame",
	"BlocksGame",
	"CardGame",
	"KidsGame",
	"LogicGame",
	"RolePlaying",
	"Simulation",
	"SportsGame",
	"StrategyGame",
	NULL
};

static const char *education_cats[] = {
	"Education",
	"Art",
	"Construction",
	"Music",
	"Languages",
	"Science",
	"ArtificialIntelligence",
	"Astronomy",
	"Biology",
	"Chemestry",
	"ComputerScience",
	"DataVisualization",
	"Economy",
	"Electricity",
	"Electronics",
	"Geography",
	"Geology",
	"Geoscience",
	"History",
	"ImageProcessing",
	"Literature",
	"Math",
	"NumericalAnalysis",
	"MedicalSoftware",
	"Physics",
	"Robotics",
	"Sports",
	"ParallelComputing",
	NULL
};

static const char *utility_cats[] = {
	"Utility",
	"TextTools",
	"Archiving",
	"Compression",
	"Calculator",
	"Clock",
	"TextEditor",
	"Accessibility",
	"File Management",
	"ConsoleOnly",
	"Core",
	NULL
};

static const char *other_cats[] = {
	"Other",
	"Documentation",
	"Help",
	NULL
};

static const CatInfo known_cats[] = {
	/* FIXME:  For some reason, these two UNUSED entries need to be
	   inserted here in order for the Games menu to show up.  */
	{N_("UNUSED"), "UNUSED", "applications-other", NULL},
	{N_("UNUSED"), "UNUSED", "applications-other", NULL},
	{N_("Games"), "Games", "applications-games", game_cats},
	{N_("Education"), "Education", "applications-science", education_cats},
	{N_("Development"), "Development", "applications-development",
	 development_cats},
	{N_("Audio & Video"), "Multimedia", "applications-multimedia",
	 audiovideo_cats},
	{N_("Graphics"), "Graphics", "applications-graphics", graphics_cats},
	{N_("Settings"), "Settings", "preferences-system", settings_cats},
	{N_("System Tools"), "System-Tools", "applications-system",
	 system_cats},
	{N_("Network"), "Internet", "applications-internet", network_cats},
	{N_("Office"), "Office", "applications-office", office_cats},
	{N_("Office"), "X-Debian-Applications-Office",
	 "applications-office", office_cats},
	{N_("Utilities"), "Utilities", "applications-accessories",
	 utility_cats},
	{N_("Other"), "Other", "applications-other", other_cats}
};

static int find_cat(char **cats)
{
	char **cat;
	for (cat = cats; *cat; ++cat) {
		register unsigned int i = 1;
		/* Skip other */
		while (++i < G_N_ELEMENTS(known_cats)) {
			register char **sub_cats =
			    (char **)known_cats[i].sub_cats;
			while (*sub_cats) {
				if (0 == strncmp(*cat, "X-", 2))	/*  Desktop specific */
					return -1;
				if (0 == strncmp(*sub_cats, *cat, 4))
					return i;

				++sub_cats;
			}
		}
	}
	return -1;
}

static void app_dirs_foreach(GFunc func, gpointer user_data);

static int compare_menu_item_titles(gpointer a, gpointer b)
{
#define TITLE(x) gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(x))))
	return g_ascii_strncasecmp(TITLE(a), TITLE(b), 4);
}

static int find_menu_item_by_name(gpointer a, gpointer name)
{
	return strncmp(((PtkAppMenuItem *)
			g_object_get_qdata(G_OBJECT(a),
					   PTK_APP_MENU_ITEM_ID))->name,
		       (char *)name, 3);
}

static char *load_cat_title(GKeyFile * kf, CatInfo * inf)
{
	char *ret = NULL;
	char *fn = g_strconcat("desktop-directories/", inf->directory_file,
			       ".directory", NULL);

	if (g_key_file_load_from_data_dirs(kf, fn, NULL, 0, NULL))
		ret =
		    g_key_file_get_locale_string(kf, desktop_ent, "Name", NULL,
						 NULL);
	g_free(fn);

	return ret;
}

static void
on_menu_item_size_request(GtkWidget * item,
			  GtkRequisition * req,
			  gpointer user_data __attribute__ ((unused)))
{
	const guint8 min_height =
	    ICON_SIZE + (GTK_CONTAINER(item)->border_width +
			 item->style->ythickness) * 2;
#define IFLTSET(x, y) if(x<y) x=y
	IFLTSET(req->height, min_height);
	IFLTSET(req->width, ICON_SIZE);
}

static bool
on_menu_item_expose(GtkWidget * item,
		    GdkEventExpose * evt __attribute__ ((unused)),
		    gpointer user_data)
{
	PtkAppMenuItem *data = (PtkAppMenuItem *) user_data;
	if (!((!data)
	      || (!GTK_IS_IMAGE_MENU_ITEM(item))
	      || (gtk_image_menu_item_get_image((GtkImageMenuItem *) item))))
		gtk_image_menu_item_set_image((GtkImageMenuItem *) item,
					      gsh_get_image(data->icon,
							    ICON_SIZE));
	return FALSE;
}

static void
on_app_menu_item_activate(GtkMenuItem * item __attribute__ ((unused)),
			  PtkAppMenuItem * data)
{
	gtkshell_system(data->exec);
}

#define SETUP_MENU_ITEM_SIGNALS(menu_item, data)\
{\
  GSHCONNECT (menu_item, "expose-event", on_menu_item_expose, data);\
  GSHCONNECT (menu_item, "size-request", on_menu_item_size_request, data);\
}
static char *translate_exec_to_cmd(const char *exec, const char *icon,
				   const char *title)
{
	GString *cmd = g_string_new(NULL);

	for (; *exec; ++exec) {
		if (G_UNLIKELY(*exec == '%')) {
			++exec;
			if (!*exec)
				break;
			switch (*exec) {
#define APPENDS(x) g_string_append(cmd, x)
#define APPENDC(x) g_string_append_c(cmd, x)
			case 'c':
				APPENDS(title);
				break;
			case 'i':
				if (icon) {
					APPENDS("--icon ");
					APPENDS(icon);
				}
				break;
			case '%':
				APPENDC('%');
				break;
			}
		} else
			APPENDC(*exec);
	}
	return g_string_free(cmd, FALSE);
}

static PtkAppMenuItem *setup_menu_item_label(GList * prev, const char *title,
					     GtkWidget ** menu_item)
{
	PtkAppMenuItem *data;

	if (!prev) {
		*menu_item = gtk_image_menu_item_new_with_label(title);
		data = g_slice_new0(PtkAppMenuItem);
	} else {
		GtkLabel *label;
		*menu_item = GTK_WIDGET(prev->data);
		label = GTK_LABEL(gtk_bin_get_child(GTK_BIN(*menu_item)));
		data =
		    (PtkAppMenuItem *) g_object_get_qdata(G_OBJECT(*menu_item),
							  PTK_APP_MENU_ITEM_ID);
		gtk_label_set_text(label, title);
		g_free(data->name);
		g_free(data->exec);
		g_free(data->icon);
	}

	return data;
}

static char *get_icon(GKeyFile * file)
{
	char *icon = g_strdup(g_key_file_get_string(file,
						    desktop_ent, "Icon", NULL));
	if (icon) {
		char *dot = strchr(icon, '.');
		if (icon[0] != '/' && dot)
			*dot = '\0';
	} else
		icon = "exec";

	return icon;
}

static GList *setup_with_title(GKeyFile * file, GList * sub_menu,
			       const char *fpath, const int prefix_len,
			       const char *exec)
{
	char *title = g_key_file_get_locale_string(file, desktop_ent,
						   "Name", NULL, NULL);
	if (title) {
		PtkAppMenuItem *data;
		GList *prev;
		GtkWidget *menu_item;

		prev = g_list_find_custom(sub_menu, (fpath + prefix_len),
					  (GCompareFunc)
					  find_menu_item_by_name);
		data = setup_menu_item_label(prev, title, &menu_item);
		data->name = g_strdup(fpath + prefix_len);
		data->exec = exec
		    ? translate_exec_to_cmd(exec, data->icon, title)
		    : NULL;
		g_free(title);
		SETUP_MENU_ITEM_SIGNALS(menu_item, data);
		data->icon = get_icon(file);
		if (!prev) {
			GSHCONNECT(menu_item, "activate",
				   on_app_menu_item_activate, data);
			g_object_set_qdata_full(G_OBJECT(menu_item),
						PTK_APP_MENU_ITEM_ID, data,
						NULL);
			sub_menu =
			    g_list_insert_sorted(sub_menu, (gpointer) menu_item,
						 (GCompareFunc)
						 compare_menu_item_titles);
		}
	}

	return sub_menu;
}

static GList *setup_with_exec(GKeyFile * file, GList * sub_menu,
			      const char *fpath, const int prefix_length)
{
	char *exec = g_key_file_get_string(file, desktop_ent, "Exec", NULL);
	if (exec) {
		sub_menu =
		    setup_with_title(file, sub_menu, fpath, prefix_length,
				     exec);
		g_free(exec);
	}

	return sub_menu;
}

static void do_load_dir(int prefix_len, const char *path, GList ** sub_menus)
{
	GDir *dir = g_dir_open(path, 0, NULL);
	const char *name;
	GKeyFile *file;

	if (G_UNLIKELY(!dir))
		return;

	file = g_key_file_new();

	while ((name = g_dir_read_name(dir))) {
		char *fpath;
		char **cats;

		if (name[0] == '.')
			continue;
		fpath = g_build_filename(path, name, NULL);
#define SKIP {g_free(fpath); continue;}
		if (g_file_test(fpath, G_FILE_TEST_IS_DIR)) {
			do_load_dir(prefix_len, fpath, sub_menus);
			SKIP;
		}
		if (!g_str_has_suffix(name, ".desktop")
		    || !g_key_file_load_from_file(file, fpath, 0, NULL)
		    || g_key_file_get_boolean(file, desktop_ent, "NoDisplay",
					      NULL))
			SKIP;
#define GETLIST(x) g_key_file_get_string_list(file,desktop_ent,x,NULL,NULL)
		if ((cats = GETLIST("Categories"))) {
			int i = find_cat(cats);
			if (i >= 0) {
				sub_menus[i] =
				    setup_with_exec(file, sub_menus[i], fpath,
						    prefix_len);
			}
			g_strfreev(cats);
		}
		g_free(fpath);
	}
	g_key_file_free(file);
	g_dir_close(dir);
}

static inline void load_dir(const char *path, GList ** sub_menus)
{
	do_load_dir(strlen(path) + 1, path, sub_menus);
}

static inline void
on_app_menu_destroy(gpointer user_data, GObject * menu __attribute__ ((unused)))
{
	g_signal_handler_disconnect(gtk_icon_theme_get_default(),
				    GPOINTER_TO_INT(user_data));
}

static inline bool ptk_app_menu_item_has_data(GtkMenuItem * item)
{
	return (g_object_get_qdata(G_OBJECT(item), PTK_APP_MENU_ITEM_ID) !=
		NULL);
}

static char *get_title(const unsigned int i)
{
	char *title;
	GKeyFile *kf;

	kf = g_key_file_new();
	title = load_cat_title(kf, (CatInfo *) & known_cats[i]);
	g_key_file_free(kf);

	return title;
}

static GtkWidget *new_menu_item_with_title(const unsigned int i)
{
	char *title = get_title(i);
	GtkWidget *menu_item
	    = gtk_image_menu_item_new_with_label(title ? title
						 : _(known_cats[i].title));
	g_free(title);

	return menu_item;
}

/*
 * Insert application menus into specified menu
 * menu: The parent menu to which the items should be inserted
 * position: Position to insert items.
             Passing -1 in this parameter means append all items
             at the end of menu.
 */

static GtkMenu *setup_submenu(GList * sub_items)
{
	GtkMenu *sub_menu;

	sub_menu = GTK_MENU(gtk_menu_new());
	{
		GList *l;

		for (l = sub_items; l; l = l->next)
			gtk_menu_shell_append(GTK_MENU_SHELL(sub_menu),
					      GTK_WIDGET(l->data));
	}
	g_list_free(sub_items);

	return sub_menu;
}

void ptk_app_menu_insert_items(GtkMenu * menu, int position)
{
	GList *sub_menus[G_N_ELEMENTS(known_cats)] = { 0 };
	unsigned int i = 0;

	if (G_UNLIKELY(PTK_APP_MENU_ITEM_ID == 0))
		PTK_APP_MENU_ITEM_ID =
		    g_quark_from_static_string("PtkAppMenuItem");

	app_dirs_foreach((GFunc) load_dir, sub_menus);

	while (++i < G_N_ELEMENTS(known_cats)) {
		GtkMenu *sub_menu;
		{
			GList *sub_items;

			if (!(sub_items = sub_menus[i]))
				continue;
			sub_menu = setup_submenu(sub_items);
		}
		{
			GtkWidget *menu_item;

			menu_item = new_menu_item_with_title(i);
			{
				PtkAppMenuItem *data;

				data = alloca(sizeof(PtkAppMenuItem));
				data->icon = g_strdup(known_cats[i].icon);
				g_object_set_qdata_full(G_OBJECT(menu_item),
							PTK_APP_MENU_ITEM_ID,
							data, NULL);
				SETUP_MENU_ITEM_SIGNALS(menu_item, data);
				on_menu_item_expose(menu_item, NULL, data);
				gtk_menu_item_set_submenu(GTK_MENU_ITEM
							  (menu_item),
							  GTK_WIDGET(sub_menu));
				gsh_add_tearoff(GTK_WIDGET(sub_menu));
				if (position >= 0)
					gtk_menu_shell_insert(GTK_MENU_SHELL
							      (menu), menu_item,
							      position);
				else
					GSHCA(menu, menu_item);
				g_free(data->icon);
			}
		}
	}
	gtk_widget_show_all(GTK_WIDGET(menu));
}

GtkWidget *ptk_app_menu_new()
{
	GtkWidget *menu;

	menu = gtk_menu_new();
	gsh_add_tearoff(menu);
	ptk_app_menu_insert_items(GTK_MENU(menu), -1);

	return menu;
}

static void app_dirs_foreach(GFunc func, gpointer user_data)
{
	const char **sys_dirs = (const char **)g_get_system_data_dirs();
	register guint len;

	len = g_strv_length((gchar **) sys_dirs);
	while (len--) {
		register char *path;
		struct stat dir_stat;

		path = g_build_filename(sys_dirs[len], app_dir_name, NULL);
		if (stat(path, &dir_stat) == 0) {
			func(path, user_data);
		}
		g_free(path);
	}
}

static void setup_app_menu_icon(GSH * gsh, GtkWidget * menu_item)
{
	/* Ensure proper icon size */
	if (!GSH_FLAG(GSH_ICON_SIZE_IS_CUSTOM))
		gsh->icon_size = GTK_ICON_SIZE_BUTTON;
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_item),
				      gtk_image_new_from_stock("gtk-home",
							       gsh->icon_size));
}

static GtkWidget *setup_menu_bar(GtkWidget * menu_button_item)
{
	GtkWidget *menu_bar;

	GSH_CREATE(menu_bar, menu_bar);
	GSHCA(menu_bar, menu_button_item);
	gtk_container_set_border_width(GTK_CONTAINER(menu_bar), 0);

	return menu_bar;
}

static GtkWidget *setup_menu_button_item(GSH * gsh, GtkWidget * app_menu)
{
	GtkWidget *menu_button_item;

	GSH_CREATE(menu_button_item, image_menu_item);
	setup_app_menu_icon(gsh, menu_button_item);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_button_item), app_menu);

	return menu_button_item;
}

void
gsh_add_app_menu_cb(GSH * gsh,
		    gint * counter __attribute__ ((unused)),
		    const gchar ** argv __attribute__ ((unused)))
{
	gsh->rows->current++;
	$(gsh, manage,
	  setup_menu_bar(setup_menu_button_item(gsh, ptk_app_menu_new())));
}
