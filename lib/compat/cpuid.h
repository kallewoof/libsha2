/* Copyright (c) 2017-2019 The Bitcoin Core developers
 * Copyright (c) 2022 Mark Friedenbach
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SHA2__COMPAT__CPUID_H
#define SHA2__COMPAT__CPUID_H

#if defined(__x86_64__) || defined(__amd64__) || defined(__i386__)
#define HAVE_GETCPUID

#include <cpuid.h>

/* We can't use cpuid.h's __get_cpuid as it does not support subleafs. */
static inline __attribute__((always_inline)) void GetCPUID(uint32_t leaf, uint32_t subleaf, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
#ifdef __GNUC__
    __cpuid_count(leaf, subleaf, *a, *b, *c, *d);
#else
  __asm__ ("cpuid" : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d) : "0"(leaf), "2"(subleaf));
#endif
}

#endif /* defined(__x86_64__) || defined(__amd64__) || defined(__i386__) */
#endif /* SHA2__COMPAT__CPUID_H */

/* End of File
 */
