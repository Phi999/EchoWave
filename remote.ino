#include <RH_ASK.h> //libraria RadioHead, pentru modulul Wireles
#include <SPI.h>//librarie folosita de libraria RadioHead
#include <Nunchuk.h>//librarie folosite pentru comunicarea cu joystickul
#include <Wire.h>//librarie folosita de Nunchuck.h
RH_ASK rf_driver; //initializam modulul wireles
int normalx = 0; //valoare x a joysticului in stadiu de repaus
int normaly = 0;//valoare y a joysticului in stadiu de repaus
int step = 50; //valoare minima pentru ca barca sa mearga - sensitivitatea
void setup() {
  Serial.begin(9600);//folosim Serial port pentru debugging

  rf_driver.init();//intializam modulul wireles
  Wire.begin();
  //initializam controlerul
  nunchuk_init();
}

void loop() {
  if (nunchuk_read()) {//cand primit date de la joystick
    // nunchuck_data - date de la joystick
    //printam pentru debuging
    nunchuk_print();
    int xValue = nunchuk_joystickX();
    int yValue = nunchuk_joystickY();
    //Preia datele de la joystick si le trimite prin radio
    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print(", y = ");
    Serial.println(yValue);
    //calculez comanda in functie de variabilele normalx, normaly si step
    const char *msg = "no";
    if (yValue > normalx + step) {
      msg = "up";//in fata
    }
    if (yValue < normalx - step) {
      msg = "dw";//in spate
    }
    if (xValue < normaly - step) {
      msg = "lt";//stanga

    }
    if (xValue > normaly + step) {
      msg = "rt";//dreapta

    }
    Serial.println(msg);
    //trimit comanda
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
  }
  //delay de 10 milisecunde pentru a nu suprasolicita placuta
  delay(10);
}
