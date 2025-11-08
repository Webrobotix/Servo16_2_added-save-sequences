# Servo16_2_added-save-sequences
# This version needs more testing!
# Webrobotix Servo Controller Servo16_2 (Processing / Arduino)

This Processing sketch provides a **16-channel RC servo controller interface** with sequence recording and Arduino sketch export.  
It communicates with an Arduino running the **Servo17_sketch and optionally supports the **Adafruit 16-Channel 12-bit PWM/Servo Shield**.

**This software is provided for educational and experimental purposes only. The author assumes no responsibility for any damage or injury resulting from its use.**
---

 **Features**

- Control up to **16 RC servos** using sliders and buttons.
- Toggle individual servos active/inactive.
- Define servo limits (**min, max, center**) and save them to files.
- Label servos for easier identification.
- Record **servo sequences** using keyframes with speed and delay.
- Play back recorded sequences in real time.
- Export recorded sequences as **Arduino sketches**:
  - Standard `Servo.h` version.
  - PWM shield version (`Adafruit_PWMServoDriver`).
- Save and load all servo settings (limits, labels, active states) to unified settings files.
- Auto-reconnect and monitoring of Arduino serial ports.
- Easing function for smooth, lifelike motion.

---

 **Requirements**

- [Processing IDE](https://processing.org/) (tested with 4.4.0).
- [Arduino IDE](https://www.arduino.cc/en/software).
- Arduino board (Uno, Nano, etc.) running `Servo17_sketch` (no EEPROM version).
- (Optional) [Adafruit 16-Channel 12-bit PWM/Servo Shield](https://www.adafruit.com/product/1411).

Processing Libraries:
- `processing.serial.*` (included by default).

---

 **Setup**

1. Upload the Arduino firmware (`Servo17_sketch`) to your Arduino.
2. Connect servos to your Arduino pins (or PWM shield channels).
3. Open this sketch in Processing and run it.
4. The program will auto-scan serial ports and connect to your Arduino.
5. Use the UI to control servos, save settings, or record sequences.

---

 **User Interface**

- **Sliders (per servo):** Move servo between 0°–180°.
- **Buttons (per servo):**
  - `Active` – toggle servo control.
  - `Center` – move to stored center.
  - `Set Ctr` – set current position as center.
  - `Set Min` / `Set Max` – define limits.
  - `Reset` – restore default 0°–180°, center 90°.
  - `Label` – rename servo.
- **Global Controls:**
  - `All Active` / `All Inactive`.
  - `Connect` – force reconnection to Arduino.
- **Settings Controls:**
  - `Save Settings` – save limits/labels to file.
  - `Load Settings` – load from file.
  - `Delete Settings` – remove a saved file.
- **Sequence Panel:**
  - `Record` – toggle recording.
  - `Add Frame` – save current servo positions.
  - `Play` – run sequence.
  - `Clear` – remove all frames.
  - `Export` – generate Arduino sketch.
  - **Sliders** for movement speed (ms) and delay (ms).
- **PWM Shield Toggle:** Switch between Standard Servo Library and PWM Shield modes.

**Hotkeys:**
- `R` – toggle recording  
- `K` – add keyframe  
- `P` – play sequence  
- `C` – clear sequence  
- `S` – toggle PWM shield  

---

 **File Management**

- Settings are saved as `data/<name>_settings.txt`.
- Unified format stores **servo limits, states, and labels** together.
- Old legacy formats (`servo_settings.txt`, `servo_labels.txt`) still load.

Exported Arduino sketches are saved as:
data/<sketchName>_StandardServo_FIXED.ino
data/<sketchName>_PWMShield_FIXED.ino

---

 **Exported Arduino Sketch**

The exported `.ino` file includes:
- Smooth motion control using millis() (non-blocking).
- Easing function (`easeInOutCubic`) for natural servo transitions.
- Accurate handling of speed + delay per keyframe.
- Support for either **Standard Servo Library** or **Adafruit PWM Shield**.

---

 **Quick Start Example**

Here’s a step-by-step workflow to go from servo setup to an exported sketch:

1. **Connect and Activate Servos**
   - Run the Processing sketch.
   - Click `Connect` if it doesn’t auto-connect.
   - Use `All Active` or press individual `Active` buttons to enable servos.

2. **Set Servo Ranges**
   - Move a slider to the minimum desired position → press `Set Min`.
   - Move it to the maximum desired position → press `Set Max`.
   - Move to neutral and press `Set Ctr` (optional).
   - Save your setup with `Save Settings`.

3. **Record a Sequence**
   - Click `Record` (or press `R`).
   - Move servos to desired positions with sliders.
   - Press `Add Frame` (or `K`) to capture that position with timing.
   - Adjust `Movement Speed` and `Delay` sliders as needed.
   - Add more frames to build your sequence.
   - Stop recording when finished.

4. **Playback**
   - Click `Play` (or `P`) to test the sequence in real time.

5. **Export for Arduino**
   - Click `Export`, enter a sketch name.
   - Choose either **Standard Servo** or **PWM Shield** mode.
   - A `.ino` file will be saved under `data/`.
   - Open it in Arduino IDE, upload to your board, and your sequence runs standalone.

---


© Webrobotix 2020–2025  
For personal, educational, and prototyping use. Not intended for critical or safety-related applications.
# RC Servo Controller Program

Terms of Use (Plain Language)

By downloading, using, or running this RC Servo Controller Program, you agree to the following terms:

**No Warranty**

This program is provided “as is” with no guarantees of safety, performance, or fitness for any purpose.

The author makes no promises that it will work as expected or be error-free.

**User Responsibility**

You are fully responsible for how you use this software and any devices (RC servos, animatronics, mechanisms) connected to it.

Safe setup and operation are entirely your responsibility.

**Safety Requirements**

Do not leave animatronics or servo-driven devices **unattended while powered**.

Keep hands, hair, and clothing away from moving parts.

Not designed for children without direct adult supervision.

Not suitable for life-safety, medical, or critical systems.

**Liability Limitation**

The author is not liable for any injury, damage, or loss that may result from using this software or related hardware.

By using this program, you accept all risk.

