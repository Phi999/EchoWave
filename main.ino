#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;//creaza o instanta a radioului
//Pini pentru motoare
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;
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
  rf_driver.init();
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void handleDirection(char direction) {
  //Directii
  switch (direction) {
    case 'u':
      Serial.println("Moving Forward");
      fw();
      break;
    case 'd':
      Serial.println("Moving Backwards");
      bw();
      break;
    case 'l':
      Serial.println("Moving Left");
        tone(8, 3000, 250);
        delay(200);
        noTone(8);
      left();
      break;
    case 'r':
      Serial.println("Moving Right");
        tone(8, 4000, 250);
        delay(200);
        noTone(8);
      right();
      break;
    default:
      Serial.println("STOP");
      stp();
  }
}

void loop() {
  uint8_t buf[2];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {
    Serial.print("Message Received: ");
    //Afiseaza mesajul primit
    for (int i = 0; i < buflen; i++) {
      Serial.print((char)buf[i]);
    }
    Serial.println();
    handleDirection((char)buf[0]); 
  }
  delay(200);
}
