#define forward 10
#define reverse 11

void setup() {
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(forward,HIGH);
  digitalWrite(reverse,LOW);
  delay(2000);

  digitalWrite(forward,LOW);
  digitalWrite(reverse,HIGH);
  delay(2000);
}
