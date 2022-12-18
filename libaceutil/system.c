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

#include "library.h"

#define MUST_REFORMAT(f) (f[strlen(f)-1]!='&')
#define GET_COMMAND_STRING(f)\
 (MUST_REFORMAT(f)?g_strconcat(f, " &", NULL):g_strdup(f))

int gtkshell_system(char *field_string)
{
	char *command;
	int return_status;

	command = GET_COMMAND_STRING(field_string);
	return_status = system(command);
	g_free(command);

	return return_status;
}

int vsysprintf(const char *format, va_list list)
{
	char *command;
	int return_value;

	g_vasprintf(&command, format, list);
	return_value = gtkshell_system(command);
	g_free(command);

	return (return_value);
}

int sysprintf(const char *format, ...)
{
	va_list list;
	int return_value;

	va_start(list, format);
	return_value = vsysprintf(format, list);
	va_end(list);
	return (return_value);
}
