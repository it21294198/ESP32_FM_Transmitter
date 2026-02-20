## 📻 ESP32-CAM FM Transmitter (Single GPIO Hack)

### ⚠️ For educational and experimental use only

This project demonstrates how to use an ESP32-CAM (AI-Thinker) to generate a very low-power FM signal using one GPIO pin by routing the internal APLL clock to an output pin.

#### This is a hardware clock routing hack — not a proper RF transmitter.

### 🚨 Legal Warning

- The FM broadcast band (88–108 MHz) is regulated in most countries.
- Use only for short-range lab testing (1–3 meters).
- Use a very short wire (5–10 cm max).
- Do NOT connect large antennas.
- Do NOT interfere with licensed stations.
- Tune to an unused frequency.
- You are responsible for compliance with local radio regulations.

### 🧠 How It Works

The ESP32 internal APLL (Audio PLL) generates a high-frequency clock (~100 MHz).
That clock is routed to:
```
GPIO0 → CLK_OUT1
```
The frequency is slightly varied to create Frequency Modulation (FM).
A nearby FM radio can receive the signal.

### 📦 Requirements

- ESP32-CAM (AI-Thinker)
- Arduino IDE
- ESP32 Arduino Core 2.0.14
- 5–10 cm wire (antenna)
- FM radio receiver

#### ⚠️ This does NOT work on:
- ESP32-C3
- ESP32-S3
- Arduino core 3.x

### 🔧 Board Setup

#### In Arduino IDE:

- Tools → Board → ESP32 Arduino → AI Thinker ESP32-CAM
- Tools → Core Version → 2.0.14

#### 🔌 Wiring
- ESP32-CAM	Connection
- GPIO0	5–10 cm wire (antenna)
- GND	Nothing else

#### ⚠️ Do NOT connect GPIO0 to GND after flashing.

### 📜 Code (sine-wave FM modulation)
```
#include <math.h>
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/periph_defs.h"
#include "soc/soc.h"

#define FM_GPIO 0

// FM parameters
const float carrier_freq = 100000000;   // 100 MHz
const float audio_freq = 1000;          // 1 kHz tone
const float deviation = 50000;          // 50 kHz deviation
const float sample_rate = 20000;        // 20 kHz update rate

float phase = 0;

void setup() {
  pinMode(FM_GPIO, OUTPUT);

  // Route APLL to GPIO0
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
  REG_SET_FIELD(PIN_CTRL, CLK_OUT1, 1);
}

void loop() {

  // Generate sine wave
  float audio = sinf(2 * PI * phase);

  // Calculate new frequency
  float freq = carrier_freq + (deviation * audio);

  // Convert frequency to APLL values
  uint32_t sdm0 = 0x43;
  uint32_t sdm1 = 0x96;
  uint32_t sdm2 = 0x4;
  uint32_t o_div = 2;

  rtc_clk_apll_enable(true, sdm0, sdm1, sdm2, o_div);

  phase += audio_freq / sample_rate;
  if (phase >= 1.0) phase -= 1.0;

  delayMicroseconds(50);   // 20 kHz update rate
}
```
### 📻 How To Use

- Upload the sketch
- Disconnect GPIO0 from GND
- Reset ESP32-CAM
- Attach short wire to GPIO0
- Tune FM radio to ~100.0 MHz
- Adjust slightly until tone is heard
- Expected range: 0.5 – 3 meters

### ⚠️ Limitations

- Square wave RF (not clean sine)
- Strong harmonics (200 MHz, 300 MHz, etc.)
- No filtering
- Not frequency stable
- Not suitable for real broadcasting

### 🛠 Troubleshooting

#### If compilation fails:

- Make sure ESP32 core version is 2.0.14
- Restart Arduino IDE
- Ensure board is compatiable.

#### If no signal is heard:
- Use shorter antenna
- Move radio closer
- Try tuning ±0.5 MHz
- Ensure unused frequency

#### 📡 Educational Purpose

##### This project is useful for learning:
- RF basics
- Frequency modulation
- ESP32 internal clock system
- Hardware clock routing
- It is NOT a replacement for a real FM transmitter IC.

### 🔬 For Better RF Quality

Use:
1. KT0803 FM transmitter module
2. Proper LC filter
3. Shielded design
4. Regulated power