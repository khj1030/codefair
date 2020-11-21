//초음파+조도

int trig = 8;
int echo = 9;
int distance_led = 3;
int light_led=2;
int cds = A0;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(distance_led, OUTPUT);
  pinMode(light_led, OUTPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  unsigned long duration = pulseIn(echo, HIGH);
  int cdsValue = analogRead(cds);
  float distance = duration / 29.0 / 2.0;
 
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("cds =  ");
  Serial.println(cdsValue);
  if (distance < 10) {
    digitalWrite(distance_led, HIGH);
  }
  else {
    digitalWrite(distance_led, LOW);
  }
   if (cdsValue < 700) {
    digitalWrite(light_led,50);
    Serial.println("LED ON");
   }
  else {
    digitalWrite(light_led, LOW);
    Serial.println("LED OFF");
  }
  delay(500);
}
