#include "ui.h"
#include <iostream>
#include <string>


void UI::drawTradeEntry(const Engine* engine) {
  int x_offset = SIDEBAR_WIDTH;
  int y_offset = 0;

  DrawSidebarText(notification, true);

  setFont(&FONT_TINY);

  DrawStringAt(
      "< home",
      0, y_offset,
      NULL, &y_offset);
  y_offset = 0;
  x_offset += SIDEBAR_MARGIN;

  const game::StateT* state = engine->getState();
  game::ShipPartT userPart = generatePart(state->status->user, state->status->score);

  setFont(&FONT_POPPINS_8);
  char buf[32];
  snprintf(buf, sizeof(buf), "Trade Parts - %d xp", userPart.quality);

  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  x_offset += 5;


  setFont(&FONT_TINY);
  DrawStringAt(
      "To trade with another player, enter",
      x_offset, y_offset,
      NULL, &y_offset);
  DrawStringAt(
      "their code using ^, v, >, and X",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;
  std::string seq = userButtonSequenceStr(getUserButtonSequence(engine->getState()->status->user));
  snprintf(buf, sizeof(buf), "Your code is: %s", seq.c_str());
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);

  auto cb = engine->getTradeState()->codeBuffer;
  std::vector<nav::Command> entered = std::vector<nav::Command>(cb.begin(), cb.end());
  std::string seq_entered = userButtonSequenceStr(entered);
  snprintf(buf, sizeof(buf), "Currently listening for: %s", seq_entered.c_str());
  DrawStringAt(
      buf,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  2 * LINESPACING;

  std::string thruster_s = "You need a thruster";
  std::string cargo_s = "You need a cargo bay";
  std::string sensors_s  = "You need a sensor array";
  std::string hull_s = "You need a hull";

  switch (userPart.type) {
    case game::ShipPartType_hull:
      hull_s = "Your factory makes hulls";
      break;
    case game::ShipPartType_thruster:
      thruster_s = "Your factory makes thrusters";
      break;
    case game::ShipPartType_cargo:
      cargo_s = "Your factory makes cargo bays";
      break;
    case game::ShipPartType_sensors:
      sensors_s = "Your factory makes sensor arrayss";
      break;
  }

  const auto* data = engine->getData();

  const auto& parts = engine->getState()->parts;
  for(int i = 0; i < parts.size(); i++) {
    auto& p = parts[i];
    switch (p->type) {
      case game::ShipPartType_hull:
        snprintf(buf, sizeof(buf), 
            "Hull from %s (%d)",
            data->users[p->creator]->username.c_str(),
            p->quality);
        hull_s = std::string(buf);
        break;
      case game::ShipPartType_thruster:
        snprintf(buf, sizeof(buf), 
            "Thruster from %s (%d)",
            data->users[p->creator]->username.c_str(),
            p->quality);
        thruster_s = std::string(buf);
        break;
      case game::ShipPartType_cargo:
        snprintf(buf, sizeof(buf), 
            "Cargo bay from %s (%d)",
            data->users[p->creator]->username.c_str(),
            p->quality);
        cargo_s = std::string(buf);
        break;
      case game::ShipPartType_sensors:
        snprintf(buf, sizeof(buf), 
            "Sensor array from %s (%d)",
            data->users[p->creator]->username.c_str(),
            p->quality);
        sensors_s = std::string(buf);
        break;
    }
  }

  if (engine->readyToLaunch()) {
    DrawStringWithin(
        "Ready to launch!",
        x_offset, y_offset,
        NULL, NULL,
        EPAPER_LONG_DIMENSION - x_offset,
        KNOWN_FONTS_DISPLAY); 
  } else {

    setFont(&FONT_ROBOTO_6);

    DrawStringAt(
        hull_s,
        x_offset, y_offset,
        NULL, &y_offset);
    y_offset +=  LINESPACING/2;

    DrawStringAt(
        thruster_s,
        x_offset, y_offset,
        NULL, &y_offset);
    y_offset +=  LINESPACING/2;

    DrawStringAt(
        sensors_s,
        x_offset, y_offset,
        NULL, &y_offset);
    y_offset +=  LINESPACING/2;

    DrawStringAt(
        cargo_s,
        x_offset, y_offset,
        NULL, &y_offset);
    y_offset +=  LINESPACING/2;
  }

  /*
  // Draw our ID sequence
  drawText(seq, SZ_S, BODY_X + (2*SZ_M), BODY_Y);
  */

  // Draw parts collected from others
  /*
  const auto& parts = engine->getState()->parts;
  for (int i = 0; i < parts.size(); i++) {
    if (parts[i]->quality == 0) {
      continue;
    }
    int l = (parts[i]->type == game::ShipPartType_hull || parts[i]->type == game::ShipPartType_thruster);
    int t = (parts[i]->type == game::ShipPartType_hull || parts[i]->type == game::ShipPartType_cargo);
    drawText(game::EnumNameShipPartType(parts[i]->type), SZ_S,
      BODY_X + 3*SZ_M*l,
      BODY_Y + SZ_M + SZ_M*t);
    snprintf(buf, sizeof(buf), "%d", parts[i]->quality);
    drawText(buf, SZ_S,
      BODY_X + (2*SZ_M) + 3*SZ_M*l,
      BODY_Y + SZ_M + SZ_M*t);
  }
  */
}
