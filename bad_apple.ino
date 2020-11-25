#include "U8glib.h"

U8GLIB_PCF8812 u8g(13, 11, 10, 9, 8);
uint8_t frame_buffer[704] = {0};

void setup()
{
	Serial.begin(1000000);
	Serial.setTimeout(1000);
}

void loop()
{
	if (Serial.available())
	{
		for (uint16_t frame = 0; frame < 6572; frame++)
		{
			for (uint16_t shift = 0; shift < 704; shift+=44)
			{
				Serial.readBytes(frame_buffer+shift, 44);
				Serial.write(0xFF);
			}
			u8g.firstPage();
			do
			{		
				u8g.drawBitmap(6, 0, 11, 64, frame_buffer);
			}
			while (u8g.nextPage());
		}
	}
}
