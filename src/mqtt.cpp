#include "model.h"
#include <Arduino_JSON.h>

void subscribe(char *topic, byte *payload, unsigned int length)
{
      char *cmd = new char[length + 1];
      memcpy((void *)cmd, payload, length);
      cmd[length] = '\0';

      JSONVar myObject = JSON.parse(cmd);
      if (JSON.typeof(myObject) == "undefined")
            return;

      if (myObject.hasOwnProperty("X"))
            model_U.Input[0] = (double)myObject["X"];
      else if (myObject.hasOwnProperty("Y"))
            model_U.Input[1] = (double)myObject["Y"];
      else if (myObject.hasOwnProperty("Z_UP"))
            model_U.Input[2] = (double)myObject["Z_UP"];

      else if (myObject.hasOwnProperty("Z_DOWN"))
            model_U.Input[2] = (double)myObject["Z_DOWN"];

      else if (myObject.hasOwnProperty("ROLL"))
            model_U.Input[3] = (double)myObject["ROLL"];

      else if (myObject.hasOwnProperty("PITCH"))
            model_U.Input[4] = (double)myObject["PITCH"];

      else if (myObject.hasOwnProperty("YAW"))
            model_U.Input[5] = (double)myObject["YAW"];
}

void connect() {
      
}