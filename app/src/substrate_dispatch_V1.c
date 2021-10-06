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

/// Pallet EqBalances
__Z_INLINE parser_error_t _readMethod_eqbalances_transfer_V1(
    parser_context_t* c, pd_eqbalances_transfer_V1_t* m)
{
    CHECK_ERROR(_readAsset(c, &m->asset));
    CHECK_ERROR(_readAccountId_V1(c, &m->to));
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
    CHECK_ERROR(_readSubAccount_V1(c, &m->subAccType));
    CHECK_ERROR(_readAsset(c, &m->asset));
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_subaccounts_transfer_from_subaccount_V1(
        parser_context_t* c, pd_subaccounts_transfer_from_subaccount_V1_t* m)
{
    CHECK_ERROR(_readSubAccount_V1(c, &m->subAccType));
    CHECK_ERROR(_readAsset(c, &m->asset));
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

/// Pallet EqBridge
__Z_INLINE parser_error_t  _readMethod_eqbridge_transfer_native_V1(
        parser_context_t* c, pd_eqbridge_transfer_native_V1_t* m)
{
    CHECK_ERROR(_readBalance(c, &m->amount))
    CHECK_ERROR(_readBytes(c, &m->recipient))
    CHECK_ERROR(_readChainId_V1(c, &m->chainId));
    CHECK_ERROR(_readu8_array_32_V1(c, &m->resourceId))
    return parser_ok;
}

/// Pallet EqLockdrop
__Z_INLINE parser_error_t _readMethod_eqlockdrop_lock_V1(
    parser_context_t* c, pd_eqlockdrop_lock_V1_t* m)
{
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_eqlockdrop_unlock_external_V1(
    parser_context_t* c, pd_eqlockdrop_unlock_external_V1_t* m)
{
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
            /// Pallet EqBalances
        case 3328: /* module 13 call 0 */
        CHECK_ERROR(_readMethod_eqbalances_transfer_V1(c, &method->basic.eqbalances_transfer_V1))
            break;

            /// Pallet Vesting
        case 5632: /* module 22 call 0 */
        CHECK_ERROR(_readMethod_vesting_vest_V1(c, &method->basic.vesting_vest_V1))
            break;

            /// Pallet Subaccounts
        case 6144: /* module 24 call 0 */
        CHECK_ERROR(_readMethod_subaccounts_transfer_to_subaccount_V1(c, &method->basic.subaccounts_transfer_to_subaccount_V1))
            break;
        case 6145: /* module 24 call 1 */
        CHECK_ERROR(_readMethod_subaccounts_transfer_from_subaccount_V1(c, &method->basic.subaccounts_transfer_from_subaccount_V1))
            break;

            /// Pallet EqBridge
        case 6912: /* module 27 call 0 */
        CHECK_ERROR(_readMethod_eqbridge_transfer_native_V1(c, &method->basic.eqbridge_transfer_native_V1))
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
    case 13:
        return STR_MO_EQBALANCES;
    case 22:
        return STR_MO_VESTING;
    case 24:
        return STR_MO_SUBACCOUNTS;
    case 27:
        return STR_MO_EQBRIDGE;

    default:
        return NULL;
    }

    return NULL;
}

const char* _getMethod_Name_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 3328: /* module 13 call 0 */    // EqBalances:transfer
        return STR_ME_TRANSFER;
    case 5632: /* module 22 call 0 */   // Vesting:vest
        return STR_ME_VEST;

    case 6144: /* module 24 call 0 */
        return STR_ME_TRANSFER_TO_SUBACCOUNT;     // Subaccounts:transfer_to_subaccount
    case 6145: /* module 24 call 1 */
        return STR_ME_TRANSFER_FROM_SUBACCOUNT;   // Subaccounts:transfer_from_subaccount

    case 6912: /* module 27 call 0 */
        return STR_ME_TRANSFER_NATIVE; // EqBridge:transfer_native

    default:
        return NULL;
    }

    return NULL;
}

uint8_t _getMethod_NumItems_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 3328: /* module 13 call 0 */ // EqBalances:transfer
        return 3;
    case 5632: /* module 22  call 0 */ // Vesting:vest
        return 0;
    case 6144: /* module 24 call 0 */ // Subaccounts:transfer_to_subaccount
        return 3;
    case 6145: /* module 24 call 1 */ // Subaccounts:transfer_from_subaccount
        return 3;
    case 6912: /* module 27 call 0 */ // EqBridge:transfer_native
        return 4;
    default:
        return 0;
    }

    return 0;
}

const char* _getMethod_ItemName_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {

    case 3328: /* module 9 -> 10 call 0 */ // EqBalances:transfer(asset, to, amount)
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
    case 6144: /* module 24 call 0 */ // Subaccounts:transfer_to_subaccount  (SubAccType, Asset, amount)
    case 6145: /* module 24 call 1 */ // Subaccounts:transfer_from_subaccount(SubAccType, Asset, amount)
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
    case 6912: /* module 27 call 0 */ // EqBridge:transfer_native(amount, recipient, chainId, resourceId)
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
        case 3328: /* module 9 -> 10 call 0 */ // EqBalances:transfer(asset, to, amount)
        switch (itemIdx) {
            case 0: /* utility_batch_V1 - calls */;
                return _toStringAsset_V1(
                        &m->basic.eqbalances_transfer_V1.asset,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            case 1:
                return _toStringAccountId_V1(
                        &m->basic.eqbalances_transfer_V1.to,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            case 2:
                return _toStringBalanceAsset_V1(
                        &m->basic.eqbalances_transfer_V1.amount,
                        &m->basic.eqbalances_transfer_V1.asset,
                        outValue, outValueLen,
                        pageIdx, pageCount);
            default:
                return parser_no_data;
        }
        case 6144: /* module 24 call 0 */ // Subaccounts:transfer_to_subaccount  (SubAccType, Asset, amount)
        case 6145: /* module 24 call 1 */ // Subaccounts:transfer_from_subaccount(SubAccType, Asset, amount)
            switch (itemIdx) {
                case 0: /* utility_batch_V1 - calls */;
                    return _toStringSubaccount_V1(
                            &m->basic.subaccounts_transfer_to_subaccount_V1.subAccType,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 1:
                    return _toStringAsset_V1(
                            &m->basic.subaccounts_transfer_to_subaccount_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                case 2:
                    return _toStringBalanceAsset_V1(
                            &m->basic.subaccounts_transfer_to_subaccount_V1.amount,
                            &m->basic.subaccounts_transfer_to_subaccount_V1.asset,
                            outValue, outValueLen,
                            pageIdx, pageCount);
                default:
                    return parser_no_data;
            }
        case 6912: /* module 27 call 0 */ // EqBridge:transfer_native(amount, recipient, chainId, resourceId)
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
    case 3328: // EqBalances:transfer
    case 5632: // Vesting:vest
    case 6144: // Subaccounts:transfer_to_subaccount
    case 6145: // Subaccounts:transfer_from_subaccount
    case 6912: // EqBridge:transfer_native
        return false;
    default:
        return true;
    }
}