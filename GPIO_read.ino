#define inputPin 23

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  IOstate = digitalread(inputPin);
  Serial.println(IOstate);
  delay(200); // delay 200ms for next GPIO read
}
