#pragma once

#include "Result.hpp"

#include <nlohmann/json.hpp>
#include <string>

namespace lst::api
{
    struct ContractPayment
    {
        size_t onAccepted = 0;
        size_t onFulfilled = 0;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ContractPayment, onAccepted, onFulfilled );
    };

    struct ContractDeliverGood
    {
        std::string tradeSymbol;
        std::string destinationSymbol;

        size_t      unitsRequired = {};
        size_t      unitsFulfilled = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ContractDeliverGood, tradeSymbol, destinationSymbol, unitsRequired, unitsFulfilled );
    };

    struct ContractTerms
    {
        std::string                         deadline;
        ContractPayment                     payment;

        std::vector< ContractDeliverGood >  deliver;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ContractTerms, deadline, payment, deliver );
    };

    struct Contract
    {
        std::string     id;
        std::string     factionSymbol;
        std::string     type;

        ContractTerms   terms;
        bool            accepted = false;
        bool            fulfilled = false;

        std::string     expiration;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Contract, id, factionSymbol, type, terms, accepted, fulfilled, expiration );
    };

    PagedResult< Contract > GetMyContracts( size_t page = 1, size_t limit = 20 );
}
