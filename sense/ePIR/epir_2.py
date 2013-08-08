import serial

serial = serial.Serial("/dev/ttyAMA0", baudrate=9600)
#serial = serial.Serial("/dev/ttyS0", baudrate=9600)

CMD = 'M'
DELAY = 0.5

serial.write(CMD)
# ePIR returns unsolicited mode status
rc = serial.read()
# Turn unsolicited mode on
serial.write('Y')
while True:
    if serial.inWaiting > 0:
        data = serial.read()
        print data