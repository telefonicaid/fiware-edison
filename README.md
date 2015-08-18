# fiware-edison

## Introduction
This repository holds examples about how to persist your Intel Edison sensors data into FIWARE IoT Stack.
Then, it will show you how to access these data using FIWARE NGSI standard APIs and its multiple connectors with external tools as CartoDB, DucksBoard or Freeboard

## Introduction to Intel Edison
If you are new with Intel Edison, we recommend you going first to the Intel Edison getting started: https://software.intel.com/es-es/iot/library/edison-getting-started
Also, you can find a lot of examples and tutorials in the Movilforum Intel Edison site: http://movilforum.com/unete-con-movilforum-al-reto-intel-edison-2015/

## Introduction to FIWARE IoT Stack
If you are not familiar with FIWARE IoT Stack, we recommend you going to its ReadTheDocs page as a starting point: http://fiware-iot-stack.readthedocs.org/en/latest/index.html

## Edison 2 Fiware Examples
In the following examples, we will be using an Intel Edison with the Arduino expansion board,
plus the Grove Starter Kit for Arduino to send both Luminosity and Button Sensors to FIWARE IoT Stack,
and show both values in several Freeboard web widgets

### Arduino IDE
In this example we will Light and Button Grove Starter Kit for Arduino to Fiware IoT Stack using Arduino IDE. If you are new working with Edison and Arduino IDE, we recommend you going [here|  <https://software.intel.com/es-es/get-started-arduino-install].
* Downlad Edison2Fiware sketch file from http://github.com/fiware-edison/arduino in your drive and open it in Arduino IDE (File > Open)
* Write your WIFI SSID and password in:
 char ssid[] = "";
 char pass[] = "";
* Write your FIWARE cloud credentials:
 char FIWARE_APIKEY = XXXXXXXXXX
* Plug Light Sensor into A0 analog input and Button Sensor into A1. You can use other analogic input, modifying the following lines in the code:
 int lum = analogRead(A0);
 int touch = analogRead(A1);
* Once you have done the configuration steps, upload the sketch to your Edison (connected using the middle USB port). It will connect to the wifi network, and send data to FIWARE Cloud:
 client.println("POST /iot/d?i=FIWARE_DEVICE&k=FIWARE_APIKEY HTTP/1.1");
 client.println("Host: test.ttcloud.net:8082");
 String body = String(alias)+"|"+ value;
 client.println("Content-Length: "+String(body.length()));
 client.println("Connection: close");
 client.println();
 client.println(body);
 client.stop();
* Now, your data is in the FIWARE IoT Stacke, so you can
** Read the data from you application using NGSI APIs:
** Show your data in Freeboard as explained in xxxx (link a la seccion de como conectar CB con Freeboard)

### Intel XDK IDE (Node.js)

### Eclipse (C++)

### Python

## Visualizing your FiWARE IoT Stack Data
### Freeboard Example
