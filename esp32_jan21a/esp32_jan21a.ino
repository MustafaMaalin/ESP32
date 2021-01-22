#include  "DHTesp.h"

#define DHTpin 15 // nr 15 of the esp32 

DHTesp dht;

void setup(){
  Serial.begin(115200);
  Serial.printIn();
  Serial.printIN("Status\tHumdidty(C)\t(F)tHeatIndex(C)\t(F)");
}
