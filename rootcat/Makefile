###############################################################################
#
#    GUIShell
#    (c) 2008 Jeffrey Bedard
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

PROG=rootcat

INCLUDES=-I/usr/pkg/include/freetype2 -I/usr/X11R6/include/freetype2 
INCLUDES+=-I/usr/pkg/include -I/usr/X11R6/include
# This is for CYGWIN:
INCLUDES+=-I/usr/include/freetype2

LDFLAGS=-L/usr/pkg/lib -L/usr/X11R6/lib -lX11 -lXft -lXext
CFLAGS+=$(INCLUDES)
#CFLAGS+=-g3
objs=$(patsubst %.c,%.o,$(wildcard *.c)) 

all: $(PROG)

$(PROG): $(objs) 
	$(CC) -o $(PROG) $(objs) $(LDFLAGS)
clean:
	rm -f $(objs) $(PROG) *.core *~
install:
	$(INSTALL) -sc $(PROG) $(PREFIX)/bin
indent: 
	indent *.[ch]
	rm *~

