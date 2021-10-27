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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextern-c-compat"
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "substrate_types.h"
#include "substrate_types_V1.h"
#include <stddef.h>
#include <stdint.h>


/// Pallet Utility
#define PD_CALL_UTILITY_BATCH_V1 0
typedef struct {
    pd_VecCall_t calls;
} pd_utility_batch_V1_t;

/// Pallet EqBalances
#define PD_CALL_EQBALANCES_TRANSFER_V1 0
typedef struct {
    eq_Asset_t asset;
    pd_AccountId_V1_t to;
    pd_Balance_t amount;
} pd_eqbalances_transfer_V1_t;

/// Pallet Vesting
#define PD_CALL_VESTING_VEST_V1 0
typedef struct {
} pd_vesting_vest_V1_t;

/// Pallet EqSubaccounts
#define PD_CALL_SUBACCOUNTS_TRANSFER_TO_SUBACCOUNT_V1 0
typedef struct {
    eq_Subaccount_t subAccType;
    eq_Asset_t asset;
    pd_Balance_t amount;
} pd_subaccounts_transfer_to_subaccount_V1_t;

#define PD_CALL_SUBACCOUNTS_TRANSFER_FROM_SUBACCOUNT_V1 1
typedef struct {
    eq_Subaccount_t subAccType;
    eq_Asset_t asset;
    pd_Balance_t amount;
} pd_subaccounts_transfer_from_subaccount_V1_t;

/// Pallet EqBridge
#define PD_CALL_EQBRIDGE_TRANSFER_NATIVE_V1 1
typedef struct {
    pd_Balance_t amount;
    pd_Bytes_t recipient;
    eq_ChainId_t chainId;
    pd_u8_array_32_V1_t resourceId;
} pd_eqbridge_transfer_native_V1_t;

/// Pallet GensCrowdloan
#define PD_CALL_GENS_CROWDLOAN_CLAIM_V1 0
typedef struct {
} pd_gensCrowdloan_claim_V1_t;

/// Pallet CurveAmm
#define PD_CALL_CURVEAMM_ADD_LIQUIDITY_V1 1
typedef struct {
    pd_u32_t poolId;
    pd_VecBalance_t amounts;
    pd_Balance_t min_mint_amount;
} pd_curveAmm_add_liquidity_V1_t;

#define PD_CALL_CURVEAMM_EXCHANGE_V1 1
typedef struct {
    pd_u32_t poolId;
    pd_u32_t poolTokenId_i;
    pd_u32_t poolTokenId_j;
    pd_Balance_t dx;
    pd_Balance_t min_dy;
} pd_curveAmm_exchange_V1_t;

#define PD_CALL_CURVEAMM_REMOVE_LIQUIDITY_V1 1
typedef struct {
    pd_u32_t poolId;
    pd_Balance_t amount;
    pd_VecBalance_t min_amounts;
} pd_curveAmm_remove_liquidity_V1_t;

#define PD_CALL_CURVEAMM_REMOVE_LIQUIDITY_IMBALANCE_V1 1
typedef struct {
    pd_u32_t poolId;
    pd_VecBalance_t amounts;
    pd_Balance_t max_burn_amount;
} pd_curveAmm_remove_liquidity_imbalance_V1_t;

#define PD_CALL_CURVEAMM_REMOVE_LIQUIDITY_ONE_COIN_V1 1
typedef struct {
    pd_u32_t poolId;
    pd_Balance_t token_amount;
    pd_u32_t poolTokenId;
    pd_Balance_t min_amount;
} pd_curveAmm_remove_liquidity_one_coin_V1_t;

/// Pallet GensOptOut
#define PD_CALL_GENSOPTOUT_SELL_V1 1
typedef struct {
} pd_gensOptOut_sell_V1_t;

#define PD_CALL_GENSOPTOUT_DISTRIBUTE_EXTERNAL_V1 1
typedef struct {
    pd_AccountId_V1_t to;
    pd_BlockNumber_t block_number;
} pd_gensOptOut_distribute_external_V1_t;

#define PD_CALL_GENSOPTOUT_BUY_V1 1
typedef struct {
    pd_Balance_t amount;
} pd_gensOptOut_buy_V1_t;

/// Pallet EqDex
#define PD_CALL_EQDEX_CREATE_ORDER_V1 1
typedef struct {
    eq_Asset_t asset;
    pd_OrderType_t order_type;
    pd_u8_t side;
    pd_FixedU128_t amount;
    pd_u64_t expiration_time;
} pd_eqDex_create_order_V1_t;

#define PD_CALL_EQDEX_DELETE_ORDER_EXTERNAL_V1 1
typedef struct {
    eq_Asset_t asset;
    pd_u64_t order_id;
    pd_FixedI64_t price;
} pd_eqDex_delete_order_external_V1_t;


typedef union {
    pd_utility_batch_V1_t utility_batch_V1;
    pd_vesting_vest_V1_t vesting_vest_V1;
    pd_eqbridge_transfer_native_V1_t eqbridge_transfer_native_V1;
    pd_gensCrowdloan_claim_V1_t gensCrowdloan_claim_V1;
    pd_curveAmm_add_liquidity_V1_t curveAmm_add_liquidity_V1;
    pd_curveAmm_exchange_V1_t curveAmm_exchange_V1;
    pd_curveAmm_remove_liquidity_V1_t curveAmm_remove_liquidity_V1;
    pd_curveAmm_remove_liquidity_imbalance_V1_t curveAmm_remove_liquidity_imbalance_V1;
    pd_curveAmm_remove_liquidity_one_coin_V1_t curveAmm_remove_liquidity_one_coin_V1;
    pd_gensOptOut_sell_V1_t gensOptOut_sell_V1;
    pd_gensOptOut_distribute_external_V1_t gensOptOut_distribute_external_V1;
    pd_gensOptOut_buy_V1_t gensOptOut_buy_V1;
    pd_eqDex_create_order_V1_t eqDex_create_order_V1;
    pd_eqDex_delete_order_external_V1_t eqDex_delete_order_external_V1;
} pd_MethodBasic_V1_t;


typedef union {
    pd_eqbalances_transfer_V1_t eqbalances_transfer_V1;
    pd_subaccounts_transfer_to_subaccount_V1_t subaccounts_transfer_to_subaccount_V1;
    pd_subaccounts_transfer_from_subaccount_V1_t subaccounts_transfer_from_subaccount_V1;
} pd_MethodNested_V1_t;

typedef union {
    pd_MethodBasic_V1_t basic;
    pd_MethodNested_V1_t nested;
} pd_Method_V1_t;

#ifdef __cplusplus
}
#endif

#pragma clang diagnostic pop
