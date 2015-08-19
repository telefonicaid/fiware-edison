#!/usr/bin/env python

# Developed by @IndustrialIoT Team (mail:iot_support@tid.es)

import mraa
import time
import requests

################ FIWARE VARIABLES ################
FIWARE_SERVER = "test.ttcloud.net"
FIWARE_PORT = "8082"
FIWARE_APIKEY = "xxxxxxxx"
FIWARE_DEVICE = "xxxxxx"

#Time between measures
MEASURES_PERIOD = 2

#Setup access to analog input #0 (A0) connected to Luminosity Sensor
luminosity = mraa.Aio(0)

#Setup access to analog input #1 (A1) connected to Button Sensor
pulse = mraa.Aio(1)

#Setup dictionary to include measures
measures = {}

def readMeasures():

    #Read Luminosity and save its value in the dictionary using the alias "l"
    lumVal = str(luminosity.read())
    measures["l"] = lumVal

    #Read Button and save its value in the dictionary using the alias "p"
    pulseVal = str(pulse.read()>100).lower()
    measures["p"] = pulseVal

def postMeasures():

    first = True
    payload = ""
    for key,value in measures.items():
        #Measures payload format is alias1|value1#alias2|value2#....
        #Add measures separator "#" to the request payload only when it is not the first measure
        if(first):
            first = False
        else:
            payload = payload + "#"

        payload = payload + key + "|" + value

    print('Sending measures to FIWARE IoT Stack '+payload)

    url = "http://" + FIWARE_SERVER+ ":" +FIWARE_PORT+ "/iot/d"
    querystring = {"i": FIWARE_DEVICE, "k": FIWARE_APIKEY}
    r = requests.post(url, data=payload, params=querystring)
    print "Response Status Code: "+str(r.status_code)

## MAIN ##
while True:
    readMeasures()
    postMeasures()
    measures.clear()
    time.sleep(MEASURES_PERIOD)
