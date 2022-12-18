###############################################################################
#
#    xshell
#    (c) 2004-2011 Alisa Bedard
#    alisabedard@gmail.com
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

# The variables here tend to override the included values,
# as they are GTK-specific.  

INCLUDES=-I/usr/X11R6/include -I/usr/pkg/include 
# This is for CYGWIN:
INCLUDES+=-I/usr/include/freetype2/freetype/config

#CFLAGS=$(INCLUDES) $(DEFS)
CFLAGS+=$(INCLUDES) $(DEFS)
CFLAGS+=-DXSH_DECORATE
# For use with patched version of evilwm
# CFLAGS+=-DEVILWM_HACK_HACK
CFLAGS+=-DXSH_USE_GRADIENT
#CFLAGS+=-DXSH_USE_INDICATORS
#CFLAGS+=-DDEBUG -g3 -Wall -W -Werror
#CFLAGS+=-DDEBUG_EVENTS
# This is for a button status indicator, currently just a decoration.  
#CFLAGS+=-DXSH_USE_INDICATOR
LIBS=-L/usr/X11R6/lib -L/usr/pkg/lib -lX11
LDFLAGS=$(LIBS)

OBJECTS=xshell.o widget.o button.o arguments.o shell.o events.o decoration.o\
	text.o layout.o color.o font.o dialog.o

all: xshell

xshell: $(OBJECTS)
	$(CC) -o xshell $(OBJECTS) $(LDFLAGS)

clean:
	rm -f *.o xshell xshell.exe* *~

install:
	cp xshell $(PREFIX)/bin

