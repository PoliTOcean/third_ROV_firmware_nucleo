#include "JsonHashTable.h"
#include "MQTTClient.h"
#include "Socket.h"
#include "SocketAddress.h"
#include "mbed.h"
#include "WIZnetInterface.h"
#include <cstdint>
#include "TCPSocket.h"
#include "MQTTClientMbedOs.h"
#include <cstdlib>
#include <memory>
#include "nsapi_types.h"
#include "cmsis_os2.h"
#include "JsonParser.h"

#define trytodelete 

//uint8_t mac = 0X2c549188c9e3;
unsigned short  int port = 1883;
MQTTPacket_connectData mqttSes = MQTTPacket_connectData_initializer;
SocketAddress sock;

int main()
{
    printf("Begin: \n");
    WIZnetInterface eth(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, SPI_RESET);
    printf("1");
    eth.init();
    printf(" 2");
    int result = eth.connect();
    sock.set_ip_address("192.168.0.5"); //Broker's IP
    sock.set_port(port);
    
    SocketAddress a;

    TCPSocket socket;

    MQTTClient client(&socket);
    socket.open(&eth);
    nsapi_error_t res = socket.connect(sock);

    printf("3");

    if(res == 0)
        printf("Connesso al socket del broker\n");
    else
        printf("Impossibile connettersi al socket del broker\n");


    res = client.connect(mqttSes);

    if(client.isConnected())
        printf("Client connesso al broker\n");
    else
        printf("Impossibile connettere il client al broker\n");

    client.subscribe("Temperature", MQTT::QOS1, [](MQTT::MessageData &md){  
        JsonParser<32> parser;
        MQTT::Message &message = md.message;

        //allocation of message buffer
        char *payload = (char *)malloc(message.payloadlen + 1);
        if(payload == NULL){
            printf("Error allocating message buffer\n");
            return;
        }

        //filling of message buffer with payload received
        for(int i=0; i<message.payloadlen; i++){
            payload[i] = ((char *)message.payload)[i];
        }
        payload[message.payloadlen] = '\0';  //terminating correctly message buffer for parseHashTable()

        JsonHashTable hashTable = parser.parseHashTable(payload);
        if (!hashTable.success()){
            printf("Error on parsing Json\n");
        }
        else {
            printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
            printf("Payload MQTT:%.*s\r\n", message.payloadlen, hashTable.getString("value"));
        }
    });

    /*MQTT::Message MSG;
    MSG.qos = MQTT::QOS1;
    MSG.retained = 0;
    MSG.dup = 0;
    char greeting[] = "CIao";              
    MSG.payload = &greeting;
    MSG.payloadlen = sizeof(greeting);      
    MSG.id = 0;            

    client.publish("Temperature", MSG);*/

    printf("%d\n", res);
    client.yield(10000);
    osDelay(5000);
    printf("Disconnecting...\n");
    client.disconnect();
    socket.close();
    eth.disconnect();
    printf("Done\n");

}

