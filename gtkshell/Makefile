###############################################################################
#
#    GUIShell
#    (c) 2004-2015 Jeffrey Bedard
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
ARFLAGS=-L../libaceutil -laceutil
GTKFLAGS=$(ARFLAGS) $(LDFLAGS)


ifeq ($(OS),MINGW32)
	INSTALLPROG=cp
else
	INSTALLPROG=install -s
endif

all: y.tab.c
	$(LEX) -o lex.yy.c guidl.lex
	$(YACC) -d -o y.tab.c guidl.y
	$(MAKE) gtkshell

objects=$(patsubst %.c,%.o,$(wildcard *.c)) 

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

