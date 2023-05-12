#pragma once

#include "StarMap.hpp"
#include "Fleet.hpp"
#include "Contracts.hpp"
#include "Factions.hpp"

#include <string>

namespace lst
{
    class Application
    {
    public:
        void        DrawWindow();

        std::string m_token;

        StarMap     m_starmap;
        Fleet       m_fleet;
        Contracts   m_contracts;
        Factions    m_factions;
    };
}