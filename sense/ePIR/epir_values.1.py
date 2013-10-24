import serial
import time

serial = serial.Serial("/dev/ttyAMA0", baudrate=9600)

STATUS_CMD = 'l'
DELAY = 0.5

while True:
    serial.write(STATUS_CMD)
    data = serial.read()
    print data
    time.sleep(DELAY) # pause