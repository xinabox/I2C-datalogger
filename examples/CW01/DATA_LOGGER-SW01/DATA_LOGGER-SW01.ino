#include <xCS11.h>
#include <xSW01.h>

String data;
float temp, press, hum;

xCS11 CS11;
xSW01 SW01;

void setup() {
  // put your setup code here, to run once:
  
  CS11.begin();
  SW01.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  temp = SW01.getTempC();
  press = SW01.getPressure() / 100;
  hum = SW01.getHumidity();
  data = String(temp) + "," + String(press) + "," + String(hum);
  
  CS11.log(data);

  delay(1000);

}