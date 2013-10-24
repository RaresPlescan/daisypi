#!/bin/sh

name=$(date | sed 's/\:/ /g' |awk '{print "daisypi_"$3"_"$2"_"$8"_"$4"_"$5"_"$6".tar.gz"}')
tar -pczf "/"$name /daisypi

