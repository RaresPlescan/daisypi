#!/bin/sh





cheie="Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g"


#temp_file="/system/temp_log/cosm_temp1_MAIN.json"
#temp_file="/system/teava_1"


#root@raspberrypi:/system/bmp05/aaa# ./palt | grep Pressure | awk '{print $2}'
#993.5100
#root@raspberrypi:/system/bmp05/aaa# ./palt | grep Temp | awk '{print $2}'
#27.2000
#root@raspberrypi:/system/bmp05/aaa# ./palt | grep analit | awk '{print $2}'
#analitical
#root@raspberrypi:/system/bmp05/aaa# ./palt | grep analit | awk '{print $3}'
#165.6563

 variabila_pres="1"
 #variabila_pres=$(/daisypi/bmp085/pres_temp)
 variabila_sht=$(/daisypi/sht11/sht11_move)
# variabila_adc=$(/daisypi/mcp3304/adc_1.py)
 variab_cpu=$(cat /sys/class/thermal/thermal_zone0/temp)
 echo " VV $variab_cpu"
 read_temp=$(echo $variabila_sht | awk '{print $2}')
 read_humid=$(echo $variabila_sht | awk '{print $3}')
 read_dew=$(echo $variabila_sht | awk '{print $4}')
 cpu_temp=$(echo "scale=2; "$variab_cpu"/1000" | /usr/bin/bc)
 ilum=$(nice -19 "/daisypi/tsl235r/tsl_read" | awk '{print $4}')
# ilum=$(/daisypi/tsl235/ilum)
# presiune=$(echo $variabila_pres | awk '{print $3}')
# temp_pres=$(echo $variabila_pres | awk '{print $2}')
# light=$(echo $variabila_adc | awk '{print $3}')
# monoxide=$(echo $variabila_adc | awk '{print $4}')
# pressdiff=$(echo $variabila_adc | awk '{print $2}')

 echo "Read temperature is $read_temp."
 echo "Read humidity is $read_humid."
 echo "Read CPU temp is $cpu_temp."
# echo "Read pressure is $presiune."
# echo "Read temp_pressure is $temp_pres."
# echo "Read altitude is $altit."
# echo "Read light is $light."
# echo "Read monoxide is $monoxide"
  timestamp=$(date | awk '{print $3 "," $2 "," $6 "," $4 ","}')
                   

#PACHUBE - COSM
#curl --request PUT --data-binary @datafile.txt --header "X-ApiKey: YOUR_API_KEY_HERE" http://api.cosm.com/v2/feeds/1977
#gX-82yojGoBJZFiK8JJwbKwdneqSAKxDMUF2V0ZEVUpBbz0g

# http://www.devicehub.net/io/40/?apiKey=2b1f14d9-e20e-44b7-bd2f-9d19df3ed9ab&temp=21
  

#post_string="http://www.devicehub.net/io/40/?apiKey=2b1f14d9-e20e-44b7-bd2f-9d19df3ed9ab&temp="$read_temp
#y=$(echo $read_temp*1000 | bc | sed 's/\.*//g')
t=$(echo $read_temp*100 | bc | sed 's/\.[^-]*$//' )
echo $y
u=$(echo $read_humid*100 | bc | sed 's/\.[^-]*$//' )
echo $y
r=$(echo $read_dew*100 | bc | sed 's/\.[^-]*$//' )
echo $y
c=$(echo $cpu_temp*100 | bc | sed 's/\.[^-]*$//' )
echo $y
#i=$(echo $read_temp*100 | bc | sed 's/\.[^-]*$//' )
#echo $y



#post_string="http://www.devicehub.net/io/40/?apiKey=2b1f14d9-e20e-44b7-bd2f-9d19df3ed9ab&temp="$t"&umid="$u"&roua="$r"&cpu_temp="$c
post_string="http://www.devicehub.net/io/40/?apiKey=2b1f14d9-e20e-44b7-bd2f-9d19df3ed9ab&temp="$read_temp"&umid="$read_humid"&roua="$read_dew"&cpu_temp="$cpu_temp"&ilum="$ilum
echo $post_string
curl --request GET $post_string
#curl --request GET '

exit 0
#curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

curl -X POST -d $post_string http://www.devicehub.net

exit 0

if [ -n "$temp_pres" ]; then 

echo "$timestamp$temp_pres," >> /daisypi/logs/temp_presiune.csv


tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"temp_2\", \"current_value\":\"$temp_pres\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi

if [ -n "$presiune" ]; then 

echo "$timestamp$presiune," >> /daisypi/logs/presiune.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"baro\", \"current_value\":\"$presiune\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi

if [ -n "$temp_pres" ]; then 

echo "$timestamp$read_humid," >> /daisypi/logs/humidity.csv

tot="{\n" 

tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"humid\", \"current_value\":\"$read_humid\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi


if [ -n "$read_temp" ]; then 

echo "$timestamp$read_temp," >> /daisypi/logs/read_temp.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"temp_1\", \"current_value\":\"$read_temp\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi






if [ -n "$read_dew" ]; then 

echo "$timestamp$read_dew," >> /daisypi/logs/dew.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"dew\", \"current_value\":\"$read_dew\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi

if [ -n "$cpu_temp" ]; then 

echo "$timestamp$cpu_temp," >> /daisypi/logs/cpu_temp.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"cpu_temp\", \"current_value\":\"$cpu_temp\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi



if [ -n "$light" ]; then 

echo "$timestamp$cpu_temp," >> /daisypi/logs/light.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"light\", \"current_value\":\"$light\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi

if [ -n "$monoxide" ]; then 

echo "$timestamp$monoxide," >> /daisypi/logs/monoxide.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"co\", \"current_value\":\"$monoxide\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi

if [ -n "$pressdiff" ]; then 

echo "$timestamp$pressdiff," >> /daisypi/logs/pressure_diff.csv

tot="{\n" 
tot=$tot"  \"version\":\"1.0.0\",\n"
tot=$tot"  \"datastreams\":[\n"
tot=$tot"      {\"id\":\"dif_press\", \"current_value\":\"$pressdiff\"}\n"
tot=$tot"  ]\n"
tot=$tot"}\n"

#echo $tot

mkfifo mypipe

echo $tot > mypipe &

curl --request PUT --data-binary @mypipe --header "X-ApiKey: Vf3K57K9yYyQpBxR11hqQ3E6eHKSAKxtZXRJSExjemhzcz0g" https://api.cosm.com/v2/feeds/125842

#https://cosm.com/feeds/125842
#cat mypipe

rm mypipe

fi
