# Modify tool allows various setting to be operated in their
# corresponding files via scripting.
# These are one time only operations performed on a fresh 
# Raspbian installation.

# Main insert in crontab :
# * * * * * /daisypi/hook_1m.sh
# 0,30 * * * * /daisypi/hook_30m.sh



#!/bin/sh



pattern="# Modified by Daisy Pi installer 1.0"

flag_1=$(crontab -l | grep -c daisy)

line="* * * * * /path/to/command"
(crontab -l; echo "$pattern" ) | crontab -

add_line="* * * * * /daisypi/hook_1m.sh"
(crontab -l; echo "$add_line" ) | crontab -


add_line="0,30 * * * * /daisypi/hook_30m.sh"
(crontab -l; echo "$add_line" ) | crontab -

