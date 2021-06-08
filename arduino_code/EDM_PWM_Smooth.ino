const int stepPin = 3; 
const int dirPin = 4; 
const int toggleA = 12;
const int toggleB = 13;
//const int probe= 2;
const int relai = 2;
const int sensor = A3;
int buttonStateA = 0; 
int buttonStateB = 0; 
int probeState = 0; 
int sensorValue = 0;


//Parameters
const int aisPin  = A3;
const int numReadings  = 20;
int readings [numReadings];
int readIndex  = 0;
long total  = 0;


//Variables
int aisVal  = 0;


void setup() {
  // Sets int / outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(toggleA,INPUT);
  pinMode(toggleB,INPUT);
  //pinMode(probe,INPUT_PULLUP);
  pinMode(relai, OUTPUT);
  pinMode(sensor,INPUT);
  Serial.begin(9600);


  //Init Serial USB
  
  Serial.println(F("Initialize System"));
  //Init AnalogSmooth
  pinMode(aisPin, INPUT);


  
}
void loop() {
  buttonStateA = digitalRead(toggleA);
  buttonStateB = digitalRead(toggleB);
  //probeState = digitalRead(probe);
  if (buttonStateA == HIGH) {
  
    digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 50;  x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
      }
    
  }
  else {
    digitalWrite(stepPin,LOW);
  }

if (buttonStateB == HIGH) {
 digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 50; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  }

  else {
    digitalWrite(stepPin,LOW);
  }
  

//digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)
/////////////////////////////////////////////////////////////////////////////
//digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)

  readAnalogSmooth();
  //Serial.print(F("ais avg : ")); Serial.println(smooth());
  //delay(200);



//sensorValue = smooth();//analogRead(sensor);
long m_amper = smooth();//map(sensorValue,0,77,0,3000); //* (5.0 / 1023.0)*55;

Serial.println(m_amper);


//digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
if (m_amper < 10) {
for(int x = 0; x < 1;  x++) {
digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
//digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)
digitalWrite(stepPin,HIGH); 
delay(1); 
digitalWrite(stepPin,LOW); 
delay(1); 

//digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
delay(1);
}
}
else {}

//sensorValue = analogRead(sensor);
//float m_amper = sensorValue * (5.0 / 1023.0)*55;
//digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
if (m_amper > 20) {
for(int x = 0; x < 1;  x++) {
digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
//digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)
digitalWrite(stepPin,HIGH); 
delay(1); 
digitalWrite(stepPin,LOW); 
delay(1); 

//digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
delay(1); 
  }
}
else {}     

/////////////////////////////////////////////////////////////////////////////
//digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW 


//delay(50);
}




void readAnalogSmooth( ) { /* function readAnalogSmooth */
  ////Test routine for AnalogSmooth
  aisVal = analogRead(aisPin);
  //Serial.print(F("ais val ")); Serial.println(aisVal);
}

long smooth() { /* function smooth */
  ////Perform average on sensor readings
  long average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = analogRead(aisPin);
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

  return average;
}


/////////////////////////////////////////////////////////
/*
   digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 30;  x++) {
      digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)
      sensorValue = analogRead(sensor);
    // print out the value you read:
    float m_amper = sensorValue * (5.0 / 1023.0)*55;
    Serial.println(m_amper);
    //Serial.println(sensorValue);
      digitalWrite(stepPin,HIGH); 
      delay(1); 
      digitalWrite(stepPin,LOW); 
      delay(1); 
      
      digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
      delay(20);
      }
      
  

  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 29; x++) {
    digitalWrite(relai, HIGH);   // turn the relai on (HIGH is the m_amper level)
    sensorValue = analogRead(sensor);
    // print out the value you read:
    float m_amper = sensorValue * (5.0 / 1023.0)*55;
    Serial.println(m_amper);
    //Serial.println(sensorValue);
    digitalWrite(stepPin,HIGH);
    delay(1); 
    digitalWrite(stepPin,LOW);
    delay(1); 
    
    digitalWrite(relai, LOW);    // turn the relai off by making the m_amper LOW
    delay(20);
  }
*/
