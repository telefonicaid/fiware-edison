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
and show both values in several Freeboard web widgets. Please make sure that you've already plugged light sensor into A0 analog input and button Sensor into A1.

### Arduino IDE
If you are an Arduino lover, [this example](https://github.com/telefonicaid/fiware-edison/tree/develop/arduino) will be straightforward for you.

### Intel XDK IDE (Node.js)
As you know Intel Edison has a Linux inside (Yocto), that we are going to use for running node.js scripts. 
And [mraa library](http://iotdk.intel.com/docs/master/mraa/) will give us access to its Analogic and Digital PINs from Node.js.
Luckily, The Intel XDK IoT Edition is fully compatible with this language, so let's get ready to Rumble.... 
* First of all download the Intel XDK IoT edition [here](https://software.intel.com/es-es/iot/library/edison-getting-started)
* Access your Edison via SSH (your laptop should be in the same WIFI network your Edison is)
```
ssh root@your_edison_ip
```
Then, we can install required Node.js libraries, as requests (used as HTTP Client in our example)
```
npm install request
```
* Download main.js file from https://github.com/telefonicaid/fiware-edison/tree/master/nodejs in your drive and create a new project and  it with Intel XDK, and replace main.js for the file that we provide you.  
* Configure your FIWARE credentials
```
FIWARE_APIKEY = "xxx"
```
* Select your device from the IoT device's list that appears on the button-left part of the screen. If you can't find it, just select "Add Manual Connection" and fill the blanks with your ip address, user name and password.
* Please make sure that you've already plugged light sensor into A0 analog input and button Sensor into A1.
* Upload the file to your Edison clicking on hammer button.
* Once it is uploaded click on the play button, so the party will start! 

*  Now, your data is in the FIWARE IoT Stacke, so you can
** Read the data from you application using NGSI APIs
** Show your data in Freeboard as explained in [Visualizing your FiWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)

### Eclipse (C++)

### Python
Even Python is not given as an option to code your Edison in the official Getting Started Guide, it has a Linux inside (Yocto),
so you can code and run Python (yeah). And [mraa library](http://iotdk.intel.com/docs/master/mraa/) will give us access to its Analogic and Digital PINs from Python.
We (still) don't have IDE plugins to directly code and upload to your device, but it is quite
easy doing so by just using your favourite Python IDE (ie, PyCharm), [FileZilla](http://sourceforge.net/projects/filezilla/) (or any other SFTP client) and SSH. Let's go! step by step...
* If you haven't done it yet, [setup a serial terminal](https://software.intel.com/es-es/get-started-edison-osx-step3) to configure your root pass and [configure your WIFI and get your Edison IP](https://software.intel.com/es-es/get-started-edison-osx-step4)
* Access your Edison via SSH (your laptop should be in the same WIFI network your Edison is)
```
ssh root@your_edison_ip
```
* Install pip (that will allow you installing Python libraries) as explained [here](http://blog.salvius.org/2015/05/installing-pip-on-intel-edison.html)
```
vi /etc/opkg/base-feeds.conf
```
And add the following lines
```
src/gz all http://repo.opkg.net/edison/repo/all
src/gz edison http://repo.opkg.net/edison/repo/edison
src/gz core2-32 http://repo.opkg.net/edison/repo/core2-32
```
Save and close the file. Then update the package list.
```
opkg update
```
And install PIP
```
opkg install python-pip
```
Then, we can install required Python libraries, as requests (used as HTTP Client in our example)
```
pip install requests
```
* Download Edison2Fiware.py file from http://github.com/fiware-edison/python in your drive and open it with your IDE
* Configure your FIWARE credentials
```
FIWARE_APIKEY = "xxx"
```
* Upload the file to your Edison (using FileZilla, for example). Using your Edison IP, user/pass. Port 22.
* Please make sure that you've already plugged light sensor into A0 analog input and button Sensor into A1.
* Execute! (using the same SSH connection used in Step 2)
```
root@edison:/home/pythonajln# python edison2fiware.py
```
* Now, your data is in the FIWARE IoT Stacke, so you can
** Read the data from you application using NGSI APIs
** Show your data in Freeboard as explained in [Visualizing your FiWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)

## Accesing your FiWARE IoT Stack Data
Now, you have your sensors data in FIWARE IoT Stack. So what?
Next step is connecting your applications with FIWARE IoT Stack to access your data and show your magic.

### Using NGSI APIs
Integrating external apps is done via NGSI APIs. [Here](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-3-get-data)
you have a getting started tutorial to start working. You should use the following FIWARE credentials:
```
FiwareService = edison
FiwareServicePath = /your_user_name
user = your_user_name
password = your_user_name
```

### Drag&Drop visualizations with Freeboard
If you just need a dashboard(like [this one](https://freeboard.io/board/0cYCHY) ) to show your sensors data in real time, you can create it using [Freeboard](https://freeboard.io)
[Tutorial](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-4-show-in-a-dashboard)

### Showing your data in a map with CartoDB
You can also use another pre-integrated visualization service as [CartoDB](https://cartodb.com/) that will allow you showing your data in a map,
and then build fantastic data aggregations (as heat maps). Connector to integrate CartoDB and FIWARE IoT Stack is [here](https://github.com/telefonicaid/fiware-orion2cartodb)
