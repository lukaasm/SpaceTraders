#include "System.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    Result<std::vector<System>> GetSystems( size_t page, size_t limit )
    {
        httplib::Params body =
        {
            { "page", std::format( "{}", page ) },
            { "limit", std::format( "{}", limit ) },
        };

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( "v2/systems", std::move( body ), {} );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<System> >();
    }

    Result<System> GetSystem( const std::string & symbol )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/systems/{}", symbol ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< System >();
    }
}
