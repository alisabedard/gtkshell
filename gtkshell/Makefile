###############################################################################
#
#    GUIShell
#    {c} 2004-2019 Jeffrey Bedard
#    jefbed@gmail.com
# 
#    This file is part of GUIShell.
#
#     GUIShell is free software; you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation; either version 2 of the License, or
#     (at your option) any later version.
#
#     GUIShell is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with GUIShell; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, 
#     Boston, MA  02110-1301  USA		
#
###############################################################################

include ../config.mk

CFLAGS+=$(DEFS) $(INCLUDE)
# The following disables error flags, specifically to allow auto-generated
# sources to compile:
CFLAGS+=-Wno-error=sign-compare -Wno-error=unused-function
ARFLAGS=-L../libaceutil -laceutil
GTKFLAGS=$(ARFLAGS) $(LDFLAGS)


ifeq ($(OS),MINGW32)
	INSTALLPROG=cp
else
	INSTALLPROG=install -s
endif

all:
	$(MAKE) gtkshell

objects=y.tab.o about_dialog.o add_options.o app_mode.o arguments.o button.o \
	callbacks.o clock.o color.o command_shell.o containers.o dialog.o \
	dialog_options.o dragdrop.o font.o form.o geometry.o gtkshell.o \
	guidl_dialog.o guidl_dictionary.o guidl_options.o guidl_util.o \
	guidl_widgets.o image_button.o init.o label.o lex.yy.o main.o \
	menu.o option_options.o options.o pane.o ptk-app-menu.o row.o \
	terminal.o terminal_options.o text.o tree.o undo.o updated_label.o \
	updated.o updated_progress.o update_manager.o

y.tab.c: guidl.y
	$(YACC) -d -o y.tab.c guidl.y

lex.yy.c: guidl.lex
	$(LEX) -o lex.yy.c guidl.lex

gtkshell: $(objects) 
	cc -o gtkshell $(objects) $(GTKFLAGS)

parser-clean:
	rm -f *.yy.c *.tab.c *.tab.h

clean:
	rm -f gtkshell *.o libgtkshell.a 

distclean: clean parser-clean
	rm -f *~

install:
	mkdir -p $(PREFIX)/bin
	$(INSTALLPROG) gtkshell$(SUFFIX) $(PREFIX)/bin
	install gshterm $(PREFIX)/bin

indent: 
	indent *.[ch]
	rm *~

