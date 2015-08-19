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
In this example we will connect Light and Button data to Fiware IoT Stack using Arduino IDE. If you are new working with Edison and Arduino IDE, we recommend you going [here|  <https://software.intel.com/es-es/get-started-arduino-install].
* Download Edison2Fiware.ino sketch file from http://github.com/fiware-edison/arduino in your drive and open it in Arduino IDE (File > Open)
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
Even Python is not given as an option to code your Edison in the official Getting Started Guide, it has a Linux inside (Yocto),
so you can code and run Python (yeah). And mraa library (http://iotdk.intel.com/docs/master/mraa/) will give us access to Analogic and Digital PINs from Python.
We (still) don't have IDE plugins to directly code and upload to your device, but it is quite
easy doing so by just using your favourite Python IDE (ie, PyCharm), FileZilla (or any other SFTP client) and SSH. Let's go! step by step...
* If you haven't done it yet, setup a serial terminal (https://software.intel.com/es-es/get-started-edison-osx-step3) to configure your root pass and configure your WIFI and get your Edison IP: https://software.intel.com/es-es/get-started-edison-osx-step4
* Access your Edison via SSH (your laptop should be in the same WIFI network your Edison is)
 ssh root@your_edison_ip
* Install pip (that will allow you installing Python libraries) as explained here: http://blog.salvius.org/2015/05/installing-pip-on-intel-edison.html
 vi /etc/opkg/base-feeds.conf
And add the following lines
 src/gz all http://repo.opkg.net/edison/repo/all
 src/gz edison http://repo.opkg.net/edison/repo/edison
 src/gz core2-32 http://repo.opkg.net/edison/repo/core2-32
Save and close the file. Then update the package list.
 opkg update
And install PIP
 opkg install python-pip
Then, we can install required Python libraries, as requests (used as HTTP Client in our example)
 pip install requests
* Download Edison2Fiware.py file from http://github.com/fiware-edison/python in your drive and open it with your IDE
* Configure your FIWARE credentials
 FIWARE_APIKEY = "xxx"
* Upload the file to your Edison (using FileZilla http://sourceforge.net/projects/filezilla/, for example). Using your Edison IP, user/pass. Port 22.
* Execute! (using the same SSH connection used in Step 2)
root@edison:/home/pythonajln# python edison2fiware.py

## Visualizing your FiWARE IoT Stack Data
### Freeboard Example
https://freeboard.io/board/0cYCHY
http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-4-show-in-a-dashboard
