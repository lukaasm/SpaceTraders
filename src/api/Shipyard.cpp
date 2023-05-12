#include "Shipyard.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    Result< Shipyard > GetWaypointShipyard( const std::string & system, const std::string & waypoint )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/systems/{}/waypoints/{}/shipyard", system, waypoint ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Shipyard >();
    }
}
