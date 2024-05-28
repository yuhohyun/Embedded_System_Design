#define X_PIN A0  // PD0
#define Y_PIN A1  // PD1
#define SW 2
#define motor 13

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP); // 16
  pinMode(X_PIN,INPUT);
  pinMode(Y_PIN,INPUT);
  pinMode(motor,OUTPUT);
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

  int value = analogRead(X_PIN);
  int speed;
  
  if(value > 519){
    speed = value - 519;  
  }
  else{
    speed = abs(speed);
  }
    
  analogWrite(motor,speed);
  delay(300);
}
