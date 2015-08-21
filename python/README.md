Edison has a Linux inside (Yocto), and [mraa library](http://iotdk.intel.com/docs/master/mraa/) give us access to its Analogic and Digital PINs from Python. Then we can code and run Python into our Edison (yeah!).
We (still) don't have IDE plugins to directly code and upload to your device, but it is quite easy doing so by just using your favourite Python IDE (ie, PyCharm), [FileZilla](http://sourceforge.net/projects/filezilla/) (or any other SFTP client) and SSH. Let's go! step by step...
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
* Download edison2fiware.py file in your drive and open it with your IDE
* Configure your FIWARE credentials
```
FIWARE_APIKEY = "xxx"
```
* Upload the file to your Edison via SFTP (ie, using Filezilla) setting your Edison IP & user/pass (Port 22).
* Please make sure that you've already plugged light sensor into A0 analog input and button sensor into A1.
* Execute! (using the same SSH connection used in Step 2)
```
root@edison:/home/pythonajln# python edison2fiware.py
```
* That's it! Your Edison is reading sensors and its data is updated in the FIWARE IoT Stack!
* Next steps: Read the data from you application using NGSI APIs or show it in a cool Freeboard as explained in [Visualizing your FIWARE IoT Stack Data](https://github.com/telefonicaid/fiware-edison/blob/develop/README.md#accesing-your-fiware-iot-stack-data)
