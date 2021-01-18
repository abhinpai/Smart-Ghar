#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define ssid ""  //WiFi SSID
#define password ""  //WiFi Password      
#define FIREBASE_HOST "" // Firebase Realtime database host id
#define FIREBASE_AUTH "" // Firebase service account secret

FirebaseData firebaseData;

//If using Relay Module
int Device_1 = D0; //initialize D0 Pin
int Device_2 = D1; //initialize D1 Pin
int Device_3 = D2; //initialize D2 Pin
int Device_4 = D6; //initialize D6 Pin

void setup() {
  
 Serial.begin(9600);
   WiFi.begin (ssid, password);
   Serial.print("Connecting");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
    
  pinMode(Device_1,OUTPUT);//initialize the Device OUTPUT  
  pinMode(Device_2,OUTPUT);//initialize the Device OUTPUT  
  pinMode(Device_3,OUTPUT);//initialize the Device OUTPUT  
  pinMode(Device_4,OUTPUT);//initialize the Device OUTPUT 


  // Reset PIN values in Firebase
  Firebase.set(firebaseData, "/D1", "0");
  Firebase.set(firebaseData, "/D2", "0");
  Firebase.set(firebaseData, "/D3", "0");
  Firebase.set(firebaseData, "/D4", "0");
}

void loop() {
  if (Firebase.get(firebaseData,"/D1")) {
    if (firebaseData.dataType() == "string") {
      String De1 = firebaseData.stringData();
      if (De1=="1") {
          digitalWrite(Device_1,HIGH); //Device1 is ON
          Serial.println ("Device 1 Turned ON");
      }
      else if (De1=="0") {
          digitalWrite(Device_1,LOW);//Device1 if OFF
          Serial.println ("Device 1 Turned OFF");
      }
    }
  }
  if (Firebase.get(firebaseData,"/D2")) {
      if (firebaseData.dataType() == "string") {
        String De2 = firebaseData.stringData();
        if (De2=="1") {
            digitalWrite(Device_2,HIGH); //Device1 is ON
            Serial.println ("Device 2 Turned ON");
        }
        else if (De2=="0") {
            digitalWrite(Device_2,LOW);//Device1 if OFF
            Serial.println ("Device 2 Turned OFF");
        }
      }
    }
   if (Firebase.get(firebaseData,"/D3")) {
      if (firebaseData.dataType() == "string") {
        String De3 = firebaseData.stringData();
        if (De3=="1") {
            digitalWrite(Device_3,HIGH); //Device1 is ON
            Serial.println ("Device 3 Turned ON");
        }
        else if (De3=="0") {
            digitalWrite(Device_3,LOW);//Device1 if OFF
            Serial.println ("Device 3 Turned OFF");
        }
      }
    }
   if (Firebase.get(firebaseData,"/D4")) {
      if (firebaseData.dataType() == "string") {
        String De4 = firebaseData.stringData();
        if (De4=="1") {
            digitalWrite(Device_4,HIGH); //Device1 is ON
            Serial.println ("Device 4 Turned ON");
        }
        else if (De4=="0") {
            digitalWrite(Device_4,LOW);//Device1 if OFF
            Serial.println ("Device 4 Turned OFF");
        }
      }
    }
  }
