#include "ui.h"
#include <iostream>

// Nametag page
void UI::drawNametag(const Engine* engine) {
  // TODO user name, location, username
  int id = engine->getState()->status->user;
  const auto* data = engine->getData();

  std::string firstname = data->users[id]->firstname;
  std::string lastname = data->users[id]->lastname;
  std::string username = data->users[id]->username;
  std::string site = data->users[id]->site;

  int score = engine->getState()->status->score;

  
  setRotation(ROTATION_NAMETAG);

  if (score == 0) {
    DrawSidebarText("press any key to play", true);
  } else {
    char buf[16];
    DrawSidebarText(notification, true);
  }

  int x_offset = SIDEBAR_WIDTH + SIDEBAR_MARGIN;;
  int y_offset = NAMETAG_TOP_MARGIN;

  DrawStringWithin(
      firstname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  LINESPACING;

  DrawStringWithin(
      lastname,
      x_offset,
      y_offset,
      NULL, &y_offset,
      EPAPER_LONG_DIMENSION - x_offset,
      KNOWN_FONTS_DISPLAY
      );
  y_offset +=  2*LINESPACING;

  setFont(&FONT_ROBOTO_6);
  DrawStringAt(
      username + "@",
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  setFont(&FONT_ROBOTO_6);
  DrawStringAt(
      site,
      x_offset, y_offset,
      NULL, &y_offset);
  y_offset +=  LINESPACING;

  // TODO active events
  // TODO visiting rockets
}
