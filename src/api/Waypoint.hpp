#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct WaypointType
    {
        static constexpr auto PLANET            = "PLANET";
        static constexpr auto GAS_GIANT         = "GAS_GIANT";
        static constexpr auto MOON              = "MOON";
        static constexpr auto ORBITAL_STATION   = "ORBITAL_STATION";
        static constexpr auto JUMP_GATE         = "JUMP_GATE";
        static constexpr auto ASTEROID_FIELD    = "ASTEROID_FIELD";
        static constexpr auto NEBULA            = "NEBULA";
        static constexpr auto DEBRIS_FIELD      = "DEBRIS_FIELD";
        static constexpr auto GRAVITY_WELL      = "GRAVITY_WELL";

        std::string symbol;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( WaypointType, symbol );
    };

    struct WaypointFaction
    {
        std::string symbol;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( WaypointFaction, symbol );
    };

    struct WaypointOrbital
    {
        std::string symbol;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( WaypointOrbital, symbol );
    };

    struct WaypointTrait
    {
        static constexpr auto UNCHARTED                 = "UNCHARTED";
        static constexpr auto MARKETPLACE               = "MARKETPLACE";
        static constexpr auto SHIPYARD                  = "SHIPYARD ";
        static constexpr auto OUTPOST                   = "OUTPOST";
        static constexpr auto SCATTERED_SETTLEMENTS     = "SCATTERED_SETTLEMENTS";
        static constexpr auto SPRAWLING_CITIES          = "SPRAWLING_CITIES";
        static constexpr auto MEGA_STRUCTURES           = "MEGA_STRUCTURES";
        static constexpr auto OVERCROWDED               = "OVERCROWDED";
        static constexpr auto HIGH_TECH                 = "HIGH_TECH";
        static constexpr auto CORRUPT                   = "CORRUPT";
        static constexpr auto BUREAUCRATIC              = "BUREAUCRATIC";
        static constexpr auto TRADING_HUB               = "TRADING_HUB";
        static constexpr auto INDUSTRIAL                = "INDUSTRIAL";
        static constexpr auto BLACK_MARKET              = "BLACK_MARKET";
        static constexpr auto RESEARCH_FACILITY         = "RESEARCH_FACILITY";
        static constexpr auto MILITARY_BASE             = "MILITARY_BASE";
        static constexpr auto SURVEILLANCE_OUTPOST      = "SURVEILLANCE_OUTPOST";
        static constexpr auto EXPLORATION_OUTPOST       = "EXPLORATION_OUTPOST";
        static constexpr auto MINERAL_DEPOSITS          = "MINERAL_DEPOSITS";
        static constexpr auto COMMON_METAL_DEPOSITS     = "COMMON_METAL_DEPOSITS";
        static constexpr auto PRECIOUS_METAL_DEPOSITS   = "PRECIOUS_METAL_DEPOSIT";
        static constexpr auto RARE_METAL_DEPOSITS       = "RARE_METAL_DEPOSITS";
        static constexpr auto METHANE_POOLS             = "METHANE_POOLS";
        static constexpr auto ICE_CRYSTALS              = "ICE_CRYSTALS";
        static constexpr auto EXPLOSIVE_GASES           = "EXPLOSIVE_GASES";
        static constexpr auto STRONG_MAGNETOSPHERE      = "STRONG_MAGNETOSPHERE";
        static constexpr auto VIBRANT_AURORAS           = "VIBRANT_AURORAS";
        static constexpr auto SALT_FLATS                = "SALT_FLATS";
        static constexpr auto CANYONS                   = "CANYONS";
        static constexpr auto PERPETUAL_DAYLIGHT        = "PERPETUAL_DAYLIGHT";    
        static constexpr auto PERPETUAL_OVERCAST        = "PERPETUAL_OVERCAST";    
        static constexpr auto DRY_SEABEDS               = "DRY_SEABEDS";
        static constexpr auto MAGMA_SEAS                = "MAGMA_SEAS";
        static constexpr auto SUPERVOLCANOES            = "SUPERVOLCANOES";
        static constexpr auto ASH_CLOUDS                = "ASH_CLOUDS";            
        static constexpr auto VAST_RUINS                = "VAST_RUINS";            
        static constexpr auto MUTATED_FLORA             = "MUTATED_FLORA";
        static constexpr auto TERRAFORMED               = "TERRAFORMED";
        static constexpr auto EXTREME_TEMPERATURES      = "EXTREME_TEMPERATURES";
        static constexpr auto EXTREME_PRESSURE          = "EXTREME_PRESSURE";
        static constexpr auto DIVERSE_LIFE              = "DIVERSE_LIFE";
        static constexpr auto SCARCE_LIFE               = "SCARCE_LIFE";
        static constexpr auto FOSSILS                   = "FOSSILS";
        static constexpr auto WEAK_GRAVITY              = "WEAK_GRAVITY";
        static constexpr auto STRONG_GRAVITY            = "STRONG_GRAVITY";
        static constexpr auto CRUSHING_GRAVITY          = "CRUSHING_GRAVITY";
        static constexpr auto TOXIC_ATMOSPHERE          = "TOXIC_ATMOSPHERE";
        static constexpr auto CORROSIVE_ATMOSPHERE      = "CORROSIVE_ATMOSPHERE";
        static constexpr auto BREATHABLE_ATMOSPHERE     = "BREATHABLE_ATMOSPHERE";
        static constexpr auto JOVIAN                    = "JOVIAN";
        static constexpr auto ROCKY                     = "ROCKY";
        static constexpr auto VOLCANIC                  = "VOLCANIC";
        static constexpr auto FROZEN                    = "FROZEN";
        static constexpr auto SWAMP                     = "SWAMP";
        static constexpr auto BARREN                    = "BARREN";
        static constexpr auto TEMPERATE                 = "TEMPERATE";
        static constexpr auto JUNGLE                    = "JUNGLE";
        static constexpr auto OCEAN                     = "OCEAN";
        static constexpr auto STRIPPED                  = "STRIPPED";

        std::string symbol;
        std::string name;
        std::string description;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( WaypointTrait, symbol, name, description );
    };

    struct Chart
    {
        std::string                    waypointSymbol;
        std::string                    submittedBy;
        std::string                    submittedOn;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Chart, waypointSymbol, submittedBy, submittedOn );
    };

    struct Waypoint
    {
        std::string                    symbol;
        std::string                    type;
        std::string                    systemSymbol;

        int                            x = {};
        int                            y = {};

        std::vector< WaypointOrbital > orbitals;
        WaypointFaction                faction;
        std::vector< WaypointTrait >   traits;
        Chart                          chart;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Waypoint, symbol, type, x, y, orbitals, faction, traits );
    };

    Result< Waypoint >      GetWaypoint( const std::string & system, const std::string & waypoint );
    PagedResult< Waypoint > GetWaypoints( const std::string & system, size_t page = 1, size_t limit = 20 );
}
