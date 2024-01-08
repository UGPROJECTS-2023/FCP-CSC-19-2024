#include <LiquidCrystal.h>

//phase pins declearation 
//phase 1
int ph1_g=0;
int ph1_y=12;
int ph1_r=8;
int ph1_sensor=A1;

//phase 2
int ph2_g=11;
int ph2_y=10;
int ph2_r=9;
int ph2_sensor=13;

//phase 3
int resetPin=A0;
int ph3_g=A3;
int ph3_y=A4;
int ph3_r=A5;
int ph3_sensor=3;
int buzzer_pin=2;

int lastSensorState=LOW, sensorState, ledState=HIGH,flag1=LOW,flag2=HIGH,flag3=HIGH,led_flag1=LOW,led_flag2=LOW,led_flag3=LOW;
unsigned long phase_1_delay=2000,phase_2_delay=4000,phase_3_delay=6000,time_counter=0,buz_delay=400;
unsigned long debounceDelay=50;
void(*resetFunc)(void)=resetPin;
class Counters
{
  public:
      unsigned long counter1=0, counter2=0, counter3=0,buz_timer=0,wait=0;
     void timer1()
     {
      counter1=millis();
     }
     void timer2()
     {
      counter2=millis();
     }
     void timer3()
     {
      counter3=millis();
     }
     void buz()
     {
      buz_timer=millis();
     }
     void reset()
     {
      resetFunc();
     }
};
Counters client;
void setup() 
{
  // setting the function of each pin
  pinMode(ph1_g,OUTPUT);
  pinMode(ph1_y,OUTPUT);
  pinMode(ph1_r,OUTPUT);
  pinMode(ph1_sensor,INPUT);
  pinMode(buzzer_pin,OUTPUT);
  
  pinMode(ph2_g,OUTPUT);
  pinMode(ph2_y,OUTPUT);
  pinMode(ph2_r,OUTPUT);
  pinMode(ph2_sensor,INPUT);
  pinMode(resetPin,OUTPUT);

  pinMode(ph3_g,OUTPUT);
  pinMode(ph3_y,OUTPUT);
  pinMode(ph3_r,OUTPUT);
  pinMode(ph3_sensor,INPUT);
  
 //all leds are off initially 
 digitalWrite(ph1_g,LOW);
 digitalWrite(ph1_y,LOW);
 digitalWrite(ph1_r,LOW);
 
 digitalWrite(ph2_g,LOW);
 digitalWrite(ph2_y,LOW);
 digitalWrite(ph2_r,HIGH);
 
 digitalWrite(ph3_g,LOW);
 digitalWrite(ph3_y,LOW);
 digitalWrite(ph3_r,HIGH);
 digitalWrite(resetPin,LOW);
   
}

void loop() 
{
  //reading phases sensors
  int ph1_s=digitalRead(ph1_sensor);
  int ph2_s=digitalRead(ph2_sensor);
  int ph3_s=digitalRead(ph3_sensor);
  client.timer1();
  client.timer2();
  client.timer3();
  client.buz();
  
  if(client.counter1<phase_1_delay and flag1==LOW)
  {
    digitalWrite(ph1_r,LOW);
    digitalWrite(ph1_g,HIGH);
    flag1=HIGH;
    client.wait=millis();
    led_flag1=HIGH;
  }
  if(client.counter1>=phase_1_delay and flag1==HIGH)
  { 
    digitalWrite(ph1_g,LOW);
    digitalWrite(ph1_y,HIGH);
    delay(500);
    digitalWrite(ph1_y,LOW);
    digitalWrite(ph1_r,HIGH);
    flag2=LOW;
    flag1=LOW;
    led_flag1=LOW;
    client.wait=millis();
  }
  if(client.counter2<phase_2_delay and flag2==LOW)
  {
    digitalWrite(ph2_r,LOW);
    digitalWrite(ph2_g,HIGH);
    flag2=HIGH;
    led_flag2=HIGH;
    client.wait=millis();
  }
   if(client.counter2>=phase_2_delay and flag2==HIGH)
  { 
    digitalWrite(ph2_g,LOW);
    digitalWrite(ph2_y,HIGH);
    delay(500);
    digitalWrite(ph2_y,LOW);
    digitalWrite(ph2_r,HIGH);
    flag3=LOW;
    flag2=LOW;
    led_flag2=LOW;
    client.wait=millis();
  }
   if(client.counter3<phase_3_delay and flag3==LOW)
  {
    analogWrite(ph3_r,LOW);
    digitalWrite(ph3_g,HIGH);
    flag3=HIGH;
    led_flag3=HIGH;
    client.wait=millis();
  }
   if(client.counter3>=phase_3_delay and flag3==HIGH)
  { 
    digitalWrite(ph3_g,LOW);
    digitalWrite(ph3_y,HIGH);
    delay(500);
    analogWrite(ph3_y,LOW);
    digitalWrite(ph3_r,HIGH);
    client.wait=millis();
    flag1=LOW;
    flag3=LOW;
    client.reset();
    led_flag3=LOW;
     
  }
  
 //buzzer code section
  if((led_flag1==LOW and ph1_s==HIGH))
  {
    digitalWrite(buzzer_pin,HIGH);
    client.wait=millis();
  }
   if((led_flag2==LOW and ph2_s==HIGH))
  {
    digitalWrite(buzzer_pin,HIGH);
    client.wait=millis();
  }
   if((led_flag3==LOW and ph3_s==HIGH))
  {
    digitalWrite(buzzer_pin,HIGH);
    client.wait=millis();
  }
  if(client.buz_timer-client.wait>=buz_delay)
  {
    digitalWrite(buzzer_pin,LOW);
  }
 
}
