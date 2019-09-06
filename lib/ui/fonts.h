#ifndef _FONTS_H_
#define _FONTS_H_

// define fonts for use

// Define a font type.
#ifdef UI_EPAPER

#include "gfxfont.h"

typedef GFXfont FONT_T;

#include "fonts/PoppinsExtraBold18pt7b.h"
#include "fonts/PoppinsExtraBold16pt7b.h"
#include "fonts/PoppinsExtraBold12pt7b.h"
#include "fonts/PoppinsExtraBold8pt7b.h"

#include "fonts/RobotoMonoBold6pt7b.h"
#include "fonts/RobotoMonoBold12pt7b.h"
#include "fonts/RobotoMonoBold14pt7b.h"


#define FONT_POPPINS_18 &PoppinsExtraBold18pt7b
#define FONT_POPPINS_16 &PoppinsExtraBold16pt7b
#define FONT_POPPINS_12 &PoppinsExtraBold12pt7b
#define FONT_POPPINS_8  &PoppinsExtraBold8pt7b

#define FONT_ROBOTO_14  &RobotoMonoBold14pt7b
#define FONT_ROBOTO_12  &RobotoMonoBold12pt7b
#define FONT_ROBOTO_6   &RobotoMonoBold6pt7b

#endif // UI_EPAPER



#ifdef UI_NATIVE

#include <SFML/Graphics.hpp>

// This is a hack. The idea is that we statically initialize the structs here,
// then actually load the files at runtime.
typedef struct {
  sf::Font* ttf; // NULL untill runtime
  const char* filename;
  int height;
} FONT_T;

FONT_T 

#endif // UI_NATIVE


#endif //_FONTS_H_
