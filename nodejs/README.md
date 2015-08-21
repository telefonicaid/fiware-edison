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
* Once it is uploaded click on the play button, so the party will start! Your Edison is reading sensors and its data is updated in the FIWARE IoT Stack!
* Next steps: Read the data from you application using NGSI APIs or show it in a cool Freeboard as explained in [Visualizing your FIWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)
