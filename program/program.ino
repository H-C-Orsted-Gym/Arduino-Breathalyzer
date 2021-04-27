#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX
int State;
const int BUTTON_PIN = 2;
const int ledpin = 4;
unsigned long StartTime;
unsigned long OnTime = 3000;
int total = 0;
int reps=0;
bool istrue = false;
void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);       // HC-05 default speed in AT command more

  
  pinMode(2, INPUT_PULLUP);
  pinMode(ledpin,OUTPUT);
  pinMode(A0,INPUT);

}

void loop()
{

  if (BTSerial.available()) {   // read from HC-05 and send to Arduino Serial Monitor
    Serial.write(BTSerial.read());
  }

  if (Serial.available()) {    // Keep reading from Arduino Serial Monitor and send to HC-05
    BTSerial.write(Serial.read());
  }
  
  // read the state of the switch/button:
  int buttonState = digitalRead(BUTTON_PIN);

  // print out the button's state 
  if(buttonState == 0){
    Lys ();
    }
      if(istrue){
    BTSerial.println(total*0.21);
        istrue = false;
    }
}
void Lys(){
        digitalWrite(ledpin, HIGH);
        StartTime = millis();
        reps = 0;
        total=0;

        if(StartTime+OnTime > millis()){
        while(StartTime+OnTime >= millis()){
          total += analogRead(A0);
          reps++;
          Serial.println(analogRead(A0));
          delay(100);

          }
        }
        Serial.println("Efter While");
        Serial.println(total);
        Serial.println(reps);

        total = total/reps;
        Serial.println(total);
        digitalWrite(ledpin, LOW);
                istrue = true;

  
  }

  
