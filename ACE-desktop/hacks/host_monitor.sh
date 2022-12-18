#!/bin/sh
#    GUIShell (c) 2007 Alisa Bedard alisabedard@gmail.com

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
	local HOSTS="$(ACE hosts_to_monitor)"
	local COMMAND="gtkshell -or 8 -og +0+0 -ou 15000"
	local LOG_LINES=4
	local LOG_FILE=/var/log/messages

	if [ "$SSH_AGENT_PID" = "" ]; then
		eval `ssh-agent`
		ssh-add
	fi
	if [ "$1" = "--auth" ]; then
		ssh-add
	fi

	for HOST in $HOSTS; do
		local SSH_CMD="ssh $HOST /usr/bin/uptime && ssh $HOST\
			/usr/bin/tail -n $LOG_LINES $LOG_FILE" 
		COMMAND="$COMMAND -al $HOST -aul \"$SSH_CMD\""
	done
	nice -n 20 sh -c "$COMMAND" &
}
#----

Main $@

