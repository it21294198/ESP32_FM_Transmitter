## 📻 ESP32-CAM AM Beep transmitter (100 kHz Carrier)

- Use GPIO14
- Tune radio near 100 kHz

```cpp
#define OUT_PIN 14

// 100 kHz carrier → 10 microseconds period
// Half period ≈ 5 microseconds
void carrierBurst(unsigned long duration_ms) {
  unsigned long start = millis();

  while (millis() - start < duration_ms) {
    digitalWrite(OUT_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(OUT_PIN, LOW);
    delayMicroseconds(5);
  }
}

void setup() {
  pinMode(OUT_PIN, OUTPUT);
}

void loop() {

  // --- Beep 1 ---
  carrierBurst(200);   // 200ms tone
  delay(200);          // silence

  // --- Beep 2 ---
  carrierBurst(200);
  delay(1000);         // pause before repeat
}
```

#### 🔌 Wiring
```
GPIO14  →  5–10 cm wire
GND     →  nothing
```

- Do NOT connect GPIO14 to GND.

Optional improvement:

- GPIO14 → 100nF capacitor → 10 cm wire

### 📻 How To Test

- Upload sketch
- Attach short wire to GPIO14
- Bring radio VERY close
- Tune around 90–110 kHz
- Slowly adjust tuning

You should hear:
```
Beep… Beep…   (pause)
Beep… Beep…
```
### 🧠 Why This Works

- Rapid HIGH/LOW switching ≈ 100 kHz carrier
- Turning carrier ON/OFF = AM modulation
- Radio detects amplitude change

#### ⚠️ Important Notes

- ESP32 timing is not perfect → frequency not exact
- Very weak signal
- Works best with analog radios

![AMvsFM](/images/AMvsFM.gif)