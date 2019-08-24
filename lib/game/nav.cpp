#include "nav.h"

nav::Page nextPage(const nav::Page& page, const nav::Command& cmd) {
  return NAV_STATE_TRANSITION.at(page).at(cmd);
}
