
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

#include "library.h"

/* FREE RETURNED STRING.  */
gchar *antiright_read_file(FILE * file)
{
	gchar buffer[BUFSIZ];
	gchar *text;
	size_t total, read;

	text = NULL;
	total = 0;
	read = 0;

	text = g_strdup("\0");
	while ((read = fread(buffer, sizeof(gchar), BUFSIZ, file)) != 0) {
		total += read;
		text = (gchar *) g_realloc(text, total * sizeof(gchar));
		g_strlcat(text, buffer, total);
	}

	return text;
}

gchar *antiright_read_named_file(const gchar * filename)
{
	gchar *contents;

	g_file_get_contents(filename, &contents, NULL, NULL);

	return contents ? contents : "";
}

/* Make sure that you free the returned string.  */
gchar *antiright_pipe_read(const gchar * command_string)
{
	/* Declare.  */
	gchar *command_stdout = NULL;

	/* Check arguments.  */
	ARPASSERT(command_string);

	g_spawn_command_line_sync(command_string, &command_stdout, NULL,
				  NULL, NULL);
	return command_stdout ? g_strchomp(command_stdout) : g_strdup("");
}
