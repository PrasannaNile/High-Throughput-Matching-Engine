#include "core/router.h"


#include <iostream>
#include <string>
#include <charconv>




void MatchingEngine::Router::run() {
    while(true) {
        std::string orderStr{};
        std::cout << "Place Order: ";
        std::getline(std::cin, orderStr);

        std::vector<std::string> orderToken = tokenization(orderStr);

        if(orderToken.size() != 3) {
            std::cerr << "[Input Error] xxxxxxxxxxxxxx Invalid Order Request xxxxxxxxxxxxxxx\n";
            continue;
        }

        [[maybe_unused]] OrderSideEnum orderSide{OrderSideEnum::BUY};
        int orderQuantity{0};
        int orderPrice{0};

        if(!handleInputException(orderToken, orderSide, orderQuantity, orderPrice)) continue;

        // --- All Inputs Verified Successfully ---
        std::cout << "[Success] Parsed Valid Order: " 
                << (orderSide == MatchingEngine::OrderSideEnum::BUY ? "BUY " : "SELL ") 
                << orderQuantity << " @ " << orderPrice << "\n";
    }
}


std::vector<std::string> MatchingEngine::Router::tokenization(std::string& orderStr) {
    std::stringstream ss{orderStr};

    std::vector<std::string> orderToken;

    std::string temp;
    while(ss >> temp) {
        orderToken.push_back(temp);
    }

    return orderToken;
}


bool MatchingEngine::Router::handleInputException(std::vector<std::string>& orderToken, OrderSideEnum& orderSide, int& orderQuantity, int& orderPrice) {

    try {
        if(orderToken[0] == "SELL") orderSide = MatchingEngine::OrderSideEnum::SELL;
        else if(orderToken[0] == "BUY") orderSide = MatchingEngine::OrderSideEnum::BUY;
        else throw std::runtime_error("[Input Error] xxxxxxxxxxxxxx Invalid Order Side xxxxxxxxxxxxxxx\n");

    } catch(std::exception& err) {
        std::cerr << err.what();
        return false;
    }
    
    // 1. Safe Quantity Parsing
    auto quantResult = std::from_chars(orderToken[1].data(), orderToken[1].data() + orderToken[1].size(), orderQuantity);

    if (quantResult.ec != std::errc() || orderQuantity <= 0) {
        std::cerr << "[Input Error] xxxxxxxxxxxx Invalid Quantity (Must be a positive number) xxxxxxxxxxxx\n";
        return false;
    }

    // 3. Safe Price Parsing (Non-throwing)
    auto priceResult = std::from_chars(orderToken[2].data(), orderToken[2].data() + orderToken[2].size(), orderPrice);

    if (priceResult.ec != std::errc() || orderPrice <= 0) {
        std::cerr << "[Input Error] xxxxxxxxxxxx Invalid Price (Must be a positive number) xxxxxxxxxxxx\n";
        return false;
    }

    return true;
}