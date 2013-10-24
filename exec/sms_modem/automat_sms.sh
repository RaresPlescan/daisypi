#!/bin/sh

a=0

while read line
do 

a=$(($a+1));
echo "-------------------------------------------------------------------------"
echo $a $line;
sudo echo "Anunt mass SMS !" | /usr/bin/gammu --sendsms TEXT $line
echo "========================================================================="

done < "lista_telefoane.txt"
echo "Final line count is: $a";
