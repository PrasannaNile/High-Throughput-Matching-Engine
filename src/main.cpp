#include "core/limitOrderBook.h"
#include "core/order.h"

#include <iostream>

int main() {

    MatchingEngine::LimitOrderBook book;

    // sellers orders
    MatchingEngine::Order seller1{1001, 2001, MatchingEngine::OrderSideEnum::SELL, MatchingEngine::OrderStateEnum::NEW, 5, 101, 10000000000};
    MatchingEngine::Order seller2{1002, 2002, MatchingEngine::OrderSideEnum::SELL, MatchingEngine::OrderStateEnum::NEW, 10, 102, 10000000000};
    MatchingEngine::Order buyer1{1003, 2003, MatchingEngine::OrderSideEnum::BUY, MatchingEngine::OrderStateEnum::NEW, 20, 105, 10000000000};
    MatchingEngine::Order buyer2{1004, 2003, MatchingEngine::OrderSideEnum::BUY, MatchingEngine::OrderStateEnum::NEW, 20, 105, 10000000000};


    book.processOrder(seller1);
    book.processOrder(seller2);
    book.processOrder(buyer1);
    book.processOrder(buyer2);

    book.displaySellers();
    book.displayBuyers();


    return 0;
}