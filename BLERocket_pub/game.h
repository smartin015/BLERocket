#ifndef BLE_GAME_H
#define BLE_GAME_H

typedef enum {
  PART_HULL = 0,
  PART_THRUSTER = 1,
  PART_CARGO = 2,
  PART_SENSORS = 3,
  NUM_PARTS = 4
} ship_part_t;
#define USER_PART PART_HULL
const char* PART_NAMES[NUM_PARTS] = {
  "Hull",
  "Thruster",
  "Cargo Bay",
  "Sensor Array",
};

#define USER_ID_BITLEN 6
typedef struct {
  uint8_t id : USER_ID_BITLEN;
} user_t;

#define MAX_SHIPS 16
typedef struct {
  uint8_t name;
  uint8_t parts[NUM_PARTS];
  user_t creators[NUM_PARTS];
  user_t owner;
} ship_t;

typedef struct {
  uint8_t id: 2;
  uint8_t txn: 6;
} phase_t;

typedef struct {
  // Metadata
  uint8_t firmware_version;
  user_t user;
  uint8_t site;

  // Game state details
  phase_t phase;
  uint16_t score;
  uint16_t reputation;
} status_t;

#endif // BLE_GAME_H
