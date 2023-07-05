int in1 = 8;
int in2 = 9;
int ConA = 10;
int speed1;

#include <SoftwareSerial.h>
int RX_pin = 6;
int TX_pin = 5;
SoftwareSerial BTserial (RX_pin, TX_pin);

string stringOne;

const int dataIN = 2;       // IR sensor INPUT

unsigned long prevmillis;   // To store time 
unsigned long duration;     // To store time difference 
unsigned long refresh;      // To store time for refresh of reading

int rpm;                    // RPM value

boolean currentstate;       // Current state of IR input scan 
boolean prevstate;          // State of IR sensor in previous scan
void setup ()
{
  pinMode (8, OUTPUT) ; 
  pinMode (9, OUTPUT) ;
  pinMode (10, OUTPUT) ;
  
  pinMode (dataIN, INPUT) ;
  prevmillis = 0;
  prevstate = LOW;
  Serial.begin (9600) ;
  BTserial.begin (9600);
}

void TurnMotorA (){         //we create a function which control the direction and speed 
  digitalWrite (inl, LOW);  //Switch between this HIGH and Low to change direction 
  digitalWrite (in2, HIGH) ;
  speed1 = analogRead (A0); //read the analog value from the potentiometer
  speed1 = speed1 (255./1023.) ;
  analogWrite(ConA, speedl);
}

void loop ()
{
  TurnMotorA();
  //RPM Measurement
  currentstate=digitalRead(dataIN);   // Read IR sensor state
  if (prevstate != currentstate)      // If there is change in input
  {
    if (currentstate==HIGH)           // If input only changes from LOW to HIGH
    {
      duration = ( micros () - prevmillis );  // Time difference between revolution in microsecond
      rpm = (60000000/duration);              // rpm = (1/ time millis) *1000*1000*60
      prevmillis = micros();                  //store time for nect revolution calculation
    }
  }
  prevstate = currentstate;  // score this
  Serial.println (rpm);
  stringOne = String (rpm, DEC):
  BTserial.println(stringOne);
}
