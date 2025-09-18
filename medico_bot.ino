#include <Servo.h>  
#include <LiquidCrystal.h>
#include <RTC.h>
Servo servo;

const int servoPin = 6;
const int buttonPin = 9;
const int ledPin = 7;
const int buzzerPin = 8;
const int tpin0 = A0;
const int tpin1 = A1;
const int tpin2 = A2;
const int tpin3 = A3;
const int comp0 = A4;
const int comp1 = A5;
const int confirm = 8;
const int change = 10;

int angle = 0;
int newAngle;
int buttonState;
int movementDelay = 50;
int debounceDelay = 1000;



int year;
int month;
int day;
int hour;
int minutes;
int seconds;
int t0;
int t1;
int t2;
int t3;
int time1;
int time2;
int time3;
int compartment0;
int compartment1;
int angle1;
int angle2;
int angle3;
int t;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){ 
  pinMode(buttonPin, INPUT); 
  pinMode(tpin0, INPUT);
  pinMode(tpin1, INPUT);
  pinMode(tpin2, INPUT);
  pinMode(tpin3, INPUT);
  pinMode(comp0, INPUT);
  pinMode(comp1, INPUT);
  pinMode(confirm, INPUT);
  pinMode(change, INPUT);
  pinMode(ledPin,OUTPUT);   
  pinMode(buzzerPin,OUTPUT); 
  digitalWrite(ledPin,LOW); 
  digitalWrite(buzzerPin,LOW);  
  servo.attach(servoPin);    
  servo.write(angle);        
  Serial.begin(9600);       

  lcd.begin(16, 2);

  RTC.begin();
  RTCTime startTime(29, Month::NOVEMBER, 2024, 11, 59, 50, DayOfWeek::THURSDAY, SaveLight::SAVING_TIME_ACTIVE);
  RTC.setTime(startTime);
}

void loop(){

  if(digitalRead(confirm)!=0){
  
   t0 = digitalRead(tpin0);
   t1 = digitalRead(tpin1);
   t2 = digitalRead(tpin2);
   t3 = digitalRead(tpin3);
   compartment0 = digitalRead(comp0);
   compartment1 = digitalRead(comp1);
   t=t3<<3 | t2<<2 | t1<<1 | t0; 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: " + String(t));
   // delay(1000);
    //updateLCD;
  if(compartment0==1 && compartment1==1)
  {   lcd.setCursor(0, 1);
      lcd.print("compartment 1");
      delay(1000);
      lcd.clear();
      updateLCD();
      time1 = t;
      angle1 = 45;
  } 

  else if(compartment0==1 && compartment1==0)
  { lcd.setCursor(0, 1);
      lcd.print("compartment 2");
      delay(1000);
      lcd.clear();
      updateLCD();
      angle2 = 90;
  }

  else if(compartment0==0 && compartment1==1)
  { lcd.setCursor(0, 1);
      lcd.print("compartment 3");
      delay(1000);
      lcd.clear();
      updateLCD();
    time3 = t;
    angle3 = 135;
  }
  }

  updateLCD(); 
  
  buttonState = digitalRead(buttonPin); 
    Serial.println(angle);   
    Serial.println(t);            

  if(hour == time1 && minutes==0 && seconds==0) {
    flashLED(4,150);
    lcd.clear();
    updateLCD();
    newAngle = angle1;}
  if(hour==time2 && minutes==0 && seconds==0){
    flashLED(4,150);
    newAngle = angle2;}
  if(hour==time3 && minutes==0 && seconds==0){
    flashLED(4,150);
    newAngle = angle3;}
  if(hour!=time1 && hour!=time2 && hour!=time3)
   newAngle = 0;

    if (newAngle<=180){           
    	while(angle < newAngle){   
      	angle = angle + 1;        
      	servo.write(angle);       
        Serial.println(angle); 
      	delay(movementDelay);   

        while(angle > newAngle){   
      	angle = angle - 1;        
      	servo.write(angle);       
        Serial.println(angle); 
      	delay(movementDelay); 
    	}
     
      
    }
    }
    else{ 
      while(angle>0){        
        angle = angle - 1;   
        servo.write(angle); 
        Serial.println(angle);
        delay(movementDelay);
      }
    }
  }





void flashLED(int numFlashes, int flashDelay){  
  lcd.clear();              
  lcd.setCursor(0, 0);      
  lcd.print("Take medicine!"); 
  for (int i = 0; i<numFlashes; i++){
    digitalWrite(ledPin,HIGH); 
    digitalWrite(buzzerPin,HIGH); 
    delay(flashDelay);  
    digitalWrite(ledPin,LOW); 
    digitalWrite(buzzerPin,LOW);  
    delay(flashDelay);   
  }

 
  delay(1000);   
  lcd.clear();  
}

void updateLCD(){
  RTCTime currentTime;
  RTC.getTime(currentTime);
  year = currentTime.getYear();
  month = Month2int(currentTime.getMonth());
  day = currentTime.getDayOfMonth();
  hour = currentTime.getHour();
  minutes = currentTime.getMinutes();
  seconds = currentTime.getSeconds();

  lcd.setCursor(0, 0);

  if(month<10){  
    lcd.print("0");
  }
  lcd.print(month);
  lcd.print("/");
  if(day<10){        
    lcd.print("0");
  }
  lcd.print(day); 
  lcd.print("/");
  lcd.print(year); 

  lcd.setCursor(0, 1); 
  if(hour<10){ 
    lcd.print("0");
  }
  lcd.print(hour);    
  lcd.print(":");
  if(minutes<10){  
    lcd.print("0");
  }
  lcd.print(minutes); 
  lcd.print(":");
  if(seconds<10){ 
    lcd.print("0");
  }
  lcd.print(seconds); 
}
  
  
      
  
