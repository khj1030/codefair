// 조이스틱+아두이노+매트릭스+서보모터+블루투스(비밀번호 구현)
#include "LedControl.h"
#include<Servo.h>
#include <SoftwareSerial.h>

int Buzzer = 4;
#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

int tempo = 200; // duration 옵션 값 설정 
int notes[25] = { E,G,B }; 
int notes2[25] = {B};

SoftwareSerial bluetooth(8, 9); // 8번 TX, 9번 RX
Servo servo;      
int value = 0; 
LedControl lc = LedControl(12, 11, 10, 1);
int xpin = A0;
int ypin = A1;

char key;
char* secretCode = "0123";  //비밀번호 설정
char password[10];
int position = 0; 
int wrong = 0;
int complete = 0;

byte space[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
byte up[8] = { B00010000, B00111000, B01010100, B00010000, B00010000, B00010000, B00010000, B00010000};//위
byte right[8] ={B00000000,B00000100,B00000010,B11111111,B00000010,B00000100,B00000000,B00000000};//오른쪽
byte down[8] = { B00010000, B00010000, B00010000, B00010000, B00010000, B01010100, B00111000, B00010000};//아래
byte left[8] ={B00000000,B00100000,B01000000,B11111111,B01000000,B00100000,B00000000,B00000000};//왼쪽
byte o[8] = {B00000000, B00111100, B01000010,  B01000010,  B01000010,  B01000010,  B00111100};
byte x[8] = {B00000000, B01000010, B00100100, B00011000, B00011000,B00100100, B01000010};

void setup(){
   pinMode(Buzzer,OUTPUT);
  bluetooth.begin(9600);
  servo.attach(7);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(3,INPUT_PULLUP);
  digitalWrite(3,HIGH);
  Serial.begin(9600);  
}

void loop(){
  char val = bluetooth.read();
  int xval = analogRead(xpin);
  int yval = analogRead(ypin);
  int buttonpressed = digitalRead(3);

  if(val == 'a')
  {
     servo.write(20);
  }
  if(val == 'b')
  {
     servo.write(120);
  }


  if (buttonpressed == 0){
     servo.write(20);
  }
  if(yval >= 800){ //위 //왼
    for (int row = 0; row < 8; row++){
      lc.setRow(0, row, up[row]);
      delay(25);
    }
    key = '3'; //3
  }
  else if (yval <=250){ //아래 //오
    for (int row = 0; row < 8; row++){
      lc.setRow(0, row, down[row]);
      delay(25);
    }
    key = '1';   //1
  }
  else if (xval >= 800){ //왼쪽 //아래
    for (int row = 0; row < 8; row++){
      lc.setRow(0, row, left[row]);
      delay(25);
    }
    key = '2';   //2
  }
  else if (xval <= 250) { //오른쪽 //위
    for (int row = 0; row < 8; row++){
      lc.setRow(0, row, right[row]);
      delay(25);
    }
    key = '0';  //0
  }
  else {
    key = '~'; 
  }
  if((key >= '0' && key <= '3')){
    if(key == '~'){
      position = position;
    }
    else if(key == secretCode[position]){ // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
    }
    
    else if(key != secretCode[position]){ // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
      position++; /**********/
      wrong++; // 비밀번호 오류 값을 늘려준다
      
    }
 
    if(position == 4){ // 4자리 비밀번호가 모두 맞았을 경우
      if(wrong != 0) {
        for (int row = 0; row < 8; row++){
          lc.setRow(0, row, x[row]);
          delay(25);
        }
        tone (Buzzer, notes[ 0 ], tempo); 
        delay(300); 
      } 
      else {
        for (int row = 0; row < 8; row++){
          lc.setRow(0, row, o[row]);
          delay(25);
        }
        servo.write(120);
        for (int i = 0; i < 3; i++) { 
          tone (Buzzer, notes[ i ], tempo); 
          delay(300); 
        }
      } 
      position = 0;
      wrong =0;
      delay(1000);
      for (int row = 0; row < 8; row++){
          lc.setRow(0, row, space[row]);
          delay(25);
      }
    }
  
    delay(1000);

  }
}
