#ifndef MQTT_H
#define MQTT_H

void subscribe(char *topic, unsigned char *payload, unsigned int length);
void connect();

#endif