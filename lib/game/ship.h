#ifndef _SHIP_H
#define _SHIP_H

#include "engine.h"

#define MAX_SHIP_NAME_LEN 8
#define SHIP_LAUNCH_SCORE_MULT 20

int getShipLaunchScore(const game::ShipT& ship);
std::string generateShipName(const game::ShipT& ship);

#endif // _SHIP_H
