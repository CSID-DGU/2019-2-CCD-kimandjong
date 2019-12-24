// 속력 측정 아두이노 코드

#include <SoftwareSerial.h>
#define transistor1 A0
#define transistor2 A1
#define transistor3 A2 
#define TX 3 // 아두이노 SoftwareSerial RX(2) -> NodeMCU D6(TX)
#define RX 2 // 아두이노 SoftwareSerial TX(3) -> NodeMCU D7(RX)
//소프트웨어시리얼 설정
SoftwareSerial nodeSerial(RX,TX);

int val1 = 0; 
int val2 = 0; 
int val3 = 0; // 물체 감지 아날로그값 변수 설정
unsigned long start, time1, time2; // 물체가 발광부에 닿는 시간 변수 설정

void setup() {
    pinMode(transistor1, INPUT); 
    pinMode(transistor2, INPUT); 
    pinMode(transistor3, INPUT);
    // 아날로그 핀 설정
    Serial.begin(9600);
    nodeSerial.begin(9600);
    //시리얼 통신 설정
}

void loop() {
    val1 = analogRead(transistor1); 
    val2 = analogRead(transistor2); 
    val3 = analogRead(transistor3);
   
    if (val1 > 770){
     start = millis();
     }
 
    if (val2 > 770){
     time1 = millis();
     }
    
    if (val3 > 770){
     time2 = millis();
     }  
  
  if(val3 > 770){
    if(nodeSerial.available() > 0 )
   {
  nodeSerial.print(start);
  nodeSerial.print(" ");
  nodeSerial.print(time1);
  nodeSerial.print(" ");
  nodeSerial.print(time2);
  Serial.println(start);
  Serial.println(time1);
  Serial.println(time2);
    
  // NodeMCU, 시리얼 모니터(COM5)에 시간 데이터 전송
   }
  }   
  }
