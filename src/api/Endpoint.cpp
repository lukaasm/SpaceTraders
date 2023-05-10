#include "Endpoint.hpp"

namespace lst::api
{
    httplib::Client & GetEndpoint()
    {
        static httplib::Client s_client( "https://api.spacetraders.io" );
        s_client.set_keep_alive( true );

        return s_client;
    }
}
