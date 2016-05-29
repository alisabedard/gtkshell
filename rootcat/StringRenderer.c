/*
  GUIShell
  (c) 2008-2010 Jeffrey Bedard
  jefbed@gmail.com

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

#include "rootcat.h"

static unsigned int
StringRenderer_get_line_height(StringRenderer * rc, const char *string)
{
	XGlyphInfo extents;

	XftTextExtentsUtf8(rc->dpy, rc->font,
			   (FcChar8 *) string, strlen(string), &extents);

	return extents.height;
}

/* Returns the number of lines printed.  */
static unsigned int
StringRenderer_draw(StringRenderer * rc,
		    const int x, const int y, const char *string)
{
	char *iter = (char *)string;
	const int max_length = strlen(string);
	int total_length = 0;
	register int length = 0;
	int lines = 0;

	for (total_length = 0; total_length <= max_length;
	     total_length += length) {
		for (length = 0; iter[length] != '\0' && iter[length] != '\n';
		     length++) ;
		length++;
		XftDrawStringUtf8(rc->__draw, &(rc->color), rc->font,
				  x, y + lines * LINE_SPACING * $(rc,
								  get_line_height,
								  iter),
				  (FcChar8 *) iter, length - 1);
		iter += length;
		lines++;
	}

	return lines;
}

static void delete_StringRenderer(StringRenderer * rc)
{
	Display *dpy = rc->dpy;
	const int screen = DefaultScreen(dpy);

	XftColorFree(dpy, DefaultVisual(dpy, screen),
		     DefaultColormap(dpy, screen), &(rc->color));
	XftFontClose(dpy, rc->font);
	XftDrawDestroy(rc->__draw);
	XCloseDisplay(dpy);
	free(rc);
}

static Display *try_open_display(Display * dpy)
{
	if (!dpy) {
		dpy = XOpenDisplay(getenv("DISPLAY"));
		if (!dpy) {
			perror("cannot open DISPLAY");
			exit(1);
		}
	}

	return dpy;
}

static void
validate_inputs(Display ** dpy,
		Window * w, const char **font, const char **color)
{
	*dpy = try_open_display(*dpy);
	/* Validate inputs.  */
	if (!*font)
		*font = SR_DEFAULT_FONT;
	if (!*color)
		*color = SR_DEFAULT_COLOR;
	if (*w == 0)
		*w = DefaultRootWindow(*dpy);
}

StringRenderer *new_StringRenderer(Display * dpy, Window w,
				   const char *font, const char *color)
{
	validate_inputs(&dpy, &w, &font, &color);

	/* Allocate class.  */
	StringRenderer *rc = malloc(sizeof(StringRenderer));
	assert(rc);

	rc->delete = (&delete_StringRenderer);
	rc->draw = (&StringRenderer_draw);
	rc->get_line_height = (&StringRenderer_get_line_height);

	rc->dpy = dpy;
	rc->window = w;
	{
		const int screen = DefaultScreen(dpy);
		{
			const Colormap cmap = DefaultColormap(dpy, screen);
			const Visual *visual = DefaultVisual(dpy, screen);

			rc->__draw =
			    XftDrawCreate(dpy, w, (Visual *) visual, cmap);
			XftColorAllocName(dpy, visual, cmap, color,
					  &(rc->color));
		}
		rc->font = XftFontOpenName(dpy, screen, font);
	}
	/* Clear previous OSD text from the screen.  */
	XClearWindow(rc->dpy, rc->window);

	return rc;
}
