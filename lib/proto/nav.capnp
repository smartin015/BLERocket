@0xa6eac0a6d72898a3;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("nav");

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

