#ifndef NAV_H
#define NAV_H

#include <map>
#include "nav_generated.h"
#include <stdint.h>

using namespace nav;

Page nextPage(const Page& page, const Command& cmd);

#endif // NAV_H
