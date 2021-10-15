//
// Created by igor on 15.10.2021.
//

#ifndef LEDGER_GENSHIRO_DEX_H
#define LEDGER_GENSHIRO_DEX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DexOrder_LIMIT = 0,
    DexOrder_MARKET = 0,
    DexOrder_MAX
} DexOrderType;

typedef enum {
    DexSide_SELL = 0,
    DexSide_BUY = 1,
    DexSide_MAX
} DexSideType;

const char *get_order_type_name(uint8_t order_type);

const char* get_order_side_name(uint8_t side);

#ifdef __cplusplus
}
#endif


#endif //LEDGER_GENSHIRO_DEX_H
