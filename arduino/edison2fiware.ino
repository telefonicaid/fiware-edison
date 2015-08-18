  
  //################# LIBRARIES ################
  #include <SPI.h>
  #include <WiFi.h>
  
  //################# WIFI DETAILS #################
  char ssid[] = "xxxxx";     // your network SSID (name) 
  char pass[] = "xxxxx";    // your network password (use for WPA, or use as key for WEP)
  int keyIndex = 0;            // your network key Index number (needed only for WEP)
  int status = WL_IDLE_STATUS;
  
  //################# NETWORK VARIABLES #################
  // Name of the server we want to connect to
  char server[] = "test.ttcloud.net";
  int port = 8082;  
  WiFiClient client;
  
  //################ FIWARE VARIABLES ################
  char FIWARE_APIKEY[] = "xxxxxx";
  char FIWARE_DEVICE[] = "myEdison";
  
  //################ SENSOR VARIABLES ################  
  const int numsensors = 2;
  String measures[numsensors][2];
  
    
  
  void setup() 
  {  
    // put your setup code here, to run once:
    // initialize serial communications at 9600 bps:
    Serial.begin(9600); 
    
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    setupNetwork(); 
  }

  
  void loop() 
  {
    // read sensors values on analogic PINs and send measures
    readSensors();
    postMeasures();
    
    // wait 1s between measures
    delay(1000);  
    
  }
 
  
  void setupNetwork()
  { 
    Serial.print("Configuring Network...");
    
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present"); 
      // don't continue:
      while(true);
    } 
  
    String fv = WiFi.firmwareVersion();
    if( fv != "1.1.0" )
      Serial.println("Please upgrade the firmware");
    
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) { 
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
      status = WiFi.begin(ssid, pass);
    
      // wait 10 seconds for connection:
      delay(10000);
    } 
    Serial.println("Connected to wifi");
  }


  void readSensors()
  {
    //Reading Light and Button Sensors contained in Grove Starter Kit for Arduino
    //Connect Light Sensor on Analogic PIN A0
    int lum = analogRead(A0);
    measures[0][0] = "l";
    measures[0][1] = String(lum);

    //Connect Button Sensor on Analogic PIN A1
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
    
    // if you get a connection, report back via serial:
    if (client.connect(server, port)) {
      Serial.println("connected to server");
      for (int i = 0; i < numsensors; i++){ 
        body= body + String(measures[i][0])+"|"+String(measures[i][1]);
        if (i!=numsensors-1){
            body = body +"#";
        }
            
      }
      
    // Make a HTTP request:
    client.println("POST /iot/d?i="+String(FIWARE_DEVICE)+"&k="+String(FIWARE_APIKEY)+" HTTP/1.1");    
    client.println("Host: test.ttcloud.net:8082");
    client.println("Content-Length: "+String(body.length()));
    client.println("Connection: close");
    client.println();
    client.println(body);
    Serial.println(body);
    client.stop();
    }
  }
  
  
  
