const int ledPin = 2;      // D2
const int buttonPin = 4;   // D4

bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Detect button press
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    ledState = !ledState;           // Toggle LED state
    digitalWrite(ledPin, ledState);
    delay(200);                     // Debounce
  }

  lastButtonState = currentButtonState;
}