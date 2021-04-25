 #include <FirebaseArduino.h>           // Includes the real time Google Firebase Database Library.
#include "DHT.h"                       //Includes the Library responsible to run the DHT Series of Temperature-Humidity Sensors.
#include  <ESP8266WiFi.h>              // Includes the Library Responsible to run one of the state of the art ESP8266 WIFI Node MicroController Unit.

#define FIREBASE_HOST "login-4cf8b.firebaseio.com"  //Defining the web loction to connect to in order to access and login for accessing the Google Firebase Data log.
#define WIFI_SSID "Hello Daily"                     //Defineing, Changing and Setting the WiFi SSID/ User to "Hello Daily".
#define WIFI_PASSWORD "Welcome2daily"               //Defineing, Changing and Setting the WiFi Password/ network PIN to "Welcome2daily"

#define DHTPIN 14                       // Connecting the Digital Output Pin '14'of Arduino to Data Pin of DHT 11 the Temperature-Humidity Sensor.
#define DHTTYPE DHT11                   // This Defines and accends to the library that the sensor connected from the DHT series of Temp-RH Sensors is 'DHT 11'.

String path = "/ESP8266_Device";        //Defines the location in the eprom memory to story the array of characters 

DHT dht(DHTPIN, DHTTYPE);               // The alphabetical Caps is defined to the following type of definitions the DHT and dht respectively.

void setup() 
{
   pinMode(2, OUTPUT);                  // Initialize GPIO2 pin as an output
   pinMode(LED_BUILTIN, OUTPUT);        // Initialize GPIO14 pin as an output
 
 Serial.begin(9600);
 WiFi.begin (WIFI_SSID, WIFI_PASSWORD); // Begins Communications and Starts and Leases the WiFi to the Previously Defined User and Network Key.
 
 while (WiFi.status() != WL_CONNECTED)  // WiFi Status shown upon successful connection to grid.
  {
    delay(500);                         // Delay of 500 milliseconds
    Serial.print(".");                  // Prints in Serial Monitor
    digitalWrite(LED_BUILTIN, LOW);     // turn the LED on (HIGH is the voltage level)
    delay(300);                         // Delay of 300 milliseconds
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    delay(300);                         // Delay of 300 milliseconds
  }
 dht.begin();                           // Enabling and Leasing the DHT Sensor to fuction and enable operations.
 pinMode(4,INPUT);                      // Data Pin of Rain Sensor , for NodeMCU D2 GPIO no. is 4
 Serial.println ("");
 Serial.println ("WiFi Connected!");    // Serial Prints in a new Line 'WiFi Connected!' when it connects to a Reciver Device.
 digitalWrite(LED_BUILTIN, LOW);        // turn the LED on (HIGH is the voltage level)
 Firebase.begin(FIREBASE_HOST);         // Begining to access the Fire database and establishing it as a 'HOST'.
}

void loop() 
{
 float h = dht.readHumidity();          // Signalling DHT to read Relative Humidity and functionalising it as a floating decimal value.
 float t = dht.readTemperature();       // Signalling DHT to read Temperature in Celcius(default) and functionalising it as a floating decimal value.
 int   r = digitalRead(4);              // Reading the Rain Sensor Data
  
 Firebase.setFloat( path + "/Temperature/Data", t);     // declaration for temperature that set float reading from the sensor and ridging it to the Google Fire Database.
 Serial.println(t);                                     // Serial printing temperature
 Firebase.setFloat( path + "/Humidity/Data", h);        // declaration for Relative Humidity that set float reading from the sensor and ridging it to the Google Fire Database.
 Serial.println(h);                                     // Serial printing humidity
 if (r == 1)
  {
     digitalWrite(2, HIGH);                             // Turnon LED
   Firebase.setString( path + "/Rain/Data","NOT_RAINING_NOW");    // declaration signalling Not raining and ridging it to the Google Fire Database.
   Serial.println("NOT RAINING NOW");                             // Serial printing temperature
  }
   else 
  {
    digitalWrite(2, LOW);                               // Turnoff LED
   Firebase.setString(path + "/Rain/Data","RAINING_NOW");         // declaration signalling Not raining and ridging it to the Google Fire Database.
   Serial.println(" RAINING NOW");                                // Serial printing temperature
  }
 delay(200);

 if(Firebase.failed()){
  Serial.print("error");
  Serial.print(Firebase.error());                                // Serial printing error and error code.
  digitalWrite(2, LOW);                                // Blink LED 4 times with 500 milliseconds gap if error in writing in Firebase
  delay(300);
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  delay(300);
  digitalWrite(2, HIGH); 
  delay(300);
  digitalWrite(2, LOW);
  delay(300);
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  delay(300);
  digitalWrite(2, HIGH);  
  return;
 }
}
