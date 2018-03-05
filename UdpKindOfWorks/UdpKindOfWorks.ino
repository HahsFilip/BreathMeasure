#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <RunningMedian.h>
#include <math.h>
const char* ssid = "WEATHER_STATION";
const char* password = "dupadupa";
RunningMedian samples = RunningMedian(7);

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup()
{
  
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
 int packetSize = Udp.parsePacket();
if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write("recived");
Udp.endPacket(); 
  }
}

int s = 0;

int i = 0;
int data;
float delog;
float median;
float oldMedian;
int exorin = 0;
int testforslope;
int tester = 0;
int average =0;
int slopelength =30;
int slopecut = 7;
char t;
void loop()
{
char c[5];

String str;

str=String(testforslope);

str.toCharArray(c,5);
 
  

 
// data = 6;
 Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write(c);
Udp.endPacket();
delay(10);
 data = analogRead(A0);

oldMedian = median;
samples.add(data);

Serial.println(samples.getAverage());
//average = samples.getAverage();


//Serial.print(log(data-100));
//Serial.print(", ");
//Serial.println(testforslope*100);



median = samples.getMedian();

if(median > oldMedian) exorin++;
if(median<oldMedian) exorin--;
if(tester = slopelength){
  if(exorin > slopecut){
    testforslope=1;
    exorin = 0;
    }
if(exorin <slopecut*-1){
  testforslope=-1;
  exorin = 0;
  }
  tester = 0;

//  Serial.print(125);
  //Serial.print(", ");
}  
  tester++;
  
  
  
  
  
  
  //Serial.print(samples.getMedian());
//Serial.print(", ");
}
