#include <NewPing.h>

#define SONAR_NUM 1 // 초음파 센서 1개    
#define MAX_DISTANCE 150 // 최대 인식 거리

#define Front 0

#define TRIG 2  //  1번 초음파 센서 Trig 핀 번호
#define ECHO 3  //  1번 초음파 센서 Echo 핀 번호

NewPing sonar[SONAR_NUM] = {  
  NewPing(TRIG, ECHO, MAX_DISTANCE)
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // 내장 LED 사용
  Serial.begin(115200); // 통신 속도를 115200으로 정의
}

long sonar_front(void) {
  long duration, distance;

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = ((float)(340 * duration) / 1000) / 2;
  
  return distance;
}

void loop() {
  float front_sonar = 0.0;  // 거리 초기화

  front_sonar = sonar[Front].ping_cm()*10;  //  단위를 mm으로 변경
  if(front_sonar == 0.0)  front_sonar = MAX_DISTANCE;
   
  Serial.print("Distance: ");
  Serial.print(front_sonar);  //   거리 출력
  Serial.println("mm");

  if((front_sonar > 0) && (front_sonar <= 200.0)){  // 200mm보다 가까우면 LED 켜짐, 멀어지면 LED 꺼짐
    digitalWrite(LED_BUILTIN, HIGH);   // LED 켜짐
    delay(1000);  //  1초동안 켜짐
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);    // LED 꺼짐
    delay(1000);  //  1초동안 꺼짐
  }
}
