// Copyright (c) 2021-2022 The Studscoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Studscoin_CRYPTO_GOOGLE_AUTHENTICATOR_H
#define Studscoin_CRYPTO_GOOGLE_AUTHENTICATOR_H

#include <cstdint>

/** A Google Authenticator support class. */
class GoogleAuthenticator
{
private:
    static const int INTERVAL_LENGHT = 30;
    static const int PIN_LENGHT = 6;

    const unsigned char* key;
    const int len;
public:
    GoogleAuthenticator(const unsigned char* key, const int len) : key(key), len(len) {}

    int GeneratePin();
};

#endif // Studscoin_CRYPTO_GOOGLE_AUTHENTICATOR_H
