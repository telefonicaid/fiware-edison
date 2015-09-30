//################# LIBRARIES ################    
var mraa = require('mraa'); //require mraa
var request = require("request");
var sleep = require('sleep');


//################ FIWARE VARIABLES ################
var FIWARE_APIKEY = '93d5810871197ae37c3d7f1f69e06a92';
var FIWARE_DEVICE = 'myEdison';
var FIWARE_SERVER = 'hackathon.ttcloud.net';
var FIWARE_PORT = '8082';

var MEASURES_PERIOD = 2000; // time between measures
var measures={}; // Dictionary to persist Sensor values   

//################ SENSOR VARIABLES ################
var analogPin0 = new mraa.Aio(0); //setup access to analog input #0 (A0) connected to Luminosity Sensor
var analogPin1 = new mraa.Aio(1); //setup access to analog input #1 (A1) connected to Button Sensor

//################# COMMANDS CONFIGURATION ##########
var led = new mraa.Gpio(6);
led.dir(mraa.DIR_OUT); 


loop();


function loop(){

    readMeasures();
    postMeasures();
    setTimeout(loop, MEASURES_PERIOD);
}


function readMeasures(){

    var lum = analogPin0.read();
    measures["l"] = lum; // save lumininosity value in the dictionary

    var touch = analogPin1.read();
    var pulse = touch>100;
    measures["p"] = pulse; // save button pulse value in the dictionary
};


function postMeasures(){

    var body=""; //FIWARE IoT Stack body message
    var counter = Object.keys(measures).length; //number of sensors
    for (var sensor in measures) { 
        body = body + sensor + '|' + measures[sensor];
        //add measures separator "#" to the body only when it is not the last measure
        if(counter>1){
                body = body +"#";
                counter--;
        }
    };

    console.log('Sending measures to FIWARE IoT Stack '+body);

    var options = { 
        method: 'POST',
        url: 'http://'+FIWARE_SERVER+':'+FIWARE_PORT+'/iot/d',
        qs: { i: FIWARE_DEVICE, k: FIWARE_APIKEY, getCmd:1 },
        body: body 
    };

    request(options, function (error, response, body) {
        // Parse chain of commands
        console.log('Response Status Code: '+response.statusCode);
        var received_commands = body.split("#");
        received_commands.reverse();

        while(received_commands!=""){
            
            var command = received_commands.pop().split("@")[1].split("|");
            console.log(command); 
            var command_name = command[0];
            var command_value = command[1];
            console.log("command name :"+command_name);
            console.log("command value :"+command_value);

            if (command_name == "ledr"){    
                led.write((command_value == "on")?1:0);
                sendAck();
            }
            sleep.sleep(1)    
        } 
    }); 
    
function sendAck(){
    // Not execute old commands again
    var options_ack = { 
    method: 'POST',
    url: 'http://'+FIWARE_SERVER+':'+FIWARE_PORT+'/iot/d',
    qs: { i: FIWARE_DEVICE, k: FIWARE_APIKEY},
    body: FIWARE_DEVICE+"@ledr|OK", 
    }; 
  
    request(options_ack, function (error, response, body){
        console.log('Response Status Code: '+response.statusCode);
    })    
}    
};
