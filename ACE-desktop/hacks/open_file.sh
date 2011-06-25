#!/bin/sh

#    GUIShell (c) 2002-2007 Jeffrey Bedard antiright@gmail.com

#    This file is part of GUIShell.

#     GUIShell is free software; you can redistribute it and/or
#     modify it under the terms of the GNU General Public License as
#     published by the Free Software Foundation; either version 2 of
#     the License, or (at your option) any later version.  GUIShell
#     is distributed in the hope that it will be useful, but WITHOUT
#     ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.  You should have
#     received a copy of the GNU General Public License along with
#     GUIShell; if not, write to the Free Software Foundation, Inc.,
#     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

Main()
{
	if [ $# -gt 0 ]; then
		if [ "$TMPDIR" = "" ]; then
			TMPDIR='/tmp'
		fi
		TMP=$TMPDIR/ARO.$$
    		file $1 > $TMP
		if grep HTML $TMP; then
			ACE Browser $1 & 
    		elif grep text $TMP; then
			ACE Text_Editor $1 &
    		elif grep executable $TMP; then
    			# Execute the file and any arguments.  
			$@ &
    		elif grep gzip $TMP; then
    			# Decompress the file.  
			gzip -d $1 &
    		elif grep tar $TMP; then
    			# Untar the file.  
			tar xf $1 &
    		elif grep emacs $TMP; then
    		# Open the file in GNU Emacs.  No xterm is needed because most
    		# modern emacs builds link to the X libraries.
			emacs $1 &
    		elif grep MP3 $TMP; then
			ACE mp3_player $1 &
    		elif grep image $TMP; then
			ACE Image_Editor $1 &
    		elif grep MS $TMP; then
    			# Wine is used to run MS programs.
			# Keep command line arguments.  
			local PROG="$1"
			shift
			wine $1 & 
    		elif grep "No such file or directory" $TMP; then
			touch $1
			ACE Text_Editor $1 &
    		elif grep empty $TMP; then
			ACE Text_Editor $1 &
    		elif grep directory $TMP; then
			AR_IN_FM=0
			cd $1 && ACE -A File_Manager
    		else
    			# Execute the file.  
			/bin/sh -c "$*" &
		fi
		rm -f $TMP
	else
		gtkshell -de "No arguments were specified" &
	fi
	if [ "$AR_IN_FM" = "1" ]; then
		ACE -A File_Manager
	fi
}

#---

Main $@


