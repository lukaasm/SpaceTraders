#include "System.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    Result<std::vector<System>> GetSystems( size_t page, size_t limit )
    {
        nlohmann::json body;
        body[ "page" ] = page;
        body[ "limit" ] = limit;

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( "v2/systems" );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected< std::vector<System> >( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<System> >();
    }
}
