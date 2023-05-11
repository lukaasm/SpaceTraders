#include "Contract.hpp"
#include "Endpoint.hpp"

namespace lst::api
{
    PagedResult< Contract > GetMyContracts( size_t page /*= 1*/, size_t limit /*= 20 */ )
    {
        nlohmann::json body;
        body[ "page" ] = page;
        body[ "limit" ] = limit;

        auto & endpoint = GetEndpoint();

        auto response = GetEndpoint().Get( "v2/my/contracts" );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected< std::vector<Contract> >( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< std::vector<Contract> >();
    }
}
