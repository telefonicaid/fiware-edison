# Edison 2 FIWARE IoT Stack Integration
This repository holds examples about how to persist your Intel Edison sensors data into FIWARE IoT Stack cloud service.

Then, it will show you how to access these data using FIWARE NGSI standard APIs and its multiple connectors with external tools as Freeboard or CartoDB.

## Introduction to Intel Edison
If you are new with Intel Edison, we recommend you going first to the Intel Edison [getting started guide](https://software.intel.com/es-es/iot/library/edison-getting-started). Also, you can find a lot of examples and tutorials in the [Movilforum Intel Edison Hackaton site](http://movilforum.com/unete-con-movilforum-al-reto-intel-edison-2015)

## Introduction to FIWARE IoT Stack
[FIWARE](https://www.fiware.org/) is an open initiative aiming to create a sustainable ecosystem to grasp the opportunities that will emerge with the new wave of digitalization caused by the integration of recent Internet technologies. Based on this FIWARE technologies, and focused on IoT area, Telefonica created and [IoT Platform](http://iot.tid.es) to help Industrial Partners and Smart Cities building its IoT services. 

This FIWARE IoT Stack is also available for independent developers and startups, and will be used in this tutorial to persist your Edison data in the cloud. You can go to its [ReadTheDocs](http://fiware-iot-stack.readthedocs.org/en/latest/index.html) to get familiar with it. 

NOTE: If you are a hacker participating in the [Movilforum Intel Edison Hackaton](http://movilforum.com/unete-con-movilforum-al-reto-intel-edison-2015) Your can get your FIWARE IoT Stack credentials [here](http://xxx.com)

If you are not, [contact us](mailto:iot_support@tid.es) and we will give you the steps to get access.

## Tutorials
In the following examples, we will be using an Intel Edison with the Arduino expansion board,
plus the Grove Starter Kit for Arduino to send both Luminosity and Button Sensors to FIWARE IoT Stack,
and show both values in several Freeboard web widgets. Please make sure that you've already plugged light sensor into A0 analog input and button Sensor into A1.

There is a huge amount of sensors and actuators in the Grove Starter Kit, so once you are familiar with the example, connect more and get it data in the cloud too!

### Arduino IDE
If you are an Arduino lover, [this example](https://github.com/telefonicaid/fiware-edison/tree/develop/arduino) will be straightforward for you.

### Intel XDK IDE (Node.js)
If you prefer programming in Node, [this is your tutorial](https://github.com/telefonicaid/fiware-edison/tree/develop/nodejs)

### Eclipse (C++)
For those who priorise optimal coding, go [here](https://github.com/telefonicaid/fiware-edison/tree/develop/cplusplus)

### Python
Even Python is not given as an option to code your Edison in the official Intel Getting Started Guide, we know you love Python (we too!), so we have also created this [Python tutorial](https://github.com/telefonicaid/fiware-edison/new/develop/python)

## Accesing your FIWARE IoT Stack Data
You have your Edison sensors data up there in the cloud in FIWARE IoT Stack. So what?

Next step is connecting your applications with FIWARE IoT Stack to access your data and show your magic to the rest of the world.

### First step: FIWARE IoT Stack Management Portal
To check your data is correctly sent and stored, first thing is accessing the [Management Portal](http://test.ttcloud.net:8008). You can log-in using your given FIWARE user/password. In the "Entities" section (An Entity is a data object representation in FIWARE, so your Edison is represented as an Entity) you will find an Entity called "device:myEdison" with a list of attributes:
* "l": Your luminosity sensor
* "p": Your button sensor

If you have connected more sensors to your Edison, they will appear here with the given alias you selected in the Edison code.

If you want to, you can go to "Devices" section to provision a device for your Edison. For example, you could change your Entity ID (setting "home" instead of "device:myEdison" or "luminosity" instead of "l"). Check [this guide](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-2-see-data) for more details

### Drag&Drop visualizations with Freeboard
If you just need a dashboard(like [this one](https://freeboard.io/board/0cYCHY) ) to show your sensors data in real time, you can create it using [Freeboard](https://freeboard.io)
[Tutorial](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-4-show-in-a-dashboard)

### Using NGSI APIs
If you want to build your own app, with your own code and UX, you are looking for an API, right?. Integrating external apps is done via [NGSI APIs](https://forge.fiware.org/plugins/mediawiki/wiki/fiware/index.php?title=Publish/Subscribe_Broker_-_Orion_Context_Broker_-_User_and_Programmers_Guide). [Here](http://fiware-iot-stack.readthedocs.org/en/latest/quickguide/index.html#step-3-get-data)
you have a getting started tutorial to start working with these APIs.
