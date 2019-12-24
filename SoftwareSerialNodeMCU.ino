#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//웹서버 클라이언트 설정

#include <SoftwareSerial.h> 
#define TX D6 // arduino softSerial RX -> NodeMcu D6(TX)
#define RX D7 // arduino softSerial TX -> NodeMcu D7(RX) 
SoftwareSerial arduSerial(RX, TX); // (RX, TX)
//소프트웨어시리얼 설정

#ifndef APSSID
#define APSSID "MechEnergyTest"
#endif

const char* ssid = APSSID;
String income_wifi="";
int timevalue[256][3];
// 시간변수 저장 배열 설정
 
ESP8266WebServer server(80);

void sendHeader();

//html javascript table set
void handleRoot() {
  String html="";
  
  String temp = "<!DOCTYPE html>";
  html = html + temp;
  temp = "<meta charset=\"UTF-8\">";
  html = html + temp;
  temp = "<head>";
  html = html + temp;
  temp = "<title>실험결과</title>";
  html = html + temp;
  temp = "</head>";
  html = html + temp;
  
  temp = "<body>";
  html = html + temp;
  temp = "<br>";
  html = html + temp;
  temp = "<table border=\"1\"  width =\"800\" height=\"200\" align = \"center\" >";
  html = html + temp;
  temp = "<caption>실험 결괏값</caption>";
  html = html + temp;
  temp = "<tr align = \"center\" bgcolor=\"skybule\">";
  html = html + temp;
  temp = "<td></td>";
  html = html + temp;
  temp = "<td></td>";
  html = html + temp;
  temp = "<td>V1,V2</td>";
  html = html + temp;
  temp = "<td>Ep=mgh</td>";
  html = html + temp;
  temp = "<td>Ek=1/2 mv^2</td>";
  html = html + temp;
  temp = "<td>Emech=Ep+Ek</td>";
  html = html + temp;
  temp = "<td>Emech 평균</td>";
  html = html + temp;
  temp = "<td>오차율(%)</td>";
  html = html + temp;
  temp = "</tr>";
  html = html + temp;

    for(int i = 0 ; i <5; i++){

      double T1 = (timevalue[i][1]-timevalue[i][0])/1000.0;
      double T2 = (timevalue[i][2]-timevalue[i][0])/1000.0;
      double V1 = (0.35 / T1)*2;
      double V2 = (0.55 / T2)*2;

      double g = 9.8;
      double m = 0.032;
      double height1 = 0.55;
      double height2 = 0.30;
      double EP1 = m*g*height1;
      double EP2 = m*g*height2;
      double EP3 = 0;
      double EK1 = 0;
      double EK2 = 0.5*m*V1*V1;
      double EK3 = 0.5*m*V2*V2;
      double Emech1 = EP1 + EK1;
      double Emech2 = EP2 + EK2;
      double Emech3 = EP3 + EK3;
      double EmechM = (Emech1 + Emech2 + Emech3)/3;
      double error = abs((Emech1-EmechM)/Emech1*100);       
      
  temp = "<tr>";
  html = html + temp;
  temp = "<td rowspan=\"3\" align = \"center\" bgcolor=\"skyblue\">";
  html = html + temp;
  temp = i+1;
  html = html + temp;
  temp = "회차</td>";
  html = html + temp;
  temp = "<td>포토센서 1</td>";
  html = html + temp;

  
  temp = "<td>";
  html = html + temp;
  temp = "0";//입력하는곳 바로넣어봄
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  
  temp = "<td>";
  html = html + temp;
  temp = EP1;//입력하는곳 배열로 넣어봄
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = EK1;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = Emech1;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;

  temp = "<td rowspan=\"3\">";
  html = html + temp;
  temp = EmechM;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;

  temp = "<td rowspan=\"3\">";
  html = html + temp;
  temp = error;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "</tr>";
  html = html + temp;

  temp = "<tr>";
  html = html + temp;
  temp = "<td>포토센서 2</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = V1;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = EP2;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = EK2;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = Emech2;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "</tr>";
  html = html + temp;

  temp = "<tr>";
  html = html + temp;
  temp = "<td>포토센서 3</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = V2;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = EP3;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = EK3;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "<td>";
  html = html + temp;
  temp = Emech3;//입력하는곳 
  html = html + temp;
  temp = "</td>";
  html = html + temp;
  
  temp = "</tr>";
  html = html + temp;
}

  
  temp = "</tr>";
  html = html + temp;
  temp = "</table>";
  html = html + temp;

  temp = "<script>";
  html = html + temp;
  temp = "document.write(\"<br>\");";
  html = html + temp;
  temp = "document.write(\"<br>\");";
  html = html + temp;
  temp = "document.write(\"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp V1: 포토센서2의 순간속력 &nbsp&nbsp&nbsp&nbsp V2: 포토센서3의 순간속력<br><br>\");";
  html = html + temp;
  temp = "document.write(\"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Ek(운동에너지) = 1/2*m(질량)*v(속도)<br><br>\");";
  html = html + temp;
  temp = "document.write(\"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Emech(역학적에너지) = Ep(위치에너지) + Ek(운동에너지)<br><br>\");";
  html = html + temp;
  temp = "document.write(\"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Emech 평균 : 각 지점에서의 역학적에너지 평균<br><br>\");";
  html = html + temp;
  temp = "document.write(\"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 오차율(%) : (이론값-실제값)/실제값*100(%)<br><br>\");";
  html = html + temp;
  temp = "</script>";
  html = html + temp;
  temp = "</body>";
  html = html + temp;
  
  server.send(200, "text/html", html);
  
}

//웹서버 초기화 및 시작
void setup() {
  delay(1000);
  Serial.begin(9600);
  arduSerial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

//아두이노에서 전송받은 시간 데이터 변수에 저장
void loop() {
   if (arduSerial.available() > 0) {
    for(int i = 0 ;i<256; i++){
    float value = arduSerial.parseInt();
    float value2 = arduSerial.parseInt();
    float value3 = arduSerial.parseInt();
    timevalue[i][0] = value;
    timevalue[i][1] = value2;
    timevalue[i][2] = value3;
    arduSerial.setTimeout(5000);
    Serial.println(timevalue[i][0]);
    Serial.println(timevalue[i][1]);
    Serial.println(timevalue[i][2]);
    Serial.println();
      //시리얼 모니터(COM7) 설정 (시간 rawdata 표시)
           }
    }else {
    arduSerial.write(0);
    delay(100);
       }
 
  server.handleClient();
}
