/*
  GUIShell
  (c) 2002-2019 Alisa Bedard
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

#ifndef GSH_MACROS_H
#define GSH_MACROS_H

#define GSHBIT(n) (1 << (n-1))

#define GSH_NONE		0
#define GSH_SCROLL		GSHBIT(1)
#define GSH_CBEXIT		GSHBIT(2)
#define GSH_UPDATING		GSHBIT(3)
#define GSH_HORIZONTAL_LABELS	GSHBIT(4)
#define GSH_PROMPT_ECHOES	GSHBIT(5)
#define GSH_FRAMED_LABELS	GSHBIT(6)
#define GSH_MENU_BUTTON		GSHBIT(7)
#define GSH_NO_BASE_FRAME	GSHBIT(8)
#define GSH_NO_EXPAND		GSHBIT(9)
#define GSH_GUIDL_NO_DUMMY	GSHBIT(10)
#define GSH_APP_MODE		GSHBIT(11)
#define GSH_PANE_NEXT		GSHBIT(12)
#define GSH_FIRST_TERMINAL	GSHBIT(13)
#define GSH_TERM_TRANSPARENT	GSHBIT(14)
#define GSH_IN_SECONDARY_WIN	GSHBIT(15)
#define GSH_ICON_SIZE_IS_CUSTOM GSHBIT(16)
#define GSH_NO_RELIEF		GSHBIT(17)
#define GSH_HORIZ_CLOCK 	GSHBIT(18)
#define GSH_HEAP_ALLOCATED      GSHBIT(19)

typedef guint32 Bitmask;

#define GSH_FLAG(flag) ((gsh->bflags & flag) == flag)
#define GSH_SET(flag) gsh->bflags |= flag
#define GSH_UNSET(flag) gsh->bflags &= ~flag

#define GSH_ACTION_IF(action, arg) if(arg) action(arg)
#define GSH_DESTROY_IF(widget) GSH_ACTION_IF(gtk_widget_destroy, widget)
#define GSH_FREE_IF(var) GSH_ACTION_IF(g_free, var)
#define GFREEIF(var) {if(var) {g_free(var); var=NULL;}}

#define GSH_FIXME() \
	sysprintf("gtkshell -dw '%s:%d: FIXME'",\
		__FILE__, __LINE__)

/* GSH Container Add */
#define GSHCA(container, widget)\
	gtk_container_add(GTK_CONTAINER(container), widget)
/* Add without expansion.  */
#define GSHCA_TIGHT(cont, widget)\
	gtk_box_pack_start(GTK_BOX(cont), widget, FALSE, FALSE, 0)

#define GSH_CREATE(var, type, ...)\
	var=GTK_WIDGET(gtk_##type##_new(__VA_ARGS__))

#define GSH_SHOW_CREATE(var, type, ...)\
	gtk_widget_show(GSH_CREATE(var, type, __VA_ARGS__))

#define GSH_ADD_WIDGET(cont, var, type, ...)\
{\
  GSH_CREATE(var, type, __VA_ARGS__);\
  GSHCA(cont,var);\
}

#define GSH_ADD_WIDGET_TIGHT(cont, var, type, ...)\
{\
  GSH_CREATE(var, type, __VA_ARGS__);\
  GSHCA_TIGHT(cont,var);\
}

#define GSH_ADD_MANAGED(gsh, var, type, ...)\
{\
	GSH_CREATE(var, type, __VA_ARGS__);\
	$(gsh, manage, var);\
}

#define GSH_GET_CHILD(widget)\
  gtk_bin_get_child(GTK_BIN(menu_button))

#define GET_STOCK_ITEM(item, ...)\
  gtk_##item##_new_from_stock(__VA_ARGS__)

#define SHOW_STOCK_ITEM(item, var, ...)\
  gtk_widget_show(var=GET_STOCK_ITEM(item, __VA_ARGS__))

#define ADD_STOCK_ITEM(item, cont, var, ...)\
  SHOW_STOCK_ITEM(item, var, __VA_ARGS__);\
  GSHCA(cont, var)

#define ADD_STOCK_BUTTON(cont, var, ...)\
  ADD_STOCK_ITEM(button, cont, var, __VA_ARGS__)

#define GSHCONNECT(widget, signal, cb, cbdata)\
	g_signal_connect(G_OBJECT(widget), signal, G_CALLBACK(cb), cbdata)

#define GSHSETCB(widget, cb, cbdata)\
        GSHCONNECT(widget, (G_UNLIKELY(GTK_IS_MENU_ITEM(widget)) \
                            ? "activate" : "clicked"), cb, cbdata)

#define GSH_OPTION_FUNC_NAME(option, op) gsh_option_##op##_##option
#define GSH_OPTION_PROTOTYPE(name)\
	void name(GSH * gsh, gint * counter, const gchar ** argv)
#define GSH_OPTION_FUNCTION(name, option, operation)\
	GSH_OPTION_PROTOTYPE(name) { operation(option); }
#define GSH_OPTION_SET_PROTOTYPE(option)\
	GSH_OPTION_PROTOTYPE(GSH_OPTION_FUNC_NAME(option, GSH_SET))
#define GSH_OPTION_SET_FUNCTION(option)\
	GSH_OPTION_FUNCTION(GSH_OPTION_FUNC_NAME(option, GSH_SET),\
		option, GSH_SET)
#define GSH_OPTION_UNSET_PROTOTYPE(option)\
	GSH_OPTION_PROTOTYPE(GSH_OPTION_FUNC_NAME(option, GSH_UNSET))
#define GSH_OPTION_UNSET_FUNCTION(option)\
	GSH_OPTION_FUNCTION(GSH_OPTION_FUNC_NAME(option, GSH_UNSET),\
		option, GSH_UNSET)

#define GSH_STOCK_ITEM(item, id) GTK_WIDGET(gtk_##item##_new_from_stock(id))

#endif /* not GSH_MACROS_H */
