#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct FactionTrait
    {
        std::string                 symbol;
        std::string                 name;
        std::string                 description;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( FactionTrait, symbol, name, description );
    };

    struct Faction
    {
        std::string                 symbol;
        std::string                 name;
        std::string                 description;
        std::string                 headquarters;

        std::vector< FactionTrait > traits;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Faction, symbol, name, description, headquarters, traits );
    };

    Result<Faction>        GetFaction( const std::string & symbol );
    PagedResult< Faction > GetFactions( size_t page = 1, size_t limit = 20 );
}
