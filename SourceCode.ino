#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL3x4FpKkao"
#define BLYNK_TEMPLATE_NAME "LPG"
#define BLYNK_AUTH_TOKEN "8C4xuYA6f7al25btfJgDQFeOoJxNKfji"

char auth[] = "8C4xuYA6f7al25btfJgDQFeOoJxNKfji"; //Auth code sent via Email
char ssid[] = "vivo Y21"; //Wifi name
char password[] = "11111111";

#include<Servo.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Servo myservo;

BlynkTimer timer;

int gas   = A0;
int flame = D1;
int servo = D2;
int limit = 450;
int pass = 0;

void gasFireAction()
{
  int gas_val = gasOutput();
  int fire_val = digitalRead(flame);
  if(gas > limit || fire_val == 0){
  
    myservo.write(130);

    if(fire_val == 0){
    Serial.println("Fire DETECTED");
    Blynk.logEvent("fire_allert");
    delay(10000);
    }

    delay(3000);
    gas_val = gasOutput();;
    if(gas > limit){
    Serial.println("Fire DETECTED");
    Blynk.logEvent("gas_allert");
    delay(10000);

    }
  }
}

void setup()
{
  pinMode(gas,INPUT);
  pinMode(flame,INPUT);
  myservo.attach(servo,500,2500);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  myservo.write(0); 
  Blynk.virtualWrite(V9,pass);
}
void loop()
{
  Blynk.run();
  timer.run(); 
  delay(2000);
  gasFireAction();
  sendGas();

}

BLYNK_WRITE(V0) // off
{
    myservo.write(130);
    
} 
int gasOutput(){
   int outputValue = analogRead(gas);
   return outputValue;
}
void sendGas()
{
  Blynk.virtualWrite(V1,gasOutput());
}

BLYNK_WRITE(V2){ // one
   
   if(param.asInt() == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 1;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V3){ // two
   if(param.asInt() == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 2;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V4){ // three
   if(param.asInt()  == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 3;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V5){ // four
   if(param.asInt()  == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 4;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V6){ // five 
   if(param.asInt() == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 5;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V7){ // six
   if(param.asInt()  == 0){
     return;
   }
   if(pass > 9999){
     pass = 0;
     Blynk.virtualWrite(V9,pass);
   }
   pass = (pass * 10) + 6;
   Serial.println(pass);
   Blynk.virtualWrite(V9,pass);
}
BLYNK_WRITE(V8){ // ON
  int gas_val = gasOutput();
  int fire_val = digitalRead(flame);
  Serial.println(gas_val);
  Serial.println(fire_val);

  if(pass == 1536 && gas_val < limit && fire_val == 1){
    myservo.write(0);
    Serial.println("ON");
    pass = 0;
    Blynk.virtualWrite(V9,pass);
  }
  else{
    Blynk.virtualWrite(V9,"Error");
    delay(1000);
  }
}
