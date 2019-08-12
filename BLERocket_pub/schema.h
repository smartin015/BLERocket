#ifndef BLE_SCHEMA_H
#define BLE_SCHEMA_H

/* msg format for rocketry: 
    *  TYPE_RACE|RocketConfig
    *  TYPE_TRADE|RocketConfig
    *  TYPE_EXPLORE|RocketConfig
    *  TYPE_SCORE|<uint32_t score>
    * msg format for manufacturing:
    *  TYPE_GIVE|RocketPart
    */
    
typedef enum {
 // Resource messages
 TYPE_GIVE = 0xA0,
 // TYPE_MAKE
 // TYPE_LAUNCH

 // Rocket action messages
 TYPE_RACE = 0xA1,
 TYPE_TRADE = 0xA2,
 TYPE_EXPLORE = 0xA3,

 // Status messages
 TYPE_SCORE = 0xA4
} message_t;

// Max number of destinations to show, ordered by RSSI
#define MAX_DEST 5
typedef uint8_t dest_addr_t;

typedef enum {
  PART_HULL = 0,
  PART_THRUSTER = 1,
  PART_C = 2,
  PART_D = 3,
  NUM_PARTS = 4
} rocket_part_t;
#define USER_PART PART_HULL
const char* PART_NAMES[NUM_PARTS] = {
  "Hull",
  "Thruster",
  "C",
  "D",
};

#define ATTRIBUTE_BITLEN 3
typedef enum {
  ATTRIB_CARGO = 0,
  ATTRIB_SPEED = 1,
  ATTRIB_C = 2, 
  ATTRIB_D = 3,
} rocket_attr_t;

#define MAX_ROCKETS 16
#define PART_QUALITY_NBITS 4
typedef struct {
  uint8_t cargo : PART_QUALITY_NBITS;
  uint8_t spd : PART_QUALITY_NBITS;
  uint8_t c : PART_QUALITY_NBITS;
  uint8_t d : PART_QUALITY_NBITS;
} rocket_config_t; // 2 bytes to fully describe a rocket

typedef struct {
  message_t msg : 8;
  rocket_config_t rocket; // 2 bytes
  dest_addr_t dest;
} rocket_action_msg_t;

typedef struct {
  message_t msg: 8;
  rocket_part_t part: 4;
  uint8_t quality: PART_QUALITY_NBITS;
  dest_addr_t dest;
} part_action_msg_t;

typedef enum {
   SCREEN_OFF = 0,
   SCREEN_STATUS = 1,
   SCREEN_MAKE = 2,
   SCREEN_GIVE = 3,
   SCREEN_LAUNCH = 4,
} screen_t;

typedef enum {
  CMD_DOWN = 0,
  CMD_UP = 1,
  CMD_LEFT = 2,
  CMD_RIGHT = 3,
  CMD_ENTER = 4,
} cmd_t;

#endif // BLE_SCHEMA_H
