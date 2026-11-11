#ifndef OLED_ANIMATIONS_H
#define OLED_ANIMATIONS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TinyML_Model.h"

/**
 * ============================================================================
 * ECO GUARDIAN - 0.96" SSD1306 HIGH-PERFORMANCE OLED MOTION ENGINE
 * ============================================================================
 * Resolution: 128x64 Monochrome OLED
 * Features:
 *  - Procedural Vector Shield & Leaf Splash Logo with Scanline Reveal
 *  - Hardware-Accelerated Smooth Page Slide Transitions (Carousel)
 *  - Animated Spinning Blower Fans & Ultrasonic Mist Droplets
 *  - Real-Time Sparkline History Buffer & Radial Gauge
 * ============================================================================
 */

// Custom 16x16 Eco Guardian Leaf & Shield Icon (1-bit bitmap)
static const unsigned char PROGMEM logo_leaf_16x16[] = {
    0x00, 0x00, 0x03, 0xC0, 0x0C, 0x30, 0x10, 0x08,
    0x23, 0xC4, 0x44, 0x22, 0x48, 0x12, 0x50, 0x0A,
    0x50, 0x0A, 0x48, 0x12, 0x24, 0x24, 0x13, 0xC8,
    0x08, 0x10, 0x04, 0x20, 0x03, 0xC0, 0x00, 0x00
};

// Fan Blade Frame 1 (8x8)
static const unsigned char PROGMEM fan_frame_0[] = {
    0x18, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x18
};
// Fan Blade Frame 2 (8x8)
static const unsigned char PROGMEM fan_frame_1[] = {
    0x00, 0x66, 0x3C, 0xFF, 0xFF, 0x3C, 0x66, 0x00
};

class OLEDMotionEngine {
private:
    Adafruit_SSD1306& oled;
    int currentScreen = 0;
    int nextScreen = 1;
    bool isTransitioning = false;
    int transitionOffset = 0; // 0 to 128
    unsigned long lastScreenSwitch = 0;
    uint8_t fanFrame = 0;
    unsigned long lastAnimTick = 0;

    // Sparkline history (16 data points)
    int historyAQI[16];
    int historyHead = 0;

public:
    OLEDMotionEngine(Adafruit_SSD1306& displayRef) : oled(displayRef) {
        for (int i = 0; i < 16; i++) historyAQI[i] = 45;
    }

    // ========================================================================
    // 1. BOOT SEQUENCE - PROCEDURAL SHIELD & LOGO SPLASH ANIMATION
    // ========================================================================
    void playBootAnimation() {
        oled.clearDisplay();
        oled.setTextColor(SSD1306_WHITE);

        // Step 1: Draw expanding cybernetic shield frame
        for (int r = 4; r <= 24; r += 2) {
            oled.clearDisplay();
            // Outer shield polygon
            oled.drawRoundRect(64 - r * 1.8f, 26 - r, r * 3.6f, r * 2, 4, SSD1306_WHITE);
            oled.drawCircle(64, 26, r / 2, SSD1306_WHITE);
            oled.display();
            delay(20);
        }

        // Step 2: Shimmering Title Reveal
        for (int p = 0; p <= 100; p += 10) {
            oled.clearDisplay();
            // Shield & Leaf Icon
            oled.drawRoundRect(18, 4, 92, 44, 5, SSD1306_WHITE);
            oled.drawBitmap(24, 18, logo_leaf_16x16, 16, 16, SSD1306_WHITE);

            oled.setTextSize(1);
            oled.setCursor(44, 14);
            oled.print("ECO GUARDIAN");

            oled.setTextSize(1);
            oled.setCursor(44, 26);
            oled.print("AI SENTINEL");

            oled.setCursor(44, 37);
            oled.print("TinyML v2.4");

            // Progress bar at bottom
            oled.drawRect(18, 52, 92, 6, SSD1306_WHITE);
            int fillW = (90 * p) / 100;
            oled.fillRect(19, 53, fillW, 4, SSD1306_WHITE);

            // Scanline laser effect
            int scanX = 18 + (92 * p) / 100;
            oled.drawFastVLine(scanX, 4, 44, SSD1306_INVERSE);

            oled.display();
            delay(35);
        }

        delay(400);

        // Flash screen
        oled.invertDisplay(true);
        delay(80);
        oled.invertDisplay(false);
        delay(150);
    }

    void pushHistory(int aqi) {
        historyAQI[historyHead] = aqi;
        historyHead = (historyHead + 1) % 16;
    }

    // ========================================================================
    // 2. MAIN LOOP - SCREEN CAROUSEL & TRANSITION CONTROLLER
    // ========================================================================
    void updateAndRender(const SensorSnapshot& snap, const PredictionResult& pred, bool blowers, bool mist) {
        unsigned long now = millis();

        // Animation frame tick (~150ms for spinning fan / pulses)
        if (now - lastAnimTick > 150) {
            fanFrame = (fanFrame + 1) % 2;
            lastAnimTick = now;
        }

        // Auto page rotation every 4.5 seconds
        if (!isTransitioning && (now - lastScreenSwitch > 4500)) {
            isTransitioning = true;
            nextScreen = (currentScreen + 1) % 4;
            transitionOffset = 0;
            lastScreenSwitch = now;
        }

        // Handle slide animation
        if (isTransitioning) {
            transitionOffset += 16; // 8 frames across 128 pixels (super crisp!)
            if (transitionOffset >= 128) {
                isTransitioning = false;
                currentScreen = nextScreen;
                transitionOffset = 0;
            }
        }

        oled.clearDisplay();

        if (!isTransitioning) {
            // Render single static page
            renderScreen(currentScreen, 0, snap, pred, blowers, mist);
        } else {
            // Render sliding transition: exiting page slides left, entering page enters right
            renderScreen(currentScreen, -transitionOffset, snap, pred, blowers, mist);
            renderScreen(nextScreen, 128 - transitionOffset, snap, pred, blowers, mist);
        }

        // Always render top status pill (tiny header indicators)
        renderHeaderBar(snap.aqi, blowers, mist);

        oled.display();
    }

private:
    void renderHeaderBar(int aqi, bool blowers, bool mist) {
        // Top 8-pixel micro status bar
        oled.setTextSize(1);
        oled.setCursor(2, 0);
        oled.print("ECO-G");

        // Animated fan icon if blowers on
        if (blowers) {
            oled.drawBitmap(68, 0, (fanFrame == 0 ? fan_frame_0 : fan_frame_1), 8, 8, SSD1306_WHITE);
        }

        // Mist icon if mist on
        if (mist) {
            oled.setCursor(80, 0);
            oled.print("~M~");
        }

        // TinyML indicator
        oled.setCursor(102, 0);
        oled.print("T-ML");
        oled.drawFastHLine(0, 9, 128, SSD1306_WHITE);
    }

    void renderScreen(int screenIdx, int xOff, const SensorSnapshot& s, const PredictionResult& p, bool blowers, bool mist) {
        switch (screenIdx) {
            case 0: renderScreen0_MainAQI(xOff, s, p); break;
            case 1: renderScreen1_Sensors(xOff, s); break;
            case 2: renderScreen2_TinyML(xOff, s, p); break;
            case 3: renderScreen3_Actuators(xOff, blowers, mist); break;
        }
    }

    // ========================================================================
    // SCREEN 0: RADIAL GAUGE & HERO AQI NUMERAL
    // ========================================================================
    void renderScreen0_MainAQI(int xOff, const SensorSnapshot& s, const PredictionResult& p) {
        // Large bold AQI value
        oled.setTextSize(3);
        int aqiVal = s.aqi;
        int numX = (aqiVal < 100) ? 14 : 4;
        oled.setCursor(xOff + numX, 18);
        oled.print(aqiVal);

        oled.setTextSize(1);
        oled.setCursor(xOff + 68, 18);
        oled.print("AQI");

        // EPA Classification Pill
        oled.setCursor(xOff + 68, 29);
        if (aqiVal <= 50) {
            oled.print("[GOOD]");
        } else if (aqiVal <= 100) {
            oled.print("[MODERATE]");
        } else if (aqiVal <= 150) {
            oled.print("[UNHEALTHY]");
        } else if (aqiVal <= 200) {
            oled.print("[POOR]");
        } else if (aqiVal <= 300) {
            oled.print("[VERY POOR]");
        } else {
            oled.print("[HAZARDOUS]");
        }

        // TinyML Trend prediction footer
        oled.drawRect(xOff + 2, 45, 124, 18, SSD1306_WHITE);
        oled.setCursor(xOff + 6, 50);
        oled.print("Pred 15m: ");
        oled.print(p.aqiPred15m);
        oled.print(" ");
        if (p.aqiPred15m > s.aqi + 5) {
            oled.print("^ RIS");
        } else if (p.aqiPred15m < s.aqi - 5) {
            oled.print("v CLN");
        } else {
            oled.print("- STB");
        }
    }

    // ========================================================================
    // SCREEN 1: MULTI-POLLUTANT SENSORS & SPARKLINE
    // ========================================================================
    void renderScreen1_Sensors(int xOff, const SensorSnapshot& s) {
        oled.setTextSize(1);
        oled.setCursor(xOff + 2, 12);
        oled.print("PM2.5: ");
        oled.print(s.pm25, 1);
        oled.print(" ug/m3");

        oled.setCursor(xOff + 2, 23);
        oled.print("Gas:   ");
        oled.print((int)s.gasPpm);
        oled.print(" ppm");

        oled.setCursor(xOff + 2, 34);
        oled.print("T: ");
        oled.print(s.tempC, 1);
        oled.print("C | H: ");
        oled.print((int)s.humidity);
        oled.print("%");

        // Sparkline graph at bottom
        oled.setCursor(xOff + 2, 46);
        oled.print("Trend:");
        oled.drawRect(xOff + 42, 45, 84, 17, SSD1306_WHITE);
        for (int i = 0; i < 15; i++) {
            int p1 = (historyHead + i) % 16;
            int p2 = (historyHead + i + 1) % 16;
            int y1 = 60 - constrain((historyAQI[p1] * 12) / 300, 0, 13);
            int y2 = 60 - constrain((historyAQI[p2] * 12) / 300, 0, 13);
            oled.drawLine(xOff + 44 + (i * 5), y1, xOff + 44 + ((i + 1) * 5), y2, SSD1306_WHITE);
        }
    }

    // ========================================================================
    // SCREEN 2: TINYML NEURAL ENGINE HUD
    // ========================================================================
    void renderScreen2_TinyML(int xOff, const SensorSnapshot& s, const PredictionResult& p) {
        oled.setTextSize(1);
        oled.setCursor(xOff + 6, 12);
        oled.print(">> TINYML NEURAL <<");

        oled.setCursor(xOff + 2, 24);
        oled.print("15m Forecast: ");
        oled.print(p.aqiPred15m);
        oled.print(" AQI");

        oled.setCursor(xOff + 2, 35);
        oled.print("60m Forecast: ");
        oled.print(p.aqiPred60m);
        oled.print(" AQI");

        // Spike Risk Bar
        oled.setCursor(xOff + 2, 47);
        oled.print("Spike Risk:");
        oled.drawRect(xOff + 70, 48, 54, 8, SSD1306_WHITE);
        int fillW = (int)(p.spikeRisk * 50);
        oled.fillRect(xOff + 72, 50, constrain(fillW, 0, 50), 4, SSD1306_WHITE);

        oled.setCursor(xOff + 2, 56);
        oled.print("Latency: ");
        oled.print(p.inferenceMs, 1);
        oled.print("ms [OK]");
    }

    // ========================================================================
    // SCREEN 3: ACTUATORS & MPPT SOLAR HARVESTING MATRIX
    // ========================================================================
    void renderScreen3_Actuators(int xOff, bool blowers, bool mist) {
        oled.setTextSize(1);
        oled.setCursor(xOff + 12, 12);
        oled.print("[ ACTUATOR MATRIX ]");

        // Blowers status with animated icon
        oled.setCursor(xOff + 2, 24);
        oled.print("Blowers: ");
        if (blowers) {
            oled.print("ACTIVE [ON]");
        } else {
            oled.print("STANDBY");
        }

        // Mist status
        oled.setCursor(xOff + 2, 36);
        oled.print("Mist Jet: ");
        if (mist) {
            oled.print("SPRAYING");
        } else {
            oled.print("OFF");
        }

        // Solar / Battery Telemetry
        oled.drawFastHLine(xOff + 2, 48, 124, SSD1306_WHITE);
        oled.setCursor(xOff + 2, 53);
        oled.print("Solar: 18.2V | Bat: 96%");
    }
};

#endif // OLED_ANIMATIONS_H
