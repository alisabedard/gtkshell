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

#include "library.h"

static ARActionFunction
ar_ARFunctionDictionary_lookup(struct ARFunctionDictionary *dict,
			       const gchar * key)
{
	const gint argc = dict->__data->argc;
	const gchar **argv = (const gchar **)dict->__data->argv;
	gint i;

	for (i = 0; i < argc; i += 2) {
		if (!strcmp(argv[i], key))
			return (ARActionFunction) argv[i + 1];
	}

	return NULL;
}

static void
ar_ARFunctionDictionary_exec(struct ARFunctionDictionary *this,
			     const gchar * key, gint * argc, gchar ** argv)
{
	const ARActionFunction definition = $$(lookup, key);
	if (definition)
		definition(argc, argv);
}

static void ar_delete_ARFunctionDictionary(struct ARFunctionDictionary *this)
{
	ARDELETE(this->__data);
	g_free(this);
}

static void
ar_ARFunctionDictionary_define(struct ARFunctionDictionary *this,
			       const gchar * key, ARActionFunction action)
{
	$(this->__data, add, key);
	$(this->__data, add, (gchar *) action);
}

static void
setup_ARFunctionDictionary_methods(struct ARFunctionDictionary *dict)
{
	dict->lookup = &ar_ARFunctionDictionary_lookup;
	dict->exec = &ar_ARFunctionDictionary_exec;
	dict->define = &ar_ARFunctionDictionary_define;
	dict->delete = &ar_delete_ARFunctionDictionary;
}

static void setup_ARFunctionDictionary_fields(struct ARFunctionDictionary *this)
{
	this->__data = ARNEW(ar, ARArguments);
}

struct ARFunctionDictionary *ar_new_ARFunctionDictionary()
{
	struct ARFunctionDictionary *dict;

	dict = armalloc(sizeof(struct ARFunctionDictionary));
	setup_ARFunctionDictionary_fields(dict);
	setup_ARFunctionDictionary_methods(dict);

	return dict;
}

static void ar_delete_ARCommandLineParser(struct ARCommandLineParser *parser)
{
	g_free(parser);
}

static void
ar_ARCommandLineParser_set_args(struct ARCommandLineParser *parser,
				const struct ARArguments *args)
{
	parser->__args = (struct ARArguments *)args;
}

static void ar_ARCommandLineParser_parse(struct ARCommandLineParser *this)
{
	struct ARFunctionDictionary *dict =
	    (struct ARFunctionDictionary *)this->__dict;
	const gint argc = (const gint)(this->__args->argc);
	gchar **argv = this->__args->argv;
	gint i;

	for (i = 0; i < argc; i++) {
		$(dict, exec, (const gchar *)argv[i], &i, argv);
	}
}

static void
setup_ARCommandLineParser_methods(struct ARCommandLineParser *parser)
{
	parser->delete = &ar_delete_ARCommandLineParser;
	parser->set_args = &ar_ARCommandLineParser_set_args;
	parser->parse = &ar_ARCommandLineParser_parse;
}

struct ARCommandLineParser *ar_new_ARCommandLineParser(struct
						       ARFunctionDictionary
						       *dictionary)
{
	struct ARCommandLineParser *parser;

	parser = armalloc(sizeof(struct ARCommandLineParser));
	parser->__dict = dictionary;
	setup_ARCommandLineParser_methods(parser);

	return parser;
}
