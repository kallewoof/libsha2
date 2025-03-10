/* Copyright (c) 2014-2020 The Bitcoin Core developers
 * Copyright (c) 2022 Mark Friedenbach
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "common.h"

#include <stdint.h> /* for uint16_t, uint32_t, uint64_t */
#include <string.h> /* for memcpy */

#include "compat/endian.h" /* for le16toh, le32toh, le64toh,
                            *     htole16, htole32, htole64,
                            *     be16toh, be32toh, be64toh,
                            *     htobe16, htobe32, htobe64 */

uint16_t ReadLE16(const unsigned char* ptr)
{
        uint16_t x;
        memcpy((char*)&x, ptr, 2);
        return le16toh(x);
}

uint32_t ReadLE32(const unsigned char* ptr)
{
        uint32_t x;
        memcpy((char*)&x, ptr, 4);
        return le32toh(x);
}

uint64_t ReadLE64(const unsigned char* ptr)
{
        uint64_t x;
        memcpy((char*)&x, ptr, 8);
        return le64toh(x);
}

void WriteLE16(unsigned char* ptr, uint16_t x)
{
        uint16_t v = htole16(x);
        memcpy(ptr, (char*)&v, 2);
}

void WriteLE32(unsigned char* ptr, uint32_t x)
{
        uint32_t v = htole32(x);
        memcpy(ptr, (char*)&v, 4);
}

void WriteLE64(unsigned char* ptr, uint64_t x)
{
        uint64_t v = htole64(x);
        memcpy(ptr, (char*)&v, 8);
}

uint16_t ReadBE16(const unsigned char* ptr)
{
        uint16_t x;
        memcpy((char*)&x, ptr, 2);
        return be16toh(x);
}

uint32_t ReadBE32(const unsigned char* ptr)
{
        uint32_t x;
        memcpy((char*)&x, ptr, 4);
        return be32toh(x);
}

uint64_t ReadBE64(const unsigned char* ptr)
{
        uint64_t x;
        memcpy((char*)&x, ptr, 8);
        return be64toh(x);
}

void WriteBE16(unsigned char* ptr, uint16_t x)
{
        uint16_t v = htobe16(x);
        memcpy(ptr, (char*)&v, 4);
}

void WriteBE32(unsigned char* ptr, uint32_t x)
{
        uint32_t v = htobe32(x);
        memcpy(ptr, (char*)&v, 4);
}

void WriteBE64(unsigned char* ptr, uint64_t x)
{
        uint64_t v = htobe64(x);
        memcpy(ptr, (char*)&v, 8);
}

/** Return the smallest number n such that (x >> n) == 0 (or 64 if the highest bit in x is set. */
uint64_t CountBits(uint64_t x)
{
#if HAVE_BUILTIN_CLZL
        if (sizeof(unsigned long) >= sizeof(uint64_t)) {
                return x ? 8 * sizeof(unsigned long) - __builtin_clzl(x) : 0;
        }
#endif
#if HAVE_BUILTIN_CLZLL
        if (sizeof(unsigned long long) >= sizeof(uint64_t)) {
                return x ? 8 * sizeof(unsigned long long) - __builtin_clzll(x) : 0;
        }
#endif
        int ret = 0;
        while (x) {
                x >>= 1;
                ++ret;
        }
        return ret;
}

/* End of File
 */
