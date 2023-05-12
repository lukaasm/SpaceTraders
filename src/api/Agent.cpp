#include "Agent.hpp"

#include "api/Endpoint.hpp"

namespace lst::api
{
    Result< Registrar > RegisterAgent( std::string symbol, std::string faction )
    {
        nlohmann::json body;
        body[ "symbol" ] = std::move( symbol );
        body[ "faction" ] = std::move( faction );

        auto content = body.dump();
        auto response = GetEndpoint().Post( "v2/register", content.c_str(), content.size(), "application/json" );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body ).get< Registrar >();
    }

    Result< Agent > GetAgentInfo( const std::string & token )
    {
        auto & endpoint = GetEndpoint();
        endpoint.set_bearer_token_auth( token );

        auto response = GetEndpoint().Get( "v2/my/agent" );
        if ( response->status != 200 )
            return HttpErrorCategory::MakeUnexpected( response->status );

        return nlohmann::json::parse( response->body )[ "data" ].get< Agent >();
    }
}
