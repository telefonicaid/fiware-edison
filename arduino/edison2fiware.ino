  
  //################# LIBRARIES ################
  #include <SPI.h>
  #include <WiFi.h>
  
  
  //################# WIFI DETAILS #################
  char ssid[] = "OWDTEST";     // your network SSID (name) 
  char pass[] = "tidowd22";    // your network password (use for WPA, or use as key for WEP)
  int keyIndex = 0;            // your network key Index number (needed only for WEP)
  int status = WL_IDLE_STATUS;
  WiFiClient client;
    
  //################ FIWARE VARIABLES ################
  char FIWARE_APIKEY[] = "93d5810871197ae37c3d7f1f69e06a92";
  char FIWARE_DEVICE[] = "myEdison";
  char FIWARE_SERVER[] = "hackathon.ttcloud.net";
  int FIWARE_PORT = 8082; 
  
  //################ SENSOR VARIABLES ################  
  const int numsensors = 2;
  String measures[numsensors][2];
  // Wait 2s between measures
  int MEASURES_PERIOD = 2000;
  
    
    
  void setup() 
  {  
    // Put your setup code here, to run once:
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
    pinMode(6, OUTPUT); 
    
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    setupNetwork(); 
  }

  
  void loop() 
  {
    // Read sensors values on analogic PINs and send measures
    readSensors();
    postMeasures();
    
    delay(MEASURES_PERIOD);   
  }
 
  
  void setupNetwork()
  { 
    Serial.print("Configuring Network...");
    
    // Check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present"); 
      // don't continue:
      while(true);
    } 
  
    String fv = WiFi.firmwareVersion();
    if( fv != "1.1.0" )
      Serial.println("Please upgrade the firmware");
    
    // Attempt to connect to Wifi network:
    while (status != WL_CONNECTED) { 
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
      status = WiFi.begin(ssid, pass);
    
      // Wait 10 seconds for connection:
      delay(10000);
    } 
    Serial.println("Connected to wifi");
  }


  void readSensors()
  {
    // Reading Light and Button Sensors contained in Grove Starter Kit for Arduino
    
    // Connect Light Sensor on Analogic PIN A0
    int lum = analogRead(A0);
    measures[0][0] = "l";
    measures[0][1] = String(lum);

    // Connect Button Sensor on Analogic PIN A1
    int touch = analogRead(A1);
    String pulse = "false";
    if(touch>100){
      pulse = "true";
    } 
    measures[1][0] = "p";
    measures[1][1] = String(pulse);
  }
  
    
  void postMeasures()
  {
    Serial.println("\nStarting connection to server...");
    
    String body;
    
    // If you get a connection, report back via serial:
    if (client.connect(FIWARE_SERVER, FIWARE_PORT)) {
      Serial.println("connected to server");
      for (int i = 0; i < numsensors; i++){ 
        body= body + String(measures[i][0])+"|"+String(measures[i][1]);
        if (i!=numsensors-1){
            body = body +"#";
        }     
      }
      
    // Make a HTTP request:
    client.println("POST /iot/d?i="+String(FIWARE_DEVICE)+"&k="+String(FIWARE_APIKEY)+"&getCmd=1 HTTP/1.1");    
    client.println("Host:"+String(FIWARE_SERVER)+":"+String(FIWARE_PORT));
    client.println("Content-Length: "+String(body.length()));
    client.println("Connection: close");
    client.println();
    client.println(body);
    Serial.println(body);

    // Parse chain of commands 
    String command="";
    bool command_part= false; 
    while (client.available()){
      char c = client.read();
      if (c == '#'){         
         command_part = false;
      }  
      if (command_part == true){  
        command +=  c ; 
      }
      if (c == '@'){
        command_part = true;
      }
    }

    String aux="";
    
    for (int x = 0 ; x< command.length(); x++){ 
        
        aux = aux + command[x];
        
        if (aux == "ledr|on"){
          digitalWrite(6, HIGH);   
          delay(500);
          //Serial.println(command);
          command=command.substring(7,command.length());
          Serial.println(command.length());
          aux="";
          Serial.println(command);
          x = 0;
          sendAck();
          delay(1000);
        }
        
        if (aux == "ledr|off"){
          digitalWrite(6, LOW);   
          delay(500);
          Serial.println(command);
          command=command.substring(8,command.length());
          aux="";
          Serial.println(command);
          x = 0;
          sendAck();
          delay(1000);  
        }
    }
    
    client.stop();
    
    }
  }
  
  // Not execute old commands again
  void sendAck(){
    String ack_payload= "";
    ack_payload= String(FIWARE_DEVICE)+"@ledr|OK";
    client.println("POST /iot/d?i="+String(FIWARE_DEVICE)+"&k="+String(FIWARE_APIKEY)+" HTTP/1.1");    
    client.println("Host:"+String(FIWARE_SERVER)+":"+String(FIWARE_PORT));
    client.println("Content-Length: "+String(ack_payload.length()));
    client.println("Connection: close");
    client.println();
    client.println(ack_payload);    
  }
