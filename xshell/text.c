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

#include "xshell.h"

void draw_widget_text(XWidget * text_widget)
{
	XShell * xsh = (XShell *)text_widget->xsh;
	XShellGUI * gui = &(xsh->gui);
	XSHTextData * data = (XSHTextData *)text_widget->data;
	char * text=data->label;
	unsigned int i, length=strlen(text), line=0, columns=80,
		font_height=data->font_height;
	/*unsigned int font_width=data->font_width;
	XTextItem * items=NULL; */

	XSH_SET_COLOR(gui->display, gui->gc, 0, 0, 0);
	for(i=0; i<length; i+=columns)
	{
		char * end;
		unsigned int line_length;

		end=strchr(text, '\n');
                if(end)
		  *end='\0';
	
		line_length=(length=strlen(text)) < columns ? length : columns;
		XDrawString(gui->display, text_widget->window, gui->gc,
			0, (++line)*font_height, text, line_length);
		text+=line_length;
		text=strchr(text, '\n');
	}
}

static void
expose(XWidget * text)
{
	draw_widget_text(text);
}

/* Set up for scrolling  */
static void
button_press(XWidget * text)
{
	XSHTextData * data;

	XMSG("PRESSED");
	data=(XSHTextData *)text->data;
	/*draw_label((XShell *)(text->xsh), text);*/
	system(data->command); 
}

static void
button_release(XWidget * text)
{
	expose(text);
}

static void
key_press(XWidget * text)
{
	button_press(text);
}

static void
configure(XWidget * text)
{
	expose(text);
}

static void
setup_events(XWidget * text)
{
	text->events.expose=&expose;
	text->events.configure=&configure;
	text->events.key_press=&key_press;
	text->events.button_press=&button_press;
	text->events.button_release=&button_release;
}

static void
setup_font_data(XShell * xsh, unsigned int * font_width, 
	unsigned int * font_height)
{
	XFontStruct * font;

	xsh_set_font(xsh, "-*-fixed-medium-r-*-*-14-*-*-*-*-*-*-*");
	font=xsh->gui.font;
	*font_width=font->max_bounds.rbearing-font->min_bounds.lbearing;
	*font_height=font->max_bounds.ascent+font->max_bounds.descent;
}

void
xshell_text_new(XShell * xsh, XWidget * parent, int x, int y, 
	unsigned int rows, const char * command)
{
	XWidget * text;
	XSHTextData * data;
	char * label;
	const unsigned int columns = 80;

	data=malloc(sizeof(XSHTextData));
	setup_font_data(xsh, &(data->font_width), &(data->font_height));
	xshell_XWidget_new(xsh, parent, x, y, 
		xsh->gui.layout.widget_width=data->font_width*columns, 
		XSH_WIDGET_HEIGHT*rows);
	text=xsh->gui.last_widget;
	data->rows=rows;
	data->command=(char *)command;
	label=strchr(command, '#');
	data->label= label ? label+1 : (char *) command;
	text->data=data;
	setup_events(text);
	xsh->gui.layout.row_count+=rows;
}

