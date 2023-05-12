#pragma once

#include "Result.hpp"

#include <vector>
#include <string>

namespace lst::api
{
    struct TradeGood
    {
        std::string                         symbol;
        std::string                         name;
        std::string                         description;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( TradeGood, symbol, name, description );
    };

    struct MarketTransaction
    {
        std::string                         waypointSymbol;
        std::string                         shipSymbol;
        std::string                         tradeSymbol;
        std::string                         type;
        int                                 units = {};
        int                                 pricePerUnit = {};
        int                                 totalPrice = {};
        std::string                         timestamp;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( MarketTransaction, waypointSymbol, shipSymbol, tradeSymbol, type, units, pricePerUnit, totalPrice, timestamp );
    };

    struct MarketTradeGood
    {
        std::string                         symbol;
        int                                 tradeVolume = {};
        std::string                         supply;
        int                                 purchasePrice = {};
        int                                 sellPrice = {};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( MarketTradeGood, symbol, tradeVolume, supply, purchasePrice, sellPrice );
    };

    struct Market
    {
        std::string                         symbol;

        std::vector< TradeGood >            exports;
        std::vector< TradeGood >            imports;
        std::vector< TradeGood >            exchange;

        std::vector< MarketTransaction >    transactions;
        std::vector< MarketTradeGood >      tradeGoods;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE( Market, symbol, exports, imports, exchange, transactions, tradeGoods );
    };

    Result< Market >        GetWaypointMarket( const std::string & system, const std::string & waypoint );
}
