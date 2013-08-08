#!/bin/sh



#Video Captures

#Image size and preview settings are the same as for stills capture. Default size for video recording is 1080p (1920x1080)
#Record a 5s clip with default settings (1080p30)
#    raspivid -t 5000 -o video.h264
#Record a 5s clip at a specified bitrate (3.5MBits/s)
#    raspivid -t 5000 -o video.h264 -b 3500000
#Record a 5s clip at a specified framerate (5fps)
#    raspivid -t 5000 -o video.h264 -f 5
#Encode a 5s camera stream and send image data to stdout
#    raspivid -t 5000 -o - 
#Encode a 5s camera stream and send image data to file
#    raspivid -t 5000 -o - > my_file.h264


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


filename="img_0"$index-$(date -u +"%d%m%Y_%H%M-%S")


raspivid -t 50000 -w 1920 -h 1080 -o $TMP/$filename -v -ISO 100 -vs -ex sports -awb sun -mm matrix -hf -fps 30
#/usr/bin/raspivid -ISO 800 -ex antishake -awb incandescent -v -t 20000 -o $TMP/video.h264 -fps 30
mv $TMP/$filename $SAVEDIR/video01.raw_mp4 &
#ffmpeg -r 30 -i /mnt/tl/video01.raw_mp4 -vcodec copy /mnt/tl/$filename".mp4"