#include "ui.h"
#include <iostream>

// Ship just sent on mission
void UI::drawMissionSplash(const Engine* engine) {
  drawText("Voyaging", TITLE_SZ, TITLE_X, TITLE_Y);
  drawText("    /\\", SZ_M, BODY_X, BODY_Y + (SZ_S));
  drawText("   (  )", SZ_M, BODY_X, BODY_Y + (1*SZ_S));
  drawText("   (  )", SZ_M, BODY_X, BODY_Y + (2*SZ_S));
  drawText("  /|/\\|\\", SZ_M, BODY_X, BODY_Y + (3*SZ_S));
  drawText(" /_||||_\\", SZ_M, BODY_X, BODY_Y + (4*SZ_S));
  drawText("    WW", SZ_M, BODY_X, BODY_Y + (5*SZ_S));
}