#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct SystemWaypoint
    {
        std::string symbol;
        std::string type;

        int x = {};
        int y = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( SystemWaypoint, symbol, type, x, y );
    };

    struct SystemFaction
    {
        std::string symbol;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( SystemFaction, symbol );
    };

    struct System
    {
        std::string symbol;
        std::string sectorSymbol;
        std::string type;

        int x = {};
        int y = {};

        std::vector< SystemWaypoint >   waypoints;
        std::vector< SystemFaction >    factions;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( System, symbol, sectorSymbol, type, x, y, waypoints, factions );
    };

    Result<std::vector<System>> GetSystems( size_t page = 1, size_t limit = 20 );
}