/*
  GUIShell
  (c) 2008-2010 Jeffrey Bedard
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

#ifndef __ROOTCAT_H__
#define __ROOTCAT_H__

#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define SR_DEFAULT_FONT "Mono 12"
#define SR_DEFAULT_COLOR "white"
#define LINE_SPACING 1.25

#ifndef $
#define $(class, method, ...) class->method(class, ##__VA_ARGS__)
#endif /* ! $ */

#include "StringRenderer.h"

#endif /* __ROOTCAT_H__ */
