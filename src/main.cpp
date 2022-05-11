#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <PubSubClient.h>
#include "mqtt.h"

extern "C"
{
#include "model.h"
}

Servo servo[8];

unsigned char servoPin[7] = {PA5, PA3, PA4, PA11, PA0, PA2, PB1},
              servoPinA7 = PA8;

unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04};
IPAddress addr(10, 0, 0, 3);

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

const char *server = "10.0.0.254";
const int port = 1883;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  Ethernet.init(D3); // SCSn pin

  int i;
  for (i = 0; i < 7; i++)
  {
    servo[i].attach(servoPin[i]);
    servo[i].writeMicroseconds(1500); // send "stop" signal to ESC.
  }
  servo[i].attach(servoPinA7);
  servo[i].writeMicroseconds(1500);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet");
  Ethernet.begin(mac, addr);
  /*{
    Serial.println("Failed to configure Ethernet using DHCP");*/
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
  else if (Ethernet.linkStatus() == LinkOFF)
    Serial.println("Ethernet cable is not connected.");

  // print your local IP address:
  // Serial.print("My IP address: ");
  // Serial.println(Ethernet.localIP());

  mqttClient.setServer(server, port);
  if (mqttClient.connect("nucleo-L432KC"))
  {
    Serial.println("Connection has been established, well done");

    mqttClient.setCallback(subscribe);

    // subscribe to a specific topic in order to receive those messages
    mqttClient.subscribe("axes/");
  }
  else
    Serial.println("Looks like the server connection failed...");

  model_initialize();

  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (mqttClient.connected() == false)
    // Serial.println("MQTT Broker connection is down");
    if (mqttClient.connect("nucleo-L432KC"))
    {
      // Serial.println("MQTT Broker Connection Restarted");
      mqttClient.setCallback(subscribe);
      // mqttClient.setCallback(subscribeReceivePressure);

      // subscribe to a specific topic in order to receive those messages
      mqttClient.subscribe("motor");
    }
  // Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");

  // while (Serial.available() == 0);

  // Serial.parseInt();
  // mqttClient.loop();
  model_step();

  for (int i = 0; i < 8; i++)
    servo[i].writeMicroseconds(model_Y.Output[i]);

  // setPWM_Motor(servoA7, valA7, i);
  // delay(30);
  mqttClient.loop();
  delay(2000);
}