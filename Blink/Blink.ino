int LED_BUILTIN = 14;
int RELAY_PIN = 13;
int PICOL_INPUT_PIN = 12;

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PICOL_INPUT_PIN, INPUT);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  delay(1000);
  int i = digitalRead(PICOL_INPUT_PIN);
  Serial.println(i);
}
