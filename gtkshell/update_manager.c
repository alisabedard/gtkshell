/*
  GUIShell
  (c) 2002-2006 Jeffrey Bedard
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

static void
gsh_update_each(gpointer data, gpointer user_data __attribute__ ((unused)))
{
	if (data)
		$(((struct GSHUpdatedWidget *)data), update);
}

static gint gsh_perform_updates(gpointer data)
{
	if (data) {
		g_slist_foreach(((struct GSHUpdateManager *)data)->list,
				gsh_update_each, NULL);
		return TRUE;
	}
	return FALSE;
}

static void gsh_GSHUpdateManager_start(struct GSHUpdateManager *updaters)
{
	if (updaters) {
		if (updaters->updating)
			return;
		else
			updaters->updating = TRUE;
		gsh_perform_updates(updaters);
		(void)g_timeout_add(updaters->period, gsh_perform_updates,
				    updaters);
	}
}

static void
gsh_GSHUpdateManager_add(struct GSHUpdateManager *updaters,
			 struct GSHUpdatedWidget *item)
{
	if (updaters) {
		if (item) {
			updaters->list = g_slist_prepend(updaters->list, item);
		}
		/* Begin updating, if necessary.  */
		gsh_GSHUpdateManager_start(updaters);
	}
}

static void
gsh_delete_each_updater(gpointer data,
			gpointer user_data __attribute__ ((unused)))
{
	struct GSHUpdatedWidget *item;

	item = (struct GSHUpdatedWidget *)data;
	$(item, delete);
}

static void gsh_delete_GSHUpdateManager(struct GSHUpdateManager *updaters)
{
	g_slist_foreach(updaters->list, gsh_delete_each_updater, NULL);
	g_slist_free(updaters->list);
	arfree(updaters);
}

/* Setup method function pointer assignments.  */
static inline void assign_methods(struct GSHUpdateManager *update)
{
	update->delete = &gsh_delete_GSHUpdateManager;
	update->add = &gsh_GSHUpdateManager_add;
}

/* Setup member data fields.  */
static inline void initialize_fields(struct GSHUpdateManager *update)
{
	update->period = 1000;
	update->list = (GSList *) NULL;
	update->updating = FALSE;
}

static inline void setup_updater(struct GSHUpdateManager *updater)
{
	assign_methods(updater);
	initialize_fields(updater);
}

struct GSHUpdateManager *gsh_new_GSHUpdateManager()
{
	struct GSHUpdateManager *updater;

	updater = armalloc(sizeof(struct GSHUpdateManager));
	setup_updater(updater);

	return updater;
}
