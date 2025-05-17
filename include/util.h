#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>

#define SIGN_EXTEND(x) (x >> 7 == 1 ? ((u16)0xff00 | (u16)x) : ((u16)x))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#endif