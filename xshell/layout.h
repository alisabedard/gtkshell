/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
  antiright@gmail.com

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

#ifndef XSH_LAYOUT_H
#define XSH_LAYOUT_H

#define XSH_ROWS_PER_COLUMN 8
#define XSH_WIDGET_PADDING 2
#define XSH_FONT_HEIGHT(xsh) (xsh->gui.font->max_bounds.ascent\
	+ xsh->gui.font->max_bounds.descent)
#define XSH_FONT_WIDTH(xsh) (xsh->gui.font->max_bounds.rbearing\
	- xsh->gui.font->min_bounds.lbearing)
#define XSH_WIDGET_HEIGHT_FOR_FONT(xsh) \
	(XSH_FONT_HEIGHT(xsh)+XSH_WIDGET_PADDING*2)
#define XSH_WORD_WIDTH(xsh, word) \
	(XSH_FONT_WIDTH(xsh)*strlen(word))
#define XSH_WIDGET_WIDTH_FOR_WORD(xsh) \
	(XSH_WORD_WIDTH(xsh)*XSH_WIDGET_PADDING)

//#define XSH_WIDGET_HEIGHT 16
#define XSH_WIDGET_HEIGHT (XSH_WIDGET_HEIGHT_FOR_FONT(xsh))
//#define XSH_WIDGET_WIDTH (XSH_FONT_WIDTH(xsh)*16+XSH_WIDGET_PADDING*2)
#define XSH_WIDGET_WIDTH 96

#define XSH_STOP_LAYOUT (1<<31)

void
xsh_layout_widgets(XShell * xsh);

#endif /* XSH_LAYOUT_H */

