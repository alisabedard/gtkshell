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



MUSIC_DIR=$(ACE mp3_dir)
cd $MUSIC_DIR
MUSIC_PLAYER=$(ACE mp3_player)

song_title() {
	TITLE="$(ps xaww | grep -v xargs | grep $MUSIC_PLAYER | grep -v '(sh)'\
		| awk '{print substr($0, index($0, $6)); exit(0);}')"
	echo $TITLE
}

osd_song_title() {
	song_title > /dev/null
	rootcat "$TITLE"
}

next_song() {
	pkill $MUSIC_PLAYER
	if [ "$(pgrep JUKE_APPLET)" = "" ]; then
		sleep 1
		osd_song_title
	fi

}

stop_playing() {
	rm -f *.core
	pkill -f $MUSIC_PLAYER juke.sh
	exit 0
}

control_applet()
{
	nice -n 20 gtkshell -or 1 -oT JUKE_APPLET\
		-og '-0+0' -on -oi menu \
		'ACE -A Hack juke -s; ACE -A Hack juke ,gtk-media-play'\
		'ACE -A Hack juke -n ,gtk-media-next'\
		'ACE -A Hack juke -s ,gtk-media-stop'\
		'ACE -A Hack juke -k ,gtk-close' &
}

random_song() {
	shuffle -p 1 -0 * | xargs -0 $MUSIC_PLAYER 
}

show_usage()
{
	echo 'USAGE:'
	echo '		song applet and play'
	echo '-a	song applet'
	echo '-h	show usage'
	echo '-k	kill applet'
	echo '-n	next song'
	echo '-r	random song'
	echo '-s	stop playing'
	echo '-t	song title'
}

if [ "$1" = "" ]; then
	trap next_song 2
	trap stop_playing 3
	control_applet &
	while :; do
		(sleep 1; osd_song_title) &
		random_song
		sleep 0.25
	done
elif [ "$1" = "-a" ]; then
	control_applet &
elif [ "$1" = "-h" ]; then
	show_usage
elif [ "$1" = "-k" ]; then
	pkill -f JUKE_APPLET
elif [ "$1" = "-n" ]; then
	next_song
elif [ "$1" = "-r" ]; then
	random_song
elif [ "$1" = "-s" ]; then
	stop_playing
elif [ "$1" = "-t" ]; then
	song_title
elif [ "$1" = "-T" ]; then
	osd_song_title
else
	show_usage
fi

