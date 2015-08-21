In this example we will connect Light and Button sensors data to FIWARE IoT Stack using Arduino IDE. If you are new working with Edison and Arduino IDE, we recommend you going [here](https://software.intel.com/es-es/get-started-arduino-install) first.
* Download edison2fiware.ino sketch file in your drive and open it with Arduino IDE (File > Open)
* Setup your WIFI SSID and password:
```
char ssid[] = "";
char pass[] = "";
```
* Write your FIWARE IoT Stack credentials:
```
char FIWARE_APIKEY = XXXXXXXXXX
```
* Plug Light Sensor into A0 analog input and Button Sensor into A1. 
* Once you have done the configuration steps, upload the sketch to your Edison (connected using the middle USB port). 
* That's it! Your Edison is reading sensors and its data is updated in the FIWARE IoT Stack!
* Next steps:Read the data from you application using NGSI APIs or show it in a cool Freeboard as explained in [Visualizing your FIWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)
