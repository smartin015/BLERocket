@0xf5750227d1666c0c

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

struct StatusMessage {
  // Metadata
  firmware_version @0 :UInt8;
  user @1 :User;
  site @2 :UInt8;

  // Game state details
  phase @3 :Phase;
  score @4 :UInt16;
  reputation @5 :UInt16;
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
