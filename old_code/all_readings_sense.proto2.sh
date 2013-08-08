#!/bin/sh





cheie="5rttnwPJR2TneXp6AOkbhA"
#
#
#
#
# Pressure       37279
# Temp P1        37280
#


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

# variabila_pres="1"
 variabila_pres=$(/daisypi/bmp085/pres1)
# variabila_sht=$(/daisypi/sht11/sht11_move)
variabila_sht=$(/daisypi/sht11/sht_read_17CLK_22_SDA)
# variabila_sht_sec=$(/daisypi/sht11/sht11_secund)
# variabila_adc=$(/daisypi/mcp3304/adc_1.py)
 variab_cpu=$(cat /sys/class/thermal/thermal_zone0/temp)
 variabila_analog=$(python /daisypi/mcp3208/adc_read.py)

# echo " VV $variab_cpu"
 read_temp=$(echo $variabila_sht | awk '{print $2}')
 read_humid=$(echo $variabila_sht | awk '{print $3}')
 read_dew=$(echo $variabila_sht | awk '{print $4}')

 read_temp_sec=$(echo $variabila_sht_sec | awk '{print $2}')
 read_humid_sec=$(echo $variabila_sht_sec | awk '{print $3}')
 read_dew_sec=$(echo $variabila_sht_sec | awk '{print $4}')

 cpu_temp=$(echo "scale=2; "$variab_cpu"/1000" | /usr/bin/bc)
 ilum=$(nice -19 "/daisypi/tsl235r/tsl_read" | awk '{print $4}')
# ilum=$(echo $ilum | awk '{print $4}')
# echo "BP  "$variabila_pres
 presiune=$(echo $variabila_pres | awk '{print $4}')
 temp_pres=$(echo $variabila_pres | awk '{print $3}')
# light=$(echo $variabila_adc | awk '{print $3}')
# monoxide=$(echo $variabila_adc | awk '{print $4}')
# pressdiff=$(echo $variabila_adc | awk '{print $2}')
 a0=$(echo $variabila_analog | grep P0 | awk '{print $2}')
 a1=$(echo $variabila_analog | grep P1 | awk '{print $5}')
 a2=$(echo $variabila_analog | grep P2 | awk '{print $8}')
 a3=$(echo $variabila_analog | grep P3 | awk '{print $11}')
 a4=$(echo $variabila_analog | grep P4 | awk '{print $14}')
 a5=$(echo $variabila_analog | grep P5 | awk '{print $17}')
 a6=$(echo $variabila_analog | grep P6 | awk '{print $21}')
 aa7=$(echo $variabila_analog | grep P7 | awk '{print $23}')

 a7=$(echo "$aa7*0.001612" | /usr/bin/bc)

 echo "Read temperature is $read_temp."
 echo "Read humidity is $read_humid."
 echo "Read CPU temp is $cpu_temp."
 echo "Illumination is "$ilum

 echo "Read pressure is $presiune."
 echo "Read temp_pressure is $temp_pres."

 message="Warning : DaisyPI is working at 90% of it's capabilities. Please aquire more sensors."
 a3=0
 a4=0
 a5=0
 a6=0
 
 online="1"


 echo "Read val A0 is $a0"
 echo "Read val A1 is $a1"
 echo "Read val A2 is $a2"
 echo "Read val A3 is $a3"
 echo "Read val A4 is $a4"
 echo "Read val A5 is $a5"
 echo "Read val A6 is $a6"
 echo "Read val AA7 is $aa7"
 echo "Read val A7 is $a7"





# echo "Read altitude is $altit."
# echo "Read light is $light."
# echo "Read monoxide is $monoxide"
  timestamp=$(date | awk '{print $3 "," $2 "," $6 "," $4 ","}')
                   



if [ -n "$online" ]; then 

echo "$timestamp$online," >> /ram/logs/read_adc_a7.csv
feed_id="37818"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$online'}]'
fi



if [ -n "$read_temp" ]; then 

echo "$timestamp$read_temp," >> /ram/logs/read_temp.csv
feed_id="37588"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_temp'}]'
fi

if [ -n "$read_humid" ]; then 

echo "$timestamp$read_humid," >> /ram/logs/read_humid.csv
feed_id="37589"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_humid'}]'
fi

if [ -n "$read_dew" ]; then 

echo "$timestamp$read_dew," >> /ram/logs/read_dew.csv
feed_id="37595"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_dew'}]'
fi


if [ -n "$cpu_temp" ]; then 

echo "$timestamp$cpu_temp," >> /ram/logs/cpu_temp.csv
feed_id="37600"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$cpu_temp'}]'
fi

if [ -n "$ilum" ]; then 

echo "$timestamp$ilum," >> /ram/logs/ilumination.csv
feed_id="37594"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$ilum'}]'
fi


if [ -n "$presiune" ]; then 

echo "$timestamp$presiune," >> /ram/logs/presiune.csv
feed_id="37592"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$presiune'}]'
fi

if [ -n "$temp_pres" ]; then 

echo "$timestamp$temp_pres," >> /ram/logs/ilumination.csv
feed_id="37593"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$temp_pres'}]'
fi

if [ -n "$a0" ]; then 

echo "$timestamp$a0," >> /ram/logs/read_adc_a0.csv
feed_id="37680"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a0'}]'
fi

if [ -n "$a1" ]; then 

echo "$timestamp$a1," >> /ram/logs/read_adc_a1.csv
feed_id="37681"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a1'}]'
fi

if [ -n "$a2" ]; then 

echo "$timestamp$a2," >> /ram/logs/read_adc_a2.csv
feed_id="37682"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a2'}]'
fi

if [ -n "$a3" ]; then 

echo "$timestamp$a3," >> /ram/logs/read_adc_a3.csv
feed_id="37683"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a3'}]'
fi

if [ -n "$a4" ]; then 

echo "$timestamp$a4," >> /ram/logs/read_adc_a4.csv
feed_id="37684"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a4'}]'
fi

if [ -n "$a5" ]; then 

echo "$timestamp$a5," >> /ram/logs/read_adc_a5.csv
feed_id="37685"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a5'}]'
fi

if [ -n "$a6" ]; then 

echo "$timestamp$a6," >> /ram/logs/read_adc_a6.csv
feed_id="37686"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a6'}]'
fi

if [ -n "$a7" ]; then 

echo "$timestamp$a7," >> /ram/logs/read_adc_a7.csv
feed_id="37687"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a7'}]'
fi

if [ -z "$message" ]; then 

echo "$timestamp$message," >> /ram/logs/message_log.csv
feed_id="37821"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$message'}]'
fi



exit 0