/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/darwinwang/Documents/IoT/MQTT/src/MQTT.ino"
void displaySetup();
void setup();
void loop();
#line 1 "/Users/darwinwang/Documents/IoT/MQTT/src/MQTT.ino"
SYSTEM_THREAD(ENABLED)

#include "MQTT.h"
#include "oled-wing-adafruit.h"
#include <blynk.h>
OledWingAdafruit display;

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

BLYNK_WRITE(V0) {
  String message = param.asStr();
  client.publish("newnewtopic", message);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (String(p).equals("1"))
  {
    digitalWrite(D7, HIGH);
    Serial.println(p);
  }
  else if (String(p).equals("0"))
  {
    digitalWrite(D7, LOW);
    Serial.println(p);
  }
  else
  {
    Serial.println(p);
    displaySetup();
    display.println(p);
    display.display();
    delay(2000);
    displaySetup();
    display.display();
  }
}

void displaySetup()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
}

void setup()
{
  pinMode(D7, OUTPUT);
  
  Blynk.begin("jdQ99UP2k3XwKO_NYUc9wKdpvbn6yWEa", IPAddress(167, 172, 234, 162), 8080);
  
  Serial.begin(9600);
  while (!Serial.isConnected()){}
  Serial.println("Serial connected");

  display.setup();
  displaySetup();
  display.setTextColor(WHITE);
  display.println("DISPLAY CONNECTED");
  display.display();
  delay(2000);
  display.display();
  displaySetup();
  display.display();

  
}

void loop()
{
  if (client.isConnected())
  {
    client.subscribe("newtopic");
    display.loop(); 
    client.loop();
    Blynk.run();
    if (display.pressedA())
    {
      client.publish("newtopic", "Button A pressed on OLED display");
    }
    else if (display.pressedB())
    {
      client.publish("newtopic", "Button B pressed on OLED display");
    }
    else if (display.pressedC())
    {
      client.publish("newtopic", "Button C pressed on OLED display");
    }
    
    // client.publish("773DA6EE-0AD3-45FC-AEC1-19598E7F4466", "hello world");
  }
  else
  {
    client.connect(System.deviceID());
    client.publish("newtopic", "Argon Connected");
  }
}