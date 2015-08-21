In this example we will connect Light and Button data to Fiware IoT Stack using Arduino IDE. If you are new working with Edison and Arduino IDE, we recommend you going [here](https://software.intel.com/es-es/get-started-arduino-install).
* Download Edison2Fiware.ino sketch file from [here](http://github.com/fiware-edison/arduino) in your drive and open it in Arduino IDE (File > Open)
* Write your WIFI SSID and password in:
```
char ssid[] = "";
char pass[] = "";
```
* Write your FIWARE cloud credentials:
```
char FIWARE_APIKEY = XXXXXXXXXX
```
* Plug Light Sensor into A0 analog input and Button Sensor into A1. 
* Once you have done the configuration steps, upload the sketch to your Edison (connected using the middle USB port). 

* Now, your data is in the FIWARE IoT Stacke, so you can
** Read the data from you application using NGSI APIs
** Show your data in Freeboard as explained in [Visualizing your FiWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)
