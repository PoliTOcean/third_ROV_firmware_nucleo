#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <PubSubClient.h>

//A0 -> esc3

byte servoPin[7] = {A0, A2, D10, A4, A3, D9, D6};

byte servoPinA7 = PA2;

Servo servoA7;
Servo servo[7];

int i=0;
int valA7;
int val[7] = {1600, 1600, 1600, 1600, 1600, 1600, 1600};

int salita = 1;
int salitaA0 = 0;

// Enter a MAC address for your controller below.
byte mac[] = {
    0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04};

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);
const char *server = "10.0.0.254";
IPAddress ip_nucleo(10,0,0,3);
const int port = 1883;

void subscribeReceiveMotor(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Topic: ");
  Serial.println(topic);
  char *cmd = new char[length + 1];

  Serial.print("Message: ");
  memcpy((void *)cmd, payload, length);

  for (int i = 0; i < length; i++)
  {
    cmd[i] = ((char *)payload)[i];
  }
  cmd[length] = '\0';
 
  Serial.print(cmd);
  servoA7.writeMicroseconds(String(cmd).toInt());
  
  //newline
  Serial.println("");
}

/*void subscribeReceivePressure(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Topic: ");
  Serial.println(topic);
  char *cmd = new char[length + 1];

  Serial.print("Message: ");
  memcpy((void *)cmd, payload, length);

  /*for (int i = 0; i < length; i++)
  {
    cmd[i] = ((char *)payload)[i];
  }
  cmd[length] = '\0';

    Serial.print(cmd);
  
 

  //newline
  Serial.println("");
}*/

void setup() {
  
 Serial.begin(9600);

  Ethernet.init(D3); // SCSn pin

 for(int n= 0; n<7; n++){
servo[n].attach(servoPin[n]);
 servo[n].writeMicroseconds(1500); // send "stop" signal to ESC.
 }

   //start the Ethernet connection:
  Serial.println("Initialize Ethernet");
  Ethernet.begin(mac, ip_nucleo);
  /*{
    Serial.println("Failed to configure Ethernet using DHCP");*/
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    else if (Ethernet.linkStatus() == LinkOFF)
    {
      Serial.println("Ethernet cable is not connected.");
    }
    
  
  //print your local IP address:
  //Serial.print("My IP address: ");
  //Serial.println(Ethernet.localIP());

  mqttClient.setServer(server, port);
  if (mqttClient.connect("nucleo-L432KC"))
  {
    Serial.println("Connection has been established, well done");

    mqttClient.setCallback(subscribeReceiveMotor);
    //mqttClient.setCallback(subscribeReceivePressure);

    //subscribe to a specific topic in order to receive those messages
    mqttClient.subscribe("motor");
    //mqttClient.subscribe("pressure");
  }
  else
  {
    Serial.println("Looks like the server connection failed...");
  }

 servoA7.attach(servoPinA7);
 servoA7.writeMicroseconds(1500);
 


 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  if (mqttClient.connected()==false){
    //Serial.println("MQTT Broker connection is down");
    if (mqttClient.connect("nucleo-L432KC")) {
       //Serial.println("MQTT Broker Connection Restarted");
    }
  }
  //Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
  
  //while (Serial.available() == 0);
  
  //Serial.parseInt(); 
  //mqttClient.loop();
  
  for(int n=0; n<7; n++){
    //servo[n].writeMicroseconds(1600);
    //setPWM_Motor(servo[n], val[n], i);
  }
  //setPWM_Motor(servoA7, valA7, i);
  //delay(30);
  mqttClient.loop();
  delay(2000);
}


int setPWM_Motor(Servo servo, int val, int i){
  
  if(i==1){
    
    val = 1100;
  }
  if(i>1 && val <= 1900 && salita == 1){
    val +=5;  
    servo.writeMicroseconds(val);
    if(val >= 1900){
      salita = 0;
    }
  }
  else if(val >= 1100 && i>1 && salita ==0){
    val -=5;  
    servo.writeMicroseconds(val);
    if(val <= 1100){
      salita = 1;
    }
  }
  
  
  
  
  if(val < 1100 || val > 1900)
  {
    //Serial.println(val);
    //Serial.println("not valid");
  }
  else
  {
   // servo.writeMicroseconds(val); // Send signal to ESC.
  }



  
  i++;

  return i;
}
