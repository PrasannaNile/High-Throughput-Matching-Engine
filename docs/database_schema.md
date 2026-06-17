# 1. ORDERS Table:
## Existence of an Order:
* Every Order is recorded before that Order is accepted or rejected.
* orderId: unique identification (64 bit unsigned)
* traderId: Trader who place the request to buy or sell (64 bit unsigned)
* orderSide: trader wants to buy or sell (ENUM)
* orderState: whether the order is new, partially filled, matched, cancelled, rejected (ENUM)
* orderQuantity: no. of shares trader wants to buy or sell (32 bit unsigned)
* orderPrice: limiting amount at which trader wants to buy or sell (64 bit unsigned)
* orderTimestamp: exact time at which order was made (TIMESTAMP(6))

# 2. Trades Table:
## Trade record after order is matched:
* One buyer and One seller involved in each Trade
* tradeId: unique identification (64 bit unsigned)
* buyOrderId: Id of trader buying the stock (64 bit unsigned)
* sellOrderId: Id of trader selling the stock (64 bit unsigned)
* matchPrice: The exact price at which the match occurred.
* matchQuantity: The exact no. of shares traded
* tradeTimestamp: exact time at which order was accepted


