#ifndef arduino-cs11
#define arduino-cs11

	#include "Arduino.h"
	#include "xCore.h"
	#include "Wire.h"

	#define debug(x) Serial.print(x)
	#define CS11_I2C_ADDRESS 0x04
	
	#define LED_RED 12
	#define LED_GREEN 13

	class xCS11
	{
		public:
			xCS11();
			void begin();
			bool log(String data);
			
			int success;
		
		private:
			bool pingSlave();
			bool testSlave();
		
	};

#endif