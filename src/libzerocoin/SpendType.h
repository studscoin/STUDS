// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2019-2020 The MasterWin developers
// Copyright (c) 2021-2021 The Studscoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Studscoin_SPENDTYPE_H
#define Studscoin_SPENDTYPE_H

#include <cstdint>

namespace libzerocoin {
    enum SpendType : uint8_t {
        SPEND, // Used for a typical spend transaction, zstuds should be unusable after
        STAKE, // Used for a spend that occurs as a stake
        MN_COLLATERAL, // Used when proving ownership of zstuds that will be used for masternodes (future)
        SIGN_MESSAGE // Used to sign messages that do not belong above (future)
    };
}

#endif //Studscoin_SPENDTYPE_H
