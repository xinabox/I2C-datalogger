//#define DEBUG  uncomment this line to show debug messages

#include "Wire.h"
#include "xCore.h"
#include "xSW01.h"
#define debug(x) Serial.print(x)
#define CS11_I2C_ADDRESS 0x04

#define LED_RED 12
#define LED_GREEN 13

xSW01 SW01;

String data;
float temp, press, hum;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;

const long interval = 10000;
const long interval1 = 300;

int success = 0;
void setup()
{
  Serial.begin(115200);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

#ifdef ESP8266
  Wire.pins(2, 14);
  Wire.setClockStretchLimit(15000);
#endif

  Wire.begin();
  SW01.begin();
  begin();
}

void loop()
{
  SW01.poll();
  
  temp = SW01.getTempC();
  press = SW01.getPressure() / 100.0;
  hum = SW01.getHumidity();
 
  data = String(temp) + "," + String(press) + "," + String(hum);

  if (success == 1)
  {
    logData(data);
  }

  delay(1000);
}


void begin()
{
  if (pingSlave())
  {
    if (testSlave())
    {
      debug("\nData Logger mode Successful.");
	  digitalWrite(LED_GREEN, HIGH);
      success = 1;
    }
    else
    {
      debug("\nFailed to test slave. Data logger mode disabled.");
      success = 0;
	  digitalWrite(LED_RED, HIGH);
    }
  }
  else
  {
    debug("\nFailed to ping slave. Data logger mode disabled.");
	digitalWrite(LED_RED, HIGH);
    success = 0;
  }
}

bool testSlave()
{
  Wire.beginTransmission(CS11_I2C_ADDRESS);
  for (uint8_t i = 0; i < 128; i++)
  {
    Wire.write(i);
  }
  if (Wire.endTransmission() != 0)
  {
#ifdef DEBUG
    debug("\nFailed to send test bytes to slave. Data Logger mode disabled.");
#endif
    return false;
  }
  Wire.requestFrom(CS11_I2C_ADDRESS, 1);
  if (Wire.available() == 1)
  {
    if (Wire.read() != 99)
    {
#ifdef DEBUG
      debug(
        "\nFailed to read test byte from slave. Data Logger mode disabled.");
#endif
      return false;
    }
  }
  return true;
}

bool pingSlave()
{
  debug("\nATTEMPTING TO PING SLAVE");
  uint32_t period = 10 * 2000L;
  for (uint32_t tStart = millis(); (millis() - tStart) < period;)
  {
    if (xCore.ping(CS11_I2C_ADDRESS))
    {
      return true;
    }
    else
    {
      debug(".");
      delay(250);
    }
  }
  return false;
}

bool logData(String data)
{
  uint16_t error_status;
#ifdef DEBUG
  debug("\nData record : ");
  debug(data);
#endif
  uint16_t data_size = strlen(data.c_str());
  debug("\nData size: ");
  debug(data_size);
  Wire.beginTransmission(CS11_I2C_ADDRESS);
  Wire.write('b');
  uint8_t k = (data_size >> 8) & 0xFF;
  uint8_t j = (uint8_t)data_size & 0xFF;
  Wire.write(k);
  Wire.write(j);
  error_status = Wire.endTransmission(false);
  if (error_status != 0)
  {
    return false;
  }

  for (uint16_t i = 0; i < data_size; i++)
  {
    Wire.beginTransmission(CS11_I2C_ADDRESS);
    Wire.write(data[i]);
    if (i == data_size)
      error_status = Wire.endTransmission(false);
    else
      error_status = Wire.endTransmission(true);
    if (error_status != 0)
    {
      return false;
    }
  }
  return true;
}
