

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

typedef enum {
  PART_HULL = 0,
  PART_THRUSTER = 1,
  PART_C = 2,
  PART_D = 3,
  PART_E = 4
} rocket_part_t;


#define ATTRIBUTE_BITLEN 3
typedef enum {
  ATTRIB_CARGO = 0,
  ATTRIB_SPEED = 1,
  ATTRIB_C = 2, 
  ATTRIB_D = 3,
  ATTRIB_E = 4
} rocket_attr_t;

typedef struct {
  uint8_t cargo : 4;
  uint8_t spd : 3;
  uint8_t c : 3;
  uint8_t d : 3;
  uint8_t e : 3;
} rocket_config_t; // 2 bytes to fully describe a rocket

typedef struct {
  message_t msg : 8;
  rocket_config_t rocket;
} rocket_action_msg_t;
