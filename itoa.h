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
#include <cstdio>

#ifndef ECHOSENSE_FIRMWARE_ITOA_H
#define ECHOSENSE_FIRMWARE_ITOA_H

#endif //ECHOSENSE_FIRMWARE_ITOA_H

#define QL_MAGIC_TENTH_SHORT 0x00000333
#define QL_MAGIC_TENTH_LONG  0x33333333


namespace QuickLog {
template<typename T>

/**
 * @brief Print an @par val as a null-ternimated string to @par buf in decimal
 * This is a fallback itoa implementation using sprintf
 * Sprintf is slow, so hopefully this is not used much
 *
 * @tparam T type of input value
 * @param val value to print
 * @param buf buffer to print to
 * @return number of characters that would have been written for sufficiently large buffer.
 */
int32_t itoa(T val, char *buf);

template<>
int32_t itoa<int8_t>(int8_t val, char *buf);

template<>
int32_t itoa<uint8_t>(uint8_t val, char *buf);

template<>
int32_t itoa<int16_t>(int16_t val, char *buf);

template<>
int32_t itoa<uint16_t>(uint16_t val, char *buf);

template<>
int32_t itoa<int32_t>(int32_t val, char *buf);

template<>
int32_t itoa<uint32_t>(uint32_t val, char *buf);
}

