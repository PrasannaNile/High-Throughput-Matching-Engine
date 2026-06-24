#pragma once

#include "core/limitOrderBook.h"

#include <vector>
#include <sstream>
#include <string>
#include <cstdint>


namespace MatchingEngine {
    class Router {
    private:
        MatchingEngine::LimitOrderBook book;
        uint64_t orderIdCtr{1001};
    public:
        void run(); // REPL entry point (continuous looking for order)
        // break done order request into meaningful tokens
        std::vector<std::string> tokenization(std::string& orderStr); 
        // handle input exception
        bool handleInputException(std::vector<std::string>& orderToken, OrderSideEnum& orderSide, uint32_t& orderQuantity, uint64_t& orderPrice);

    };
}