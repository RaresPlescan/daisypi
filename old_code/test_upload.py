#!/usr/bin/python

import json
import requests

new_read = {}
new_read['temperature'] = 20.77
new_read['dew_point'] = 12.34
new_read['co'] = 200
new_read['pressure'] = 300
new_read['humidity'] = 400
new_read['mic'] = 50
new_read['pressure_diff'] = 123
new_read['light'] = 100
new_read['webcam_status'] = 'OK'
new_read['status_message'] = 'CO level is too low!'
new_read['pir'] = 0

body = json.dumps(new_read)
url = u'http://192.168.1.108:5000/update'
r = requests.post(headers={'content-type': 'application/json'},
                             url=url, data=body)
print(r.status_code)
print(r.text)

