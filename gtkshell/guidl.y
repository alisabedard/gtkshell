%{

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

#include <stdio.h>
#define YYFILE
#include "gtkshell.h"

void
yyerror(const char *string)
{
	g_error("error:  %s\n", string);
}

int
yywrap(void)
{
	return 1;
}

struct GDLEnvironment * gsh_guidl_env;

%}
%union
{
	gchar * string;
	gint number;
}
%token IFS SC COMMA OPTION DIALOG 
%token END ADD BUTTONS BUTTON TOKEN_ECHO
%token <string> STRING
%token <number> NUM
%%
commands:
/* empty */
| 
commands command END
;

command: 
option
|
add
|
dialog
|
TOKEN_ECHO STRING
{
	g_print("%s", $2);
	g_free($2);
}
;

dialog:
DIALOG STRING
{
	gsh_guidl_dialog($2, NULL);
}
|
DIALOG STRING STRING
{
	gsh_guidl_dialog($2, $3);
}
;

option:
OPTION STRING
{
	gsh_guidl_option($2, NULL);
}
|
OPTION STRING STRING
{
	gsh_guidl_option($2, $3);
}
|
OPTION STRING NUM
{
	gsh_guidl_option($2, ar_dtostr($3));
	/* num_string is freed in above call.  */
}
;

add:
ADD STRING STRING
{
	gsh_guidl_widget($2, $3);
}
|
ADD STRING
{
	gsh_guidl_widget($2, NULL);
}
|
ADD BUTTONS buttons
|
ADD BUTTON button
;

buttons:
/* empty */
|
buttons button COMMA
|
buttons button
;

button:
STRING
{
	ARMETHOD(gsh_guidl_env->args, add, ($1));
	g_free($1);
}
;

