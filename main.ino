int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

void fw(){
   digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, HIGH);

}
void stp(){
  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, LOW);
}
void left(){
  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);  
}
    
void right(){
  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);  
  
}
void setup() {
  // put your setup code here, to run once:
   pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,   OUTPUT);
  pinMode(motor2pin2, OUTPUT);

}

void loop() {
   // put your main code here, to run repeatedly:
   
}
