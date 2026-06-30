#include "core/limitOrderBook.h"
#include "core/order.h"
#include "core/router.h"
#include "core/orderGenerator.h"

#include <iostream>
#include <chrono>

void runPerformanceBenchmark() {
    MatchingEngine::LimitOrderBook orderBook{};
    MatchingEngine::OrderGenerator generator{};

    uint32_t orderCount {1000000};
    generator.generateOrder(orderCount);
    auto& orderPool = generator.getOrderPool();

    auto startTime = std::chrono::high_resolution_clock::now();

    for(auto& order: orderPool) orderBook.processOrder(order);

    auto endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // 1. Convert milliseconds to fractional seconds
    double seconds = duration / 1000.0;

    // 2. Calculate Million Orders Per Second (MOPS)
    double mops = (static_cast<double>(orderCount) / 1'000'000.0) / seconds;

    // 3. Print the scannable summary report
    std::cout << "\n====================================" << std::endl;
    std::cout << "     MATCHING ENGINE PERFORMANCE    " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Total Orders Processed : " << orderCount << std::endl;
    std::cout << "Total Execution Time   : " << duration << " ms (" << seconds << " seconds)" << std::endl;
    std::cout << "Engine Throughput      : " << mops << " MOPS" << std::endl;
    std::cout << "====================================" << std::endl;

}



int main() {

    MatchingEngine::Router app;
    app.run();
    // runPerformanceBenchmark();


    return 0;
} 