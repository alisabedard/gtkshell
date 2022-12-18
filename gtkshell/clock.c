/*
  GUIShell
  (c) 2007-2010 Alisa Bedard
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
#include <time.h>

#define GSH_CLOCK_TIME_STRING_SIZE 65

struct GSHClockData {
	GSH *gsh;
	GtkWidget *clock_widget;
};

static void get_time_string(gchar * time_string, GSH * gsh)
{
	time_t time_value;
	struct tm *split_time;

	time_value = time(NULL);
	split_time = localtime(&time_value);
#define GSHTM(element) split_time->tm_##element
	(void)snprintf(time_string, GSH_CLOCK_TIME_STRING_SIZE,
		       "%.2d/%.2d/%.2d %c%.2d:%.2d:%.2d",
		       GSHTM(mday), GSHTM(mon) + 1, GSHTM(year) % 100,
		       (GSH_FLAG(GSH_HORIZ_CLOCK) ? ' ' : '\n'),
		       GSHTM(hour), GSHTM(min), GSHTM(sec));
}

static void
update_clock(const gchar * command __attribute__ ((unused)),
	     gpointer clock_pointer)
{
	struct GSHClockData *clock = (struct GSHClockData *)clock_pointer;
	gchar time_string[GSH_CLOCK_TIME_STRING_SIZE];

	get_time_string(time_string, clock->gsh);
	gtk_label_set_text(GTK_LABEL(clock->clock_widget), time_string);
}

GtkWidget *gsh_clock_new(GSH * gsh)
{
	GtkWidget *clock;
	struct GSHClockData *clock_data;

	clock_data = malloc(sizeof(struct GSHClockData));
	gsh_widget_set_font(clock = gtk_label_new(NULL), "Mono 10");
	clock_data->clock_widget = clock;
	clock_data->gsh = gsh;
	GSH_NEW_UPDATER(gsh, update_clock, (gpointer) clock_data);
	gtk_widget_show(clock);

	return clock;
}
