int cm = 0;
int switchpin = 6;
int bulbpin = 8;
int sensorstatus;
int sensorpin = A0;
int buzzerpin = 9;


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(switchpin,INPUT);
  pinMode(bulbpin,OUTPUT);
  pinMode(buzzerpin,OUTPUT);
}

void loop()
{
  int status = digitalRead(switchpin);
  if(status == HIGH)
  { 
    //Serial.print("ON");
    // measure the ping time in cm
    cm = 0.01723 * readUltrasonicDistance(7, 7);
    //Serial.print(cm);
    //Serial.println("cm");
    delay(100); // Wait for 100 millisecond(s)
    if(cm<=250)
    {
      digitalWrite(bulbpin,HIGH);
      sensorstatus = analogRead(sensorpin);
      Serial.println(sensorstatus);
      if(sensorstatus > 990)
      {
        digitalWrite(buzzerpin,HIGH);
      }
    }
    else
    {
      digitalWrite(buzzerpin,LOW);
      delay(5000);
      digitalWrite(bulbpin,LOW);
    }
  }
  else
  {
    //Serial.print("OFF");
    digitalWrite(bulbpin,LOW);
    digitalWrite(buzzerpin,LOW);
  }
}