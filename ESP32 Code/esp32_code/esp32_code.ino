#include <HTTPClient.h>
#include <WiFi.h>

#define sensor_pin 33
#define led_pin 13

const char* ssid     = "oneplus6";
const char* password = "hello123";

int sensor_value;
int led_state = 0;

void setup(){

  pinMode(sensor_pin, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wifi Successfully");

}

void loop(){

  sensor_value = digitalRead(sensor_pin);
  
  Serial.print("Sensor Reading Value: ");
  Serial.println(sensor_value);
  
  if (led_state){
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }
 
  send_sensor_value(sensor_value);
  get_led_state();
  
  delay(1000);

}

void send_sensor_value(int sensor_data){
  
  HTTPClient http;
//  http.begin("http://simple-iot-node-backend.herokuapp.com/sensordata");
  http.begin("http://192.168.43.122:3000/sensordata");
  http.addHeader("Content-Type", "application/json");
  
  String request = "{\"sensor_value\":\"" + (String)(sensor_data) + "\"}";

  int http_response_code = http.POST(request);
  
  if (http_response_code < 0){
    Serial.println("Error in sending sensor value");
  }
  else{
    String response = http.getString();
    Serial.print("Response (/sensordata): ");
    Serial.println(response);
  }
  http.end();
}

void get_led_state(){
  
  HTTPClient http;
  
//  http.begin("http://simple-iot-node-backend.herokuapp.com/ledstate");
  http.begin("http://192.168.43.122:3000/ledstate");
  http.addHeader("Content-Type", "text/plain");
  
  int http_response_code = http.GET();
  
  if (http_response_code < 0){
    Serial.println("Error in getting LED State");
  }
  else{
    String response = http.getString();
    Serial.print("Response (/ledstate): ");
    Serial.println(response);
    led_state = response.toInt();
  }
  
  http.end();
}
