/*
MIT License

Copyright (c) 2025 Webrobotix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 * Webrobotix 16-Channel RC Servo Controller 1.5.0
 * Final design before PIR
 * Using Adafruit 16-channel 12-bit servo shield
 * Communicates with Processing for UI control
 * UPDATED: Removed EEPROM usage - all settings managed by Processing
 * SIMPLIFIED: No persistent storage in Arduino, all data comes from Processing
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// Removed EEPROM include - no longer needed

// PWM servo driver instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Constants
const int NUM_SERVOS = 16;
const int SERVOMIN = 100;  // This is the 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 600;  // This is the 'maximum' pulse length count (out of 4096)
const int SERVO_FREQ = 50;  // Standard servo frequency is 50Hz

// Servo positions (0-180 degrees)
int servoPositions[NUM_SERVOS];

// Min/Max limits for each servo (0-180 degrees)
int servoMinLimits[NUM_SERVOS];
int servoMaxLimits[NUM_SERVOS];

// Center positions for each servo (0-180 degrees)
int servoCenterPositions[NUM_SERVOS];

// Active/Inactive state for each servo
bool servoActive[NUM_SERVOS];

// Command parsing
String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize servo driver
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Standard frequency for RC servos
  
  // Initialize with default values (no EEPROM loading)
  initializeDefaults();
  
  // Reserve memory for serial input
  inputString.reserve(50);
  
  Serial.println("Servo Controller Ready - All servos inactive (no EEPROM)");
  
  // Send all current data to Processing on startup
  delay(1000);
  sendAllData();
}

void loop() {
  // Process any incoming commands
  if (stringComplete) {
    processCommand();
    inputString = "";
    stringComplete = false;
  }
}

// Initialize all servos with default values
void initializeDefaults() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoMinLimits[i] = 0;
    servoMaxLimits[i] = 180;
    servoCenterPositions[i] = 90;
    servoActive[i] = false;  // Start inactive
    servoPositions[i] = 90;  // Default to center
    
    // Turn off all PWM outputs
    pwm.setPWM(i, 0, 0);
  }
}

// Function to update servo position
void updateServo(int servoNum) {
  if (servoNum < 0 || servoNum >= NUM_SERVOS) return;
  
  if (servoActive[servoNum]) {
    // Map angle to pulse width
    int pulseWidth = map(servoPositions[servoNum], 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servoNum, 0, pulseWidth);
  } else {
    // Turn off PWM for inactive servos
    pwm.setPWM(servoNum, 0, 0);
  }
}

// Function to process incoming commands
void processCommand() {
  inputString.trim();
  
  if (inputString.startsWith("S:")) {
    // Servo position command: S:servoNum:position
    int firstColon = inputString.indexOf(':');
    int secondColon = inputString.indexOf(':', firstColon + 1);
    
    if (firstColon > 0 && secondColon > firstColon) {
      int servoNum = inputString.substring(firstColon + 1, secondColon).toInt();
      int position = inputString.substring(secondColon + 1).toInt();
      
      if (servoNum >= 0 && servoNum < NUM_SERVOS && position >= 0 && position <= 180) {
        if (servoActive[servoNum]) {
          // Apply limits
          position = constrain(position, servoMinLimits[servoNum], servoMaxLimits[servoNum]);
          servoPositions[servoNum] = position;
          updateServo(servoNum);
          
          // Send position confirmation
          Serial.print("PO:");
          Serial.print(servoNum);
          Serial.print(":");
          Serial.println(position);
        }
      }
    }
  }
  else if (inputString.startsWith("SETMINLIMIT:")) {
    // Set minimum limit: SETMINLIMIT:servoNum:limit
    int firstColon = inputString.indexOf(':');
    int secondColon = inputString.indexOf(':', firstColon + 1);
    
    if (firstColon > 0 && secondColon > firstColon) {
      int servoNum = inputString.substring(firstColon + 1, secondColon).toInt();
      int minLimit = inputString.substring(secondColon + 1).toInt();
      
      if (servoNum >= 0 && servoNum < NUM_SERVOS && minLimit >= 0 && minLimit <= 180) {
        servoMinLimits[servoNum] = minLimit;
        Serial.print("MI:");
        Serial.print(servoNum);
        Serial.print(":");
        Serial.println(minLimit);
      }
    }
  }
  else if (inputString.startsWith("SETMAXLIMIT:")) {
    // Set maximum limit: SETMAXLIMIT:servoNum:limit
    int firstColon = inputString.indexOf(':');
    int secondColon = inputString.indexOf(':', firstColon + 1);
    
    if (firstColon > 0 && secondColon > firstColon) {
      int servoNum = inputString.substring(firstColon + 1, secondColon).toInt();
      int maxLimit = inputString.substring(secondColon + 1).toInt();
      
      if (servoNum >= 0 && servoNum < NUM_SERVOS && maxLimit >= 0 && maxLimit <= 180) {
        servoMaxLimits[servoNum] = maxLimit;
        Serial.print("MA:");
        Serial.print(servoNum);
        Serial.print(":");
        Serial.println(maxLimit);
      }
    }
  }
  else if (inputString.startsWith("SETCENTER:")) {
    // Set center position: SETCENTER:servoNum:position
    int firstColon = inputString.indexOf(':');
    int secondColon = inputString.indexOf(':', firstColon + 1);
    
    if (firstColon > 0 && secondColon > firstColon) {
      int servoNum = inputString.substring(firstColon + 1, secondColon).toInt();
      int centerPos = inputString.substring(secondColon + 1).toInt();
      
      if (servoNum >= 0 && servoNum < NUM_SERVOS && centerPos >= 0 && centerPos <= 180) {
        servoCenterPositions[servoNum] = centerPos;
        Serial.print("CE:");
        Serial.print(servoNum);
        Serial.print(":");
        Serial.println(centerPos);
      }
    }
  }
  else if (inputString.startsWith("RESET:")) {
    // Reset servo limits and center: RESET:servoNum
    int servoNum = inputString.substring(6).toInt();
    if (servoNum >= 0 && servoNum < NUM_SERVOS) {
      servoMinLimits[servoNum] = 0;
      servoMaxLimits[servoNum] = 180;
      servoCenterPositions[servoNum] = 90;
      
      Serial.print("RE:");
      Serial.print(servoNum);
      Serial.print(":");
      Serial.println("RESET");
    }
  }
  else if (inputString.startsWith("ACTIVE:")) {
    // Set servo active/inactive: ACTIVE:servoNum:state (state: 1=active, 0=inactive)
    int firstColon = inputString.indexOf(':');
    int secondColon = inputString.indexOf(':', firstColon + 1);
    
    if (firstColon > 0 && secondColon > firstColon) {
      int servoNum = inputString.substring(firstColon + 1, secondColon).toInt();
      int state = inputString.substring(secondColon + 1).toInt();
      
      if (servoNum >= 0 && servoNum < NUM_SERVOS) {
        servoActive[servoNum] = (state == 1);
        updateServo(servoNum); // Update PWM output
        
        Serial.print("AC:");
        Serial.print(servoNum);
        Serial.print(":");
        Serial.println(servoActive[servoNum] ? 1 : 0);
      }
    }
  }
  else if (inputString.equals("ALLACTIVE")) {
    // Set all servos active
    for (int i = 0; i < NUM_SERVOS; i++) {
      servoActive[i] = true;
      updateServo(i);
      Serial.print("AC:");
      Serial.print(i);
      Serial.print(":");
      Serial.println(1);
    }
  }
  else if (inputString.equals("ALLINACTIVE")) {
    // Set all servos inactive
    for (int i = 0; i < NUM_SERVOS; i++) {
      servoActive[i] = false;
      updateServo(i);
      Serial.print("AC:");
      Serial.print(i);
      Serial.print(":");
      Serial.println(0);
    }
  }
  else if (inputString.equals("SAVE")) {
    // Legacy command - now just acknowledge (no EEPROM saving)
    Serial.println("LI:ACKNOWLEDGED");
    Serial.println("# Note: Settings now managed by Processing, not stored in EEPROM");
  }
  else if (inputString.equals("GETALL")) {
    // Send all current data
    sendAllData();
  }
}

// Function to send all servo data to Processing
void sendAllData() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    // Send position
    Serial.print("PO:");
    Serial.print(i);
    Serial.print(":");
    Serial.println(servoPositions[i]);
    
    // Send min limit
    Serial.print("MI:");
    Serial.print(i);
    Serial.print(":");
    Serial.println(servoMinLimits[i]);
    
    // Send max limit
    Serial.print("MA:");
    Serial.print(i);
    Serial.print(":");
    Serial.println(servoMaxLimits[i]);
    
    // Send center position
    Serial.print("CE:");
    Serial.print(i);
    Serial.print(":");
    Serial.println(servoCenterPositions[i]);
    
    // Send active state
    Serial.print("AC:");
    Serial.print(i);
    Serial.print(":");
    Serial.println(servoActive[i] ? 1 : 0);
    
    delay(10); // Small delay to prevent overwhelming the serial buffer
  }
}

// Serial event handler
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
