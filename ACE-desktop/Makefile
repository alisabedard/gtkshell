##############################################################################
#
#    GUIShell
#    (c) 2004-2007 Jeffrey Bedard
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
#     Foundation, Inc., 51 Franklin Street, 
#     Fifth Floor, Boston, MA  02110-1301  USA		
#
###############################################################################

include ../config.mk

all: ACE.install hacks

ACE.install: ACE
	echo '#!/bin/sh' > ACE.install
	grep ^PREFIX ../config.mk >> ACE.install
	cat ACE >> ACE.install
	chmod +x ACE.install

hacks: hacks/*.sh
	chmod +x hacks/*.sh
	
clean:
	rm -f ACE.install


INSTALL_PROGRAM=$(INSTALL) -c -s
INSTALL_SCRIPT=$(INSTALL) -c -m 755
INSTALL_DATA=$(INSTALL) -c -m 644
INSTALL_DIR=$(INSTALL) -d
bindir=$(PREFIX)/bin
mandir=$(PREFIX)/man
man1dir=$(mandir)/man1
man5dir=$(mandir)/man5
datadir=$(PREFIX)/share/antiright
hackdir=$(datadir)/hacks
icondir=$(datadir)/icons
confdir=$(PREFIX)/etc/xdg/antiright

install: all
	$(INSTALL_DIR) $(bindir)
	${INSTALL_DIR} $(man1dir)
	$(INSTALL_DIR) $(man5dir)
	${INSTALL_DIR} $(datadir)
	${INSTALL_DIR} $(icondir)
	$(INSTALL_DIR) $(hackdir)
	$(INSTALL_DIR) $(confdir)
	$(INSTALL_SCRIPT) hacks/*.sh $(hackdir)
	$(INSTALL_DATA) system.antiright $(confdir)
	$(INSTALL_DATA) guidl/*.gdl $(datadir)
	$(INSTALL_SCRIPT) ACE.install $(bindir)/ACE
	$(INSTALL_DATA) ACE.1 $(man1dir)
	$(INSTALL_DATA) system.antiright.5 $(man5dir)
	$(INSTALL_DATA) icons/*.png $(icondir)
	$(INSTALL_DATA) icons/gnome_medium/*.png $(icondir)
	$(INSTALL_DATA) icons/gnome_small/*.png $(icondir)

