#!/bin/sh
TEMP=`mktemp`
COMMAND=bc
VERSION="calculator.sh 1.0"
touch $TEMP
gtkshell File::Exit__ 'Help::gtkshell -da & # About,gtk-about' \
	-aul "tail $TEMP" -al Calculate: -at echo -al "$VERSION" \
	| $COMMAND > $TEMP
rm -f $TEMP

