#include "Waypoint.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    PagedResult< Waypoint > GetWaypoints( const std::string & system, size_t page, size_t limit )
    {
        httplib::Params body =
        {
            { "page", std::format( "{}", page ) },
            { "limit", std::format( "{}", limit ) },
        };

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/systems/{}/waypoints", system ), body, {} );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<Waypoint> >();
    }

    Result< Waypoint > GetWaypoint( const std::string & system, const std::string & waypoint )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/systems/{}/waypoints/{}", system, waypoint ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Waypoint >();
    }
}
