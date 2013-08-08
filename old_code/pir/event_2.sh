#!/bin/sh

# "return to idle state"

pir="0"

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"pir\", \"current_value\":\"$pir\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot


echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

