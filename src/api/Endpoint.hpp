#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

namespace lst::api
{
    httplib::Client & GetEndpoint();
}
