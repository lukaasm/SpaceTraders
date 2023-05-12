#include "Faction.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    PagedResult< Faction > GetFactions( size_t page /*= 1*/, size_t limit /*= 20 */ )
    {
        httplib::Params body =
        {
            { "page", std::format( "{}", page ) },
            { "limit", std::format( "{}", limit ) },
        };

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( "v2/factions", body, {} );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<Faction> >();
    }

    Result<Faction> GetFaction( const std::string & symbol )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/factions/{}", symbol ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Faction >();
    }
}
