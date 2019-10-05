#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include "Ultrasonic.h"

#include <SoftwareSerial.h>

#define MAX_STRING_LEN  20
#define DHTPIN A15
#define ECHO A9
#define TIRG A8

#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
Ultrasonic water_level(TIRG,ECHO);


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const char* host = "ucstaungoo.000webhostapp.com";
const int httpPort = 80;

String path_switch = "/ihome/api/switch/io.json";
String path_water = "/ihome/api/arduino/io.json";
String path_window = "/ihome/api/door/window.json";

int water_distance = 0;
int out_light = 40;
int pir_sensor = 22;
int flame_sensor = A13;
int light_sensor = A14;
int buzz = 21;


float h=0;
float t=0;
int light_sensorReading;
int flame_sensorReading;
int pir_sensorReading;

int light_send =0;
int motion_send=0;
String data = "";
String win = "";

//gsm
SoftwareSerial phone(18,19);

//control
int devices[]={30,31,32,33,34,35,36,37,38,39};
int window[]={44,45,46,47};

int pump = 41;
bool flag = false;

EthernetClient client;

void setup(){
  phone.begin(9600);
  Serial.begin(9600);
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to configure Ethernet"));
    return;
  }
  delay(1000);

  Serial.println(F("Connecting..."));
  
  for(int i=0;i<10;i++)
  {
   pinMode(devices[i],OUTPUT); 
  }
  for(int i=0;i<4;i++){
    pinMode(window[i],INPUT);
    digitalWrite(window[i],LOW);
  }
  pinMode(pump,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(out_light,OUTPUT);
  
  pinMode(pir_sensor,INPUT);
  pinMode(light_sensor,INPUT);
  pinMode(flame_sensor,INPUT);
}
void loop(){
        //flame_sensor_read();
        light_sensor_read();
        temp_sensor_read();
        pir_sensor_read();
        water_ultrasonic();
        
        sendSensor();
        WindowRead();
        JsonRead();
        WaterRead();
}
