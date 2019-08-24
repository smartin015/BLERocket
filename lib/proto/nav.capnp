@0xa6eac0a6d72898a3;

const cmdNum :UInt8 = 5;
enum Command {
  unknown @0;
  down @1;
  up @2;
  left @3;
  right @4;
  enter @5;
}

const pageNum :UInt8 = 19;
enum Page {
  # Default page for user (including the ever-important nametag)
  main @0;

  # Entry points for user-triggered flows
  settingsEntry @1;
  tradeEntry @2;
  fleetEntry @3;
  launchEntry @4;

  # Different game settings pages
  settingsChangeName @5;
  settingsSelectUser @6;
  settingsReset @7;

  # UI for acting on a single ship
  shipDetails @8;
  shipMissionSelect @9;
  shipDestSelect @10;
  shipConfirm @11;
  shipSplash @12;
  shipRename @13;

  # Events are arrive async from other users.
  # They are handled synchronously by the dest user.
  eventShipVisit @14;
  eventPlayerLaunch @15;

  # When user ships visit; the dest user is presented
  # with a random decision to make; and an outcome
  # following that decision.
  shipVisitDecision @16;
  shipVisitOutcome @17;

  launchSplash @18;

  noOp @19;
}

enum Action {
 # Resource messages
 give @0;
 # MAKE
 # LAUNCH

 # Ship action messages
 race @1;
 trade @2;
 explore @3;

 # Status messages
 score @4;
}

enum ShipPartType {
  hull @0;
  thruster @1;
  cargo @2;
  sensors @3;
}

struct ShipPart {
  type @0 :ShipPartType;
  quality @1 :UInt8;
}

struct ActionMessage {
  action @0 :Action;
  ship @1 :Ship;
  dest @2 :User;
};

struct PartActionMessage {
  action @0 :Action;
  part @1 :Part;
  quality @2 :UInt8;
  dest @3 :User;
}


#define USER_ID_BITLEN 6
struct User {
  id @0 :UInt8;
}

#define MAX_SHIPS 16
struct Ship {
  name @0 :Text;
  parts @1 :List(ShipPart);
  creators @2 :List(User);
  owner @3 :User;
}

struct GamePhase {
  id @0 :UInt8;
  txn @1 :UInt8;
}

struct Status {
  // Metadata
  firmware_version @0 :UInt8;
  user @1 :User;
  site @2 :UInt8;

  // Game state details
  phase @3 :Phase;
  score @4 :UInt16;
  reputation @5 :UInt16;
}
