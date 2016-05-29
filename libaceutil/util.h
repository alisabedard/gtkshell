/*
  GUIShell
  (c) 2002-2005 Jeffrey Bedard
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

#ifndef LIBAR_UTIL_H
#define LIBAR_UTIL_H

#define AR_TEXT_TO_FILE(filename, text)\
	g_file_set_contents(filename, text, strlen(text), NULL)

#ifdef LIBGC
#define armalloc(size)	GC_MALLOC(size)
#define arfree(data)    GC_FREE(data)
#else /* not LIBGC */
/* Compatibility macros for older versions of glib */
#if GLIB_CHECK_VERSION(2, 10, 0)
#define armalloc(size)  g_slice_alloc(size)
#define arfree(ptr)    g_slice_free1(sizeof(*ptr), ptr)
#else /* glib is less than 2.10.0 */
#define armalloc(size)  g_malloc(size)
#define arfree(data)    g_free(data)
/* older versions of glib don't provde g_slice API */
#define g_slice_alloc(size)         g_malloc(size)
#define g_slice_alloc0(size)        g_malloc0(size)
#define g_slice_new(type)           g_new(type, 1)
#define g_slice_new0(type)          g_new0(type, 1)
#define g_slice_free(type, mem)     g_free(mem)
#define g_slice_free1(size, mem)    g_free(mem)
#endif /* GLIB_CHECK_VERSION */
#endif /* LIBGC */

#include <sys/mman.h>
#include <unistd.h>

typedef void (*ARActionFunction) (gint *, gchar **);

struct ARFunctionDictionary {
	struct ARArguments *__data;
	void (*define) (struct ARFunctionDictionary *, const gchar *,
			ARActionFunction);
	 ARActionFunction(*lookup) (struct ARFunctionDictionary *,
				    const gchar *);
	void (*exec) (struct ARFunctionDictionary *, const gchar *,
		      gint *, gchar **);
	void (*delete) (struct ARFunctionDictionary *);
};

struct ARFunctionDictionary *ar_new_ARFunctionDictionary();

struct ARCommandLineParser {
	struct ARArguments *__args;
	struct ARFunctionDictionary *__dict;
	void (*set_args) (struct ARCommandLineParser *,
			  const struct ARArguments * args);
	void (*parse) (struct ARCommandLineParser *);
	void (*delete) (struct ARCommandLineParser *);
};

struct ARCommandLineParser *ar_new_ARCommandLineParser(struct
						       ARFunctionDictionary
						       *dict);

#endif
