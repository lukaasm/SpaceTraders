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

    struct SystemType
    {
        static constexpr auto NEUTRON_STAR = "NEUTRON_STAR";
        static constexpr auto RED_STAR     = "RED_STAR";
        static constexpr auto ORANGE_STAR  = "ORANGE_STAR";
        static constexpr auto BLUE_STAR    = "BLUE_STAR";
        static constexpr auto YOUNG_STAR   = "YOUNG_STAR";
        static constexpr auto WHITE_DWARF  = "WHITE_DWARF";
        static constexpr auto BLACK_HOLE   = "BLACK_HOLE";
        static constexpr auto HYPERGIANT   = "HYPERGIANT";
        static constexpr auto NEBULA       = "NEBULA";
        static constexpr auto UNSTABLE     = "UNSTABLE";

        std::string symbol;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( SystemType, symbol );
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

    Result<System>          GetSystem( const std::string & symbol );
    PagedResult<System>     GetSystems( size_t page = 1, size_t limit = 20 );
}
