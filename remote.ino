#include <Nunchuk.h>
#include <Wire.h> 
void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600); 
	   Wire.begin(); 
       //  Wire.setClock(400000);

	   nunchuk_init(); 


}

void loop() {
  // put your main code here, to run repeatedly:
  	   if (nunchuk_read()) { 
	       // Work with nunchuk_data 

	       int x =  nunchuk_joystickX();
         int y =  nunchuk_joystickY();
         int angle = nunchuk_joystick_angle();
         int pitch = nunchuk_pitch();
         int roll = nunchuk_roll();
         Serial.print(x);
         Serial.print(" ");
         Serial.print(y);
         Serial.print(" ");
         Serial.print(angle);
         Serial.print(" ");
         Serial.print(pitch);
         Serial.print(" ");
         Serial.println(roll);
	   } 
	   delay(10); 


}
