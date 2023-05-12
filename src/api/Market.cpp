#include "Market.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    Result< Market > GetWaypointMarket( const std::string & system, const std::string & waypoint )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/systems/{}/waypoints/{}/market", system, waypoint ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Market >();
    }

}
