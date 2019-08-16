#ifndef BLE_MSG_H
#define BLE_MSG_H

#include "game.h"

enum message_t {
 // Resource messages
 TYPE_GIVE = 0xA0,
 // TYPE_MAKE
 // TYPE_LAUNCH

 // Ship action messages
 TYPE_RACE = 0xA1,
 TYPE_TRADE = 0xA2,
 TYPE_EXPLORE = 0xA3,

 // Status messages
 TYPE_SCORE = 0xA4
};

typedef struct {
  message_t msg : 8;
  ship_t ship;
  user_t dest;
} ship_action_msg_t;

typedef struct {
  message_t msg: 8;
  ship_part_t part: 4;
  uint8_t quality: 6;
  user_t dest;
} part_action_msg_t;

#endif // BLE_MSG_H
