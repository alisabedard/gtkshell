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

#include "library.h"

static void
delete_options(struct ARArguments * args)
{
	guint counter=args->argc;

	for(; counter>0; counter--)
	{
		gchar * arg=args->argv[counter-1];
		if(arg[0]=='-')
		{
			g_free(arg);
			args->argv[counter-1]=NULL;
		}
	}
}

static void
delete(struct ARArguments * args)
{
        delete_options(args);
        g_strfreev(args->argv);
	arfree(args);
}

static void
add(struct ARArguments * this, const gchar * item)
{
	this->argc++;
	this->argv=g_realloc(this->argv, sizeof(gchar*)*this->argc);
	this->argv[this->argc-1]=g_strdup(item);
}

static void
prepend(struct ARArguments * this, const gchar * item)
{
	gchar * swap;

	add(this, item);
	swap=this->argv[0];
	this->argv[0]=this->argv[this->argc-1];
	this->argv[this->argc-1]=swap;
}

static void
setup(struct ARArguments * args)
{
	args->argc=0;
	args->argv=NULL;
	args->add=&add;
	args->prepend=&prepend;
	args->delete=&delete;
        args->delete_options=&delete_options;
}

struct ARArguments *
ar_new_ARArguments()
{
	struct ARArguments * args;

	args=armalloc(sizeof(struct ARArguments));
	setup(args);

	return args;
}

