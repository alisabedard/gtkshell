###############################################################################
#
#    GUIShell
#    (c) 2004-2011 Jeffrey Bedard
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

include ./config.mk

CFLAGS += $(INCLUDE) $(DEFS) -Wall -W -g

all: 
	cd libaceutil && $(MAKE)
	cd gtkshell && $(MAKE)
	cd ACE-desktop && $(MAKE)
ifneq ($(OS),MINGW32)
	cd xshell && $(MAKE)
	cd rootcat && $(MAKE)
endif
ctags:
	ctags -w */*.[ch] ACE-desktop/ACE

clean:
	cd libaceutil && $(MAKE) clean
	cd gtkshell && $(MAKE) clean
	cd ACE-desktop && $(MAKE) clean
	$(XSHELL_BUILD) clean
ifneq ($(OS),MINGW32)
	cd xshell && $(MAKE) clean
	cd rootcat && $(MAKE) clean
endif

distclean: clean
	cd gtkshell && $(MAKE) distclean
	rm -rf config.mk tags *~ */.\#* .\#* 

INSTALL=install
INSTALL_PROGRAM=$(INSTALL) -c -s
INSTALL_SCRIPT=$(INSTALL) -c -m 755
INSTALL_DATA=$(INSTALL) -c -m 644
INSTALL_DIR=$(INSTALL) -d
bindir=$(PREFIX)/bin
mandir=$(PREFIX)/man
man1dir=$(mandir)/man1
man5dir=$(mandir)/man5
datadir=$(PREFIX)/share
docdir=$(datadir)/doc
PKGBASE=aceutil

install: all
	${INSTALL_DIR} $(PREFIX)
	${INSTALL_DIR} $(bindir)
	${INSTALL_DIR} $(man1dir)
	${INSTALL_DIR} $(docdir)/aceutil
	$(INSTALL_DATA) doc/gtkshell.1 $(man1dir)
	$(INSTALL_DATA) doc/gshterm.1 $(man1dir)
	$(INSTALL_DATA) COPYING $(docdir)/aceutil
	$(INSTALL_DATA) doc/AUTHORS $(docdir)/aceutil
	$(INSTALL_DATA) README $(docdir)/aceutil
	$(INSTALL_DATA) doc/TODO $(docdir)/aceutil
	$(INSTALL_DATA) doc/INSTALL $(docdir)/aceutil
	cd gtkshell && $(MAKE) install
	cd ACE-desktop && $(MAKE) install
	$(XSHELL_BUILD) install
ifneq ($(OS),MINGW32)
	cd xshell && $(MAKE) install
	cd rootcat && $(MAKE) install
endif

bzball: distclean
	cd .. && cp -R aceutil guishell-$(VERSION) \
	&& tar cjf guishell-$(VERSION).tar.bz2 guishell-$(VERSION) \
	&& rm -rf guishell-$(VERSION)

