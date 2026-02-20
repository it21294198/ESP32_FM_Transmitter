#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/periph_defs.h"
#include "soc/soc.h"

#define FM_GPIO 0

void setup() {
  pinMode(FM_GPIO, OUTPUT);

  // Enable APLL
  rtc_clk_apll_enable(true, 0x43, 0x96, 0x4, 2);

  // Route clock to GPIO0
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
  REG_SET_FIELD(PIN_CTRL, CLK_OUT1, 1);
}

void loop() {
  // Simple 1 kHz FM tone
  for (int i = 0; i < 500; i++) {
    rtc_clk_apll_enable(true, 0x43, 0x96, 0x4, 2);
    delayMicroseconds(500);

    rtc_clk_apll_enable(true, 0x43, 0x95, 0x4, 2);
    delayMicroseconds(500);
  }

  delay(1000);
}