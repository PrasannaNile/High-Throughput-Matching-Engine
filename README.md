
# High Throughput Matching Engine
* This system mimics how a real-world financial exchange (like the National Stock Exchange or a crypto platform) handles trades.

* An ultra-low latency, in-memory financial matching engine built in C++17 utilizing high-performance data structures for deterministic O(1) order insertion, matching, and cancellation. 
* To maximize throughput, execution logic is entirely decoupled from disk I/O, utilizing an asynchronous thread pool to batch-persist trade events into a MySQL database without blocking the critical path. 
* The project demonstrates low-latency software engineering principles, cache-friendly memory management, and modern concurrent system design.

## Build & Installation Instructions
***************** Section under development during Phase 1. *******************