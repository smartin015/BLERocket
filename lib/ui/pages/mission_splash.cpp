#include "ui.h"
#include <iostream>

#define SPLASH_X 80
#define SPLASH_Y 40

// Ship just sent on mission
void UI::drawMissionSplash(const Engine* engine) {
  setFont(&FONT_POPPINS_8);
  DrawStringAt("Voyaging...", SIDEBAR_WIDTH + SIDEBAR_MARGIN, 0, NULL, NULL);
  setFont(&FONT_ROBOTO_6);
  drawText("    /\\", SZ_M, SPLASH_X, SPLASH_Y + (0*11));
  drawText("   (  )", SZ_M, SPLASH_X, SPLASH_Y + (1*11));
  drawText("   (  )", SZ_M, SPLASH_X, SPLASH_Y + (2*11));
  drawText("  /|/\\|\\", SZ_M, SPLASH_X, SPLASH_Y + (3*11));
  drawText(" /_||||_\\", SZ_M, SPLASH_X, SPLASH_Y + (4*11));
  drawText("    WW", SZ_M, SPLASH_X, SPLASH_Y + (5*11));

  drawText("Press any key to continue", 0, SIDEBAR_WIDTH + SIDEBAR_MARGIN, EPAPER_SHORT_DIMENSION - 11);
}
