#!/bin/sh

#umount /mnt/tl
#sleep 5
#mount -t cifs //192.168.87.10/tl -o username=user,password=pass /mnt/tl
#sleep 5
#mkdir -p /ram
#mount -t tmpfs -o size=100m tmpfs /ram
#SAVEDIR=/mnt/tl

#index=$(cat /daisypi/timelapse/index.txt)


#SAVEDIR=/mnt/m1
SAVEDIR=/mnt/tl
TMP=/ram
#stop='0'


#filename="img_0"$index-$(date -u +"%d%m%Y_%H%M-%S")
filename="img_0"-$(date -u +"%d%m%Y_%H%M-%S")
#stop=$(cat /ram/enable.txt | grep -c 'stop')

#/opt/vc/bin/raspistill -ex night -t 1000 -hf -w 1920 -h 1080 -q 100 -tl 50 -o $TMP
#/opt/vc/bin/raspistill -ex night -hf -w 1920 -h 1080 -q 100 -t 300 -tl 300 -o $TMP"/"$filename"%d".jpg
#/opt/vc/bin/raspistill -ex sports -awb incandescent -hf -w 1920 -h 1080 -q 100 -t 2000 -tl 20 -o $TMP"/"$filename"%d".jpg
#/opt/vc/bin/raspistill -ex antishake -awb incandescent -hf -w 1920 -h 1080 -q 100 -t 500 -tl 100 -o $TMP"/"$filename"%d".jpg
/opt/vc/bin/raspistill -ex night -awb off -hf -w 1920 -h 1080 -q 100 -t 500 -tl 250 -o $TMP"/"$filename"%d".jpg
#/opt/vc/bin/raspistill -ex auto -t 0 -hf -w 1920 -h 1080 -q 100 -o $TMP/$filename
#mv $TMP/$filename $SAVEDIR/$filename &
mv $TMP/* $SAVEDIR &


#stop=$(cat /ram/enable.txt | grep -c 'stop')
#/opt/vc/bin/raspistill -t 0 -hf -w 1920 -h 1080 -q 100 -o $TMP/$filename
#mv $TMP/$filename $SAVEDIR/$filename


