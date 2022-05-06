#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <PubSubClient.h>
#include <Arduino_JSON>

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
float u[6] = {0};
float t[8] = {0};

// Constant parameters (default storage)
const double gain[48] =   { 0.33299667313036063, 0.37393307874758769, 0.37411010805618666,
                            0.33317370243895972, 0.036960629992566246, 0.03719100454601746,
                            -0.037106306603676947, -0.037045327934906641, 1.0950664274301052,
                            -1.0886807026437848, -0.38795964624355667, 0.38157392145723612,
                            0.061208141578512218, -0.061346831213904988, 0.061105829455647465,
                            -0.060967139820254646, -5.7367847451639253E-17, -2.6224140046993138E-17,
                            1.1064283170214573E-16, 1.1785277614917433E-16, 0.2623166854207124,
                            0.23936151405332984, 0.26059528123896658, 0.23772651928699146,
                            -2.4633073358870661E-16, -1.43982048506075E-16, 1.8735013540549517E-16,
                            2.0990154059319366E-16, 1.8570431304160009, -1.8612509470238192,
                            1.8539390004747502, -1.8497311838669304, 5.7782554782614959E-16,
                            -9.893344823930228E-17, -5.3697823097775821E-16, 4.809791887688819E-17,
                            -1.1213783371531021, -1.1283678563718882, 1.1257981372474815,
                            1.1239480562775086, 3.2157555671353864, -3.1880622846013362,
                            -3.2157555671353832, 3.1880622846013331, 1.3392065234540951E-15,
                            1.97758476261356E-16, -6.6266436782314031E-16, 1.1796119636642288E-16 };

void step()
{
  // Outport: '<Root>/t' incorporates:
  //   Gain: '<Root>/Gain2'
  //   Inport: '<Root>/u'

  for (int16_T i{0}; i < 8; i++) {
    t[i] = 0.0;
    for (int16_T i_0{0}; i_0 < 6; i_0++) {
      t[i] += gain[(i_0 << 3) + i] * u[i_0];
    }
  }

  // End of Outport: '<Root>/t'
}

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

  JSONVar myObject = JSON.parse(cmd);
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  Serial.println((float)myObject["X"]);
  u[0] = (float)myObject["X"];
  u[1] = (float)myObject["Y"];
  u[2] += (float)myObject["Z_UP"];
  u[2] -= (float)myObject["Z_DOWN"];
  u[3] = (float)myObject["ROLL"];
  u[4] = (float)myObject["PITCH"];
  u[5] = (float)myObject["YAW"];
 
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
    mqttClient.subscribe("axes/");
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
       mqttClient.setCallback(subscribeReceiveMotor);
    //mqttClient.setCallback(subscribeReceivePressure);

    //subscribe to a specific topic in order to receive those messages
    mqttClient.subscribe("motor");
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
