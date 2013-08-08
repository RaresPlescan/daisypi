#!/bin/sh

#umount /mnt/tl
#sleep 5
#mount -t cifs //192.168.47.10/tl -o username=rape,password=mamasaid /mnt/tl
#sleep 5
#mkdir -p /ram
#mount -t tmpfs -o size=100m tmpfs /ram
#SAVEDIR=/mnt/tl

index=$(cat /daisypi/timelapse/index.txt)


#SAVEDIR=/mnt/m1
SAVEDIR=/mnt/tl
TMP=/ram
stop='0'

while [ true ]; do

filename="img_0"$index-$(date -u +"%d%m%Y_%H%M-%S").jpg
#stop=$(cat /ram/enable.txt | grep -c 'stop')

if [ $stop -lt 1 ]
then
#/opt/vc/bin/raspistill -ex night -t 1000 -hf -w 1920 -h 1080 -q 100 -tl 50 -o $TMP
/opt/vc/bin/raspistill -ex auto -t 0 -hf -w 1920 -h 1080 -q 100 -o $TMP/$filename
mv $TMP/$filename $SAVEDIR/$filename &
#mv $TMP/img* $SAVEDIR &
fi

stop=$(cat /ram/enable.txt | grep -c 'stop')


#/opt/vc/bin/raspistill -t 0 -hf -w 1920 -h 1080 -q 100 -o $TMP/$filename
#mv $TMP/$filename $SAVEDIR/$filename

sleep 1;

done;