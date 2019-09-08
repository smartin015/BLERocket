#ifndef _FONTS_H_
#define _FONTS_H_

// define fonts for use

// Define a font type.
#ifdef UI_EPAPER

#include <Arduino.h>
#include "gfxfont.h"
#include <Fonts/Org_01.h>

typedef const GFXfont FONT_T;

#include "fonts/PoppinsExtraBold18pt7b.h"
#include "fonts/PoppinsExtraBold16pt7b.h"
#include "fonts/PoppinsExtraBold12pt7b.h"
#include "fonts/PoppinsExtraBold8pt7b.h"

#include "fonts/RobotoMonoBold6pt7b.h"
#include "fonts/RobotoMonoBold8pt7b.h"
#include "fonts/RobotoMonoBold12pt7b.h"
#include "fonts/RobotoMonoBold14pt7b.h"


#define FONT_POPPINS_18 PoppinsExtraBold18pt7b
#define FONT_POPPINS_16 PoppinsExtraBold16pt7b
#define FONT_POPPINS_12 PoppinsExtraBold12pt7b
#define FONT_POPPINS_8  PoppinsExtraBold8pt7b

#define FONT_ROBOTO_14  RobotoMonoBold14pt7b
#define FONT_ROBOTO_12  RobotoMonoBold12pt7b
#define FONT_ROBOTO_8   RobotoMonoBold8pt7b
#define FONT_ROBOTO_6   RobotoMonoBold6pt7b

#define FONT_TINY Org_01

#endif // UI_EPAPER



#ifdef UI_NATIVE
#include <SFML/Graphics.hpp>

// This is a hack. The idea is that we statically initialize the structs here,
// then actually load the files at runtime.
typedef struct {
  sf::Font* ttf; // NULL untill runtime
  const char* filename;
  int size; // in pixels
} FONT_T;

static FONT_T FONT_POPPINS_18 = {
  NULL,
  "lib/ui/fonts/PoppinsExtraBold.ttf",
  24
};

static FONT_T FONT_POPPINS_16 = {
  NULL,
  "lib/ui/fonts/PoppinsExtraBold.ttf",
  22
};

static FONT_T FONT_POPPINS_12 = {
  NULL,
  "lib/ui/fonts/PoppinsExtraBold.ttf",
  16
};

static FONT_T FONT_POPPINS_8 = {
  NULL,
  "lib/ui/fonts/PoppinsExtraBold.ttf",
  11
};

static FONT_T FONT_ROBOTO_14 = {
  NULL,
  "lib/ui/fonts/RobotoMonoBold.ttf",
  19
};

static FONT_T FONT_ROBOTO_12 = {
  NULL,
  "lib/ui/fonts/RobotoMonoBold.ttf",
  16
};

static FONT_T FONT_ROBOTO_8 = {
  NULL,
  "lib/ui/fonts/RobotoMonoBold.ttf",
  11
};

static FONT_T FONT_ROBOTO_6 = {
  NULL,
  "lib/ui/fonts/RobotoMonoBold.ttf",
  8
};

static FONT_T FONT_TINY = {
  NULL,
  "lib/ui/fonts/RobotoMonoBold.ttf",
  8
};
#endif // UI_NATIVE

static const FONT_T* const KNOWN_FONTS_DISPLAY[] = {
  &FONT_POPPINS_18,
  &FONT_POPPINS_16,
  &FONT_POPPINS_12,
  &FONT_POPPINS_8,
  NULL,
};


#endif //_FONTS_H_
