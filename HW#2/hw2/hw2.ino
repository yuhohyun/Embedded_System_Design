const int Ain = A0; // Ain: A0 핀
const int IN1 = 3; // IN1: 3번 핀
unsigned long distance;

void setup() {
    pinMode(IN1,OUTPUT); // IN1을 출력 핀으로 이용
    pinMode(10,OUTPUT); // 10번 핀을 출력핀으로 설정(초음파센서 TRIG핀)
    pinMode(11,INPUT_PULLUP); // 11번 핀을 PULLUP저항이 사용된 입력핀으로 설정(초음파센서 ECHO핀)
    Serial.begin(9600); // Serial 통신의 초당 전송 속도를 9600비트로 설정함.
}

void loop() {
  unsigned long Width;
  int value = analogRead(Ain); // Ain 핀에 입력된 아날로그 값을 읽음.
  
  digitalWrite(10,HIGH); // 10번핀의 디지털 출력을 HIGH로 설정하여 초음파를 보냄
  delayMicroseconds(10); // 10μs간 대기
  digitalWrite(10,LOW); // 10번핀의 디지털 출력을 LOW로 설정하여 초음파를 보내는 것을 종료함.

  Width = pulseIn(11,HIGH); // 11번 핀에서 HIGH신호가 입력될 때까지의 시간을 측정하여 Width변수에 저장
      // 초음파가 물체에 반사되고 돌아오는 시간을 나타냄.
  distance = Width / 58; // 변수 Width값을 초음파가 이동하는 거리로 변환하여 distance 변수에 저장
     //초음파는 1츠를 이동하는데 약 58μs가 소요되므로 58로 나눔.

  Serial.print("Distance = "); // 거리값을 시리얼 모니터에 출력함.
  Serial.print(distance);
  Serial.println("cm");

  if(distance<10){ // 거리가 10cm보다 가까워지면(작으면)
    analogWrite(IN1,value*0.5); // IN1 핀에 value 아날로그 값에 0.5를 곱한 값을 출력
  }
  else{ // 아니면
    analogWrite(IN1,value); // IN1 핀에 value 아날로그 값을 출력
  }
}
