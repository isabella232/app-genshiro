/*******************************************************************************
*  (c) 2019 Zondax GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include "substrate_dispatch_V1.h"
#include "substrate_strings.h"
#include "zxmacros.h"
#include <stdint.h>

#define GET_CALL_PRIV_IDX(pallet_id, method_id) ((uint16_t)pallet_id << 8u) + method_id

#define PALLET_ID_UTILITY        1
#define PALLET_ID_EQBALANCES    13
#define PALLET_ID_VESTING       22
#define PALLET_ID_SUBACCOUNTS   24
#define PALLET_ID_EQBRIDGE      27
#define PALLET_ID_CURVE_AMM     32
#define PALLET_ID_GENSOPOUT     31
#define PALLET_ID_EQDEX         35

/// Pallet Utility
#define METHOD_ID_BATCH 0
#define PRIV_ID_BATCH GET_CALL_PRIV_IDX(PALLET_ID_UTILITY, METHOD_ID_BATCH)

/// Pallet EqBalances
#define METHOD_ID_TRANSFER 0
#define PRIV_ID_TRANSFER GET_CALL_PRIV_IDX(PALLET_ID_EQBALANCES, METHOD_ID_TRANSFER)

/// Pallet Vesting
#define METHOD_ID_VEST 0
#define PRIV_ID_VEST GET_CALL_PRIV_IDX(PALLET_ID_VESTING, METHOD_ID_VEST)

/// Pallet Subaccounts
#define METHOD_ID_TRANSFER_TO_SUBACC    0
#define METHOD_ID_TRANSFER_FROM_SUBACC  1
#define PRIV_ID_TRANSFER_TO_SUBACC   GET_CALL_PRIV_IDX(PALLET_ID_SUBACCOUNTS, METHOD_ID_TRANSFER_TO_SUBACC)
#define PRIV_ID_TRANSFER_FROM_SUBACC GET_CALL_PRIV_IDX(PALLET_ID_SUBACCOUNTS, METHOD_ID_TRANSFER_FROM_SUBACC)

/// Pallet EqBridge
#define METHOD_ID_TRANSFER_NATIVE 0
#define PRIV_ID_BRIDGE_TRANSFER_NATIVE GET_CALL_PRIV_IDX(PALLET_ID_EQBRIDGE, METHOD_ID_TRANSFER_NATIVE)

/// Pallet CurveAmm
#define METHOD_ID_ADD_LIQUIDITY                 1
#define METHOD_ID_EXCHANGE                      2
#define METHOD_ID_REMOVE_LIQUIDITY              3
#define METHOD_ID_REMOVE_LIQUIDITY_IMBALANCE    4
#define METHOD_ID_REMOVE_LIQUIDITY_ONE_COIN     5

#define PRIV_ID_CURVE_ADD_LIQUIDITY                 GET_CALL_PRIV_IDX(PALLET_ID_CURVE_AMM, METHOD_ID_ADD_LIQUIDITY)
#define PRIV_ID_CURVE_EXCHANGE                      GET_CALL_PRIV_IDX(PALLET_ID_CURVE_AMM, METHOD_ID_EXCHANGE)
#define PRIV_ID_CURVE_REMOVE_LIQUIDITY              GET_CALL_PRIV_IDX(PALLET_ID_CURVE_AMM, METHOD_ID_REMOVE_LIQUIDITY)
#define PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE    GET_CALL_PRIV_IDX(PALLET_ID_CURVE_AMM, METHOD_ID_REMOVE_LIQUIDITY_IMBALANCE)
#define PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN     GET_CALL_PRIV_IDX(PALLET_ID_CURVE_AMM, METHOD_ID_REMOVE_LIQUIDITY_ONE_COIN)

/// Pallet GensOptOut
#define METHOD_ID_GENSOPTOUT_SELL                   0
#define METHOD_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL    1
#define METHOD_ID_GENSOPTOUT_BUY                    3

#define PRIV_ID_GENSOPTOUT_SELL                     GET_CALL_PRIV_IDX(PALLET_ID_GENSOPOUT, METHOD_ID_GENSOPTOUT_SELL)
#define PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL      GET_CALL_PRIV_IDX(PALLET_ID_GENSOPOUT, METHOD_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL)
#define PRIV_ID_GENSOPTOUT_BUY                      GET_CALL_PRIV_IDX(PALLET_ID_GENSOPOUT, METHOD_ID_GENSOPTOUT_BUY)

/// Pallet EqDex
#define METHOD_ID_EQDEX_CREATE_ORDER                0
#define METHOD_ID_EQDEX_DELETE_ORDER_EXTERNAL       2

#define PRIV_ID_EQDEX_CREATE_ORDER                  GET_CALL_PRIV_IDX(PALLET_ID_EQDEX, METHOD_ID_EQDEX_CREATE_ORDER)
#define PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL         GET_CALL_PRIV_IDX(PALLET_ID_EQDEX, METHOD_ID_EQDEX_DELETE_ORDER_EXTERNAL)




/// Pallet Utility
__Z_INLINE parser_error_t _readMethod_utility_batch_V1(
    parser_context_t* c, pd_utility_batch_V1_t* m)
{
    CHECK_ERROR(_readVecCall(c, &m->calls))
    return parser_ok;
}

/// Pallet EqBalances
__Z_INLINE parser_error_t _readMethod_eqbalances_transfer_V1(
    parser_context_t* c, pd_eqbalances_transfer_V1_t* m)
{
    CHECK_ERROR(_readAsset(c, &m->asset))
    CHECK_ERROR(_readAccountId_V1(c, &m->to))
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

/// Pallet Vesting
__Z_INLINE parser_error_t _readMethod_vesting_vest_V1(
    parser_context_t* c, pd_vesting_vest_V1_t* m)
{
    return parser_ok;
}

/// Pallet Subaccounts
__Z_INLINE parser_error_t _readMethod_subaccounts_transfer_to_subaccount_V1(
    parser_context_t* c, pd_subaccounts_transfer_to_subaccount_V1_t* m)
{
    CHECK_ERROR(_readSubAccount_V1(c, &m->subAccType))
    CHECK_ERROR(_readAsset(c, &m->asset))
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_subaccounts_transfer_from_subaccount_V1(
        parser_context_t* c, pd_subaccounts_transfer_from_subaccount_V1_t* m)
{
    CHECK_ERROR(_readSubAccount_V1(c, &m->subAccType))
    CHECK_ERROR(_readAsset(c, &m->asset))
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

/// Pallet EqBridge
__Z_INLINE parser_error_t  _readMethod_eqbridge_transfer_native_V1(
        parser_context_t* c, pd_eqbridge_transfer_native_V1_t* m)
{
    CHECK_ERROR(_readBalance(c, &m->amount))
    CHECK_ERROR(_readBytes(c, &m->recipient))
    CHECK_ERROR(_readChainId_V1(c, &m->chainId))
    CHECK_ERROR(_readu8_array_32_V1(c, &m->resourceId))
    return parser_ok;
}

/// Pallet CurveAmm
__Z_INLINE parser_error_t  _readMethod_curveAmm_add_liquidity_V1(
    parser_context_t* c, pd_curveAmm_add_liquidity_V1_t* m)
{
    CHECK_ERROR(_readu32(c, &m->poolId))
    CHECK_ERROR(_readVecBalance(c, &m->amounts))
    CHECK_ERROR(_readBalance(c, &m->min_mint_amount))
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_curveAmm_exchange_V1(
    parser_context_t* c, pd_curveAmm_exchange_V1_t* m)
{
    CHECK_ERROR(_readu32(c, &m->poolId))
    CHECK_ERROR(_readu32(c, &m->poolTokenId_i))
    CHECK_ERROR(_readu32(c, &m->poolTokenId_j))
    CHECK_ERROR(_readBalance(c, &m->dx))
    CHECK_ERROR(_readBalance(c, &m->min_dy))
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_curveAmm_remove_liquidity_V1(
    parser_context_t* c, pd_curveAmm_remove_liquidity_V1_t* m)
{
    CHECK_ERROR(_readu32(c, &m->poolId))
    CHECK_ERROR(_readBalance(c, &m->amount))
    CHECK_ERROR(_readVecBalance(c, &m->min_amounts))
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_curveAmm_remove_liquidity_imbalance_V1(
    parser_context_t* c, pd_curveAmm_remove_liquidity_imbalance_V1_t* m)
{
    CHECK_ERROR(_readu32(c, &m->poolId))
    CHECK_ERROR(_readVecBalance(c, &m->amounts))
    CHECK_ERROR(_readBalance(c, &m->max_burn_amount))
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_curveAmm_remove_liquidity_one_coin_V1(
    parser_context_t* c, pd_curveAmm_remove_liquidity_one_coin_V1_t* m)
{
    CHECK_ERROR(_readu32(c, &m->poolId))
    CHECK_ERROR(_readBalance(c, &m->token_amount))
    CHECK_ERROR(_readu32(c, &m->poolTokenId))
    CHECK_ERROR(_readBalance(c, &m->min_amount))
    return parser_ok;
}

/// Pallet GensOptOut
__Z_INLINE parser_error_t  _readMethod_gensOptOut_sell_V1(
    parser_context_t* c, pd_gensOptOut_sell_V1_t* m)
{
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_gensOptOut_distribute_external_V1(
    parser_context_t* c, pd_gensOptOut_distribute_external_V1_t* m)
{
    CHECK_ERROR(_readAccountId_V1(c, &m->to))
    CHECK_ERROR(_readBlockNumber(c, &m->block_number))
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_gensOptOut_buy_V1(
    parser_context_t* c, pd_gensOptOut_buy_V1_t* m)
{
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

/// Pallet EqDex
__Z_INLINE parser_error_t  _readMethod_eqDex_create_order_V1(
    parser_context_t* c, pd_eqDex_create_order_V1_t* m)
{
    // TODO
    return parser_ok;
}

__Z_INLINE parser_error_t  _readMethod_eqDex_delete_order_external_V1(
    parser_context_t* c, pd_eqDex_delete_order_external_V1_t* m)
{
    // TODO
    return parser_ok;
}




parser_error_t _readMethod_V1(
    parser_context_t* c,
    uint8_t moduleIdx,
    uint8_t callIdx,
    pd_Method_V1_t* method)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
            /// Pallet Utility
        case PRIV_ID_BATCH:
            CHECK_ERROR(_readMethod_utility_batch_V1(c, &method->basic.utility_batch_V1))
            break;

            /// Pallet EqBalances
        case PRIV_ID_TRANSFER:
            CHECK_ERROR(_readMethod_eqbalances_transfer_V1(c, &method->nested.eqbalances_transfer_V1))
            break;

            /// Pallet Vesting
        case PRIV_ID_VEST:
            CHECK_ERROR(_readMethod_vesting_vest_V1(c, &method->basic.vesting_vest_V1))
            break;

            /// Pallet Subaccounts
        case PRIV_ID_TRANSFER_TO_SUBACC:
            CHECK_ERROR(_readMethod_subaccounts_transfer_to_subaccount_V1(c, &method->nested.subaccounts_transfer_to_subaccount_V1))
            break;
        case PRIV_ID_TRANSFER_FROM_SUBACC:
            CHECK_ERROR(_readMethod_subaccounts_transfer_from_subaccount_V1(c, &method->nested.subaccounts_transfer_from_subaccount_V1))
            break;

            /// Pallet EqBridge
        case PRIV_ID_BRIDGE_TRANSFER_NATIVE:
            CHECK_ERROR(_readMethod_eqbridge_transfer_native_V1(c, &method->basic.eqbridge_transfer_native_V1))
            break;

            /// Pallet CurveAmm
        case PRIV_ID_CURVE_ADD_LIQUIDITY:
            CHECK_ERROR(_readMethod_curveAmm_add_liquidity_V1(c, &method->basic.curveAmm_add_liquidity_V1))
            break;
        case PRIV_ID_CURVE_EXCHANGE:
            CHECK_ERROR(_readMethod_curveAmm_exchange_V1(c, &method->basic.curveAmm_exchange_V1))
            break;
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY:
            CHECK_ERROR(_readMethod_curveAmm_remove_liquidity_V1(c, &method->basic.curveAmm_remove_liquidity_V1))
            break;
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE:
            CHECK_ERROR(_readMethod_curveAmm_remove_liquidity_imbalance_V1(c, &method->basic.curveAmm_remove_liquidity_imbalance_V1))
            break;
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN:
            CHECK_ERROR(_readMethod_curveAmm_remove_liquidity_one_coin_V1(c, &method->basic.curveAmm_remove_liquidity_one_coin_V1))
            break;

            /// Pallet GensOptOut
        case PRIV_ID_GENSOPTOUT_SELL:
            CHECK_ERROR(_readMethod_gensOptOut_sell_V1(c, &method->basic.gensOptOut_sell_V1))
            break;
        case PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL:
            CHECK_ERROR(_readMethod_gensOptOut_distribute_external_V1(c, &method->basic.gensOptOut_distribute_external_V1))
            break;
        case PRIV_ID_GENSOPTOUT_BUY:
            CHECK_ERROR(_readMethod_gensOptOut_buy_V1(c, &method->basic.gensOptOut_buy_V1))
            break;

            /// Pallet EqDex
        case PRIV_ID_EQDEX_CREATE_ORDER:
            CHECK_ERROR(_readMethod_eqDex_create_order_V1(c, &method->basic.eqDex_create_order_V1))
            break;
        case PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL:
            CHECK_ERROR(_readMethod_eqDex_delete_order_external_V1(c, &method->basic.eqDex_delete_order_external_V1))
            break;

    default:
        return parser_not_supported;
    }

    return parser_ok;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

const char* _getMethod_ModuleName_V1(uint8_t moduleIdx)
{
    switch (moduleIdx) {
    case PALLET_ID_UTILITY:
        return STR_MO_UTILITY;
    case PALLET_ID_EQBALANCES:
        return STR_MO_EQBALANCES;
    case PALLET_ID_VESTING:
        return STR_MO_VESTING;
    case PALLET_ID_SUBACCOUNTS:
        return STR_MO_SUBACCOUNTS;
    case PALLET_ID_EQBRIDGE:
        return STR_MO_EQBRIDGE;
    case PALLET_ID_CURVE_AMM:
        return STR_MO_CURVE_AMM;
    case PALLET_ID_GENSOPOUT:
        return STR_MO_GENSOPTOUT;
    case PALLET_ID_EQDEX:
        return STR_MO_EQDEX;
    default:
        return NULL;
    }

    return NULL;
}

const char* _getMethod_Name_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
        /// Pallet Utility
    case PRIV_ID_BATCH:                           // Utility:batch
        return STR_ME_BATCH;
        /// Pallet EqBalances
    case PRIV_ID_TRANSFER:                        // EqBalances:transfer
        return STR_ME_TRANSFER;
        /// Pallet Vesting
    case PRIV_ID_VEST:                            // Vesting:vest
        return STR_ME_VEST;
        /// Pallet Subaccounts
    case PRIV_ID_TRANSFER_TO_SUBACC:              // Subaccounts:transfer_to_subaccount
        return STR_ME_TRANSFER_TO_SUBACCOUNT;
    case PRIV_ID_TRANSFER_FROM_SUBACC:            // Subaccounts:transfer_from_subaccount
        return STR_ME_TRANSFER_FROM_SUBACCOUNT;
        /// Pallet EqBridge
    case PRIV_ID_BRIDGE_TRANSFER_NATIVE:          // EqBridge:transfer_native
        return STR_ME_TRANSFER_NATIVE;
        /// Pallet CurveAmm
    case PRIV_ID_CURVE_ADD_LIQUIDITY:             // CurveAmm:add_liquidity
        return STR_ME_ADD_LIQUIDITY;
    case PRIV_ID_CURVE_EXCHANGE:                  // CurveAmm:exchange
        return STR_ME_EXCHANGE;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY:          // CurveAmm:remove_liquidity
        return STR_ME_REMOVE_LIQUIDITY;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE:// CurveAmm:remove_liquidity_imbalance
        return STR_ME_REMOVE_LIQUIDITY_IMBALANCE;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN: // CurveAmm:remove_liquidity_one_coin
        return STR_ME_REMOVE_LIQUIDITY_ONE_COIN;
        /// Pallet GensOptOut
    case PRIV_ID_GENSOPTOUT_SELL:                 // GensOptOut:sell
        return STR_ME_SELL;
    case PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL:  // GensOptOut:distribute_external
        return STR_ME_DISTRIBUTE_EXTERNAL;
    case PRIV_ID_GENSOPTOUT_BUY:                  // GensOptOut:buy
        return STR_ME_BUY;
        /// Pallet EqDex
    case PRIV_ID_EQDEX_CREATE_ORDER:
        return STR_ME_CREATE_ORDER;
    case PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL:
        return STR_ME_DELETE_ORDER_EXTERNAL;
    default:
        return NULL;
    }

    return NULL;
}

uint8_t _getMethod_NumItems_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case PRIV_ID_BATCH:                             // Utility:batch
        return 1;
    case PRIV_ID_TRANSFER:                          // EqBalances:transfer
        return 3;
    case PRIV_ID_VEST:                              // Vesting:vest
        return 0;
    case PRIV_ID_TRANSFER_TO_SUBACC:                // Subaccounts:transfer_to_subaccount
        return 3;
    case PRIV_ID_TRANSFER_FROM_SUBACC:              // Subaccounts:transfer_from_subaccount
        return 3;
    case PRIV_ID_BRIDGE_TRANSFER_NATIVE:            // EqBridge:transfer_native
        return 4;
    case PRIV_ID_CURVE_ADD_LIQUIDITY:               // CurveAmm:exchange
        return 3;
    case PRIV_ID_CURVE_EXCHANGE:                    // CurveAmm:exchange
        return 5;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY:            // CurveAmm:remove_liquidity
        return 3;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE:  // CurveAmm:remove_liquidity_imbalance
        return 3;
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN:   // CurveAmm:remove_liquidity_one_coin
        return 4;
    case PRIV_ID_GENSOPTOUT_SELL:                   // GensOptOut:sell
        return 0;
    case PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL:    // GensOptOut:distribute_external
        return 2;
    case PRIV_ID_GENSOPTOUT_BUY:                    // GensOptOut:buy
        return 1;
    case PRIV_ID_EQDEX_CREATE_ORDER:                // EqDex:create_order
        return 5;
    case PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL:       // EqDex:delete_order_external
        return 3;
    default:
        return 0;
    }

    return 0;
}

const char* _getMethod_ItemName_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case PRIV_ID_BATCH:
        switch (itemIdx) {
        case 0:
            return STR_IT_calls;
        default:
            return NULL;
        }
    case PRIV_ID_TRANSFER: // EqBalances:transfer(asset, to, amount)
        switch (itemIdx) {
        case 0:
            return STR_IT_asset;
        case 1:
            return STR_IT_to;
        case 2:
            return STR_IT_value;
        default:
            return NULL;
        }
    case PRIV_ID_TRANSFER_TO_SUBACC:  // Subaccounts:transfer_to_subaccount  (SubAccType, Asset, amount)
    case PRIV_ID_TRANSFER_FROM_SUBACC: // Subaccounts:transfer_from_subaccount(SubAccType, Asset, amount)
        switch (itemIdx) {
            case 0:
                return STR_IT_subaccount;
            case 1:
                return STR_IT_asset;
            case 2:
                return STR_IT_value;
            default:
                return NULL;
        }
    case PRIV_ID_BRIDGE_TRANSFER_NATIVE: // EqBridge:transfer_native(amount, recipient, chainId, resourceId)
        switch (itemIdx) {
        case 0:
            return STR_IT_amount;
        case 1:
            return STR_IT_recipient;
        case 2:
            return STR_IT_chain_id;
        case 3:
            return STR_IT_asset;
        default:
            return NULL;
        }
    case PRIV_ID_CURVE_ADD_LIQUIDITY:              // CurveAmm:add_liquidity
        switch (itemIdx) {
        case 0:
            return STR_IT_poolId;
        case 1:
            return STR_IT_amounts;
        case 2:
            return STR_IT_min_mint_amount;
        default:
            return NULL;
        }
    case PRIV_ID_CURVE_EXCHANGE:                   // CurveAmm:exchange
        switch (itemIdx) {
        case 0:
            return STR_IT_poolId;
        case 1:
            return STR_IT_poolTokenId_send;
        case 2:
            return STR_IT_poolTokenId_receive;
        case 3:
            return STR_IT_dx;
        case 4:
            return STR_IT_min_dy;
        default:
            return NULL;
        }
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY:           // CurveAmm:remove_liquidity
        switch (itemIdx) {
        case 0:
            return STR_IT_poolId;
        case 1:
            return STR_IT_value;
        case 2:
            return STR_IT_min_amounts;
        default:
            return NULL;
        }
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE: // CurveAmm:remove_liquidity_imbalance
        switch (itemIdx) {
        case 0:
            return STR_IT_poolId;
        case 1:
            return STR_IT_amounts;
        case 2:
            return STR_IT_max_burn_amount;
        default:
            return NULL;
        }
    case PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN:  // CurveAmm:remove_liquidity_one_coin
        switch (itemIdx) {
        case 0:
            return STR_IT_poolId;
        case 1:
            return STR_IT_value;
        case 2:
            return STR_IT_poolTokenId;
        case 3:
            return STR_IT_min_amount;
        default:
            return NULL;
        }
    case PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL:   // GensOptOut:distribute_external
        switch (itemIdx) {
        case 0:
            return STR_IT_account;
        case 1:
            return STR_IT_block;
        default:
            return NULL;
        }
    case PRIV_ID_GENSOPTOUT_BUY:                   // GensOptOut:buy
        switch (itemIdx) {
        case 0:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case PRIV_ID_EQDEX_CREATE_ORDER:               // EqDex:create_order
        switch (itemIdx) {
        case 0:
            return STR_IT_asset;
        case 1:
            return STR_IT_order_type;
        case 2:
            return STR_IT_side;
        case 3:
            return STR_IT_amount;
        case 4:
            return STR_IT_expiration_time;
        default:
            return NULL;
        }
    case PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL:      // EqDex:delete_order_external
        switch (itemIdx) {
        case 0:
            return STR_IT_asset;
        case 1:
            return STR_IT_order_id;
        case 2:
            return STR_IT_price;
        default:
            return NULL;
        }
    default:
        return NULL;
    }


    return NULL;
}

parser_error_t _getMethod_ItemValue_V1(
    pd_Method_V1_t* m,
    uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx,
    char* outValue, uint16_t outValueLen,
    uint8_t pageIdx, uint8_t* pageCount)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
        case PRIV_ID_BATCH:  // Utility:batch
        switch (itemIdx) {
            case 0:
                return _toStringVecCall(
                        &m->basic.utility_batch_V1.calls,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            default:
                return parser_no_data;
        }
        case PRIV_ID_TRANSFER: // EqBalances:transfer(asset, to, amount)
        switch (itemIdx) {
            case 0:
                return _toStringAsset_V1(
                        &m->nested.eqbalances_transfer_V1.asset,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            case 1:
                return _toStringAccountId_V1(
                        &m->nested.eqbalances_transfer_V1.to,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            case 2:
                return _toStringBalanceAsset_V1(
                        &m->nested.eqbalances_transfer_V1.amount,
                        &m->nested.eqbalances_transfer_V1.asset,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            default:
                return parser_no_data;
        }
        case PRIV_ID_TRANSFER_TO_SUBACC: // Subaccounts:transfer_to_subaccount  (SubAccType, Asset, amount)
        case PRIV_ID_TRANSFER_FROM_SUBACC: // Subaccounts:transfer_from_subaccount(SubAccType, Asset, amount)
            switch (itemIdx) {
                case 0:
                    return _toStringSubaccount_V1(
                            &m->nested.subaccounts_transfer_to_subaccount_V1.subAccType,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringAsset_V1(
                            &m->nested.subaccounts_transfer_to_subaccount_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringBalanceAsset_V1(
                            &m->nested.subaccounts_transfer_to_subaccount_V1.amount,
                            &m->nested.subaccounts_transfer_to_subaccount_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_BRIDGE_TRANSFER_NATIVE: // EqBridge:transfer_native(amount, recipient, chainId, resourceId)
            switch (itemIdx) {
                case 0:
                    return _toStringAmount(
                        &m->basic.eqbridge_transfer_native_V1.amount,
                        outValue, outValueLen,
                        pageIdx, pageCount);
                case 1:
                    return _toStringBytes(
                            &m->basic.eqbridge_transfer_native_V1.recipient,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringChainId_V1(
                                &m->basic.eqbridge_transfer_native_V1.chainId,
                                outValue, outValueLen,
                                pageIdx, pageCount);
                case 3:
                    return _toStringResourceId_V1(
                            &m->basic.eqbridge_transfer_native_V1.resourceId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_CURVE_ADD_LIQUIDITY: // CurveAmm:add_liquidity
            switch (itemIdx) {
                case 0:
                    return _toStringu32(
                            &m->basic.curveAmm_add_liquidity_V1.poolId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringVecBalance(
                            &m->basic.curveAmm_add_liquidity_V1.amounts,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringAmount(
                            &m->basic.curveAmm_add_liquidity_V1.min_mint_amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_CURVE_EXCHANGE: // CurveAmm:exchange
            switch (itemIdx) {
                case 0:
                    return _toStringu32(
                            &m->basic.curveAmm_exchange_V1.poolId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringu32(
                            &m->basic.curveAmm_exchange_V1.poolTokenId_i,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringu32(
                            &m->basic.curveAmm_exchange_V1.poolTokenId_j,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 3:
                    return _toStringAmount(
                            &m->basic.curveAmm_exchange_V1.dx,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 4:
                    return _toStringAmount(
                            &m->basic.curveAmm_exchange_V1.min_dy,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY:            // CurveAmm:remove_liquidity
            switch (itemIdx) {
                case 0:
                    return _toStringu32(
                            &m->basic.curveAmm_remove_liquidity_V1.poolId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringAmount(
                            &m->basic.curveAmm_remove_liquidity_V1.amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return  _toStringVecBalance(
                            &m->basic.curveAmm_remove_liquidity_V1.min_amounts,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY_IMBALANCE:  // CurveAmm:remove_liquidity_imbalance
            switch (itemIdx) {
                case 0:
                    return _toStringu32(
                            &m->basic.curveAmm_remove_liquidity_imbalance_V1.poolId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringVecBalance(
                            &m->basic.curveAmm_remove_liquidity_imbalance_V1.amounts,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return  _toStringAmount(
                            &m->basic.curveAmm_remove_liquidity_imbalance_V1.max_burn_amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_CURVE_REMOVE_LIQUIDITY_ONE_COIN: // CurveAmm:remove_liquidity_one_coin
            switch (itemIdx) {
                case 0:
                    return _toStringu32(
                            &m->basic.curveAmm_remove_liquidity_one_coin_V1.poolId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringAmount(
                            &m->basic.curveAmm_remove_liquidity_one_coin_V1.token_amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringu32(
                            &m->basic.curveAmm_remove_liquidity_one_coin_V1.poolTokenId,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 3:
                    return _toStringAmount(
                            &m->basic.curveAmm_remove_liquidity_one_coin_V1.min_amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);

                default:
                    return parser_no_data;
            }
        case PRIV_ID_GENSOPTOUT_DISTRIBUTE_EXTERNAL:
            switch (itemIdx) {
                case 0:
                    return _toStringAccountId_V1(
                            &m->basic.gensOptOut_distribute_external_V1.to,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringBlockNumber(
                            &m->basic.gensOptOut_distribute_external_V1.block_number,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_GENSOPTOUT_BUY:
            switch (itemIdx) {
                case 0:
                    return _toStringAmount(
                            &m->basic.gensOptOut_buy_V1.amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_EQDEX_CREATE_ORDER:               // EqDex:create_order
            switch (itemIdx) {
                case 0:
                    return _toStringAsset_V1(
                            &m->basic.eqDex_create_order_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringOrderType(
                            &m->basic.eqDex_create_order_V1.order_type,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringSide(
                            &m->basic.eqDex_create_order_V1.side,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 3:
                    return _toStringFixedU128(
                            &m->basic.eqDex_create_order_V1.amount,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 4:
                    return _toStringu64(
                            &m->basic.eqDex_create_order_V1.expiration_time,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case PRIV_ID_EQDEX_DELETE_ORDER_EXTERNAL:      // EqDex:delete_order_external
            switch (itemIdx) {
                case 0:
                    return _toStringAsset_V1(
                            &m->basic.eqDex_delete_order_external_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringu64(
                            &m->basic.eqDex_delete_order_external_V1.order_id,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringFixedI64(
                            &m->basic.eqDex_delete_order_external_V1.price,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        default:
            return parser_ok;
    }

    return parser_ok;
}

bool _getMethod_ItemIsExpert_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    return false;
}

bool _getMethod_IsNestingSupported_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case PRIV_ID_TRANSFER_TO_SUBACC:        // Subaccounts:transfer_to_subaccount
    case PRIV_ID_TRANSFER_FROM_SUBACC:      // Subaccounts:transfer_from_subaccount
        return true;
    default:
        return false;
    }
}
