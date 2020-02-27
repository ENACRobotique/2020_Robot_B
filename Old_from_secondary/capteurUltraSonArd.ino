const byte TRIGGER_PIN = 2; //Tx
const byte ECHO_PIN = 3; //Rx
const unsigned long MEASURE_TIMEOUT = 25000UL; //Microseconds
const float SOUND_SPEED = 342.0;
const unsigned long CONVERT = 1000000;

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

  long mesure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  Serial.println("mesure = " + String(mesure));
  double distance_m = mesure*SOUND_SPEED/(2*CONVERT);
  Serial.println(distance_m);
  delay(1000);

}