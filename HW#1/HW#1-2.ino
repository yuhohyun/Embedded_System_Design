const int Green_Button = 2; // Green LED 스위치 = pin 2
const int Blue_Button = 4;// Blue LED 스위치 = pin 4
const int Red_Button = 7;// Red LED 스위치 = pin 7
const int Green_LED = 8;// Green LED = pin 8
const int Blue_LED = 12;// Blue LED = pin 12
const int Red_LED = 13;// Red LED = pin 13
boolean current_GB_State = 0; // 현재 Green LED 버튼이 눌린 상태인지 아닌지를 판단하는 변수 -> 0으로 초기화
boolean current_BB_State = 0;// 현재 Blue LED 버튼이 눌린 상태인지 아닌지를 판단하는 변수 -> 0으로 초기화
boolean current_RB_State = 0;// 현재 Red LED 버튼이 눌린 상태인지 아닌지를 판단하는 변수 -> 0으로 초기화
boolean last_GB_State = 0; // 현재 버튼의 값(current_GB_State)을 받는 변수
boolean last_BB_State = 0;// 현재 버튼의 값(current_BB_State)을 받는 변수
boolean last_RB_State = 0;// 현재 버튼의 값(current_RB_State)을 받는 변수
boolean Green_State = false; 
boolean Blue_State = false; 
boolean Red_State = false; 

void setup()
{
  pinMode(Green_Button, INPUT);// Green_Button을 입력 핀으로 정의
  pinMode(Blue_Button, INPUT);// Blue_Button을 입력 핀으로 정의
  pinMode(Red_Button, INPUT);// Red_Button을 입력 핀으로 정의
  pinMode(Green_LED, OUTPUT);// Green_LED를 출력 핀으로 정의
  pinMode(Blue_LED, OUTPUT);// Blue_LED를 출력 핀으로 정의
  pinMode(Red_LED, OUTPUT);// Red_LED를 출력 핀으로 정의
}

void loop()
{
  // Green_Button의 상태값을 읽어와 current_GB_State 변수에 저장
  current_GB_State = digitalRead(Green_Button); 

  // 버튼이 눌렸는지 상태를 판단
  if (last_GB_State == LOW && current_GB_State == HIGH){
    Green_State =! Green_State; // 변수 Green_State의 상태를 이전과 반대 상태로 변환
  }
    // 현재 Green Button의 상태값을 last_GB_State 변수에 저장해준다.
    last_GB_State = current_GB_State; 

    // Green_State 변수의 상태에 따라 Green_LED를 점등한다.
    digitalWrite(Green_LED,Green_State);
    delay(100);
    
  // Blue_Button의 상태값을 읽어와 current_BB_State 변수에 저장
  current_BB_State = digitalRead(Blue_Button);//Read button1 state

  // 버튼이 눌렸는지 상태를 판단
  if (last_BB_State == LOW && current_BB_State == HIGH){
    Blue_State =! Blue_State; // 변수 Blue_State의 상태를 이전과 반대 상태로 변환
  }
    // 현재 Blue Button의 상태값을 last_BB_State 변수에 저장해준다.
    last_BB_State = current_BB_State;

    // Blue_State 변수의 상태에 따라 Blue_LED를 점등한다.
    digitalWrite(Blue_LED,Blue_State);
    delay(100);

  // Red_Button의 상태값을 읽어와 current_RB_State 변수에 저장
  current_RB_State = digitalRead(Red_Button);//Read button1 state

  // 버튼이 눌렸는지 상태를 판단
  if (last_RB_State == LOW && current_RB_State == HIGH){
    Red_State =! Red_State; // 변수 Red_State의 상태를 이전과 반대 상태로 변환
  }
    // 현재 Red Button의 상태값을 last_RB_State 변수에 저장해준다.
    last_RB_State = current_RB_State;

    // Red_State 변수의 상태에 따라 Red_LED를 점등한다.
    digitalWrite(Red_LED,Red_State);
    delay(100);
}
