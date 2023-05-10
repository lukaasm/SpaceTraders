#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct Waypoint
    {
        std::string symbol;
        std::string type;

        int x = {};
        int y = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Waypoint, symbol, type, x, y );
    };

    struct System
    {
        std::string symbol;
        std::string sectorSymbol;
        std::string type;

        int x = {};
        int y = {};

        std::vector< Waypoint > waypoints;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( System, symbol, sectorSymbol, type, x, y, waypoints );
    };

    Result<std::vector<System>> GetSystems( size_t page = 1, size_t limit = 20 );
}