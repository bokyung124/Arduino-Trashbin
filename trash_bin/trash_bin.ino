#include <DFPlayer_Mini_Mp3.h>
#include <Servo.h>
#include <SoftwareSerial.h>


//초음파 센서 핀설정
int trig01Pin = 9;// 쓰레기
int echo01Pin = 8;
int trig02Pin = 5;// 사람
int echo02Pin = 4;
long echo_time01 = 0;// 쓰레기
long echo_time02 = 0;// 사람

// 서보모터
//Servo myservo01;//팔
Servo myservo02;//압축
float duration01, distance01;// 쓰레기
float duration02, distance02;// 사람

void setup () {
    Serial.begin (9600);
    mp3_set_serial (Serial);     // DFPlayer-mini mp3 module 시리얼 세팅
    delay(1);                     // 볼륨을 Setup 하기 위한 delay
    mp3_set_volume (10);          // 볼륨 0~30
     
    // 초음파 센서 핀설정
    pinMode(trig01Pin, OUTPUT);
    pinMode(echo01Pin, INPUT);
    pinMode(trig02Pin, OUTPUT);
    pinMode(echo02Pin, INPUT);

   // myservo01.attach();
    myservo02.attach(10);
}


void loop () {

 us_distance01();
 us_distance02(); 
 
  if(distance02 < 50) // 장애물이 50cm 이내일 때
  { mp3_play(0001); // 안녕하세요
    delay(3000);
  }
     if(distance02 < 50) // 장애물이 50cm 이내일 때
     {  
        mp3_play(0002); // 일반쓰레기만 버려주세요
        delay(4000);   
        mp3_play(0003); // 칭찬해주기
        delay(4000);
    }
  
if(distance01 < 3){
    myservo02.write(125);
    delay(1500);
    myservo02.write(179);
  }
  
}

void us_distance01(){ // 쓰레기 거리 측정함수

  digitalWrite(trig01Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig01Pin, LOW);
  echo_time01 = pulseIn(echo01Pin, HIGH); // 반사되어 돌아온 초음파의 왕복 시간값
  distance01 = echo_time01/29/2;  // cm 단위로 변환 : distance = echo_time/29/2
  Serial.print(distance01);
  Serial.println(" cm ");  
}

void us_distance02(){ // 사람 거리 측정함수

  digitalWrite(trig02Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig02Pin, LOW);
  echo_time02 = pulseIn(echo02Pin, HIGH); // 반사되어 돌아온 초음파의 왕복 시간값
  distance02 = echo_time02/29/2;  // cm 단위로 변환 : distance = echo_time/29/2

  Serial.print(distance02);
  Serial.println(" cm ");  
}
