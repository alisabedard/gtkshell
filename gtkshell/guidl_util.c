/*
  GUIShell
  (c) 2007 Alisa Bedard
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

/* This must be eliminated if thread-safe gtkshell is to be implemented.  */
struct GDLEnvironment *gsh_guidl_env = NULL;

static void gsh_delete_GDLEnvironment(struct GDLEnvironment *env)
{
	ARDELETE(env->dictionaries);
	/* Command line arguments (env->args) should remain 
	 * intact for updater widgets.  */
	$(env->args, delete_options);
	arfree(env);
}

static void
gsh_GDLEnvironment_add(struct GDLEnvironment *env,
		       const gchar * switches, gchar * argument)
{
	/* A command base argument (for command line 
	   switch translation) is required.  */
	if (switches) {
		$(env->args, add, switches);
		if (argument) {
			$(env->args, add, argument);
			g_free(argument);
		}
	}
}

static void setup_GDLEnvironment(struct GDLEnvironment *env)
{
	env->args = ARNEW(ar, ARArguments);
	env->dictionaries = ARNEW(gsh, GDLDictionaries);
	env->delete = &gsh_delete_GDLEnvironment;
	env->add = &gsh_GDLEnvironment_add;
}

struct GDLEnvironment *gsh_new_GDLEnvironment()
{
	struct GDLEnvironment *env;

	env = armalloc(sizeof(struct GDLEnvironment));
	setup_GDLEnvironment(env);

	return env;
}
