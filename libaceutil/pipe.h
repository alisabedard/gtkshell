/*
 * GUIShell (c) 2002-2006 Alisa Bedard alisabedard@gmail.com
 *
 * This file is part of GUIShell.
 *
 * GUIShell is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GUIShell is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with GUIShell; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LIBAR_PIPE_H
#define LIBAR_PIPE_H

gchar *antiright_pipe_read(const gchar * command_string);

gchar *antiright_read_file(FILE * file);

gchar *antiright_read_named_file(const gchar * filename);

/* void */
/* antiright_pipe_write(char *command_string, char* data); */
/* void */
/* antiright_fifo_server(char *command_string, char *fifo); */
#endif
