//기울기 + 피에조 + 온도

int tilt = 13;
int Buzzer = 3;
int potpin = A0;
int tmp = 0;

void setup(){

  Serial.begin(9600);
  pinMode(Buzzer,OUTPUT);
  pinMode(tilt,INPUT);
}

void loop(){
  //온도
  int val = analogRead(potpin);
  tmp = (val-20)/10;
  if (26 < tmp) {
    Serial.println("on ");
    Serial.println(tmp);
    digitalWrite(Buzzer, HIGH);
    delay(100);
  }
  else {
    Serial.println("off ");
    Serial.println(tmp);
    digitalWrite(Buzzer, LOW);
    delay(100);
  }

  //기울기
  if(digitalRead(tilt)==LOW){
    Serial.println("1");
    analogWrite(Buzzer, 32);
    delay(960);
  }else{
    Serial.println("0");
    digitalWrite(Buzzer, LOW);
    delay(960);
  }
    
}
