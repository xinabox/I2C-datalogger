#include <xCS11.h>


xCS11 CS11;

void setup() {
  // put your setup code here, to run once:

  CS11.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  CS11.log("Hello World!");

  delay(1000);

}