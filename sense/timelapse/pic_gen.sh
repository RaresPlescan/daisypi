#!/bin/sh

SAVEDIR=/mnt/tl
TMP=/ram

date
filename="img_01"-$(date -u +"%d%m%Y_%H%M-%S").jpg

#/opt/vc/bin/raspistill -t 0 -w 2592 -h 1944 -hf -q 100 -o $TMP/$filename
#/opt/vc/bin/raspistill -ISO 800 -ex night -t 5 -w 1920 -h 1080 -hf -q 100 -o $TMP/$filename

/opt/vc/bin/raspistill -ex night -t 1000 -tl 50 -w 1920 -h 1080 -hf -q 100 -o /ram/image_num_%d.jpg

#mv $TMP/$filename $SAVEDIR/$filename &

date
