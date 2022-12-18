#!/usr/bin/env python


#    PyGUI (c) 2010 Alisa Bedard alisabedard@gmail.com

#     This file is part of GUIShell.

#     GUIShell is free software; you can redistribute it and/or
#     modify it under the terms of the GNU General Public License as
#     published by the Free Software Foundation; either version 2 of
#     the License, or (at your option) any later version.  GUIShell
#     is distributed in the hope that it will be useful, but WITHOUT
#     ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.  You should have
#     received a copy of the GNU General Public License along with
#     GUIShell; if not, write to the Free Software Foundation, Inc.,
#     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

import pygtk
pygtk.require('2.0')
import gtk
import sys
import os
import getopt

class PyGUI(gtk.Window):
	icon_size=gtk.ICON_SIZE_BUTTON
	cb_exits=False
	rows=8

	def __init__(self, parent=None):
		gtk.Window.__init__(self)
		try:
			self.set_screen(parent.get_screen())
		except AttributeError:
			self.connect('destroy', lambda *w: gtk.main_quit())
		self.set_title(self.__class__.__name__)
		self.set_default_size(0, 0)
		self.hrow = gtk.HBox()
		self.add(self.hrow)
		self.hrow.show()
		self.add_column()
		if (self.is_composited()):
			self.set_opacity(0.9)
		self.show_all()

	def add_column(self):
		self.vrow = gtk.VBox()
		self.hrow.add(self.vrow)
		self.vrow.show()
		self.row=1

	def system_cb(self, widget, data=None):
		if(data==None):
			data=widget.get_text()
		os.system(data)
		if(self.cb_exits):
			gtk.main_quit()

	def add_button(self, arg):
		splitarg = arg.split(',', 1)
		command=splitarg[0]
		if(len(splitarg)>1):
			img_id=splitarg[1]
		else:
			img_id=None

		button=gtk.Button(command)
		if(img_id):
			button.set_label(img_id)
			button.set_use_stock(True)
			if(button.get_image()==None):
				image=gtk.Image()
				image.set_from_file(img_id)
				button.set_image(image)
		button.connect("clicked", self.system_cb, command)
		self.manage(button)

	def add_label(self, text):
		label = gtk.Label(text)
		self.manage(label)

	def add_text_field(self, text=None):
		field = gtk.Entry()
		if(text != None):
			field.set_text(text)
		field.connect("activate", self.system_cb)
		self.manage(field)

	def manage(self, widget):
		if(self.row > self.rows):
			self.add_column()
		self.row+=1
		widget.show()
		self.vrow.add(widget)

	nextop=None
	def parse_item(self, arg):
		if(arg[0]=='-'):
			if(arg[1]=='a'):
				if(arg[2]=='l'):
					self.nextop="add label"
					return
				elif(arg[2]=='t'):
					self.nextop="add text field"
					return
			elif(arg[1]=='o'):
				if(arg[2]=='i'):
					self.nextop="set icon size"
					return
				if(arg[2]=='r'):
					self.nextop="set rows"
					return
				if(arg[2]=='e'):
					self.cb_exits=True
					return
		if(self.nextop!=None):
			if(self.nextop=="add label"):
				self.add_label(arg)
			elif(self.nextop=="add text field"):
				self.add_text_field(arg)
			elif(self.nextop=="set icon size"):
				self.icon_size=arg
			elif(self.nextop=="set rows"):
				self.rows=int(arg)
			self.nextop=None
		else:
			self.add_button(arg)

	def main(self):
		for arg in sys.argv[1:]:
			self.parse_item(arg)
		gtk.main()

if (__name__ == "__main__"):
	app = PyGUI()
	app.main()

