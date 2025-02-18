#define WIFI_SSID "your_SSID"        // To connect to wifi with SSID
#define WIFI_PASSWORD "your_password"    // To connect to wifi with password

#include <WiFi.h>               // Include Wi-Fi library
#include <FirebaseESP32.h>      // Include Firebase library
#include <Servo.h>              // To connect to Servo

// Firebase Config
#define FIREBASE_HOST "your_firebase_project.firebaseio.com"  // Replace with your Firebase database URL
#define FIREBASE_AUTH "your_firebase_database_secret"        // Replace with your Firebase database secret

// Define servos
Servo servo1;               // Fingers of arm
Servo servo2;               // Wrist of arm
Servo servo3;               // Elbow of arm
Servo servo4;               // Shoulder of arm

// Servo positions
int pos1;
int pos2;
int pos3;
int pos4;

// Data from camera
String material;
String plastic = "plastic";
String metal = "metal";
String glass = "glass";
String paper = "paper";

// Firebase reference
FirebaseData firebaseData;
FirebaseJson firebaseJson;

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    delay(5000); // Delay before retry
  }
  Serial.println("Connected to Wi-Fi!");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  // Enable automatic reconnection to Wi-Fi

  // Attach servos
  servo1.attach(0);
  servo2.attach(1);
  servo3.attach(2);
  servo4.attach(3);
  
  starting_point();
}

void starting_point() {
  pos1 = 45;
  pos2 = 90;
  pos3 = 90;
  pos4 = 0;
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
}

void catch_object() {
  pos1 = 10;
  pos2 = 175;
  pos3 = 175;
  pos4 = 0;
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
}

void plastic_go() {
  pos3 = 120;
  pos4 = 60;
  pos1 = 45;
  servo3.write(pos3);
  servo4.write(pos4);
  servo1.write(pos1);
}

void metal_go() {
  pos3 = 120;
  pos4 = 120;
  pos1 = 45;
  servo3.write(pos3);
  servo4.write(pos4);
  servo1.write(pos1);
}

void glass_go() {
  pos3 = 120;
  pos4 = 180;
  pos1 = 45;
  servo3.write(pos3);
  servo4.write(pos4);
  servo1.write(pos1);
}

void paper_go() {
  pos3 = 120;
  pos4 = 240;
  pos1 = 45;
  servo3.write(pos3);
  servo4.write(pos4);
  servo1.write(pos1);
}

void organic_materials() {
  pos3 = 120;
  pos4 = 300;
  pos1 = 45;
  servo3.write(pos3);
  servo4.write(pos4);
  servo1.write(pos1);
}

void loop() {
  // Example of fetching material from Firebase
  if (Firebase.getString(firebaseData, "/material")) {
    material = firebaseData.stringData();  // Get material data from Firebase
    Serial.print("Material from Firebase: ");
    Serial.println(material);
  }
  
  // Perform actions based on the material
  if (material.equalsIgnoreCase(plastic)) {
    plastic_go();
  }
  else if (material.equalsIgnoreCase(metal)) {
    metal_go();
  }
  else if (material.equalsIgnoreCase(glass)) {
    glass_go();
  }
  else if (material.equalsIgnoreCase(paper)) {
    paper_go();
  }
  else {
    organic_materials();
  }

  starting_point();
  delay(1000);  // Delay for 1 second
}
