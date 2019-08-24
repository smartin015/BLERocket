@0xf5750227d1666c0c;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("message");

using Nav = import "nav.capnp";
using Game = import "game.capnp";

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
  # Metadata
  firmwareVersion @0 :UInt8;
  user @1 :Game.User;
  site @2 :UInt8;

  # Game state details
  phase @3 :Game.Phase;
  score @4 :UInt16;
  reputation @5 :UInt16;
}

struct ActionMessage {
  action @0 :Action;
  ship @1 :Game.Ship;
  dest @2 :Game.User;
}

struct PartActionMessage {
  action @0 :Action;
  part @1 :Game.ShipPart;
  quality @2 :UInt8;
  dest @3 :Game.User;
}
