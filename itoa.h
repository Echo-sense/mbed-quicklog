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


#include <cstdint>

#ifndef ECHOSENSE_FIRMWARE_ITOA_H
#define ECHOSENSE_FIRMWARE_ITOA_H

#endif //ECHOSENSE_FIRMWARE_ITOA_H

#define QL_MAGIC_INT8 0x0333

char *QL_itoa_uint8(uint8_t val, char *buf) {
    uint64_t x;
    uint32_t num   = val;
    uint32_t pow10 = 1;
    uint32_t dig;
    char     *end;

    while (pow10 <= num) {
        pow10 *= 10;
        buf++;
    } // establish the length of the number

    end = buf + 1;

    // loop backwards through the number printing the result
    do {
        // divide num by 10
        num++;
        num *= QL_MAGIC_INT8;
        dig = num >> 9;

        // store remainder in dig
        dig &= 0x1F;
        dig *= 10;
        dig >>= 4;
        if (dig >= 10) {
            dig -= 10;
        } // dig %= 10

        // print digit
        *buf-- = '0' + dig;

        // store quotient back in num
        num >>= 13;
    } while (num > 0);

    return end;
}

char *QL_itoa_int8(int8_t val, char *buf) {
    if (val < 0) {
        *(buf++) = '-';
        val = -val;
    }
    return QL_itoa_uint8(val, buf);
}


