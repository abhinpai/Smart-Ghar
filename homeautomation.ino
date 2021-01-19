#include <FirebaseESP8266.h> // Install FirebaseESP8266 library
#include <ESP8266WiFi.h> // Install ESP8266WiFi library and Esp8266 Board from Borad Manager
#include <Espalexa.h> // Install Alexa 

#define ssid ""  //WiFi SSID
#define password ""  //WiFi Password      
#define FIREBASE_HOST "" // Firebase Realtime database host id
#define FIREBASE_AUTH "" // Firebase service account secret

FirebaseData firebaseData;
Espalexa espalexa;

//If using Relay Module
int Device_1 = D0; //initialize D0 Pin
int Device_2 = D1; //initialize D1 Pin
int Device_3 = D2; //initialize D2 Pin
int Device_4 = D6; //initialize D6 Pin

String Room_Light = "Room light"; // Alexa CMD
boolean wifiConnected = false;
boolean connectWifi();

void lightChanged(uint8_t brightness); // Callback method

void setup() {
  Serial.begin(9600);
  wifiConnected = connectWifi();

  if (wifiConnected){
    init_realy(); //initialize the Device OUTPUT 
    init_alexa(); // Alexa Connection
    init_firebase(); // Firebase Connection & Reset PIN values in Firebase
  } else {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }  
}

void init_alexa() {
  espalexa.addDevice(Room_Light, lightChanged);
  espalexa.begin();
}

void init_realy() {
  pinMode(Device_1,OUTPUT);
  pinMode(Device_2,OUTPUT);
  pinMode(Device_3,OUTPUT);
  pinMode(Device_4,OUTPUT);
  reset_relay();
}

void reset_relay() {
  digitalWrite(Device_1,HIGH); 
  digitalWrite(Device_2,HIGH); 
  digitalWrite(Device_3,HIGH); 
  digitalWrite(Device_4,HIGH); 
}

void init_firebase() {
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(firebaseData, "Plugs/D1", 1);
  Firebase.setInt(firebaseData, "Plugs/D2", 1);
  Firebase.setInt(firebaseData, "Plugs/D3", 1);
  Firebase.setInt(firebaseData, "Plugs/D4", 1);
}

boolean connectWifi() {
  boolean state = true;
  int i = 0;
  
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  Serial.print("Connecting...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}

void loop() {
  espalexa.loop();
  
  if (Firebase.getInt(firebaseData,"Plugs/D1")) {
    int De1 = firebaseData.intData();
    if (De1==1) {
      digitalWrite(Device_1,HIGH); 
    }
    else if (De1==0) {
      digitalWrite(Device_1,LOW);
    }
  }
  if (Firebase.get(firebaseData,"Plugs/D2")) {
    int De2 = firebaseData.intData();
    if (De2==1) {
      digitalWrite(Device_2,HIGH); 
    }
    else if (De2==0) {
      digitalWrite(Device_2,LOW);
    }
   }
  if (Firebase.get(firebaseData,"Plugs/D3")) {
    int De3 = firebaseData.intData();
    if (De3==1) {
      digitalWrite(Device_3,HIGH); 
    }
    else if (De3==0) {
      digitalWrite(Device_3,LOW);
    }
  }
  if (Firebase.get(firebaseData,"Plugs/D4")) {
    int De4 = firebaseData.intData();
    if (De4==1) {
      digitalWrite(Device_4,HIGH); 
    }
    else if (De4==0) {
      digitalWrite(Device_4,LOW);
    }
  }

  delay(1);
}

void lightChanged(uint8_t brightness) {
  if (brightness) {
    Firebase.setInt(firebaseData, "Plugs/D1", 0);
    digitalWrite(Device_1, LOW);
    Serial.println("Device1 ON");
  } else {
    Firebase.setInt(firebaseData, "Plugs/D1", 1);
    digitalWrite(Device_1, HIGH);
    Serial.println("Device1 OFF");
  }
}
