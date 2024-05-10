#include <RH_ASK.h>
#include <SPI.h>
#include <Nunchuk.h>
#include <Wire.h>
RH_ASK rf_driver;
int normalx = 0;
int normaly = 0;
int step = 50;
void setup() {
  Serial.begin(9600);

  // Initialize ASK Object
  rf_driver.init();
  Wire.begin();
  //  Wire.setClock(400000);

  nunchuk_init();
}

void loop() {
  if (nunchuk_read()) {
    // Work with nunchuk_data
    nunchuk_print();
    int xValue = nunchuk_joystickX();
    int yValue = nunchuk_joystickY();
    //Preia datele de la joystick si le trimite prin radio
    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print(", y = ");
    Serial.println(yValue);
    const char *msg = "no";
    if (yValue > normalx + step) {
      msg = "up";
    }
    if (yValue < normalx - step) {
      msg = "dw";
    }
    if (xValue < normaly - step) {
      msg = "lt";

    }
    if (xValue > normaly + step) {
      msg = "rt";

    }
    Serial.println(msg);
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
  }
  delay(10);
}
