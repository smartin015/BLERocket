#ifndef NAV_H
#define NAV_H

#include <map>
#include "nav.capnp.h"
#include <stdint.h>

using nav::Page;
using nav::Command;

const std::map<Page, std::map<Command, Page>> NAV_STATE_TRANSITION = {
  {
    Page::MAIN,
    {
      {Command::UP,     Page::LAUNCH_ENTRY},
      {Command::DOWN,   Page::FLEET_ENTRY},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::TRADE_ENTRY},
      {Command::ENTER,  Page::SETTINGS_ENTRY}
    }
  },
  {
    Page::SETTINGS_ENTRY,
    {
      {Command::UP,     Page::SETTINGS_RESET},
      {Command::DOWN,   Page::SETTINGS_SELECT_USER},
      {Command::LEFT,   Page::MAIN},
      {Command::RIGHT,  Page::SETTINGS_CHANGE_NAME},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::TRADE_ENTRY,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::MAIN},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::FLEET_ENTRY,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::MAIN},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::SHIP_DETAILS}
    }
  },
  {
    Page::LAUNCH_ENTRY,
    {
      {Command::UP,     Page::MAIN},
      {Command::DOWN,   Page::MAIN},
      {Command::LEFT,   Page::MAIN},
      {Command::RIGHT,  Page::MAIN},
      {Command::ENTER,  Page::LAUNCH_SPLASH}
    }
  },
  {
    Page::SETTINGS_CHANGE_NAME,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::SETTINGS_ENTRY}
    }
  },
  {
    Page::SETTINGS_SELECT_USER,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::SETTINGS_ENTRY},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::MAIN}
    }
  },
  {
    Page::SETTINGS_RESET,
    {
      {Command::UP,     Page::MAIN},
      {Command::DOWN,   Page::MAIN},
      {Command::LEFT,   Page::MAIN},
      {Command::RIGHT,  Page::MAIN},
      {Command::ENTER,  Page::MAIN}
    }
  },
  {
    Page::SHIP_DETAILS,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::SHIP_RENAME},
      {Command::LEFT,   Page::FLEET_ENTRY},
      {Command::RIGHT,  Page::SHIP_MISSION_SELECT},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::SHIP_MISSION_SELECT,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::SHIP_DETAILS},
      {Command::RIGHT,  Page::SHIP_DEST_SELECT},
      {Command::ENTER,  Page::SHIP_DEST_SELECT}
    }
  },
  {
    Page::SHIP_DEST_SELECT,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::SHIP_MISSION_SELECT},
      {Command::RIGHT,  Page::SHIP_CONFIRM},
      {Command::ENTER,  Page::SHIP_CONFIRM}
    }
  },
  {
    Page::SHIP_CONFIRM,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::SHIP_DEST_SELECT},
      {Command::RIGHT,  Page::SHIP_SPLASH},
      {Command::ENTER,  Page::SHIP_SPLASH}
    }
  },
  {
    Page::SHIP_SPLASH,
    {
      {Command::UP,     Page::FLEET_ENTRY},
      {Command::DOWN,   Page::FLEET_ENTRY},
      {Command::LEFT,   Page::FLEET_ENTRY},
      {Command::RIGHT,  Page::FLEET_ENTRY},
      {Command::ENTER,  Page::FLEET_ENTRY}
    }
  },
  {
    Page::SHIP_RENAME,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::SHIP_DETAILS}
    }
  },
  {
    Page::EVENT_SHIP_VISIT,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::EVENT_PLAYER_LAUNCH,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::SHIP_VISIT_DECISION,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::SHIP_VISIT_OUTCOME,
    {
      {Command::UP,     Page::NO_OP},
      {Command::DOWN,   Page::NO_OP},
      {Command::LEFT,   Page::NO_OP},
      {Command::RIGHT,  Page::NO_OP},
      {Command::ENTER,  Page::NO_OP}
    }
  },
  {
    Page::LAUNCH_SPLASH,
    {
      {Command::UP,     Page::SHIP_RENAME},
      {Command::DOWN,   Page::SHIP_RENAME},
      {Command::LEFT,   Page::SHIP_RENAME},
      {Command::RIGHT,  Page::SHIP_RENAME},
      {Command::ENTER,  Page::SHIP_RENAME}
    }
  }
};

Page nextPage(const Page& page, const Command& cmd);

#endif // NAV_H
