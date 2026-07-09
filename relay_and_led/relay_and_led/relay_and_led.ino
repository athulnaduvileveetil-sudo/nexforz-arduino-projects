/**
 * Nexforz IoT Internship - Phase 1: Day 5
 * Relay Control & Safety State Machine
 * Using INPUT_PULLUP (No external resistor required)
 */

// Pin Definitions
const int SWITCH_PIN = 2;   // Push Button
const int LED_PIN = 3;      // Status LED
const int RELAY_PIN = 4;    // Relay IN

// Set to true if your relay turns ON when IN is LOW
const bool IS_ACTIVE_LOW = true;

bool systemEStop = false;

void setup() {
  Serial.begin(9600);

  // Configure Pins
  pinMode(SWITCH_PIN, INPUT_PULLUP);   // Internal pull-up enabled
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Safe startup
  relayOff();
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== Nexforz Day 5 Safety Firmware ===");
  Serial.println("Press the button to turn ON the relay.");
  Serial.println("Type 'S' in Serial Monitor for Emergency Stop.");
}

void loop() {

  // Check for Emergency Stop command
  checkSerialCommand();

  // If Emergency Stop is active
  if (systemEStop) {
    relayOff();
    digitalWrite(LED_PIN, LOW);
    return;
  }

  // Read Button
  int switchState = digitalRead(SWITCH_PIN);

  // Button Pressed = LOW (because of INPUT_PULLUP)
  if (switchState == LOW) {
    relayOn();
    digitalWrite(LED_PIN, HIGH);
  } else {
    relayOff();
    digitalWrite(LED_PIN, LOW);
  }
}

// Turn Relay ON
void relayOn() {
  if (IS_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }
}

// Turn Relay OFF
void relayOff() {
  if (IS_ACTIVE_LOW) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}

// Emergency Stop through Serial Monitor
void checkSerialCommand() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == 'S' || cmd == 's') {
      systemEStop = true;
      Serial.println("!!! EMERGENCY STOP ACTIVATED !!!");
    }
  }
}