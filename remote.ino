#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;
int normalx = 350;
int normaly = 350;
int step = 70;
void setup() {
  Serial.begin(9600);

  // Initialize ASK Object
  rf_driver.init();
}

void loop() {
  delay(200);
  int xValue = analogRead(A5);
  int yValue = analogRead(A4);
  //Preia datele de la joystick si le trimite prin radio
    Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  const char *msg = "no";
  if(xValue > normalx + step){
    msg = "up";
  }
  if(xValue < normalx - step){
    msg = "dw";
  } 
  if(yValue < normaly-step)
  {
  msg = "lt";
  tone(8, 3600, 250);
  delay(200);
  noTone(8);
  
  }
  if(yValue > normaly+step){
    msg = "rt";
          tone(8, 3000, 250);
      delay(200);
          noTone(8);
  }
  Serial.println(msg);
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
}
