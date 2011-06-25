%{
/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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


%}
%%
\"[^\"]*\"	 { 	
			/* Remove quotes.  */ 
			yylval.string=g_strdup(yytext+1); 
			yylval.string[yyleng-2]='\0';
			return STRING;
	 	}
[0-9]+		yylval.number=atoi(yytext); return NUM;
, 		return COMMA;
;		return END;
option		return OPTION;
add		return ADD;
buttons		return BUTTONS;
button		return BUTTON;
echo		return TOKEN_ECHO;
dialog		return DIALOG;
if		{
			char * cond=malloc(0);
			char * result;
			char c;
			unsigned int length=0;
			
			/* Find beginning condition to evaluate with shell.  */
			while(input()!='\"');
			while((c=input())!='\"')
			{
				/* Resize string buffer as needed.  */
				cond=realloc(cond, ++length);
				cond[length-1]=c;
			cond[length]='\0'; /* NULL termination.  */
				puts(cond);
			}
			cond[length]='\0'; /* NULL termination.  */
			result=antiright_pipe_read(cond);
			free(cond);
			puts("*** Test truth.");
			/* Skip command on FALSE.  */
			if(!strcmp(result, "FALSE"))
				while(input()!=';');
			/* Else, leave command for parser.  */
			g_free(result); /* Cleanup.  */
		}
[ \t\n]		; /* ignore */
"//".*$		; /* comment */
%%
