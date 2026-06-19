# Developer Log: Day 0.

## 1. Toolchain & Environment Fixes
* **Issue:** CMake defaulted to Visual Studio `NMake` toolchain, failing to find the MSYS64 environment.
* **Resolution:** Wiped `/build` sandbox and forced GCC/G++ explicitly via PowerShell:
  ```powershell
  Remove-Item -Recurse -Force *
  cmake -G "MinGW Makefiles" ..
  cmake --build .
  
## 2. Domain Models
* **`Order.hpp` Layout:** Implemented as a POD `struct` in `namespace MatchingEngine` to eliminate getter/setter overhead. Grouped 8-byte primitives first (`orderId`, `traderId`, `orderPrice`, `orderTimestamp`) before 4-byte types (`orderQuantity`, `orderSide`, `orderState`) to optimize hardware cache alignment and eliminate compiler padding bytes.
* **`Trade.hpp` Layout:** Designed as a 44-byte execution data carrier. Optimized memory alignment by ordering 8-byte primitives (`tradeId`, `buyOrderId`, `sellOrderId`, `matchPrice`, `tradeTimestamp`) above the 4-byte `matchQuantity`.
* **Timestamping Engine:** Integrated `<chrono>` to map both order and trade execution times as standard `uint64_t` nanoseconds from the Unix epoch.

---

## 3. Environment & Workspace Configurations
* **`CMakeLists.txt` Syntactical Cleanup:** Removed a stray trailing brace (`}`) from `CMAKE_RUNTIME_OUTPUT_DIRECTORY` that was breaking path routing, successfully guiding the final compilation `.exe` straight into the project root `/bin` folder. Corrected `-WALL` flag to lowercase `-Wall`.
* **Version Control Setup:** Implemented `.gitignore` rules to isolate the `/build` tree and operational system binaries from tracked source blocks.

---

## 4. Source Control Status
* **Active Branch:** `feature/domain-models`
* **Commit:** `feat: implement cache-aligned Order and Trade data structures for core domain`
* **Next Target (Day 2):** Blueprinting the $O(1)$ in-memory dynamic `LimitOrderBook.hpp` interface.


# Price Hook AND LimitOrderBook: Day 1

## Limit Order Book Architecture & Component Design
* **PriceLevel Model Blueprint:** Designed `PriceLevel` as a single tick price point container holding aggregate volume trackers (`totalVolume`, `orderCount`) and a sequential `std::list<Order>` to maintain strict FIFO price-time priority.

* **Bookcase Topology:** Structured the main `LimitOrderBook` using standard sorted maps (`std::map`). Configured the Buy Book (`bids`) via `std::greater` for descending price discovery, and the Sell Book (`asks`) via `std::less` for ascending price discovery.

* **O(1) Cancellation Routing:** Implemented an `orderRegistry` using an `std::unordered_map` that pairs a unique `orderId` directly to a `std::list<Order>::iterator`. This bypasses linear search requirements, enabling instant, direct node un-linking during order cancellation or deletion requests.
* **Next Target (Day 3):** Commencing implementation of the public interface methods for order insertion and cancellation algorithms.
