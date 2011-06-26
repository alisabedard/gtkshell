###############################################################################
#
#    GUIShell
#    (c) 2004-2010 Jeffrey Bedard
#    antiright@gmail.com
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

all: libantiright.a

objects=$(patsubst %.c,%.o,$(wildcard *.c)) 

libantiright.a: ${objects}
	ar rcs libantiright.a ${objects}
clean:
	rm -f *.o *.a *~

