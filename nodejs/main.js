
//################# LIBRARIES ################    
var mraa = require('mraa'); //require mraa


//################ FIWARE VARIABLES ################
var FIWARE_APIKEY = 'xxxxxx';
var FIWARE_DEVICE = 'xxxxx';
var FIWARE_SERVER = 'test.ttcloud.net';
var FIWARE_PORT = '8082';

var MEASURES_PERIOD = 2000; // time between measures

var measures={}; // Dictionary to persist Sensor values

loop();

function loop(){
    
var analogPin0 = new mraa.Aio(0); //setup access to analog input #0 (A0) connected to Luminosity Sensor
var lum = analogPin0.read();
measures["l"] = lum; // save lumininosity value in the dictionary

var analogPin1 = new mraa.Aio(1); //setup access to analog input #1 (A1) connected to Button Sensor
var touch = analogPin1.read();
var pulse = touch>100;
measures["p"] = pulse; // save button pulse value in the dictionary

var body=""; //FIWARE IoT Stack body message
var counter = Object.keys(measures).length; //number of sensors
for (var sensor in measures) { 
    body = body + sensor + '|' + measures[sensor];
    //add measures separator "#" to the body only when it is not the last measure
    if(counter>1){
        body = body +"#";
        counter--;
    }
}
    
console.log('Sending measures to FIWARE IoT Stack '+body);
    
var request = require("request");
var options = { 
  method: 'POST',
  url: 'http://'+FIWARE_SERVER+':'+FIWARE_PORT+'/iot/d',
  qs: { i: FIWARE_DEVICE, k: FIWARE_APIKEY },
  body: body 
};

request(options, function (error, response, body) {
  console.log('Response Status Code: '+response.statusCode);
}); 

setTimeout(loop, MEASURES_PERIOD);

}