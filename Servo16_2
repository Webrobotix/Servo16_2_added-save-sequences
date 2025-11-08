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
 
 Terms of Use (Plain Language)
 By downloading, using, or running this RC Servo Controller Program, you agree to the following terms:
 
 No Warranty - This program is provided "as is" with no guarantees of safety, performance, or fitness for any purpose.
 User Responsibility - You are fully responsible for how you use this software and any devices connected to it.
 Safety Requirements - Do not leave animatronics unattended while powered. Keep away from moving parts.
 Liability Limitation - The author is not liable for any injury, damage, or loss that may result from using this software.
 
 WARNING: This program controls mechanical devices that may move suddenly and with force. Use at your own risk.
 */

/*
 * Webrobotix 2020-2025 - Servo16 v2
 * 16-Channel RC Servo Controller Interface with Sequence Recording
 * NEW in v1.6.1: Added Save As button for saving settings with a new filename
 */

import processing.serial.*;
import java.io.File;
import java.util.ArrayList;

// Constants
final int NUM_SERVOS = 16;
final int WINDOW_WIDTH = 1280;
final int WINDOW_HEIGHT = 800;
final int SLIDER_WIDTH = 300;
final int SLIDER_HEIGHT = 30;
final int BUTTON_WIDTH = 120;
final int BUTTON_HEIGHT = 30;
final int MARGIN = 50;
final int ROW_HEIGHT = 140;
final color BG_COLOR = color(240);
final color SLIDER_COLOR = color(180, 200, 220);
final color BUTTON_COLOR = color(144, 213, 255);
final color BUTTON_HOVER_COLOR = color(80, 140, 180);
final color TEXT_COLOR = color(40);
final color CENTER_BUTTON_COLOR = color(255, 200, 100);
final color SET_CENTER_BUTTON_COLOR = color(255, 150, 50);
final color MIN_BUTTON_COLOR = color(241, 241, 241);
final color MAX_BUTTON_COLOR = color(241, 241, 241);
final color RESET_BUTTON_COLOR = color(241, 241, 241);
final color LABEL_BUTTON_COLOR = color(198, 219, 255);
final color ACTIVE_BUTTON_COLOR = color(100, 255, 100);
final color INACTIVE_BUTTON_COLOR = color(255, 100, 100);
final color RECORD_BUTTON_COLOR = color(255, 100, 100);
final color RECORDING_BUTTON_COLOR = color(255, 50, 50);
final color PLAY_BUTTON_COLOR = color(100, 255, 100);
final color CLEAR_BUTTON_COLOR = color(255, 150, 100);
final color EXPORT_BUTTON_COLOR = color(100, 200, 255);
final color SAVE_SETTINGS_BUTTON_COLOR = color(100, 200, 100);
final color LOAD_SETTINGS_BUTTON_COLOR = color(100, 150, 255);
final color DELETE_SETTINGS_BUTTON_COLOR = color(255, 100, 100);
final color PWM_SHIELD_BUTTON_COLOR = color(255);
final color INACTIVE_SLIDER_COLOR = color(150, 150, 150);
final color INACTIVE_BUTTON_COLOR_GRAY = color(200, 200, 200);
final color INACTIVE_TEXT_COLOR = color(120);
final int FILES_PER_PAGE = 10;
final color PAGE_BUTTON_COLOR = color(100, 150, 255);

// Variables for smooth keyframe execution
boolean isExecutingKeyframe = false;
int executionStartTime = 0;
int currentKeyframeIndex = 0;
int[] startPositions = new int[NUM_SERVOS];
int[] targetPositions = new int[NUM_SERVOS];
boolean[] keyframeActiveServos = new boolean[NUM_SERVOS];
int keyframeSpeed = 1000;

// Serial communication
Serial arduinoPort;
String[] serialPorts;
String[] previousSerialPorts;
boolean connected = false;
String receivedData = "";
String connectedPort = "";
int lastConnectionCheck = 0;
final int CONNECTION_CHECK_INTERVAL = 2000;
String connectionStatus = "Disconnected";
int connectionStatusTime = 0;

// Interface elements
Slider[] servoSliders = new Slider[NUM_SERVOS];
Button[] centerButtons = new Button[NUM_SERVOS];
Button[] setCenterButtons = new Button[NUM_SERVOS];
Button[] minButtons = new Button[NUM_SERVOS];
Button[] maxButtons = new Button[NUM_SERVOS];
Button[] resetButtons = new Button[NUM_SERVOS];
Button[] labelButtons = new Button[NUM_SERVOS];
Button[] activeButtons = new Button[NUM_SERVOS];
Button allActiveButton;
Button allInactiveButton;
Button reconnectButton;

// Settings buttons
Button saveSettingsButton;
Button saveAsSettingsButton;  // NEW: Save As button
Button loadSettingsButton;
Button deleteSettingsButton;

// Sequence recording buttons
Button recordButton;
Button playButton;
Button clearSequenceButton;
Button exportSketchButton;
Button addKeyframeButton;

// PWM Shield support
Button pwmShieldToggleButton;
boolean usePWMShield = true;

// Current servo positions and limits
int[] servoPositions = new int[NUM_SERVOS];
int[] servoMinLimits = new int[NUM_SERVOS];
int[] servoMaxLimits = new int[NUM_SERVOS];
int[] servoCenterPositions = new int[NUM_SERVOS];

// Servo states
boolean[] servoActive = new boolean[NUM_SERVOS];

// Servo labels
String[] servoLabels = new String[NUM_SERVOS];
boolean isEditingLabel = false;
int editingServoIndex = -1;
String tempLabel = "";

// Settings file status
String settingsStatus = "";
int settingsStatusTime = 0;

// File naming and selection
boolean isNamingFile = false;
boolean isSelectingFile = false;
String tempFileName = "";
String[] savedFilesList = new String[0];
int selectedFileIndex = -1;
String fileOperation = "";
String lastLoadedFileName = "";

// Pagination variable
int fileListPage = 0;

// Sequence recording variables
ArrayList<ServoKeyframe> sequence;
boolean isRecording = false;
boolean isPlayingSequence = false;
int playbackIndex = 0;
int playbackStartTime = 0;
String sequenceStatus = "";
int sequenceStatusTime = 0;

String lastLoadedKeyframeFile = "";
Button saveKeyframesButton;
Button loadKeyframesButton;

// Keyframe timing controls
Slider speedSlider;
Slider delaySlider;

// Sequence export variables
boolean isNamingSketch = false;
String tempSketchName = "";

// Rectangle properties
int rectX = 45;
int rectY = 40;
int rectWidth = 308;
int rectHeight = 180;
int colSpacing = 41;
int rowSpacing = 23;

// Servo keyframe class
class ServoKeyframe {
  int[] positions;
  boolean[] activeServos;
  int speed;
  int delay;
  String name;

  ServoKeyframe() {
    positions = new int[NUM_SERVOS];
    activeServos = new boolean[NUM_SERVOS];
    speed = 1000;
    delay = 500;
    name = "";

    for (int i = 0; i < NUM_SERVOS; i++) {
      positions[i] = servoPositions[i];
      activeServos[i] = servoActive[i];
    }
  }

  ServoKeyframe(int spd, int dly, String nm) {
    this();
    speed = spd;
    delay = dly;
    name = nm;
  }
}

void setup() {
  size(1440, 800);
  smooth();
  surface.setTitle("16-Channel RC Servo Controller");

  sequence = new ArrayList<ServoKeyframe>();
  initializeLabels();
  createUI();

  for (int i = 0; i < NUM_SERVOS; i++) {
    servoPositions[i] = 90;
    servoMinLimits[i] = 0;
    servoMaxLimits[i] = 180;
    servoCenterPositions[i] = 90;
    servoActive[i] = false;
  }

  loadSettingsFromFile();
  previousSerialPorts = Serial.list();
  establishConnection();

  if (connected) {
    delay(500);
    setAllServosInactive();
  }

  loadKeyframesFromFile();
}

void draw() {
  background(BG_COLOR);
  textAlign(LEFT, TOP);
  textSize(24);
  text("Servo16", WINDOW_WIDTH - 700, 15);
  textSize(16);
  textAlign(RIGHT, TOP);
  text("Webrobotix 2025", WINDOW_WIDTH - 5, 780);

  if (millis() - lastConnectionCheck > CONNECTION_CHECK_INTERVAL) {
    checkForNewSerialPorts();
    lastConnectionCheck = millis();
  }

  drawConnectionStatus();

  textAlign(LEFT, TOP);
  textSize(16);
  int activeCount = 0;
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (servoActive[i]) activeCount++;
  }
  text("Active Servos: " + activeCount + "/" + NUM_SERVOS, 65, 720);
  text("PWM Shield: " + (usePWMShield ? "ENABLED" : "DISABLED"), 250, 720);

  drawSequenceStatus();
  drawSettingsStatus();

  noFill();
  stroke(#FFFFE4);
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      int x = rectX + col * (rectWidth + colSpacing);
      int y = rectY + row * (rectHeight + rowSpacing);

      int servoIndex = row * 4 + col;
      if (!servoActive[servoIndex]) {
        stroke(color(250, 250, 250));
      } else {
        stroke(#FFFFE4);
      }
      rect(x, y+10, rectWidth, rectHeight);
    }
  }

  for (int i = 0; i < NUM_SERVOS; i++) {
    drawServoControl(i);
  }

  allActiveButton.display();
  allInactiveButton.display();
  reconnectButton.display();

  saveSettingsButton.display();
  saveAsSettingsButton.display();  // NEW: Display Save As button
  loadSettingsButton.display();
  deleteSettingsButton.display();

  pwmShieldToggleButton.buttonColor = usePWMShield ? color(100, 255, 100) : PWM_SHIELD_BUTTON_COLOR;
  pwmShieldToggleButton.label = usePWMShield ? "PWM: ON" : "PWM: OFF";
  pwmShieldToggleButton.display();

  drawSequenceControls();

  if (isEditingLabel) {
    drawLabelEditDialog();
  }

  if (isNamingFile) {
    drawFileNamingDialog();
  }

  if (isSelectingFile) {
    drawFileSelectionDialog();
  }

  if (isNamingSketch) {
    drawSketchNamingDialog();
  }

  if (isPlayingSequence) {
    updateSequencePlayback();
  }

  if (connected) {
    readSerialData();
  }
}

void drawSequenceControls() {
  fill(220);
  stroke(150);
  rect(50, 600, 800, 140);

  fill(TEXT_COLOR);
  textAlign(LEFT, TOP);
  textSize(16);
  text("Sequence Recording Panel", 60, 610);

  textSize(14);
  text("Keyframes: " + sequence.size(), 60, 630);
  text("Recording: " + (isRecording ? "ON" : "OFF"), 150, 630);
  text("Playing: " + (isPlayingSequence ? "ON" : "OFF"), 250, 630);

  text("Movement Speed (ms):", 60, 655);
  speedSlider.display();
  text(int(speedSlider.getValue()) + " ms", 417, 660);

  textSize(14);
  text("Delay After Move (ms):", 530, 660);
  delaySlider.display();
  text(int(delaySlider.getValue()) + " ms", 817, 660);

  if (!lastLoadedKeyframeFile.equals("")) {
    textSize(12);
    fill(100);
    text("Loaded: " + lastLoadedKeyframeFile, 60, 708);
  }

  recordButton.buttonColor = isRecording ? RECORDING_BUTTON_COLOR : RECORD_BUTTON_COLOR;
  recordButton.label = isRecording ? "Stop Rec" : "Record";
  recordButton.display();

  addKeyframeButton.display();
  playButton.display();
  clearSequenceButton.display();
  exportSketchButton.display();
  saveKeyframesButton.display();
  loadKeyframesButton.display();
}

void drawSequenceStatus() {
  if (millis() - sequenceStatusTime < 3000 && !sequenceStatus.equals("")) {
    fill(200, 0, 100);
    textAlign(LEFT, TOP);
    textSize(14);
    text("● " + sequenceStatus, 400, 720);
  }
}

void drawSketchNamingDialog() {
  fill(0, 0, 0, 150);
  rect(0, 0, width, height);

  fill(255);
  stroke(0);
  strokeWeight(2);
  rect(width/2 - 250, height/2 - 120, 500, 240, 10);

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(16);
  text("Export Arduino Sketch", width/2, height/2 - 80);
  text("Sketch Name: " + tempSketchName + "_", width/2, height/2 - 50);

  textSize(14);
  text("Target Hardware:", width/2, height/2 - 20);
  text(usePWMShield ? "☑ Arduino 16-Channel PWM Shield" : "☐ Standard Arduino Servo", width/2, height/2 + 5);
  text("(Toggle PWM Shield button to change)", width/2, height/2 + 25);

  textSize(16);
  text("Press ENTER to export, ESC to cancel", width/2, height/2 + 50);
  textSize(12);
  text("(Use only letters, numbers, hyphens, underscores)", width/2, height/2 + 75);
}

void mousePressed() {
  redraw();
  if (isEditingLabel || isNamingFile || isNamingSketch) return;

  if (isSelectingFile) {
    int totalPages = (savedFilesList.length + FILES_PER_PAGE - 1) / FILES_PER_PAGE;
    int startIndex = fileListPage * FILES_PER_PAGE;
    int endIndex = min(startIndex + FILES_PER_PAGE, savedFilesList.length);

    for (int i = startIndex; i < endIndex; i++) {
      int displayIndex = i - startIndex;
      float fileY = height/2 - 110 + displayIndex * 30;
      if (mouseX >= width/2 - 280 && mouseX <= width/2 + 280 &&
        mouseY >= fileY - 12 && mouseY <= fileY + 12) {
        selectedFileIndex = i;
        return;
      }
    }

    if (fileListPage > 0) {
      if (mouseX >= width/2 - 270 && mouseX <= width/2 - 150 &&
        mouseY >= height/2 -180 && mouseY <= height/2 -150) {
        fileListPage--;
        selectedFileIndex = -1;
        return;
      }
    }

    if (fileListPage < totalPages - 1) {
      if (mouseX >= width/2 + 150 && mouseX <= width/2 + 270 &&
        mouseY >= height/2 - 180 && mouseY <= height/2 - 150) {
        fileListPage++;
        selectedFileIndex = -1;
        return;
      }
    }

    return;
  }

  if (pwmShieldToggleButton.isOver()) {
    togglePWMShield();
    return;
  }

  if (speedSlider.isOver()) {
    speedSlider.locked = true;
    return;
  }
  if (delaySlider.isOver()) {
    delaySlider.locked = true;
    return;
  }

  if (recordButton.isOver()) {
    toggleRecording();
    return;
  }
  if (addKeyframeButton.isOver()) {
    addKeyframe();
    return;
  }
  if (playButton.isOver()) {
    playSequence();
    return;
  }
  if (clearSequenceButton.isOver()) {
    clearSequence();
    return;
  }
  if (exportSketchButton.isOver()) {
    startSketchNaming();
    return;
  }

  if (saveKeyframesButton.isOver()) {
    saveKeyframesToFile();
    return;
  }
  if (loadKeyframesButton.isOver()) {
    startFileSelection("loadKeyframes");
    return;
  }

  for (int i = 0; i < NUM_SERVOS; i++) {
    if (servoActive[i] && servoSliders[i].isOver()) {
      servoSliders[i].locked = true;
      return;
    }
  }

  for (int i = 0; i < NUM_SERVOS; i++) {
    if (activeButtons[i].isOver()) {
      toggleServoActive(i);
      return;
    }
  }

  for (int i = 0; i < NUM_SERVOS; i++) {
    if (!servoActive[i]) continue;

    if (centerButtons[i].isOver()) {
      centerServo(i);
      return;
    } else if (setCenterButtons[i].isOver()) {
      setCenterPosition(i);
      return;
    } else if (minButtons[i].isOver()) {
      setMinLimit(i);
      return;
    } else if (maxButtons[i].isOver()) {
      setMaxLimit(i);
      return;
    } else if (resetButtons[i].isOver()) {
      resetLimits(i);
      return;
    } else if (labelButtons[i].isOver()) {
      startLabelEdit(i);
      return;
    }
  }

  if (allActiveButton.isOver()) {
    setAllServosActive();
  } else if (allInactiveButton.isOver()) {
    setAllServosInactive();
  } else if (reconnectButton.isOver()) {
    manualReconnect();
  } else if (saveSettingsButton.isOver()) {
    startFileNaming();
  } else if (saveAsSettingsButton.isOver()) {  // NEW: Handle Save As button
    startFileNamingAs();
  } else if (loadSettingsButton.isOver()) {
    startFileSelection("load");
  } else if (deleteSettingsButton.isOver()) {
    startFileSelection("delete");
  }
}

void mouseReleased() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoSliders[i].locked = false;
  }
  speedSlider.locked = false;
  delaySlider.locked = false;
}

void mouseDragged() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (servoActive[i] && servoSliders[i].locked) {
      servoSliders[i].updatePosition(mouseX);
      updateServoPosition(i, int(servoSliders[i].getValue()));
    }
  }

  if (speedSlider.locked) {
    speedSlider.updatePosition(mouseX);
  }
  if (delaySlider.locked) {
    delaySlider.updatePosition(mouseX);
  }
}

void keyPressed() {
  if (isEditingLabel) {
    if (key == ENTER) {
      if (tempLabel.length() > 0) {
        servoLabels[editingServoIndex] = tempLabel;
      }
      isEditingLabel = false;
      tempLabel = "";
      editingServoIndex = -1;
    } else if (key == ESC) {
      isEditingLabel = false;
      tempLabel = "";
      editingServoIndex = -1;
      key = 0;
    } else if (key == BACKSPACE) {
      if (tempLabel.length() > 0) {
        tempLabel = tempLabel.substring(0, tempLabel.length() - 1);
      }
    } else if (key >= 32 && key <= 126 && tempLabel.length() < 20) {
      tempLabel += key;
    }
  } else if (isNamingFile) {
    if (key == ENTER) {
      if (isValidFileName(tempFileName)) {
        saveSettingsToFileWithName(tempFileName);
        isNamingFile = false;
        tempFileName = "";
      } else {
        settingsStatus = "Invalid file name";
        settingsStatusTime = millis();
      }
    } else if (key == ESC) {
      isNamingFile = false;
      tempFileName = "";
      key = 0;
    } else if (key == BACKSPACE) {
      if (tempFileName.length() > 0) {
        tempFileName = tempFileName.substring(0, tempFileName.length() - 1);
      }
    } else if (key >= 32 && key <= 126 && tempFileName.length() < 30) {
      tempFileName += key;
    }
  } else if (isNamingSketch) {
    if (key == ENTER) {
      if (isValidFileName(tempSketchName)) {
        exportArduinoSketch(tempSketchName);
        isNamingSketch = false;
        tempSketchName = "";
      } else {
        sequenceStatus = "Invalid sketch name";
        sequenceStatusTime = millis();
      }
    } else if (key == ESC) {
      isNamingSketch = false;
      tempSketchName = "";
      key = 0;
    } else if (key == BACKSPACE) {
      if (tempSketchName.length() > 0) {
        tempSketchName = tempSketchName.substring(0, tempSketchName.length() - 1);
      }
    } else if (key >= 32 && key <= 126 && tempSketchName.length() < 30) {
      tempSketchName += key;
    }
  } else if (isSelectingFile) {
    if (key == ENTER && selectedFileIndex >= 0) {
      String selectedFile = savedFilesList[selectedFileIndex];
      if (fileOperation.equals("load")) {
        loadSettingsFromFileWithName(selectedFile);
      } else if (fileOperation.equals("delete")) {
        deleteSettingsFileWithName(selectedFile);
      } else if (fileOperation.equals("loadKeyframes")) {
        loadKeyframesFromFileWithName(selectedFile);
      }
      isSelectingFile = false;
      selectedFileIndex = -1;
      fileOperation = "";
      fileListPage = 0;
    } else if (key == ESC) {
      isSelectingFile = false;
      selectedFileIndex = -1;
      fileOperation = "";
      fileListPage = 0;
      key = 0;
    }
  } else {
    if (key == 'r' || key == 'R') {
      toggleRecording();
    } else if (key == 'k' || key == 'K') {
      addKeyframe();
    } else if (key == 'p' || key == 'P') {
      playSequence();
    } else if (key == 'c' || key == 'C') {
      clearSequence();
    } else if (key == 's' || key == 'S') {
      togglePWMShield();
    }
  }
}


void togglePWMShield() {
  usePWMShield = !usePWMShield;
  sequenceStatus = "PWM Shield: " + (usePWMShield ? "ON" : "OFF");
  sequenceStatusTime = millis();
}

int countActiveServos(ServoKeyframe kf) {
  int count = 0;
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (kf.activeServos[i]) count++;
  }
  return count;
}

void toggleRecording() {
  isRecording = !isRecording;
  if (isRecording) {
    sequenceStatus = "Recording - press K to add keyframes";
  } else {
    sequenceStatus = "Recording stopped";
  }
  sequenceStatusTime = millis();
}

void addKeyframe() {
  int speed = int(speedSlider.getValue());
  int delay = int(delaySlider.getValue());
  String name = "Keyframe " + (sequence.size() + 1);

  ServoKeyframe kf = new ServoKeyframe(speed, delay, name);
  int activeCount = countActiveServos(kf);
  sequence.add(kf);

  sequenceStatus = "Added keyframe " + sequence.size() + " (" + activeCount + " servos)";
  sequenceStatusTime = millis();
}

void playSequence() {
  if (sequence.size() == 0) {
    sequenceStatus = "No keyframes to play";
    sequenceStatusTime = millis();
    return;
  }

  if (isPlayingSequence) {
    isPlayingSequence = false;
    sequenceStatus = "Playback stopped";
  } else {
    isPlayingSequence = true;
    playbackIndex = 0;
    playbackStartTime = millis();
    sequenceStatus = "Playing sequence";
  }
  sequenceStatusTime = millis();
}

void clearSequence() {
  sequence.clear();
  isPlayingSequence = false;
  sequenceStatus = "Sequence cleared";
  sequenceStatusTime = millis();
}

void startSketchNaming() {
  if (sequence.size() == 0) {
    sequenceStatus = "No keyframes to export";
    sequenceStatusTime = millis();
    return;
  }
  isNamingSketch = true;
  tempSketchName = "";
}

void updateSequencePlayback() {
  if (playbackIndex >= sequence.size()) {
    isPlayingSequence = false;
    isExecutingKeyframe = false;
    sequenceStatus = "Playback complete";
    sequenceStatusTime = millis();
    return;
  }

  ServoKeyframe currentFrame = sequence.get(playbackIndex);

  if (!isExecutingKeyframe) {
    isExecutingKeyframe = true;
    executionStartTime = millis();
    currentKeyframeIndex = playbackIndex;
    keyframeSpeed = currentFrame.speed;

    for (int i = 0; i < NUM_SERVOS; i++) {
      startPositions[i] = servoPositions[i];
      targetPositions[i] = currentFrame.positions[i];
      keyframeActiveServos[i] = currentFrame.activeServos[i];

      if (currentFrame.activeServos[i] && !servoActive[i]) {
        servoActive[i] = true;
        if (connected) {
          arduinoPort.write("ACTIVE:" + i + ":1\n");
          delay(10);
        }
      }
    }
  }

  int elapsed = millis() - executionStartTime;

  if (elapsed < keyframeSpeed) {
    float progress = (float)elapsed / (float)keyframeSpeed;
    float easedProgress = easeInOutCubic(progress);

    for (int i = 0; i < NUM_SERVOS; i++) {
      if (keyframeActiveServos[i]) {
        int deltaPos = targetPositions[i] - startPositions[i];
        int newPos = startPositions[i] + (int)(deltaPos * easedProgress);
        newPos = constrain(newPos, 0, 180);

        servoSliders[i].setValue(newPos);

        if (connected) {
          servoPositions[i] = newPos;
          arduinoPort.write("S:" + i + ":" + newPos + "\n");
          delay(5);
        }
      }
    }
  } else if (elapsed < keyframeSpeed + currentFrame.delay) {
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (keyframeActiveServos[i]) {
        servoSliders[i].setValue(targetPositions[i]);
        if (connected) {
          servoPositions[i] = targetPositions[i];
          arduinoPort.write("S:" + i + ":" + targetPositions[i] + "\n");
        }
      }
    }
  } else {
    isExecutingKeyframe = false;
    playbackIndex++;
    playbackStartTime = millis();
  }
}

float easeInOutCubic(float t) {
  if (t < 0.5) {
    return 4.0 * t * t * t;
  } else {
    float f = (2.0 * t) - 2.0;
    return 1.0 + (f * f * f) / 2.0;
  }
}

// ******************************************************************************************
// ******************************************************************************************

// FIXED: I can now export the Arduino sketch with proper multi-servo simultaneous movement and speed control
void exportArduinoSketch(String sketchName) {
  if (sequence.size() == 0) {
    sequenceStatus = "No keyframes to export";
    sequenceStatusTime = millis();
    return;
  }

  ArrayList<String> sketchLines = new ArrayList<String>();

  // Header
  sketchLines.add("/*");
  sketchLines.add(" * Generated Multi-Servo Animatronic Sequence Sketch");
  sketchLines.add(" * Created by Webrobotix Servo Controller v2");
  sketchLines.add(" * Date: " + month() + "/" + day() + "/" + year());
  sketchLines.add(" * Keyframes: " + sequence.size());
  sketchLines.add(" * Hardware: " + (usePWMShield ? "Arduino 16-Channel 12-bit PWM Servo Shield" : "Standard Arduino Servo Library"));
  sketchLines.add(" * FIXED: Proper speed control for smooth servo movement");
  sketchLines.add(" */");
  sketchLines.add("");

  if (usePWMShield) {
    // PWM Shield version
    sketchLines.add("#include <Wire.h>");
    sketchLines.add("#include <Adafruit_PWMServoDriver.h>");
    sketchLines.add("");
    sketchLines.add("// Create the PWM driver object");
    sketchLines.add("Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();");
    sketchLines.add("");
    sketchLines.add("// Servo configuration");
    sketchLines.add("#define SERVOMIN  100 // minimum pulse length (out of 4096)");
    sketchLines.add("#define SERVOMAX  600 // maximum pulse length (out of 4096)");
    sketchLines.add("#define SERVO_FREQ 50 // 50 Hz for servos");
  } else {
    // Standard servo library version
    sketchLines.add("#include <Servo.h>");
  }
  sketchLines.add("");

  // Find which servos are used
  boolean[] usedServos = new boolean[NUM_SERVOS];
  for (ServoKeyframe kf : sequence) {
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (kf.activeServos[i]) {
        usedServos[i] = true;
      }
    }
  }

  if (!usePWMShield) {
    // Servo declarations for standard library
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (usedServos[i]) {
        sketchLines.add("Servo servo" + i + ";  // " + servoLabels[i]);
      }
    }
    sketchLines.add("");

    // Pin definitions (adjust these for your setup)
    sketchLines.add("// Pin definitions - adjust for your servo connections");
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (usedServos[i]) {
        int pin = i + 2; // Assuming pins start at 2
        sketchLines.add("const int SERVO" + i + "_PIN = " + pin + ";");
      }
    }
  } else {
    // PWM Shield - servos are on channels 0-15
    sketchLines.add("// PWM Shield channels (0-15) for servos");
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (usedServos[i]) {
        sketchLines.add("const int SERVO" + i + "_CHANNEL = " + i + ";  // " + servoLabels[i]);
      }
    }
  }
  sketchLines.add("");

  // Helper function for PWM Shield
  if (usePWMShield) {
    sketchLines.add("// Convert angle to PWM pulse length");
    sketchLines.add("int angleToPulse(int angle) {");
    sketchLines.add("  return map(angle, 0, 180, SERVOMIN, SERVOMAX);");
    sketchLines.add("}");
    sketchLines.add("");
  }

  // Keyframe data structure
  sketchLines.add("// Keyframe structure");
  sketchLines.add("struct Keyframe {");
  sketchLines.add("  int positions[" + NUM_SERVOS + "];");
  sketchLines.add("  bool activeServos[" + NUM_SERVOS + "];");
  sketchLines.add("  unsigned long speed;  // Movement duration in milliseconds");
  sketchLines.add("  unsigned long delayAfter;  // Delay after movement in milliseconds");
  sketchLines.add("};");
  sketchLines.add("");

  // Current position tracking
  sketchLines.add("// Current servo positions for smooth movement");
  String initLine = "int currentPositions[" + NUM_SERVOS + "] = {";
  for (int i = 0; i < NUM_SERVOS; i++) {
    initLine += "90"; // Start all at center
    if (i < NUM_SERVOS - 1) initLine += ", ";
  }
  initLine += "};";
  sketchLines.add(initLine);
  sketchLines.add("");

  // Keyframe data
  sketchLines.add("// Sequence data (" + sequence.size() + " keyframes)");
  sketchLines.add("const int NUM_KEYFRAMES = " + sequence.size() + ";");
  sketchLines.add("Keyframe sequence[NUM_KEYFRAMES] = {");

  for (int i = 0; i < sequence.size(); i++) {
    ServoKeyframe kf = sequence.get(i);
    String line = "  { {";

    // Positions array
    for (int j = 0; j < NUM_SERVOS; j++) {
      line += kf.positions[j];
      if (j < NUM_SERVOS - 1) line += ", ";
    }
    line += "}, {";

    // Active servos array
    for (int j = 0; j < NUM_SERVOS; j++) {
      line += (kf.activeServos[j] ? "true" : "false");
      if (j < NUM_SERVOS - 1) line += ", ";
    }
    line += "}, " + kf.speed + "UL, " + kf.delay + "UL }"; // UL for unsigned long

    if (i < sequence.size() - 1) line += ",";

    // Add comment showing which servos are active
    int activeCount = 0;
    String activeList = "";
    for (int j = 0; j < NUM_SERVOS; j++) {
      if (kf.activeServos[j]) {
        if (activeCount > 0) activeList += ",";
        activeList += j;
        activeCount++;
      }
    }
    line += "  // " + activeCount + " servos: " + activeList + " (" + kf.speed + "ms, " + kf.delay + "ms)";

    sketchLines.add(line);
  }
  sketchLines.add("};");
  sketchLines.add("");

  // Setup function
  sketchLines.add("void setup() {");
  sketchLines.add("  Serial.begin(115200);");
  sketchLines.add("  Serial.println(\"Multi-Servo Animatronic Sequence Controller Started\");");
  sketchLines.add("  Serial.println(\"Hardware: " + (usePWMShield ? "PWM Shield" : "Standard Servos") + "\");");
  sketchLines.add("  Serial.println(\"Keyframes: \" + String(NUM_KEYFRAMES));");
  sketchLines.add("");

  if (usePWMShield) {
    sketchLines.add("  // Initialize PWM shield");
    sketchLines.add("  pwm.begin();");
    sketchLines.add("  pwm.setPWMFreq(SERVO_FREQ);");
    sketchLines.add("  delay(10);");
  } else {
    sketchLines.add("  // Attach servos");
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (usedServos[i]) {
        sketchLines.add("  servo" + i + ".attach(SERVO" + i + "_PIN);");
      }
    }
  }
  sketchLines.add("");
  sketchLines.add("  // Initialize all servos to center position");
  sketchLines.add("  for (int i = 0; i < " + NUM_SERVOS + "; i++) {");
  if (usePWMShield) {
    sketchLines.add("    pwm.setPWM(i, 0, angleToPulse(90));");
  } else {
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (usedServos[i]) {
        sketchLines.add("    if (i == " + i + ") servo" + i + ".write(90);");
      }
    }
  }
  sketchLines.add("  }");
  sketchLines.add("");
  sketchLines.add("  delay(2000); // Wait 2 seconds before starting sequence");
  sketchLines.add("}");
  sketchLines.add("");

  // Main loop function
  sketchLines.add("void loop() {");
  sketchLines.add("  Serial.println(\"Starting sequence playback...\");");
  sketchLines.add("");
  sketchLines.add("  for (int i = 0; i < NUM_KEYFRAMES; i++) {");
  sketchLines.add("    Serial.print(\"Executing keyframe \");");
  sketchLines.add("    Serial.print(i + 1);");
  sketchLines.add("    Serial.print(\"/\");");
  sketchLines.add("    Serial.print(NUM_KEYFRAMES);");
  sketchLines.add("    Serial.print(\" (Speed: \");");
  sketchLines.add("    Serial.print(sequence[i].speed);");
  sketchLines.add("    Serial.print(\"ms, Delay: \");");
  sketchLines.add("    Serial.print(sequence[i].delayAfter);");
  sketchLines.add("    Serial.println(\"ms)\");");
  sketchLines.add("    ");
  sketchLines.add("    executeKeyframe(i);");
  sketchLines.add("    ");
  sketchLines.add("    // Wait for the delay period after movement");
  sketchLines.add("    if (sequence[i].delayAfter > 0) {");
  sketchLines.add("      Serial.print(\"Waiting \");");
  sketchLines.add("      Serial.print(sequence[i].delayAfter);");
  sketchLines.add("      Serial.println(\"ms...\");");
  sketchLines.add("      delay(sequence[i].delayAfter);");
  sketchLines.add("    }");
  sketchLines.add("  }");
  sketchLines.add("");
  sketchLines.add("  Serial.println(\"Sequence complete. Waiting 3 seconds before repeat...\");");
  sketchLines.add("  delay(3000); // Wait 3 seconds before repeating");
  sketchLines.add("}");
  sketchLines.add("");

  // FIXED: Execute keyframe function with proper speed control
  sketchLines.add("// Execute a keyframe with proper speed control");
  sketchLines.add("void executeKeyframe(int keyframeIndex) {");
  sketchLines.add("  if (keyframeIndex < 0 || keyframeIndex >= NUM_KEYFRAMES) return;");
  sketchLines.add("");
  sketchLines.add("  Keyframe kf = sequence[keyframeIndex];");
  sketchLines.add("  ");
  sketchLines.add("  // Count active servos");
  sketchLines.add("  int activeCount = 0;");
  sketchLines.add("  for (int i = 0; i < " + NUM_SERVOS + "; i++) {");
  sketchLines.add("    if (kf.activeServos[i]) activeCount++;");
  sketchLines.add("  }");
  sketchLines.add("  ");
  sketchLines.add("  if (activeCount == 0) {");
  sketchLines.add("    Serial.println(\"No active servos in this keyframe\");");
  sketchLines.add("    return;");
  sketchLines.add("  }");
  sketchLines.add("  ");
  sketchLines.add("  Serial.print(\"Moving \");");
  sketchLines.add("  Serial.print(activeCount);");
  sketchLines.add("  Serial.print(\" servos over \");");
  sketchLines.add("  Serial.print(kf.speed);");
  sketchLines.add("  Serial.println(\" milliseconds\");");
  sketchLines.add("");

  // Calculate movement parameters
  sketchLines.add("  // Calculate movement parameters");
  sketchLines.add("  unsigned long startTime = millis();");
  sketchLines.add("  const int UPDATE_INTERVAL = 20; // 50 FPS for smooth movement");
  sketchLines.add("  unsigned long nextUpdate = startTime + UPDATE_INTERVAL;");
  sketchLines.add("");

  // Store starting positions
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (usedServos[i]) {
      sketchLines.add("  int startPos" + i + " = currentPositions[" + i + "];");
      sketchLines.add("  int targetPos" + i + " = kf.positions[" + i + "];");
      sketchLines.add("  int deltaPos" + i + " = targetPos" + i + " - startPos" + i + ";");
    }
  }
  sketchLines.add("");

  // Main movement loop with proper timing
  sketchLines.add("  // Smooth movement loop");
  sketchLines.add("  while (millis() - startTime < kf.speed) {");
  sketchLines.add("    unsigned long currentTime = millis();");
  sketchLines.add("    ");
  sketchLines.add("    // Only update at the specified interval for smooth movement");
  sketchLines.add("    if (currentTime >= nextUpdate) {");
  sketchLines.add("      float progress = (float)(currentTime - startTime) / (float)kf.speed;");
  sketchLines.add("      ");
  sketchLines.add("      // Ensure progress doesn't exceed 1.0");
  sketchLines.add("      if (progress > 1.0) progress = 1.0;");
  sketchLines.add("      ");
  sketchLines.add("      // Apply easing function for natural movement");
  sketchLines.add("      float easedProgress = easeInOutCubic(progress);");
  sketchLines.add("      ");
  sketchLines.add("      // Update all active servos simultaneously");

  for (int i = 0; i < NUM_SERVOS; i++) {
    if (usedServos[i]) {
      sketchLines.add("      if (kf.activeServos[" + i + "]) {");
      sketchLines.add("        int newPos = startPos" + i + " + (int)(deltaPos" + i + " * easedProgress);");
      sketchLines.add("        newPos = constrain(newPos, 0, 180);");
      sketchLines.add("        currentPositions[" + i + "] = newPos;");

      if (usePWMShield) {
        sketchLines.add("        pwm.setPWM(" + i + ", 0, angleToPulse(newPos));");
      } else {
        sketchLines.add("        servo" + i + ".write(newPos);");
      }
      sketchLines.add("      }");
    }
  }

  sketchLines.add("      ");
  sketchLines.add("      nextUpdate = currentTime + UPDATE_INTERVAL;");
  sketchLines.add("    }");
  sketchLines.add("    ");
  sketchLines.add("    // Small delay to prevent overwhelming the processor");
  sketchLines.add("    delayMicroseconds(1000); // 1ms delay");
  sketchLines.add("  }");
  sketchLines.add("");
  sketchLines.add("  // Ensure all servos reach their exact final positions");

  for (int i = 0; i < NUM_SERVOS; i++) {
    if (usedServos[i]) {
      sketchLines.add("  if (kf.activeServos[" + i + "]) {");
      sketchLines.add("    currentPositions[" + i + "] = kf.positions[" + i + "];");
      if (usePWMShield) {
        sketchLines.add("    pwm.setPWM(" + i + ", 0, angleToPulse(kf.positions[" + i + "]));");
      } else {
        sketchLines.add("    servo" + i + ".write(kf.positions[" + i + "]);");
      }
      sketchLines.add("  }");
    }
  }

  sketchLines.add("  ");
  sketchLines.add("  Serial.println(\"Keyframe movement complete\");");
  sketchLines.add("}");
  sketchLines.add("");

  // Enhanced easing function
  sketchLines.add("// Enhanced cubic ease-in-out function for natural, lifelike movement");
  sketchLines.add("float easeInOutCubic(float t) {");
  sketchLines.add("  if (t < 0.5) {");
  sketchLines.add("    return 4.0 * t * t * t;");
  sketchLines.add("  } else {");
  sketchLines.add("    float f = (2.0 * t) - 2.0;");
  sketchLines.add("    return 1.0 + (f * f * f) / 2.0;");
  sketchLines.add("  }");
  sketchLines.add("}");

  // Save the sketch file
  String[] sketchArray = sketchLines.toArray(new String[sketchLines.size()]);
  String hardwareType = usePWMShield ? "_PWMShield" : "_StandardServo";
  saveStrings("data/" + sketchName + hardwareType + ".ino", sketchArray);  // hardwareType + "_FIXED.ino"

  sequenceStatus = "FIXED sketch exported as '" + sketchName + hardwareType + ""; // "_FIXED.ino' with proper speed control"
  sequenceStatusTime = millis();

  println("FIXED Arduino sketch exported: " + sketchName + hardwareType + ".ino"); // _FIXED
  println("Key improvements:");
  println("- Proper timing control using millis() instead of delay()");
  println("- Separate movement and delay phases");
  println("- 50 FPS update rate for smooth movement");
  println("- Enhanced easing function");
  println("- Accurate progress calculation");
}

void checkForNewSerialPorts() {
  if (connected) {
    try {
      if (arduinoPort != null && arduinoPort.available() >= 0) {
        return;
      }
    }
    catch (Exception e) {
      connected = false;
      connectedPort = "";
      connectionStatus = "Connection lost";
      connectionStatusTime = millis();
    }
  }

  if (!connected) {
    establishConnection();
  }
}

void establishConnection() {
  serialPorts = Serial.list();

  if (serialPorts.length == 0) {
    connectionStatus = "No serial ports";
    connectionStatusTime = millis();
    return;
  }

  connectionStatus = "Scanning...";
  connectionStatusTime = millis();

  for (int i = 0; i < serialPorts.length; i++) {
    try {
      if (arduinoPort != null) {
        arduinoPort.stop();
      }

      arduinoPort = new Serial(this, serialPorts[i], 115200);
      arduinoPort.bufferUntil('\n');
      delay(2000);
      arduinoPort.write("GETALL\n");

      int timeout = 0;
      boolean responded = false;
      while (timeout < 50 && !responded) {
        if (arduinoPort.available() > 0) {
          responded = true;
        }
        delay(100);
        timeout++;
      }

      if (responded) {
        connected = true;
        connectedPort = serialPorts[i];
        connectionStatus = "Connected to " + connectedPort;
        connectionStatusTime = millis();

        delay(500);
        arduinoPort.write("ALLINACTIVE\n");
        break;
      } else {
        arduinoPort.stop();
      }
    }
    catch (Exception e) {
      if (arduinoPort != null) {
        try {
          arduinoPort.stop();
        }
        catch (Exception e2) {
        }
      }
    }
  }

  if (!connected) {
    connectionStatus = "Unable to connect";
    connectionStatusTime = millis();
  }
}

void centerServo(int servoNum) {
  if (!connected || !servoActive[servoNum]) return;
  servoSliders[servoNum].setValue(servoCenterPositions[servoNum]);
  updateServoPosition(servoNum, servoCenterPositions[servoNum]);
}

void setCenterPosition(int servoNum) {
  if (!connected || !servoActive[servoNum]) return;
  int currentPosition = int(servoSliders[servoNum].getValue());
  servoCenterPositions[servoNum] = currentPosition;
  arduinoPort.write("SETCENTER:" + servoNum + ":" + currentPosition + "\n");
}

void setMinLimit(int servoNum) {
  if (!connected || !servoActive[servoNum]) return;
  int currentPosition = int(servoSliders[servoNum].getValue());
  servoMinLimits[servoNum] = currentPosition;
  servoSliders[servoNum].min = currentPosition;
  arduinoPort.write("SETMINLIMIT:" + servoNum + ":" + currentPosition + "\n");
}

void setMaxLimit(int servoNum) {
  if (!connected || !servoActive[servoNum]) return;
  int currentPosition = int(servoSliders[servoNum].getValue());
  servoMaxLimits[servoNum] = currentPosition;
  servoSliders[servoNum].max = currentPosition;
  arduinoPort.write("SETMAXLIMIT:" + servoNum + ":" + currentPosition + "\n");
}

void resetLimits(int servoNum) {
  if (!connected || !servoActive[servoNum]) return;
  servoMinLimits[servoNum] = 0;
  servoMaxLimits[servoNum] = 180;
  servoCenterPositions[servoNum] = 90;
  servoSliders[servoNum].min = 0;
  servoSliders[servoNum].max = 180;
  arduinoPort.write("RESET:" + servoNum + "\n");
}

void updateServoPosition(int servoNum, int position) {
  if (!connected || !servoActive[servoNum]) return;
  servoPositions[servoNum] = position;
  String command = "S:" + servoNum + ":" + position + "\n";
  arduinoPort.write(command);
}

void readSerialData() {
  try {
    while (arduinoPort.available() > 0) {
      String data = arduinoPort.readStringUntil('\n');
      if (data != null) {
        data = trim(data);

        if (data.startsWith("PO:")) {
          String[] parts = split(data, ':');
          int servoNum = int(parts[1]);
          int position = int(parts[2]);
          if (!servoSliders[servoNum].locked) {
            servoPositions[servoNum] = position;
            servoSliders[servoNum].setValue(position);
          }
        } else if (data.startsWith("MI:")) {
          String[] parts = split(data, ':');
          int servoNum = int(parts[1]);
          servoMinLimits[servoNum] = int(parts[2]);
          servoSliders[servoNum].min = int(parts[2]);
        } else if (data.startsWith("MA:")) {
          String[] parts = split(data, ':');
          int servoNum = int(parts[1]);
          servoMaxLimits[servoNum] = int(parts[2]);
          servoSliders[servoNum].max = int(parts[2]);
        } else if (data.startsWith("CE:")) {
          String[] parts = split(data, ':');
          servoCenterPositions[int(parts[1])] = int(parts[2]);
        } else if (data.startsWith("AC:")) {
          String[] parts = split(data, ':');
          servoActive[int(parts[1])] = int(parts[2]) == 1;
        } else if (data.startsWith("RE:")) {
          String[] parts = split(data, ':');
          int servoNum = int(parts[1]);
          servoMinLimits[servoNum] = 0;
          servoMaxLimits[servoNum] = 180;
          servoCenterPositions[servoNum] = 90;
          servoSliders[servoNum].min = 0;
          servoSliders[servoNum].max = 180;
        }
      }
    }
  }
  catch (Exception e) {
    connected = false;
    connectedPort = "";
    connectionStatus = "Connection error";
    connectionStatusTime = millis();
  }
}

void startLabelEdit(int servoNum) {
  if (!servoActive[servoNum]) return;
  isEditingLabel = true;
  editingServoIndex = servoNum;
  tempLabel = servoLabels[servoNum];
}

void toggleServoActive(int servoNum) {
  servoActive[servoNum] = !servoActive[servoNum];
  if (connected) {
    arduinoPort.write("ACTIVE:" + servoNum + ":" + (servoActive[servoNum] ? "1" : "0") + "\n");
  }
}

void setAllServosActive() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoActive[i] = true;
  }
  if (connected) {
    arduinoPort.write("ALLACTIVE\n");
  }
}

void setAllServosInactive() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoActive[i] = false;
  }
  if (connected) {
    arduinoPort.write("ALLINACTIVE\n");
  }
}

void manualReconnect() {
  if (connected) {
    try {
      arduinoPort.stop();
    }
    catch (Exception e) {
    }
    connected = false;
    connectedPort = "";
  }
  connectionStatus = "Manual reconnect...";
  connectionStatusTime = millis();
  establishConnection();
}

void updateSavedFilesList(String operation) {
  File dataDir = new File(sketchPath("data"));
  if (!dataDir.exists()) {
    dataDir.mkdirs();
  }

  File[] files = dataDir.listFiles();
  ArrayList<String> filesList = new ArrayList<String>();

  if (files != null) {
    String suffix = operation.equals("loadKeyframes") ? "_keyframes.txt" : "_settings.txt";
    for (File file : files) {
      if (file.isFile() && file.getName().endsWith(suffix)) {
        filesList.add(file.getName().replace(suffix, ""));
      }
    }
  }

  savedFilesList = filesList.toArray(new String[filesList.size()]);
}

// MODIFIED: Save uses last loaded filename or prompts
void startFileNaming() {
  if (!lastLoadedFileName.equals("")) {
    saveSettingsToFileWithName(lastLoadedFileName);
  } else {
    isNamingFile = true;
    tempFileName = "";
  }
}

// NEW: Save As always prompts for name
void startFileNamingAs() {
  isNamingFile = true;
  tempFileName = lastLoadedFileName.equals("") ? "" : lastLoadedFileName;
}

void startFileSelection(String operation) {
  updateSavedFilesList(operation);  // Pass operation to filter files

  if (savedFilesList.length == 0 && !operation.equals("save")) {
    if (operation.equals("loadKeyframes")) {
      sequenceStatus = "No saved keyframe files found";
      sequenceStatusTime = millis();
    } else {
      settingsStatus = "No saved settings files found";
      settingsStatusTime = millis();
    }
    return;
  }

  isSelectingFile = true;
  fileOperation = operation;
  selectedFileIndex = -1;
  fileListPage = 0;
}

boolean isValidFileName(String name) {
  if (name.length() == 0 || name.length() > 50) return false;
  return name.matches("[a-zA-Z0-9\\-_]+");
}

void saveSettingsToFileWithName(String fileName) {
  String[] settingsData = new String[NUM_SERVOS * 2 + 4];

  settingsData[0] = "# Servo Settings: " + fileName;
  settingsData[1] = "# Saved: " + day() + "/" + month() + "/" + year();
  settingsData[2] = "# Format: servoNum:minLimit:maxLimit:centerPos:active";
  settingsData[3] = "# Labels: L:servoNum:labelText";

  for (int i = 0; i < NUM_SERVOS; i++) {
    settingsData[i + 4] = i + ":" + servoMinLimits[i] + ":" +
      servoMaxLimits[i] + ":" + servoCenterPositions[i] +
      ":" + (servoActive[i] ? "1" : "0");
  }

  for (int i = 0; i < NUM_SERVOS; i++) {
    settingsData[i + NUM_SERVOS + 4] = "L:" + i + ":" + servoLabels[i];
  }

  saveStrings("data/" + fileName + "_settings.txt", settingsData);
  lastLoadedFileName = fileName;
  settingsStatus = "Saved as '" + fileName + "'";
  settingsStatusTime = millis();
}

void loadSettingsFromFileWithName(String fileName) {
  try {
    String[] settingsData = loadStrings("data/" + fileName + "_settings.txt");
    if (settingsData == null || settingsData.length <= 4) {
      settingsStatus = "Could not read '" + fileName + "'";
      settingsStatusTime = millis();
      return;
    }

    int settingsLoaded = 0;
    int labelsLoaded = 0;

    for (int i = 4; i < settingsData.length; i++) {
      String line = settingsData[i].trim();
      if (line.length() > 0 && line.contains(":")) {

        if (line.startsWith("L:")) {
          String[] parts = split(line.substring(2), ':');
          if (parts.length >= 2) {
            int servoNum = int(trim(parts[0]));
            String label = trim(parts[1]);
            if (parts.length > 2) {
              for (int j = 2; j < parts.length; j++) {
                label += ":" + trim(parts[j]);
              }
            }
            if (servoNum >= 0 && servoNum < NUM_SERVOS) {
              servoLabels[servoNum] = label;
              labelsLoaded++;
            }
          }
        } else {
          String[] parts = split(line, ':');
          if (parts.length >= 5) {
            int servoNum = int(trim(parts[0]));
            if (servoNum >= 0 && servoNum < NUM_SERVOS) {
              servoMinLimits[servoNum] = int(trim(parts[1]));
              servoMaxLimits[servoNum] = int(trim(parts[2]));
              servoCenterPositions[servoNum] = int(trim(parts[3]));
              servoActive[servoNum] = int(trim(parts[4])) == 1;

              servoSliders[servoNum].min = servoMinLimits[servoNum];
              servoSliders[servoNum].max = servoMaxLimits[servoNum];

              if (servoPositions[servoNum] < servoMinLimits[servoNum]) {
                servoPositions[servoNum] = servoMinLimits[servoNum];
                servoSliders[servoNum].setValue(servoMinLimits[servoNum]);
              } else if (servoPositions[servoNum] > servoMaxLimits[servoNum]) {
                servoPositions[servoNum] = servoMaxLimits[servoNum];
                servoSliders[servoNum].setValue(servoMaxLimits[servoNum]);
              }
              settingsLoaded++;
            }
          }
        }
      }
    }

    lastLoadedFileName = fileName;
    settingsStatus = "Loaded " + settingsLoaded + " settings, " + labelsLoaded + " labels";
    settingsStatusTime = millis();

    if (connected) {
      delay(100);
      sendAllSettingsToArduino();
    }
  }
  catch (Exception e) {
    settingsStatus = "Error loading '" + fileName + "'";
    settingsStatusTime = millis();
  }
}

void deleteSettingsFileWithName(String fileName) {
  try {
    File settingsFile = new File(sketchPath("data/" + fileName + "_settings.txt"));
    if (settingsFile.exists() && settingsFile.delete()) {
      settingsStatus = "Deleted '" + fileName + "'";
      settingsStatusTime = millis();
    } else {
      settingsStatus = "Failed to delete";
      settingsStatusTime = millis();
    }
  }
  catch (Exception e) {
    settingsStatus = "Error deleting file";
    settingsStatusTime = millis();
  }
}

void saveKeyframesToFile() {
  if (sequence.size() == 0) {
    sequenceStatus = "No keyframes to save";
    sequenceStatusTime = millis();
    return;
  }

  String fileName = "keyframes_" + year() + month() + day() + "_" + hour() + minute() + second();

  ArrayList<String> keyframeData = new ArrayList<String>();
  keyframeData.add("# Keyframe Sequence Data");
  keyframeData.add("# Saved: " + day() + "/" + month() + "/" + year() + " " + hour() + ":" + minute() + ":" + second());
  keyframeData.add("# Total Keyframes: " + sequence.size());
  keyframeData.add("# Format: KF:speed:delay:name:pos0,pos1,...,pos15:active0,active1,...,active15");

  for (ServoKeyframe kf : sequence) {
    String line = "KF:" + kf.speed + ":" + kf.delay + ":" + kf.name + ":";

    // Positions
    for (int i = 0; i < NUM_SERVOS; i++) {
      line += kf.positions[i];
      if (i < NUM_SERVOS - 1) line += ",";
    }
    line += ":";

    // Active servos
    for (int i = 0; i < NUM_SERVOS; i++) {
      line += (kf.activeServos[i] ? "1" : "0");
      if (i < NUM_SERVOS - 1) line += ",";
    }

    keyframeData.add(line);
  }

  String[] dataArray = keyframeData.toArray(new String[keyframeData.size()]);
  saveStrings("data/" + fileName + "_keyframes.txt", dataArray);

  lastLoadedKeyframeFile = fileName;

  // Also save a reference to the last loaded file
  String[] lastFileRef = new String[1];
  lastFileRef[0] = fileName;
  saveStrings("data/last_keyframes.txt", lastFileRef);

  sequenceStatus = "Saved " + sequence.size() + " keyframes as '" + fileName + "'";
  sequenceStatusTime = millis();
}

void loadKeyframesFromFileWithName(String fileName) {
  try {
    String[] keyframeData = loadStrings("data/" + fileName + "_keyframes.txt");
    if (keyframeData == null || keyframeData.length <= 4) {
      sequenceStatus = "Could not read keyframe file";
      sequenceStatusTime = millis();
      return;
    }

    sequence.clear();
    int keyframesLoaded = 0;

    for (int i = 4; i < keyframeData.length; i++) {
      String line = keyframeData[i].trim();
      if (line.startsWith("KF:")) {
        String[] parts = split(line.substring(3), ':');
        if (parts.length >= 5) {
          int speed = int(trim(parts[0]));
          int delay = int(trim(parts[1]));
          String name = trim(parts[2]);

          ServoKeyframe kf = new ServoKeyframe(speed, delay, name);

          // Parse positions
          String[] positions = split(trim(parts[3]), ',');
          for (int j = 0; j < min(positions.length, NUM_SERVOS); j++) {
            kf.positions[j] = int(trim(positions[j]));
          }

          // Parse active servos
          String[] activeServos = split(trim(parts[4]), ',');
          for (int j = 0; j < min(activeServos.length, NUM_SERVOS); j++) {
            kf.activeServos[j] = int(trim(activeServos[j])) == 1;
          }

          sequence.add(kf);
          keyframesLoaded++;
        }
      }
    }

    lastLoadedKeyframeFile = fileName;

    // Save as last loaded
    String[] lastFileRef = new String[1];
    lastFileRef[0] = fileName;
    saveStrings("data/last_keyframes.txt", lastFileRef);

    sequenceStatus = "Loaded " + keyframesLoaded + " keyframes from '" + fileName + "'";
    sequenceStatusTime = millis();
  }
  catch (Exception e) {
    sequenceStatus = "Error loading keyframes";
    sequenceStatusTime = millis();
  }
}

void loadKeyframesFromFile() {
  try {
    String[] lastFileRef = loadStrings("data/last_keyframes.txt");
    if (lastFileRef != null && lastFileRef.length > 0) {
      String fileName = trim(lastFileRef[0]);
      loadKeyframesFromFileWithName(fileName);
      if (sequenceStatus.contains("Error") || sequenceStatus.contains("Could not")) {
        sequenceStatus = "No previous keyframes";
        sequenceStatusTime = millis();
        lastLoadedKeyframeFile = "";
      }
    }
  }
  catch (Exception e) {
    // No previous keyframes file, that's okay
    lastLoadedKeyframeFile = "";
  }
}

void loadSettingsFromFile() {
  loadSettingsFromFileWithName("default");
  if (settingsStatus.contains("Could not read") || settingsStatus.contains("Error")) {
    settingsStatus = "No default settings";
    settingsStatusTime = millis();
    lastLoadedFileName = "";
  }
}

void sendAllSettingsToArduino() {
  if (!connected) return;

  for (int i = 0; i < NUM_SERVOS; i++) {
    arduinoPort.write("SETMINLIMIT:" + i + ":" + servoMinLimits[i] + "\n");
    delay(10);
    arduinoPort.write("SETMAXLIMIT:" + i + ":" + servoMaxLimits[i] + "\n");
    delay(10);
    arduinoPort.write("SETCENTER:" + i + ":" + servoCenterPositions[i] + "\n");
    delay(10);
    arduinoPort.write("ACTIVE:" + i + ":" + (servoActive[i] ? "1" : "0") + "\n");
    delay(10);
  }
}

void initializeLabels() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servoLabels[i] = "Servo " + i;
  }
}

void createUI() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    int row = i / 4;
    int col = i % 4;
    int x = MARGIN + col * (SLIDER_WIDTH + MARGIN);
    int y = 70 + row * ROW_HEIGHT;

    servoSliders[i] = new Slider(x, y, SLIDER_WIDTH, SLIDER_HEIGHT, 0, 180);
    servoSliders[i].setValue(90);

    centerButtons[i] = new Button(x, y + 70, 60, BUTTON_HEIGHT, "Center", CENTER_BUTTON_COLOR);
    setCenterButtons[i] = new Button(x, y + 35, 60, BUTTON_HEIGHT, "Set Ctr", SET_CENTER_BUTTON_COLOR);
    minButtons[i] = new Button(x + 65, y + 35, 60, BUTTON_HEIGHT, "Set Min", MIN_BUTTON_COLOR);
    maxButtons[i] = new Button(x + 130, y + 35, 60, BUTTON_HEIGHT, "Set Max", MAX_BUTTON_COLOR);
    resetButtons[i] = new Button(x + 195, y + 35, 50, BUTTON_HEIGHT, "Reset", RESET_BUTTON_COLOR);
    labelButtons[i] = new Button(x + 250, y + 35, 50, BUTTON_HEIGHT, "Label", LABEL_BUTTON_COLOR);
    activeButtons[i] = new Button(x + 65, y + 70, 60, BUTTON_HEIGHT, "Active", ACTIVE_BUTTON_COLOR);
  }

  allActiveButton = new Button(WINDOW_WIDTH - 1225, WINDOW_HEIGHT - 50, 100, 40, "All Active", color(100, 255, 100));
  allInactiveButton = new Button(WINDOW_WIDTH - 1100, WINDOW_HEIGHT - 50, 100, 40, "All Inactive", color(255, 100, 100));
  reconnectButton = new Button(WINDOW_WIDTH - 1275, WINDOW_HEIGHT - 795, 80, 30, "Connect", color(255));

  // MODIFIED: Adjusted positions for Save As button
  saveSettingsButton = new Button(WINDOW_WIDTH - 720, WINDOW_HEIGHT - 50, 80, 40, "Save", SAVE_SETTINGS_BUTTON_COLOR);
  saveAsSettingsButton = new Button(WINDOW_WIDTH - 630, WINDOW_HEIGHT - 50, 80, 40, "Save As", SAVE_SETTINGS_BUTTON_COLOR);
  loadSettingsButton = new Button(WINDOW_WIDTH - 540, WINDOW_HEIGHT - 50, 80, 40, "Load", LOAD_SETTINGS_BUTTON_COLOR);
  deleteSettingsButton = new Button(WINDOW_WIDTH - 450, WINDOW_HEIGHT - 50, 80, 40, "Delete", DELETE_SETTINGS_BUTTON_COLOR);

  pwmShieldToggleButton = new Button(WINDOW_WIDTH - 360, WINDOW_HEIGHT - 50, 120, 40, "PWM Shield", PWM_SHIELD_BUTTON_COLOR);

  recordButton = new Button(60, 680, 80, 30, "Record", RECORD_BUTTON_COLOR);
  addKeyframeButton = new Button(150, 680, 80, 30, "Add Frame", color(100, 200, 255));
  playButton = new Button(240, 680, 80, 30, "Play", PLAY_BUTTON_COLOR);
  clearSequenceButton = new Button(330, 680, 80, 30, "Clear", CLEAR_BUTTON_COLOR);
  exportSketchButton = new Button(420, 680, 80, 30, "Export", EXPORT_BUTTON_COLOR);
  saveKeyframesButton = new Button(510, 680, 90, 30, "Save Keys", color(100, 200, 100));
  loadKeyframesButton = new Button(610, 680, 90, 30, "Load Keys", color(100, 150, 255));

  speedSlider = new Slider(200, 650, 150, 20, 100, 5000);
  speedSlider.setValue(1000);
  delaySlider = new Slider(600, 650, 150, 20, 0, 3000);
  delaySlider.setValue(500);
}

void drawServoControl(int servoNum) {
  int row = servoNum / 4;
  int col = servoNum % 4;
  int x = MARGIN + col * (SLIDER_WIDTH + MARGIN);
  int y = 70 + row * ROW_HEIGHT;

  color textColor = servoActive[servoNum] ? TEXT_COLOR : INACTIVE_TEXT_COLOR;

  fill(textColor);
  textAlign(LEFT, CENTER);
  textSize(14);
  String statusText = servoActive[servoNum] ? " (ACTIVE)" : " (INACTIVE)";
  text(servoLabels[servoNum] + " (" + servoPositions[servoNum] + "°)" + statusText, x, y - 10);

  textSize(12);
  text("Min: " + servoMinLimits[servoNum] + "° | Max: " + servoMaxLimits[servoNum] +
    "° | Ctr: " + servoCenterPositions[servoNum] + "°", x + 135, y + 90);

  servoSliders[servoNum].display(servoActive[servoNum]);

  if (servoActive[servoNum]) {
    centerButtons[servoNum].display();
    setCenterButtons[servoNum].display();
    minButtons[servoNum].display();
    maxButtons[servoNum].display();
    resetButtons[servoNum].display();
    labelButtons[servoNum].display();
  } else {
    centerButtons[servoNum].displayInactive();
    setCenterButtons[servoNum].displayInactive();
    minButtons[servoNum].displayInactive();
    maxButtons[servoNum].displayInactive();
    resetButtons[servoNum].displayInactive();
    labelButtons[servoNum].displayInactive();
  }

  activeButtons[servoNum].buttonColor = servoActive[servoNum] ? ACTIVE_BUTTON_COLOR : INACTIVE_BUTTON_COLOR;
  activeButtons[servoNum].label = servoActive[servoNum] ? "Active" : "Inactive";
  activeButtons[servoNum].display();
}

// MODIFIED: Show current filename
void drawSettingsStatus() {
  if (millis() - settingsStatusTime < 3000 && !settingsStatus.equals("")) {
    fill(0, 100, 200);
    textAlign(LEFT, TOP);
    textSize(14);
    text("● " + settingsStatus, 880, 700);
  }

  // Show currently loaded file
  if (!lastLoadedFileName.equals("")) {
    fill(100);
    textAlign(LEFT, TOP);
    textSize(18);
    text("Current file: " + lastLoadedFileName, 880, 720);
  }
}

void drawConnectionStatus() {
  textAlign(LEFT, TOP);
  textSize(16);

  int statusX = 10;
  int statusY = 10;
  int statusSize = 12;

  fill(connected ? color(0, 200, 0) : color(200, 0, 0));
  ellipse(statusX + statusSize/2, statusY + statusSize/2, statusSize, statusSize);

  fill(100);
  textSize(12);
  text("Auto-scan: " + (CONNECTION_CHECK_INTERVAL - (millis() - lastConnectionCheck))/1000 + "s",
    statusX + 98, statusY + 17);

  if (millis() - connectionStatusTime < 3000) {
    fill(0, 100, 200);
    textSize(14);
    text("● " + connectionStatus, statusX + 80, statusY + 2);
  }
}

void drawLabelEditDialog() {
  fill(0, 0, 0, 150);
  rect(0, 0, width, height);

  fill(255);
  stroke(0);
  strokeWeight(2);
  rect(width/2 - 200, height/2 - 80, 400, 160, 10);

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(16);
  text("Edit Label for Servo " + editingServoIndex, width/2, height/2 - 40);
  text("Current: " + servoLabels[editingServoIndex], width/2, height/2 - 20);
  text("New: " + tempLabel + "_", width/2, height/2 + 10);
  text("Press ENTER to save, ESC to cancel", width/2, height/2 + 40);
}

void drawFileNamingDialog() {
  fill(0, 0, 0, 150);
  rect(0, 0, width, height);

  fill(255);
  stroke(0);
  strokeWeight(2);
  rect(width/2 - 200, height/2 - 80, 400, 160, 10);

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(16);
  text("Enter Settings File Name", width/2, height/2 - 40);
  text("Name: " + tempFileName + "_", width/2, height/2 - 10);
  text("Press ENTER to save, ESC to cancel", width/2, height/2 + 20);
  text("(Letters, numbers, hyphens, underscores only)", width/2, height/2 + 40);
}

void drawFileSelectionDialog() {
  fill(0, 0, 0, 150);
  rect(0, 0, width, height);

  fill(255);
  stroke(0);
  strokeWeight(2);
  rect(width/2 - 300, height/2 - 200, 600, 400, 10);

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(18);
  String operation = fileOperation.equals("load") ? "Load" :
    fileOperation.equals("loadKeyframes") ? "Load Keyframes" : "Delete";
  text(operation + " Settings File", width/2, height/2 - 170);

  if (savedFilesList.length == 0) {
    text("No saved files found", width/2, height/2 - 50);
  } else {
    int totalPages = (savedFilesList.length + FILES_PER_PAGE - 1) / FILES_PER_PAGE;
    int startIndex = fileListPage * FILES_PER_PAGE;
    int endIndex = min(startIndex + FILES_PER_PAGE, savedFilesList.length);

    textSize(14);
    text("Page " + (fileListPage + 1) + " of " + totalPages, width/2, height/2 - 140);

    for (int i = startIndex; i < endIndex; i++) {
      int displayIndex = i - startIndex;
      float fileY = height/2 - 110 + displayIndex * 30;

      if (i == selectedFileIndex) {
        fill(100, 150, 255);
        noStroke();
        rect(width/2 - 280, fileY - 12, 560, 24, 5);
      }

      fill(selectedFileIndex == i ? color(255) : color(0));
      textAlign(LEFT, CENTER);
      textSize(13);
      text((i + 1) + ". " + savedFilesList[i], width/2 - 270, fileY);
    }

    fill(0);
    textAlign(CENTER, CENTER);
    textSize(14);
    text("Click to select, ENTER to confirm, ESC to cancel", width/2, height/2 + 90);

    if (selectedFileIndex >= 0) {
      fill(0, 100, 200);
      textSize(12);
      text("Selected: " + savedFilesList[selectedFileIndex], width/2, height/2 + 110);
    }

    if (fileListPage > 0) {
      fill(mouseX >= width/2 - 270 && mouseX <= width/2 - 150 &&
        mouseY >= height/2 - 180 && mouseY <= height/2 - 150 ?
        lerpColor(PAGE_BUTTON_COLOR, color(255), 0.2) : PAGE_BUTTON_COLOR);
      stroke(50);
      rect(width/2 - 270, height/2 - 180, 120, 30, 5);
      fill(255);
      text("◄ Prev", width/2 - 210, height/2 - 165);
    }

    if (fileListPage < totalPages - 1) {
      fill(mouseX >= width/2 + 150 && mouseX <= width/2 + 270 &&
        mouseY >= height/2 - 180 && mouseY <= height/2 - 150 ?
        lerpColor(PAGE_BUTTON_COLOR, color(255), 0.2) : PAGE_BUTTON_COLOR);
      stroke(50);
      rect(width/2 + 150, height/2 - 180, 120, 30, 5);
      fill(255);
      text("Next ►", width/2 + 210, height/2 - 165);
    }
  }
}

class Slider {
  float x, y, w, h;
  float min, max, value;
  boolean locked = false;

  Slider(float x, float y, float w, float h, float min, float max) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.min = min;
    this.max = max;
    this.value = (min + max) / 2;
  }

  void display(boolean active) {
    noStroke();
    fill(active ? SLIDER_COLOR : INACTIVE_SLIDER_COLOR);
    rect(x, y, w, h, h/2);

    float handleX = map(value, min, max, x, x + w);
    fill(active ? BUTTON_COLOR : INACTIVE_BUTTON_COLOR_GRAY);
    ellipse(handleX, y + h/2, h * 1.2, h * 1.2);

    fill(active ? TEXT_COLOR : INACTIVE_TEXT_COLOR);
    textAlign(CENTER, CENTER);
    textSize(18);
    text(int(value), handleX, y + h/2);
  }

  void display() {
    display(true);
  }

  boolean isOver() {
    float handleX = map(value, min, max, x, x + w);
    return dist(mouseX, mouseY, handleX, y + h/2) < h;
  }

  void updatePosition(float mx) {
    value = round(map(constrain(mx, x, x + w), x, x + w, min, max));
  }

  void setValue(float v) {
    value = round(constrain(v, min, max));
  }

  float getValue() {
    return value;
  }
}

class Button {
  float x, y, w, h;
  String label;
  color buttonColor;

  Button(float x, float y, float w, float h, String label, color buttonColor) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;
    this.buttonColor = buttonColor;
  }

  void display() {
    stroke(50);
    strokeWeight(1);
    fill(isOver() ? lerpColor(buttonColor, color(255), 0.2) : buttonColor);
    rect(x, y, w, h, h/4);

    fill(0);
    textAlign(CENTER, CENTER);
    textSize(16);
    text(label, x + w/2, y + h/2);
  }

  void displayInactive() {
    stroke(120);
    strokeWeight(1);
    fill(INACTIVE_BUTTON_COLOR_GRAY);
    rect(x, y, w, h, h/4);

    fill(INACTIVE_TEXT_COLOR);
    textAlign(CENTER, CENTER);
    textSize(16);
    text(label, x + w/2, y + h/2);
  }

  boolean isOver() {
    return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
  }
}
