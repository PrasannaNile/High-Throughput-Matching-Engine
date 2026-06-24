#pragma once

#include "core/limitOrderBook.h"

#include <vector>
#include <sstream>


namespace MatchingEngine {
    class Router {
    private:
        MatchingEngine::LimitOrderBook book;
    public:
        void run(); // REPL entry point (continuous looking for order)
        // break done order request into meaningful tokens
        std::vector<std::string> tokenization(std::string& orderStr); 
        
    };
}