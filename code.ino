#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int incomingByte = 0;   
int errorLED = 11;

String ssid     = "Simulator Wifi";	// SSID para se conectar
String password = ""; 

String host     = "https://hooks.zapier.com/"; 
const int httpPort   = 80;
String uri		 = "hooks/catch/6003612/o4320x8/";



void setup() {
  // Setup LCD e texto de informaçao
  lcd.begin(16,2);
  lcd.print("Testando");
  lcd.setCursor(0,1);
  lcd.print("F: ");
  
  pinMode(errorLED, OUTPUT); 
  
  // Start ESP8266
  Serial.begin(115200);		
  Serial.println("AT");	
  delay(10);				
  
  if (Serial.available() > 0) {
    
     			lcd.setCursor(0,1);
  				lcd.print("Buffer");

                incomingByte = Serial.read();

 
                Serial.print("Recebido: ");
                Serial.println(incomingByte, DEC);
        }
  
  if (!Serial.find("OK")) digitalWrite(errorLED, HIGH);
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);				
  if (!Serial.find("OK")) digitalWrite(errorLED, HIGH);	

  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);			
  if (!Serial.find("OK")) digitalWrite(errorLED, HIGH);	
}


void loop() {
  String httpPacket = "GET " + uri + " HTTP/1.1\r\n" 
    +"Host: "+  host + "\r\n" + 
    "Connection: close\r\n\r\n";
  int length = httpPacket.length();


  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find(">")) digitalWrite(errorLED, HIGH); 
lcd.print(Serial.read());
lcd.print(Serial.read());  
  Serial.print(httpPacket);
  delay(10);
  if (!Serial.find("SEND OK\r\n")) digitalWrite(errorLED, HIGH);
	
  while(!Serial.available()) delay(5);

  if (Serial.find("\r\n\r\n")){	
    delay(5);
    
    delay (2000);
    unsigned int i = 0; //timeout counter
    String outputString = "";
    
    while (!Serial.find("\"temp\":")){}
    
    while (i<60000) { // 1 minute timeout checker
      if(Serial.available()) {
        char c = Serial.read();
        if(c==',') break;
        outputString += c;
        i=0;
      }
      i++;
    }
    
    lcd.setCursor(3,1);
    lcd.print(outputString);
 
  }
  
  delay(10000);
}
