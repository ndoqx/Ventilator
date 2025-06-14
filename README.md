# Emergency DIY Ventilator | Third-Year Embedded Project at KMITL

🔗 GitHub Repository: [ndoqx/Ventilator](https://github.com/ndoqx/Ventilator)

This project is a DIY emergency ventilator system designed during my third year as a Biomedical Engineering student at KMITL. Built with Arduino Mega and a Cytron Motor Driver, the ventilator offers multiple breathing modes with customizable inspiration and expiration timing, making it a practical prototype for low-resource emergency support.

It reads a respiration rate input from a potentiometer and uses mode selection pins to determine the inspiration-to-expiration (I:E) ratio. The motor moves a mechanical piston or airbag to simulate natural breathing cycles, with safety checks via limit switches and LED feedback.

---

# Device Images

## Front Panel
![Front Panel](images/front_panel.jpg)

## Back Panel
![Back Panel](images/back_panel.jpg)

## Assembled Emergency Ventilator
![Assembled View](images/assembled.jpg)

---

# Features

- Adjustable Respiratory Rate (RR) via potentiometer input
- Multiple I:E Ratio Modes using selector switches (e.g., 1:1, 1:2, 1:3, etc.)
- Real-time calculation of inspiration and expiration timing
- Limit switches to detect motor endpoints and stop movement safely
- Onboard LED status and serial output for diagnostics
- Auto-stop safety if multiple modes are selected incorrectly
- Serial monitor output for real-time debugging

---

# How It Works

1. User selects a mode via a physical switch (M0 to M4).
2. Respiration Rate (RR) is read from an analog sensor (potentiometer).
3. The code calculates inTime and outTime based on the I:E ratio and RR.
4. Motor runs forward until it hits the min limit switch (inhale).
5. After `inTime` delay, the motor runs **backward** until max limit switch (exhale).
6. The cycle repeats while displaying real-time values to the serial monitor.

---

# Hardware Used

| Component             | Description                                  |
|----------------------|----------------------------------------------|
| Arduino Mega 2560     | Microcontroller used for all logic & control |
| Cytron MD10C Driver   | Motor driver to handle DC motor control      |
| DC Motor              | Drives piston or airbag mechanism            |
| Limit Switches (2x)   | Safety feedback for endpoints                |
| Potentiometer         | Controls respiration rate input              |
| Mode Switches (5x)    | Selects I:E ratio modes (e.g., 1:1 to 1:4)   |
| LED Indicator         | Onboard status display (Pin 13)             |

---

# 🧾 Wiring Overview

| Component        | Pin #         |
|------------------|---------------|
| Motor PWM        | Pin 11        |
| Motor Direction  | Pin 12        |
| Min Limit Switch | Pin 23        |
| Max Limit Switch | Pin 25        |
| Mode Switches    | Pins 36, 34, 32, 30, 28 |
| LED Onboard      | Pin 13        |
| RR Sensor        | Analog Pin A0 |

---

# Code Overview

Main logic is in `Ventilator_updated_check.ino`.  
Key functions include:

- `motorRun()`: Runs inhale/exhale cycle based on timing.
- `motorStop()`: Stops motor in case of invalid mode.
- `GetInExTime()`: Calculates inhale/exhale time.
- `loop()`: Continuously checks mode and runs the cycle.

---

# Installation & Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/ndoqx/Ventilator.git
   cd Ventilator
````

2. Open `Ventilator_updated_check.ino` in Arduino IDE.

3. Select Board: Arduino Mega 2560, and connect via USB.

4. Upload the sketch and open Serial Monitor at `9600 baud`.

5. Observe real-time data and test the ventilator cycles.

---

# Sample Output (Serial Monitor)

```
Ventilator On
Checking Pin : 36 --> 0
Checking Pin : 34 --> 0
Checking Pin : 32 --> 1
...
Selector mode : 1:3
Respiration rate : 20
Inspire time : 1500 ms
Expire time : 4500 ms
-----------------------
!! Output result!!
OUT I time: 1502.00
OUT E time: 4498.00
OUT RR: 20.00
```

---

# Modes Available

| Mode Pin | I\:E Ratio | Description              |
| -------- | ---------- | ------------------------ |
| M0       | Off        | Stops ventilator         |
| M1       | 1:4        | Long exhale              |
| M2       | 1:3        | Moderate exhale          |
| M3       | 1:2        | Balanced mode            |
| M4       | 1:1        | Equal inhale/exhale time |

---

# Future Improvements

* Add LCD screen for local display
* Add real-time RR visualization with Blynk or Bluetooth
* Add fail-safe watchdog timer
* Improve switch debounce logic
* Create enclosure for motor/switch safety

---

# Author

**Thanetpol Noynuai**
Biomedical Engineering, KMITL (3rd Year Project)
🔗 GitHub: [@ndoqx](https://github.com/ndoqx)

---

# Disclaimer

This project was created for academic and prototyping purposes only and **is not intended for clinical or medical use**. Please consult medical device regulations and experts before attempting real-world application.

---

