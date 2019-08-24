#include "nav.h"

Page nextPage(const Page& page, const Command& cmd) {
  return NAV_STATE_TRANSITION.at(page).at(cmd);
}
