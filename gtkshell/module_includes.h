/*
  GUIShell
  (c) 2002-2007 Jeffrey Bedard
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

#ifndef GSH_MODULE_INCLUDES_H
#define GSH_MODULE_INCLUDES_H

#include "arguments.h"
#include "options.h"
#include "callbacks.h"
#include "label.h"
#include "button.h"
#include "text.h"
#include "updated_label.h"
#include "updated_progress.h"
#include "option_options.h"
#include "add_options.h"
#include "dialog_options.h"
#include "file_dialog.h"
#include "row.h"
#include "containers.h"
#include "geometry.h"
#include "font.h"
#include "dragdrop.h"
#include "image_button.h"

#ifdef HAVE_VTE
#include "terminal_options.h"
#include "terminal.h"
#else /* not HAVE_VTE */
#include "command_shell.h"
#endif /* HAVE_VTE */

#include "guidl_dictionary.h"
#include "guidl_util.h"
#include "guidl_dialog.h"
#include "guidl_options.h"
#include "guidl_widgets.h"

#include "about_dialog.h"
#include "menu.h"
#include "init.h"
#include "update_manager.h"
#include "pane.h"
#include "app_mode.h"
#include "applets.h"
#include "tree.h"
#include "form.h"
#include "dialog.h"
#include "color.h"
#include "ptk-app-menu.h"

#endif /* not GSH_MODULE_INCLUDES_H */
