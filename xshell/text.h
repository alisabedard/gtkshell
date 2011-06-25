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


#ifndef XSH_TEXT_H
#define XSH_TEXT_H

struct XSHTextData
{
	char * command;
	char * label;
	unsigned int font_height, font_width, rows;
};

typedef struct XSHTextData XSHTextData;

void
xshell_text_new(XShell * xsh, XWidget * parent, int x, int y, unsigned int rows,
	const char * command);

#endif /* XSH_TEXT_H */


