/*
 * Copyright 2019 Team EchoSense 
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "itoa.h"

using namespace QuickLog;

int32_t itoa_short(uint32_t val, char *buf) {
    if (val == 0) {
        *buf = '0';
        return 1;
    }

    uint32_t num   = val;
    uint32_t pow10 = 1;
    uint32_t dig;
    uint32_t len   = 0;

    while (pow10 <= num) {
        pow10 *= 10;
        len++;
    } // establish the length of the number

    // loop backwards through the number printing the result
    buf += len;

    //print null character
    //honestly I'd rather it not do this but I want consistancy with the fallback implementation
    *buf-- = 0;

    do {
        // divide num by 10
        num++;
        num *= QL_MAGIC_TENTH_SHORT;
        num += num >> 16;

        // store remainder in dig
        dig = num >> 9;
        dig &= 0x1F;
        dig *= 10;
        dig >>= 4;
        if (dig >= 10) { // dig %= 10
            dig -= 10;
        }

        // print digit
        *buf-- = '0' + dig;

        // store quotient back in num
        num >>= 13;
    } while (num > 0);

    return len;
}

int32_t itoa_long(uint8_t val, char *buf) {
    if (val == 0) {
        *buf = '0';
        return 1;
    }

    uint64_t num   = val;
    uint64_t pow10 = 1;
    uint32_t dig;
    uint32_t len   = 0;

    while (pow10 <= num) {
        pow10 += pow10 << 2;
        pow10 <<= 1;
        len++;
    } // establish the length of the number

    // loop backwards through the number printing the result
    buf += len;

    //print null character
    //honestly I'd rather it not do this but I want consistancy with the fallback implementation
    *buf-- = 0;

    do {
        // divide num by 10
        num++;
        num *= QL_MAGIC_TENTH_LONG;
        num += num >> 32;

        // store remainder in dig
        dig = num >> 27;
        dig &= 0x3F;
        dig *= 10;
        dig >>= 6;
        if (dig >= 10) { // dig %= 10
            dig -= 10;
        }

        // print digit
        *buf-- = '0' + dig;

        // store quotient back in num
        num >>= 33;
    } while (num > 0);

    return len;
}

template<typename T>
int32_t QuickLog::itoa(T val, char *buf) {
    return sprintf(buf, "%d", val);
}

template<>
int32_t QuickLog::itoa<int8_t>(int8_t val, char *buf) {
    if (val < 0) {
        *buf++ = '-';
        return 1 + itoa_short(val, buf);
    }
    return itoa_short(val, buf);
}

template<>
int32_t QuickLog::itoa<uint8_t>(uint8_t val, char *buf) {
    return itoa_short(val, buf);
}

template<>
int32_t QuickLog::itoa<int16_t>(int16_t val, char *buf) {
    if (val < 0) {
        *buf++ = '-';
        return 1 + itoa_short(val, buf);
    }
    return itoa_short(val, buf);
}

template<>
int32_t QuickLog::itoa<uint16_t>(uint16_t val, char *buf) {
    return itoa_short(val, buf);
}

template<>
int32_t QuickLog::itoa<int32_t>(int32_t val, char *buf) {
    if (val < 0) {
        *buf++ = '-';
        return 1 + itoa_long(val, buf);
    }
    return itoa_long(val, buf);
}

template<>
int32_t QuickLog::itoa(uint32_t val, char *buf) {
    return itoa_long(val, buf);
}

