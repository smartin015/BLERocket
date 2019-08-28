@0xf5750227d1666c0c;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("message");

using Nav = import "nav.capnp";
using Game = import "game.capnp";

enum Type {
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

struct Message {
  msg :union {
    status @0 :Status;
    ship @1 :Ship;
    part @2 :Part;
  }
}

struct Status {
  # Metadata
  firmwareVersion @0 :UInt8;
  user @1 :Game.User;
  site @2 :UInt8;

  # Game state details
  phase @3 :Game.Phase;
  score @4 :UInt16;
  reputation @5 :UInt16;
}

struct Ship {
  action @0 :Type;
  ship @1 :Game.Ship;
  dest @2 :Game.User;
}

struct Part {
  action @0 :Type;
  part @1 :Game.ShipPart;
  quality @2 :UInt8;
  dest @3 :Game.User;
}
