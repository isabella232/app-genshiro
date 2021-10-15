//
// Created by overseven on 15.10.2021.
//


#include <stdint.h>
#include "dex.h"

static const char* ORDER_LIMIT = "Limit";
static const char* ORDER_MARKET = "Market";

static const char* SIDE_BUY  = "Buy";
static const char* SIDE_SELL = "Sell";

static const char* ERROR = "ERROR";

const char *get_order_type_name(uint8_t order_type) {
    switch (order_type) {
        case 0:
            return ORDER_LIMIT;
        case 1:
            return ORDER_MARKET;
        default:
            return ERROR;
    }
}

const char* get_order_side_name(uint8_t side) {
    switch (side) {
        case 0:
            return SIDE_BUY;
        case 1:
            return SIDE_SELL;
        default:
            return ERROR;
    }
}