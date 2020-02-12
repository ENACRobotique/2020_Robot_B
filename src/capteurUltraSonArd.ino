const byte TRIGGER_PIN = 2; //Tx
const byte ECHO_PIN = 3; //Rx
const unsigned long MEASURE_TIMEOUT = 2500;
const float SOUND_SPEED = 342.0*1000; // m/ms

void setup() 
{
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  
}

void loop() 
{
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long mesure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT); //mesure = dt en ms
  Serial.println("mesure = " + String(mesure));
  float distance = mesure/(2*SOUND_SPEED); //distance en m
  //Serial.println(distance);
  delay(500);

}