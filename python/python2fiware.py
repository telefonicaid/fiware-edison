#!/usr/bin/env python

import mraa
import time
import requests

FIWARE_SERVER = "test.ttcloud.net"
FIWARE_PORT = "8082"
FIWARE_APIKEY = "xxxx"
FIWARE_DEVICE = "myEdison"

URL = "http://"+FIWARE_SERVER+":"+FIWARE_PORT+'/iot/d?k='+FIWARE_APIKEY+'&i='+FIWARE_DEVICE

luminosity = mraa.Aio(0)
pulse = mraa.Aio(1)

while 1:
    lumVal = str(luminosity.read())
    pulseVal = str(pulse.read()>100)
    print lumVal
    print pulseVal
    payload = "l|"+lumVal+"#p|"+pulseVal
    r = requests.post(URL, data=payload)
    print "* Status Code: "+str(r.status_code)
    time.sleep(10)
