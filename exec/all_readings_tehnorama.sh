#!/bin/sh


 variabila_pres=$(/daisypi/sense/bmp085/pres1)
 variabila_sht=$(/daisypi/sense/sht11/sht_read_17CLK_22_SDA)
 variab_cpu=$(cat /sys/class/thermal/thermal_zone0/temp)
 variabila_analog=$(python /daisypi/sense/mcp3208/adc_read.py)

 read_temp=$(echo $variabila_sht | awk '{print $2}')
 read_humid=$(echo $variabila_sht | awk '{print $3}')
 read_dew=$(echo $variabila_sht | awk '{print $4}')

 read_temp_sec=$(echo $variabila_sht_sec | awk '{print $2}')
 read_humid_sec=$(echo $variabila_sht_sec | awk '{print $3}')
 read_dew_sec=$(echo $variabila_sht_sec | awk '{print $4}')

 cpu_temp=$(echo "scale=2; "$variab_cpu"/1000" | /usr/bin/bc)
 ilum=$(nice -19 "/daisypi/sense/tsl235r/tsl_read" | awk '{print $4}')
 presiune=$(echo $variabila_pres | awk '{print $4}')
 temp_pres=$(echo $variabila_pres | awk '{print $3}')

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

 a3=0
 a4=0
 a5=0
 a6=0
 
 echo "Read val A0 is $a0"
 echo "Read val A1 is $a1"
 echo "Read val A2 is $a2"
 echo "Read val A3 is $a3"
 echo "Read val A4 is $a4"
 echo "Read val A5 is $a5"
 echo "Read val A6 is $a6"
 echo "Read val AA7 is $aa7"
 echo "Read val A7 is $a7"

  timestamp=$(date | awk '{print $3 "," $2 "," $6 "," $4 ","}')


cheie="feed_key"
post_url="http://tehnorama.ro/daisypi/post.php"


if [ -n "$read_temp" ]; then 

feed_id="37825"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_temp'}]'
fi

if [ -n "$read_humid" ]; then 

feed_id="37834"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_humid'}]'
fi

if [ -n "$cpu_temp" ]; then 

feed_id="37848"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$cpu_temp'}]'
fi

if [ -n "$ilum" ]; then 

feed_id="37849"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$ilum'}]'
fi

if [ -n "$presiune" ]; then 

feed_id="37832"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$presiune'}]'
fi

if [ -n "$temp_pres" ]; then 

feed_id="37833"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$temp_pres'}]'
fi



#adaugare viorel

if [ -n "$a0" ]; then 

feed_id="37836"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a0'}]'
fi

if [ -n "$a1" ]; then 

feed_id="37837"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a1'}]'
fi


if [ -n "$a2" ]; then 

feed_id="37838"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a2'}]'
fi


if [ -n "$a3" ]; then 

feed_id="37839"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a3'}]'
fi



if [ -n "$a4" ]; then 

feed_id="37840"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a4'}]'
fi



if [ -n "$a5" ]; then 

feed_id="37841"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a5'}]'
fi


if [ -n "$a6" ]; then 

feed_id="37842"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a6'}]'
fi



if [ -n "$a7" ]; then 

feed_id="37843"
curl $post_url'/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a7'}]'
fi



#/adaugare viorel


exit 0

cheie="5rttnwPJR2TneXp6AOkbhA"


if [ -n "$read_dew" ]; then 

feed_id="37835"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$read_dew'}]'
fi

cheie="feed_key"
post_url="http://tehnorama.ro/daisypi/post.php"




post_url="http://tehnorama.ro/daisypi/post.php"


if [ -n "$a0" ]; then 

feed_id="37836"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a0'}]'
fi


exit 0

if [ -n "$a1" ]; then 

feed_id="37837"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a1'}]'
fi

if [ -n "$a2" ]; then 

feed_id="37838"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a2'}]'
fi

if [ -n "$a3" ]; then 

feed_id="37839"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a3'}]'
fi

if [ -n "$a4" ]; then 

feed_id="37840"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a4'}]'
fi

if [ -n "$a5" ]; then 

feed_id="37841"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a5'}]'
fi

if [ -n "$a6" ]; then 

feed_id="37942"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a6'}]'
fi

if [ -n "$a7" ]; then 

feed_id="37843"
curl 'http://api.sen.se/events/?sense_key='$cheie -X POST -H "Content-type: application/json" -d '[{"feed_id": '$feed_id',"value": '$a7'}]'
fi


exit 0
