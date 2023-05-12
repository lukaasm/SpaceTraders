#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct ShipType
    {
        static constexpr auto SHIP_PROBE                 = "SHIP_PROBE";
        static constexpr auto SHIP_MINING_DRONE          = "SHIP_MINING_DRONE";
        static constexpr auto SHIP_INTERCEPTOR           = "SHIP_INTERCEPTOR";
        static constexpr auto SHIP_LIGHT_HAULER          = "SHIP_LIGHT_HAULER";
        static constexpr auto SHIP_COMMAND_FRIGATE       = "SHIP_COMMAND_FRIGATE";
        static constexpr auto SHIP_EXPLORER              = "SHIP_EXPLORER";
        static constexpr auto SHIP_HEAVY_FREIGHTER       = "SHIP_HEAVY_FREIGHTER";
        static constexpr auto SHIP_LIGHT_SHUTTLE         = "SHIP_LIGHT_SHUTTLE";
        static constexpr auto SHIP_ORE_HOUND             = "SHIP_ORE_HOUND";
        static constexpr auto SHIP_REFINING_FREIGHTER    = "SHIP_REFINING_FREIGHTER";

        std::string type;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ShipType, type );
    };

    struct ShipyardTransaction
    {
        std::string             waypointSymbol;
        std::string             shipSymbol;
        int                     price = {};
        std::string             agentSymbol;
        std::string             timestamp;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ShipyardTransaction, waypointSymbol, shipSymbol, price, agentSymbol, timestamp );
    };

    struct ShipyardShip
    {
        std::string             type;
        std::string             name;
        std::string             description = {};
        int                     purchasePrice = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ShipyardShip, type, name, description, purchasePrice );
    };

    struct Shipyard
    {
        std::string                         symbol;
        std::vector< ShipType >             shipTypes;
        std::vector< ShipyardTransaction >  transactions;
        std::vector< ShipyardShip >         ships;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Shipyard, symbol, shipTypes, transactions, ships );
    };

    Result< Shipyard >        GetWaypointShipyard( const std::string & system, const std::string & waypoint );
}
