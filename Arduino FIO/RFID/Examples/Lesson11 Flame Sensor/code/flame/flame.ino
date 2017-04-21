const int analogInPin = A0; //pinA0 attach to A0
const int digitalInPin = 8; //pinD0 attach to pin8 of uno board
const int ledPin = 13; //pin13 built-in led

void setup()
{
   //set the pins state
  pinMode(digitalInPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600); //initialize serial monitor
}

void loop()
{
  int analogVal = analogRead(analogInPin);//read the value of A0
  Serial.print("A0: "); 
  Serial.println(analogVal); //print to serial monitor 
  boolean stat = digitalRead(digitalInPin);//read the value of D0
  Serial.print("D0: "); 
  Serial.println(stat); // print to serial monitor 
  if(stat == HIGH)
  { 
    digitalWrite(ledPin,HIGH);//turn on the led
  }
  else
  {
    digitalWrite(ledPin,LOW);
  } 
}
