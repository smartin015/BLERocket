#ifndef NAV_H
#define NAV_H

#include <map>
#include "nav_generated.h"
#include <stdint.h>

using namespace nav;

const std::map<Page, std::map<Command, Page>> NAV_STATE_TRANSITION = {
  {
    Page_main,
    {
      {Command_up,     Page_launchEntry},
      {Command_down,   Page_fleetEntry},
      {Command_left,   Page_noOp},
      {Command_right,  Page_tradeEntry},
      {Command_enter,  Page_settingsEntry}
    }
  },
  {
    Page_settingsEntry,
    {
      {Command_up,     Page_settingsReset},
      {Command_down,   Page_settingsSelectUser},
      {Command_left,   Page_main},
      {Command_right,  Page_settingsChangeName},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_tradeEntry,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_main},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_fleetEntry,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_main},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_shipDetails}
    }
  },
  {
    Page_launchEntry,
    {
      {Command_up,     Page_main},
      {Command_down,   Page_main},
      {Command_left,   Page_main},
      {Command_right,  Page_main},
      {Command_enter,  Page_launchSplash}
    }
  },
  {
    Page_settingsChangeName,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_settingsEntry}
    }
  },
  {
    Page_settingsSelectUser,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_settingsEntry},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_main}
    }
  },
  {
    Page_settingsReset,
    {
      {Command_up,     Page_main},
      {Command_down,   Page_main},
      {Command_left,   Page_main},
      {Command_right,  Page_main},
      {Command_enter,  Page_main}
    }
  },
  {
    Page_shipDetails,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_shipRename},
      {Command_left,   Page_fleetEntry},
      {Command_right,  Page_shipMissionSelect},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_shipMissionSelect,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_shipDetails},
      {Command_right,  Page_shipDestSelect},
      {Command_enter,  Page_shipDestSelect}
    }
  },
  {
    Page_shipDestSelect,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_shipMissionSelect},
      {Command_right,  Page_shipConfirm},
      {Command_enter,  Page_shipConfirm}
    }
  },
  {
    Page_shipConfirm,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_shipDestSelect},
      {Command_right,  Page_shipSplash},
      {Command_enter,  Page_shipSplash}
    }
  },
  {
    Page_shipSplash,
    {
      {Command_up,     Page_fleetEntry},
      {Command_down,   Page_fleetEntry},
      {Command_left,   Page_fleetEntry},
      {Command_right,  Page_fleetEntry},
      {Command_enter,  Page_fleetEntry}
    }
  },
  {
    Page_shipRename,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_shipDetails}
    }
  },
  {
    Page_eventShipVisit,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_eventPlayerLaunch,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_shipVisitDecision,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_shipVisitOutcome,
    {
      {Command_up,     Page_noOp},
      {Command_down,   Page_noOp},
      {Command_left,   Page_noOp},
      {Command_right,  Page_noOp},
      {Command_enter,  Page_noOp}
    }
  },
  {
    Page_launchSplash,
    {
      {Command_up,     Page_shipRename},
      {Command_down,   Page_shipRename},
      {Command_left,   Page_shipRename},
      {Command_right,  Page_shipRename},
      {Command_enter,  Page_shipRename}
    }
  }
};

Page nextPage(const Page& page, const Command& cmd);

#endif // NAV_H
