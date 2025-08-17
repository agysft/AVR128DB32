void setup() {
  // put your setup code here, to run once:
  /* initialize digital pin LED_BUILTIN as an output.*/
  pinMode(7, OUTPUT);     // LED pin7 (=PIN_PA7)
  digitalWrite(7, HIGH);  // turn the LED on

  Serial.pins(0,1);//AVR64DB32 TX=0,RX=1
  Serial.begin(115200);
  while (!Serial);
  Serial.print("Brink!");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, LOW);  // turn the LED off
  delay(900);
  digitalWrite(7, HIGH);  // turn the LED on
  delay(100);
}
