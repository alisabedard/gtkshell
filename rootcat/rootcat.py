#!/usr/bin/env python

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


# Based on:

# examples/draw.py -- high-level xlib test application.
#
#    Copyright (C) 2000 Peter Liljenberg <petli@ctrl-c.liu.se>
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

import sys
import os
from Xlib import X, display, Xutil
from optparse import OptionParser

DEBUG=False;

class StringRenderer:
	def __init__(self, display):
		self.dpy=display;
		self.screen=self.dpy.screen();
		self.root=self.screen.root;
		self.font=self.dpy.open_font("fixed")
		self.gc=self.root.create_gc(
			foreground=self.screen.white_pixel,
			background=self.screen.black_pixel,
			font=self.font);
	def clear(self):
		self.root.clear_area();
		if DEBUG:
			print("clear()");
	def draw(self, text, x=16, y=32):
		self.root.draw_text(self.gc, x, y, text);
	def __del__(self):
		if DEBUG:
			print("Cleaning up StringRenderer...");
		self.gc.free();
		self.font.close();
		self.dpy.close();

class RootCat:
	def __init__(self):
		self.renderer=StringRenderer(display.Display());
		self.renderer.clear();
	def echo_args(self, args=sys.argv[1:]):
		line=0
		for string in args:
			line=line+1;
			self.renderer.draw(string, y=line*16);
	def parse_args(self, args=sys.argv):
		parser=OptionParser();
		parser.add_option("-c", "--clear", 
			dest="clear", action="store_true");
		(options, args)=parser.parse_args();
		if options.clear:
			sys.exit(0);
		self.echo_args(args)
	def __del__(self):
		if DEBUG:
			print("Cleaning up RootCat...");

if __name__ == '__main__':
	RootCat().parse_args();


