#!/bin/sh

umount /mnt/tl
sleep 1

mount -t cifs //192.168.47.10/tl -o username=rape,password=mamasaid /mnt/tl
sleep 1


mkdir -p /ram
mount -t tmpfs -o size=100m tmpfs /ram

mount /dev/sda1 /mnt/m1
mount /dev/sdb1 /mnt/m2
mount /dev/sdc1 /mnt/m3
mount /dev/sdd1 /mnt/m4