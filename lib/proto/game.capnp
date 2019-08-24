@0xa98c2975f96d9835;

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

struct User {
  id @0 :UInt8;
}

struct Ship {
  name @0 :Text;
  parts @1 :List(ShipPart);
  creators @2 :List(User);
  owner @3 :User;
}

struct Phase {
  id @0 :UInt8;
  txn @1 :UInt8;
}
