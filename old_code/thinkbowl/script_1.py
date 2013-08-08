from i2clibraries import i2c_adxl345
from time import *
 
adxl345 = i2c_adxl345.i2c_adxl345(0)
 
while True:
        print(adxl345)
        sleep(1)