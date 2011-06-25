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


#include "rootcat.h"


int
main (int argc, char **argv)
{
  StringRenderer *rc = NULL;
  register int counter = 0;
  unsigned int line = 0;
  char *color = NULL;
  char *font = NULL;

  while (++counter < argc)
    {
      const char *string = argv[counter];

      if (string[0] == '-')
	{
	  switch (string[1])
	    {
	    case 'C':		/* Set color */
	      counter++;
	      if (argv[counter])
		color = (char*)argv[counter];
	      else
                goto print_usage;
	      break;
	    case 'c':		/* Clean up previous invocations.  */
              rc = new_StringRenderer_root (NULL, NULL);
              $(rc, clear);
              $(rc, delete);
              rc=NULL;
	      break;
	    case 'F':		/* Set font */
	      counter++;
	      if (argv[counter])
                {
		  font = (char*)argv[counter];
                  break;
                }
	    default:
print_usage:
              fprintf (stderr, 
                       "%s:  Invalid argument\n"
                       "USAGE %s [-CFcf] [string] ...\n", 
                       argv[0], argv[0]);
              return 1;
	    }
	}
      else
	{
	  if (!rc)
	    {
	      rc = new_StringRenderer_root (font, color);
	      $ (rc, clear);
	    }
	  {
	    const unsigned int height = $ (rc, get_line_height, string);

	    $ (rc, draw, (height / 2),
	       ((++line) * LINE_SPACING * height), string);
	  }
	}
    }
  if (rc)
    $ (rc, delete);

  return 0;
}
