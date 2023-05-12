#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct ConnectedSystem
    {
        std::string symbol;
        std::string sectorSymbol;
        std::string type;

        int         x = {};
        int         y = {};
        int         distance = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ConnectedSystem, symbol, sectorSymbol, type, x, y, distance );
    };

    struct JumpGate
    {
        int                             jumpRange = 0;
        std::string                     factionSymbol;

        std::vector<ConnectedSystem>    connectedSystems;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( JumpGate, jumpRange, factionSymbol, connectedSystems );
    };

    Result< JumpGate >      GetWaypointJumpGate( const std::string & system, const std::string & waypoint );
}

