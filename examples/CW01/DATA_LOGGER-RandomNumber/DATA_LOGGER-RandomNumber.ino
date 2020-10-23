#include <xCS11.h>

String data;
int randNum = 0;

xCS11 CS11;

void setup() {
  // put your setup code here, to run once:

  randomSeed(5);
  CS11.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  randNum = random(100);
  CS11.log(String(randNum));

  delay(1000);

}