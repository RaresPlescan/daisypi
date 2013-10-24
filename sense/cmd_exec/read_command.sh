#!/bin/sh


# $(cat /proc/cpuinfo | grep Revision | awk '{print $3}')


cheie="yyyyyyyyyyyyyyyyyyyy"


 tt=$(cat /proc/cpuinfo | grep Revision | awk '{print $3}')
 vv=$(echo $tt | tr '[a-z]' '[A-Z]')
 raspi_ver=$(echo "obase=10; "$vv"" | /usr/bin/bc) 

if [ "$raspi_ver" -gt 3 ]; then 
 echo "VERSION 2"
else
  
 echo "VERSION 1"
fi

feed_id="38780"
curl -s 'http://api.sen.se/feeds/'$feed_id'/last_event/?sense_key='$cheie -X GET -H "Content-type: application/json" > /ram/cmd_read.txt
cat /ram/cmd_read.txt 
echo "---------------"
cmd_full=$(cat /ram/cmd_read.txt  | sed 's/\"//g' | grep value | awk 'BEGIN { FS = ":" } ; {print $2}' | sed 's/\,//g')
time_new=$(cat /ram/cmd_read.txt  | grep timetag | sed 's/\"//g' | sed 's/ //g' | sed 's/\,//g' | sed 's/\://g' | sed 's/\+//g' | sed 's/\-//g' )
time_old=$(cat /ram/cmd_timetag.txt)

echo $time_new > /ram/cmd_timetag.txt

echo "OLD "$time_old
echo "NEW "$time_new

if [ "$time_new" != "$time_old" ]; then
 echo " new command ! "
else
  echo "old comand" 
  exit 0
fi
# echo "to be printed only if new one in place"
# A new command has been issued, starting interpreter + executing


echo "$cmd_full," >> /ram/logs/cmd_exec.csv


echo ">"$cmd_full"<"

eval=$(echo $cmd_full | grep -c 'speech')
if [ "$eval" -gt 0 ]; then
# speech exec
echo "clean"
text=$(echo $cmd_full | sed 's/speech//g')
echo $text
/usr/bin/espeak -v ro -s 100 --stdout "$text" | /usr/bin/aplay

fi

exit 0

eval=$(echo $cmd_full | grep -c 'speech')
if [ "$eval" -gt 0 ]; then
# speech exec
echo "clean"
text=$(echo $cmd_full | sed 's/speech//g')
echo $text
/usr/bin/espeak -v ro -s 100 --stdout "$text" | /usr/bin/aplay

fi
