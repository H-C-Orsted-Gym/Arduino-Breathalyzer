  #include <SoftwareSerial.h>
  SoftwareSerial BTSerial(10, 11); // RX | TX
  // Pins 
  const int BUTTON_PIN = 2;
  const int ledpin = 4;
  const int PT = 5;
  const int ARMEDPIN = 3;
  
  // Time related variables
  unsigned long StartTime;
  unsigned long OnTime = 3000;
  const int WarmUpTime = 3000;
  
  // Math variables
  int total = 0;
  int reps=0;
  
  //Bools for wamup and bt comunicaton
  bool istrue = false;
  bool WarmUp = true;
  
  void setup()
  {
    // Setup serial and Bt serial
    Serial.begin(9600);
    //Serial.println("Enter AT commands:");
    BTSerial.begin(9600);       // HC-05 default speed in AT command more
  
    // Pin modes
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    pinMode(PT,INPUT);
    pinMode(ledpin,OUTPUT);
    pinMode(ARMEDPIN,OUTPUT);
    pinMode(A0,INPUT);
  
  }
  
  void loop()
  {
  int buttonState = digitalRead(PT);

    // Warmup for Ethanol sensor
   if(WarmUp && buttonState == 1){
      delay(WarmUpTime);
      digitalWrite(ARMEDPIN,HIGH);
      WarmUp = false;
      } 
    if(buttonState == 0){
       WarmUp = true;
       digitalWrite(ARMEDPIN,LOW);
      }
  
    // Comunication between BT and Arduino
    if (BTSerial.available()) {   // read from HC-05 and send to Arduino Serial Monitor
      Serial.write(BTSerial.read());
    }
  
    if (Serial.available()) {    // Keep reading from Arduino Serial Monitor and send to HC-05
      BTSerial.write(Serial.read());
    }
    
    // read the state of the switch/button:
    buttonState = digitalRead(BUTTON_PIN);
  
    // Runs Lys func to take sensor reading
    if(buttonState == 0){
      Lys ();
      }
      // sends data to bt moduel
        if(istrue){
          // Calculates promille
          BTSerial.println(total);
          istrue = false;
      }
  }
  void Lys(){
          // ligth on lamp
          digitalWrite(ledpin, HIGH);
          // reset variables
          StartTime = millis();
          reps = 0;
          total=0;
          // Takes 30 test cases
          while(StartTime+OnTime >= millis()){
            total += map(analogRead(A0),0,1023,25,500);
            reps++;
            Serial.println(map(analogRead(A0),0,1023,25,500) );
            delay(100);
          }
          // Prints output

  
          // Calculates average
          total = total/reps;
          // Prints Average, turn of led and sets bool to true
          Serial.println(total);
          digitalWrite(ledpin, LOW);
          istrue = true;
  
    
    }
  
  
