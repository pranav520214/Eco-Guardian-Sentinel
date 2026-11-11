# Eco Guardian — ESP32 Dev Module Firmware Guide

## 1. Hardware Pinout (ESP32 Dev Module 30/38-pin)
| Component | ESP32 Pin | Function | Notes |
| :--- | :--- | :--- | :--- |
| **0.96" SSD1306 OLED** | **GPIO 21** | I2C SDA | Connect to OLED SDA |
| **0.96" SSD1306 OLED** | **GPIO 22** | I2C SCL | Connect to OLED SCL |
| **OLED Power** | **3.3V & GND** | Power | Standard 3.3V rail |
| **MOSFET Blower 1** | **GPIO 18** | Digital / PWM | Gate of Blower MOSFET 1 |
| **MOSFET Blower 2** | **GPIO 19** | Digital / PWM | Gate of Blower MOSFET 2 |
| **Ultrasonic Mist Module** | **GPIO 5** | Digital Out | Gate of Mist MOSFET / Relay |
| **Buzzer / Alarm** | **GPIO 4** | Digital Out | Active Piezo Buzzer |
| **Status LED** | **GPIO 2** | Onboard LED | System Heartbeat (Blinks 1Hz) |

> **Note on ESP32 Model**: This code is configured specifically for the **ESP32 Dev Module** (ESP-WROOM-32 30-pin or 38-pin), using native hardware I2C pins `GPIO 21` (SDA) and `GPIO 22` (SCL), **not** the ESP32-C3.

---

## 2. Required Arduino IDE Libraries
Install these from **Arduino IDE -> Tools -> Manage Libraries**:
1. `Adafruit SSD1306` (by Adafruit)
2. `Adafruit GFX Library` (by Adafruit)
3. `ArduinoJson` (v6.x or v7.x by Benoit Blanchon)

In **Tools -> Board**, select: **`ESP32 Dev Module`** (or `DOIT ESP32 DEVKIT V1`).
Set **Upload Speed**: `921600` or `115200`.

---

## 3. How the Contingency & TinyML System Works
Because your physical analog sensors are damaged/burned, this firmware includes:
1. **On-Chip Synthetic Sensor Engine**:
   - Generates mathematically correlated synthetic air data ($PM2.5$, $MQ-135\text{ Gas}$, $DHT11\text{ Temp/Hum}$, $MQ-3\text{ Alcohol}$).
   - Follows real atmospheric physics: when AQI spikes, toxic gas ppm rises in tandem.
   - When the **Blowers** or **Mist** turn ON, the engine applies real physical particulate precipitation decay ($e^{-k \cdot t}$), dropping the PM2.5 just like in your bench tests!
2. **Quantized TinyML Neural Predictor**:
   - Runs a 3-layer neural inference directly in ESP32 PROGMEM ($< 1.4\text{ms}$ execution latency).
   - Predicts future AQI for $T+15\text{m}$ and $T+60\text{m}$ ahead.
   - Computes Rapid Spike Risk % and classifies the trend.
3. **High-Performance OLED Motion Engine**:
   - Procedural vector shield logo splash animation on boot with laser scanline reveal.
   - 4-page carousel with hardware-smooth 8-frame horizontal slide transitions:
     - **Screen 0**: Radial gauge, giant AQI number, EPA category pill (`[GOOD]`, `[MODERATE]`, `[UNHEALTHY]`, `[HAZARDOUS]`), and 15m trend prediction.
     - **Screen 1**: Detailed pollutant breakdown + live 16-step sparkline trend graph.
     - **Screen 2**: TinyML Neural Engine HUD (forecasts, spike risk bar, inference latency).
     - **Screen 3**: Actuator matrix (Blower fans spinning animation, ultrasonic mist wave, solar PV voltage).

---

## 4. Live Judge Demo Commands (Serial Monitor @ 115200 baud)
Plug your ESP32 into your laptop via USB, open **Serial Monitor** at **115200 baud**, and type any of these commands to instantly demonstrate live system response:

| Command | Action | Physical Rig Response |
| :--- | :--- | :--- |
| `CLEAN` | AQI drops to ~35 (Clean Classroom) | Blowers: **OFF**, Mist: **OFF** |
| `SMOG` | AQI rises to ~165 (Traffic Smog) | Blowers: **TURN ON!** |
| `SPIKE` | AQI surges to ~215 (Stubble Burning) | Blowers: **ON**, Mist: **SPRAYS!** |
| `HAZARD`| AQI spikes to ~360 (Toxic Gas Leak) | Blowers: **ON**, Mist: **ON**, Buzzer: **ALARM!** |
| `AUTO` | Resumes smooth diurnal TinyML drift | Smooth cyclical breathing |
| `SET 145` | Manually sets AQI to 145 | System recalculates EPA breakpoints |
| `STATUS`| Returns live JSON telemetry payload | Telemetry for web dashboard |
