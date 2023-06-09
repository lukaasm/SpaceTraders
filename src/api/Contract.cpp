#include "Contract.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    PagedResult< Contract > GetContracts( size_t page /*= 1*/, size_t limit /*= 20 */ )
    {
        httplib::Params body =
        {
            { "page", std::format( "{}", page ) },
            { "limit", std::format( "{}", limit ) },
        };

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( "v2/my/contracts", body, {} );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<Contract> >();
    }

    Result< Contract > GetContract( const std::string & contractId )
    {
        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( std::format( "v2/my/contracts/{}", contractId ) );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Contract >();
    }

}
