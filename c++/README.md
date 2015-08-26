Intel Edison has a Linux (Yocto) inside. We are using this for running c++ program and the mraa library is very useful to access analogic and digital pins from Eclipse (IDE c++).
* First and foremost the setup of your Eclipse environment is explained in this [getting started guide] (https://software.intel.com/es-es/iot/library/edison-getting-started)
* Access your Edison via SSH (your laptop should be in the same WIFI network that your Edison).
```
ssh root@your_edison_ip
```
* Now we must ensure that the curl library is linked in our proyect (it is necessary for the HTTP POST). If you get compiler errors, do the following to add the curl library:
```
Right click on the project and select properties. Then navigate to C/C++ Build -->Settings --> Cross G++ Linker --> Libraries --> Click the green plus button,and add the “curl” library.
```
```
 Add the path of the curl library.
```
* Configure your FIWARE credentials:
```
string FIWARE_APIKEY = "xxxxx";
```
* Choose your Edison for the boards available list. If your device is not displayed in the list, select "Enable broadcast target search".
* Please make sure that you've already plugged light sensor into A0 analog input and button sensor into A1.
* Compile the .cpp file clicking on the "hammer button".
* Upload and run the .cpp to your Edison clicking on the play button. Now your Edison is reading sensors and its data is updated in the FIWARE IoT Stack! 
* Next steps: Read the data from you application using NGSI APIs or show it in a cool Freeboard as explained in [Visualizing your FIWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)


