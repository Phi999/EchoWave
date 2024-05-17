#include <RH_ASK.h>//libraria RadioHead, pentru modulul Wireles
#include <SPI.h>//librarie folosita de libraria RadioHead

RH_ASK rf_driver;//creaza o instanta a modulului wireles
//Pini pentru motoare

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;
//functii pentru controlarea fiecarui motor
void motor1(){
  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);
}
void motor1s(){
  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, LOW);
}
void motor1b(){
  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);
}

void motor2(){
  digitalWrite(motor2pin1,  HIGH);
  digitalWrite(motor2pin2, LOW);
}
void motor2s(){
  digitalWrite(motor2pin1,  LOW);
  digitalWrite(motor2pin2, LOW);
}
void motor2b(){
  digitalWrite(motor2pin1,  LOW);
  digitalWrite(motor2pin2, HIGH);
}
//functii pentru fata, spate, stanga, dreapta
void fw(){
  motor1();
  motor2();
}
void bw(){
  motor1b();
  motor2b();
}
void stp(){
  motor1s();
  motor2s();
}
void left(){
  motor1s();
  motor2();
}
    
void right(){
  motor1();
  motor2s();
}
void setup() {
  rf_driver.init();//intializam modulul wireles
  Serial.begin(9600);//folosim Serial port pentru debugging
  //setam pini motoarelor ca OUTPUT
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void handleDirection(char direction) {
//functia handledirection primeste un character si in functie de
//acel character ii spune barcii in ce directie sa mearga
  //Directii
  switch (direction) {
    case 'u':
      Serial.println("Moving Forward");
      //fata
      fw();
      break;
    case 'd':
      Serial.println("Moving Backwards");
      //spate
      bw();
      break;
    case 'l':
      Serial.println("Moving Left");
      //stanga
      left();
      break;
    case 'r':
      Serial.println("Moving Right");
      //dreapta
      right();
      break;
    default:
    //daca nu e nici una dintre cele de mai sus, barca se opreste
      Serial.println("STOP");
      stp();
  }
}

void loop() {

  uint8_t buf[2];//mesajul ce il voi primi
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {//daca primesc un mesaj 
    Serial.print("Message Received: ");
    //Afiseaza mesajul primit
    for (int i = 0; i < buflen; i++) {
      Serial.print((char)buf[i]);
    }
    Serial.println();
    handleDirection((char)buf[0]); //trimit prima litera a mesajului functiei handleDirection()

  }
  delay(200);//delay pentru a nu suprasolicita placa arduino
}
