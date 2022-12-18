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
#include <glib/gstdio.h>
#include <fcntl.h>

extern FILE *yyin, *yyout;
extern struct GDLEnvironment *gsh_guidl_env;

static void common_guidl_handler(GSH * gsh)
{
	/* make sure environment has been initialized */
	if (!gsh_guidl_env)
		gsh_guidl_env = ARNEW(gsh, GDLEnvironment);
	/* Determine whether or not to include an initial
	   dummy argument.  Needed as argv[0] is skipped
	   by the command line handling code. */
	if (!GSH_FLAG(GSH_GUIDL_NO_DUMMY))
		$(gsh_guidl_env->args, add, (const gchar *)"guidl");
	yyparse();
	/* Shortcut for specification of arguments.  */
#define GGEA gsh_guidl_env->args
	$(gsh, parse, GGEA->argc, (const gchar **)GGEA->argv);
	$(gsh_guidl_env, delete);
	gsh_guidl_env = NULL;
}

__attribute__ ((noreturn))
static void
gsh_invalid_option(GSH * gsh, const gchar ** argv, const gint option)
{
	g_warning("%s:  %s undefined\n", argv[0], argv[option]);
	if (gsh->usage)
		g_message("%s\n", gsh->usage);
	exit(EXIT_FAILURE);
}

static void guidl_file_cb(GSH * gsh, gint * counter, const gchar ** argv)
{
	const gchar *filename = argv[++(*counter)];

	/* If the argument is "-", use stdin for yyin.  */
	/* Otherwise, use FILENAME.  */
	if (strcmp("-", filename))
		yyin = fopen(filename, "r");
	common_guidl_handler(gsh);
}

#define GSH_KEY_FILE "gtkshell"
#define GSH_KEY_FILE_GROUP "user"

static inline gchar *add_to_usage(gchar * usage, const gchar * key,
				  const gchar * descr)
{
	gchar *tmp = usage;

	usage = g_strconcat(tmp, "\n", key, "\t", descr, NULL);
	g_free(tmp);

	return usage;
}

static gchar *get_key_filename(void)
{
	return g_build_filename(g_get_user_config_dir(), GSH_KEY_FILE, NULL);
}

static GKeyFile *get_key_file(void)
{
	GKeyFile *kf;
	gchar *fn;

	kf = g_key_file_new();
	fn = get_key_filename();
	g_key_file_load_from_file(kf, fn, G_KEY_FILE_NONE, NULL);
	g_free(fn);

	return kf;
}

static gchar *get_value(const gchar * key)
{
	GKeyFile *kf;
	gchar *value;

	kf = get_key_file();
	value = g_key_file_get_string(kf, GSH_KEY_FILE_GROUP, key, NULL);
	g_key_file_free(kf);

	return value;
}

__attribute__ ((noreturn))
static void
print_value(GSH * gsh __attribute__ ((unused)),
	    gint * counter, const gchar ** argv)
{
	gchar *value;

	value = get_value(argv[++(*counter)]);
	if (value) {
		puts(value);
		g_free(value);
	}
	exit(0);
}

static gchar *get_key_file_data(gsize * data_size)
{
	GKeyFile *kf;
	gchar *data;

	kf = get_key_file();
	data = g_key_file_to_data(kf, data_size, NULL);
	g_key_file_free(kf);

	return data;
}

__attribute__ ((noreturn))
static void
print_all_values(GSH * gsh __attribute__ ((unused)),
		 gint * counter __attribute__ ((unused)),
		 const gchar ** argv __attribute__ ((unused)))
{
	gchar *data;

	data = get_key_file_data(NULL);
	puts(data);
	g_free(data);
	exit(0);
}

__attribute__ ((noreturn))
static void
set_value(GSH * gsh __attribute__ ((unused)),
	  gint * counter, const gchar ** argv)
{
	GKeyFile *kf;
	gchar *data, *fn;
	gsize data_size;
	const gchar *key = argv[++(*counter)];
	const gchar *value = argv[++(*counter)];

	kf = get_key_file();
#ifdef DEBUG
	fprintf(stderr, "KEY: %s\tVALUE:  %s\n", key, value);
#endif
	g_key_file_set_string(kf, GSH_KEY_FILE_GROUP, key, value);
	data = g_key_file_to_data(kf, &data_size, NULL);
	g_key_file_free(kf);
	fn = get_key_filename();
	g_file_set_contents(fn, data, (gssize) data_size, NULL);
	g_free(fn);
	g_free(data);
	exit(0);
}

static ARTupleVector *gsh_define_command_line_options(GSH * gsh)
{
	ARTupleVector *dictionary;
	gchar *usage;
	const bool usage_defined = (usage = gsh->usage);

	if (!usage_defined)
		usage = g_strdup("Usage:  ");

#define ARTDEF(key, cb, descr)\
	$(dictionary, add, key, (const gchar *)cb);\
        if(!usage_defined)usage=add_to_usage(usage, key, descr)

	dictionary = ARNEW(ar, ARTupleVector);

	/* Widgets */
	ARTDEF("-aAm", gsh_add_app_menu_cb, "add application menu");
	ARTDEF("-aAc", gsh_add_applet_clock_cb, "add clock applet");
	ARTDEF("-ab", gsh_add_pane_cb, "add resizable pane");
	ARTDEF("-acb", gsh_add_commanded_button_cb, "add commanded button");
	ARTDEF("-acl", gsh_add_commanded_label_cb, "add commanded label");
	ARTDEF("-ae", gsh_add_editor_cb, "add editor");
	ARTDEF("-af", gsh_add_form_cb, "add radio button form");
	ARTDEF("-aL", gsh_add_list_cb, "add list");
	ARTDEF("-al", gsh_add_label_cb, "add label");
	ARTDEF("-aP", gsh_add_piped_text_cb, "add piped text from stdin");
	ARTDEF("-ap", gsh_add_piped_label_cb, "add piped label from stdin");
	ARTDEF("-ar", gsh_add_row_cb, "add new row");
	ARTDEF("-aS", gsh_add_separator_cb, "add separator");
#ifdef HAVE_VTE
	ARTDEF("-as", gsh_add_shell_cb, "add terminal (VTE)");
#else /* not HAVE_VTE */
	ARTDEF("-as", gsh_add_command_cb, "add command shell");
#endif /* HAVE_VTE */
	ARTDEF("-at", gsh_add_entry_cb, "add text entry");
	ARTDEF("-aT", gsh_add_text_cb, "add text editor");
	ARTDEF("-aw", gsh_add_window_cb, "add new window");

	/* Updating widgets */
	ARTDEF("-aul", gsh_add_updating_label_cb, "add updating label");
	ARTDEF("-aup", gsh_add_updating_progress_cb,
	       "add updating progress bar");

	/* Configuration utility */
	ARTDEF("-ca", print_all_values, "print all values");
	ARTDEF("-cg", print_value, "print value");
	ARTDEF("-cs", set_value, "set value");

	/* Options */
	ARTDEF("-oa", gsh_option_app_mode_cb, "set app mode");
	ARTDEF("-oc", gsh_option_color_cb, "set color");
	ARTDEF("-oD", gsh_option_no_dummy_cb, "set no dummy");
	ARTDEF("-oE", gsh_option_echoes_cb, "set echoes");
	ARTDEF("-oe", gsh_option_exits_cb, "set exits");
	ARTDEF("-oF", gsh_option_no_base_frame_cb, "set no base frame");
	ARTDEF("-of", gsh_option_framed_labels_cb, "set framed labels");
	ARTDEF("-og", gsh_option_geometry_cb, "set geometry");
	ARTDEF("-oH", gsh_option_horiz_clock_cb, "set horizontal clock");
	ARTDEF("-oh", gsh_option_horiz_labels_cb, "set horizontal labels");
	ARTDEF("-oi", gsh_option_icon_size_cb, "set icon size");
	ARTDEF("-ol", gsh_option_no_expand_cb, "set no expand");
	ARTDEF("-oL", gsh_option_expand_cb, "set expand");
	ARTDEF("-on", gsh_option_no_decorations_cb, "set no decorations");
	ARTDEF("-op", gsh_option_pane_next_cb, "set adding to next pane");
	ARTDEF("-oR", gsh_option_no_relief_cb,
	       "set no relief on image buttons");
	ARTDEF("-or", gsh_option_rows_cb, "set number of rows");
	ARTDEF("-os", gsh_option_scroll_cb, "set scroll");
	ARTDEF("-oT", gsh_option_title_cb, "set window title");
	ARTDEF("-ou", gsh_option_update_cb, "set update frequency");

#ifdef HAVE_VTE
	/* Terminal options */
	ARTDEF("-otf", gsh_option_terminal_font_cb, "set terminal font");
	ARTDEF("-oth", gsh_option_terminal_height_cb, "set terminal height");
	ARTDEF("-otN", gsh_option_terminal_not_tab_cb, "set terminal not tab");
	ARTDEF("-otT", gsh_option_terminal_not_transparent_cb,
	       "set not transparent");
	ARTDEF("-ott", gsh_option_terminal_transparent_cb, "set transparent");
	ARTDEF("-otw", gsh_option_terminal_width_cb, "set terminal width");
#else /* not HAVE_VTE */
	ARTDEF("-otf", gsh_option_null_cb, "NOT SUPPORTED:  set terminal font");
	ARTDEF("-oth", gsh_option_null_cb,
	       "NOT SUPPORTED:  set terminal height");
	ARTDEF("-otN", gsh_option_null_cb,
	       "NOT SUPPORTED:  set terminal not tab");
	ARTDEF("-otT", gsh_option_null_cb,
	       "NOT SUPPORTED:  set not transparent");
	ARTDEF("-ott", gsh_option_null_cb, "NOT SUPPORTED:  set transparent");
	ARTDEF("-otw", gsh_option_null_cb,
	       "NOT SUPPORTED:  set terminal width");
#endif /* HAVE_VTE */

	/* Dialog options */
	ARTDEF("-da", gsh_dialog_about_cb, "show about dialog");
	ARTDEF("-dc", gsh_dialog_color_cb, "show color chooser");
	ARTDEF("-dD", gsh_dialog_folder_cb, "show folder chooser");
	ARTDEF("-dd", gsh_dialog_folder_open_cb, "show folder opener");
	ARTDEF("-de", gsh_dialog_error_cb, "show error dialog");
	ARTDEF("-dF", gsh_dialog_font_cb, "show font dialog");
	ARTDEF("-df", gsh_dialog_file_cb, "show file dialog");
	ARTDEF("-di", gsh_dialog_information_cb, "show information dialog");
	ARTDEF("-ds", gsh_dialog_save_cb, "show save dialog");
	ARTDEF("-dw", gsh_dialog_warning_cb, "show warning dialog");

	/* GUIDL file */
	ARTDEF("-f", guidl_file_cb, "open GUIDL file");

	gsh->usage = usage;
	return dictionary;
}

void gsh_handle_switch_argument(GSH * gsh, const gchar ** argv, gint * counter)
{
	void (*callback) (GSH *, gint *, const gchar **) = NULL;
	ARTupleVector *dict;

	/* Needed for proper widget layout.  */
	$(gsh->rows, check);

	/* Define command line option dictionary if such has not already
	   been done.  */
	if (!(dict = gsh->command_dictionary))
		dict = gsh->command_dictionary =
		    gsh_define_command_line_options(gsh);
	/* Look up the callback per command line switch.  */
	/* Execute callback if lookup fruitful.  */
	if ((callback = (void (*)(GSH *, gint *, const gchar **))
	     $(dict, find, argv[*counter])))
		callback(gsh, counter, argv);
	else			/* Invalid option, display warning */
		gsh_invalid_option(gsh, argv, *counter);
}
