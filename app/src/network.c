//
// Created by overseven on 21.06.2021.
//


#include <stdint.h>
#include "network.h"


static const char* NETWORK_KSM = "KSM";
static const char* NETWORK_GENS = "GENS";
static const char* GENESIS_GENS  = "9b8cefc0eb5c568b527998bdd76c184e2b76ae561be76e4667072230217ea243";
static const char* GENESIS_KSM   = "b0a8d493285c2df73290dfb7e61f870f17b41801197a149ca93654499ea3dafe";

static const char* NETWORK_ERROR = "ERROR";
static const char* GENESIS_ERROR = "00";

const char *get_network_name(uint8_t id) {
    switch (id) {
        case Network_GENS:
            return NETWORK_GENS;
        case Network_KSM:
            return NETWORK_KSM;
        default:
            return NETWORK_ERROR;
    }
}

//  Full list of der. paths: https://github.com/satoshilabs/slips/blob/master/slip-0044.md
uint32_t get_network_derivation_path(uint8_t id) {
    switch (id) {
        case Network_GENS:
            return (0x80000000 | 0x5f5e0fc); // 99999996
        case Network_KSM:
            return (0x80000000 | 0x1b2); // 434
        default:
            return 0;
    }
}

const char* get_network_genesis_hash(uint8_t id){
    switch (id) {
        case Network_GENS:
            return GENESIS_GENS;
        case Network_KSM:
            return GENESIS_KSM;
        default:
            return GENESIS_ERROR;
    }
}

// https://polkadot.subscan.io/tools/ss58_transform
uint8_t get_network_address_type(uint8_t id){
    switch (id) {
        case Network_GENS:
            return 67;
        case Network_KSM:
            return 2;
        default:
            return 0;
    }
}