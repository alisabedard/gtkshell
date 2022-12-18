/*
  GUIShell
  (c) 2008-2010 Alisa Bedard
  alisabedard@gmail.com

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

#ifndef __STRINGRENDERER_H__
#define __STRINGRENDERER_H__

typedef struct _StringRenderer {
	Display *dpy;
	Window window;
	XftDraw *__draw;
	XftColor color;
	XftFont *font;

	void (*delete) (struct _StringRenderer *);
	unsigned int (*draw) (struct _StringRenderer *,
			      const int, const int, const char *);
	unsigned int (*get_line_height) (struct _StringRenderer *,
					 const char *);
} StringRenderer;

StringRenderer *new_StringRenderer(Display * dpy, Window w,
				   const char *font, const char *color);

#define new_StringRenderer_root(f,c) new_StringRenderer(NULL, 0, f, c)

#endif /* __STRINGRENDERER_H__ */
