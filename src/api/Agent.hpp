#pragma once

#include "Result.hpp"

#include <nlohmann/json.hpp>
#include <string>

namespace lst::api
{
    struct Agent
    {
        std::string symbol;
        std::string headquarters;
        uint32_t    credits = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Agent, symbol, headquarters, credits );
    };

    struct Registrar
    {
        Agent       agent;
        std::string token;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Registrar, agent, token );
    };

    Result< Registrar > RegisterAgent( std::string symbol, std::string faction );
    Result< Agent >     GetAgentInfo( const std::string & token );
}
