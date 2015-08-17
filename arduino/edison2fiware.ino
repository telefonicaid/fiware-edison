//################# LIBRARIES ################
  #include <SPI.h>
  #include <WiFi.h>
  
  //################# WIFI DETAILS #################
  char ssid[] = "xxx"; //  your network SSID (name) 
  char pass[] = "xxx";    // your network password (use for WPA, or use as key for WEP)
  int keyIndex = 0;            // your network key Index number (needed only for WEP)
  int status = WL_IDLE_STATUS;
  
  //################# NETWORK VARIABLES #################
  // Name of the server we want to connect to
  char server[] = "test.ttcloud.net";
  int port = 8082;  
  WiFiClient client;
  
  //################ FIWARE VARIABLES ################
  int value = 0;
  char alias[] = "l";
    
  
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
    // read luminosity sensor value on analogic PIN 0
    readSensor();
    // send luminosity value to FIWARE IoT Stack
    postMeasure(alias, value);
    // wait 10s between measures
    delay(10000);  
    
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("Disconnecting from wifi");
      client.stop();
    } 
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


  void readSensor()
  {
    //Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
    //read the input on analog pin 0:
    value = analogRead(A0);
  }

    
  void postMeasure(char alias[],int value)
  {
    Serial.println("\nStarting connection to server...");
    
    // if you get a connection, report back via serial:
    if (client.connect(server, port)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.println("POST /iot/d?i=xxxx&k=xxxxx HTTP/1.1");
      client.println("Host: test.ttcloud.net:8082");
      String body = String(alias)+"|"+String(value);
      client.println("Content-Length: "+String(body.length()));
      client.println();
      client.println(body);
    }
  }
  
  
