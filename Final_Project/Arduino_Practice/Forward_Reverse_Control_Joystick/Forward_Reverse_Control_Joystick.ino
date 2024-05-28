#define X_PIN A0  // PD0
#define Y_PIN A1  // PD1
#define SW 2
#define forward 12
#define reverse 13

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP); // 16
  pinMode(X_PIN,INPUT);
  pinMode(Y_PIN,INPUT);
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
}

void loop() {
  //X축 값 출력
  Serial.print("X : ");
  Serial.print(analogRead(X_PIN));
  Serial.print(" ");

  //Y축 값 출력
  Serial.print("Y : ");
  Serial.print(analogRead(Y_PIN));
  Serial.print(" ");

  //SW 값 출력
  Serial.print("SW : ");
  Serial.println(digitalRead(SW));
  Serial.print(" ");

  int X_value = analogRead(X_PIN);

  if(X_value > 530){
    digitalWrite(forward,HIGH);
    digitalWrite(reverse,LOW);
  }
  else if(X_value <508){
    digitalWrite(forward,LOW);
    digitalWrite(reverse,HIGH);
  }
  else{
    digitalWrite(forward,LOW);
    digitalWrite(reverse,LOW);
  }
}
