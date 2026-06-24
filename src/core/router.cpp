#include "core/router.h"


#include <iostream>
#include <string>


void MatchingEngine::Router::run() {
    while(true) {
        std::string orderStr{};
        std::cout << "Place Order: ";
        std::getline(std::cin, orderStr);

        std::vector<std::string> orderToken = tokenization(orderStr);

        
        
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