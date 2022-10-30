#include <ESP8266WiFi.h>
#define FAN D2
#define LIGHT D4
const char* ssid = "Dicky KOST";
const char* password = "100rivera";

WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  pinMode(FAN, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  digitalWrite(FAN,HIGH);
  digitalWrite(LIGHT,HIGH);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi Connected");
  server.begin();
  Serial.println("Server Started");
  Serial.println(WiFi.localIP());
}
void loop(){
  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if(req.indexOf("/fanon") != -1)
  {
  //  status_fan=0;
    digitalWrite(FAN,LOW);
    Serial.println("FAN ON");
  }
  else if(req.indexOf("/fanoff") != -1)
  {
//    status_fan=1;
    digitalWrite(FAN,HIGH);
    Serial.println("FAN OFF");
  }

  if(req.indexOf("/lighton") != -1)
  {
//    status_light=0;
    digitalWrite(LIGHT,LOW);
    Serial.println("LIGHT ON");
  }
  else if(req.indexOf("/lightoff") != -1)
  {
 //   status_light=1;
    digitalWrite(LIGHT,HIGH);
    Serial.println("LIGHT OFF");
  }
  
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  /*web +="<html>\r\n";
  web +="<body>\r\n";
  web +="<h1>LED Status</h1>\r\n";
  web +="<p>\r\n";
  if(status_fan==1)
    web +="FAN Off\r\n";
  else
    web +="FAN on\r\n";
  if(status_light==1)
    web +="LIGHT On\r\n";
  else
    web +="LIGHT Off\r\n";
  web +="</p>\r\n";
  web +="</p>\r\n";
  web +="<a href=\"/fanon\">\r\n";
  web +="<button>FAN ON</button>\r\n";
  web +="</a>\r\n";
  web +="</p>\r\n";

  web +="<a href=\"/fanoff\">\r\n";
  web +="<button>FAN OFF</button>\r\n";
  web +="</a>\r\n";
    web +="</p>\r\n";
  web +="</p>\r\n";
  web +="<a href=\"/lightoff\">\r\n";
  web +="<button>LIGHT OFF</button>\r\n";
  web +="</a>\r\n";
  web +="</p>\r\n";

  web +="<a href=\"/lighton\">\r\n";
  web +="<button>LIGHT ON</button>\r\n";
  web +="</a>\r\n";

  web +="</body>\r\n";
  web +="</html>\r\n";
  */
  client.print(web);
}
