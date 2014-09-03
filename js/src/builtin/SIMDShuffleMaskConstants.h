/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef builtin_SIMDShuffleMaskConstants_h
#define builtin_SIMDShuffleMaskConstants_h

#define COMMON_PROPERTY_NAMES_MACRO(macro, mask, maskStr, value) macro(mask, mask, maskStr)

#define SET_SHUFFLE_MASK(macro, maskId, maskStr, value)              \
    {                                                                \
      RootedValue mask##maskId(cx, JS::Int32Value(value));           \
      JSObject::defineProperty(cx, SIMD, cx->names().maskId,         \
                               mask##maskId, nullptr, nullptr,       \
                               JSPROP_READONLY | JSPROP_PERMANENT);  \
    }

#define SET_ALL_SHUFFLE_MASKS FOR_EACH_SIMD_SHUFFLE_MASK(SET_SHUFFLE_MASK, 0)

#define FOR_EACH_SIMD_SHUFFLE_MASK(macro, innerMacro)                \
    macro(innerMacro, XXXX, "XXXX", 0x0)                             \
    macro(innerMacro, XXXY, "XXXY", 0x40)                            \
    macro(innerMacro, XXXZ, "XXXZ", 0x80)                            \
    macro(innerMacro, XXXW, "XXXW", 0xC0)                            \
    macro(innerMacro, XXYX, "XXYX", 0x10)                            \
    macro(innerMacro, XXYY, "XXYY", 0x50)                            \
    macro(innerMacro, XXYZ, "XXYZ", 0x90)                            \
    macro(innerMacro, XXYW, "XXYW", 0xD0)                            \
    macro(innerMacro, XXZX, "XXZX", 0x20)                            \
    macro(innerMacro, XXZY, "XXZY", 0x60)                            \
    macro(innerMacro, XXZZ, "XXZZ", 0xA0)                            \
    macro(innerMacro, XXZW, "XXZW", 0xE0)                            \
    macro(innerMacro, XXWX, "XXWX", 0x30)                            \
    macro(innerMacro, XXWY, "XXWY", 0x70)                            \
    macro(innerMacro, XXWZ, "XXWZ", 0xB0)                            \
    macro(innerMacro, XXWW, "XXWW", 0xF0)                            \
    macro(innerMacro, XYXX, "XYXX", 0x4)                             \
    macro(innerMacro, XYXY, "XYXY", 0x44)                            \
    macro(innerMacro, XYXZ, "XYXZ", 0x84)                            \
    macro(innerMacro, XYXW, "XYXW", 0xC4)                            \
    macro(innerMacro, XYYX, "XYYX", 0x14)                            \
    macro(innerMacro, XYYY, "XYYY", 0x54)                            \
    macro(innerMacro, XYYZ, "XYYZ", 0x94)                            \
    macro(innerMacro, XYYW, "XYYW", 0xD4)                            \
    macro(innerMacro, XYZX, "XYZX", 0x24)                            \
    macro(innerMacro, XYZY, "XYZY", 0x64)                            \
    macro(innerMacro, XYZZ, "XYZZ", 0xA4)                            \
    macro(innerMacro, XYZW, "XYZW", 0xE4)                            \
    macro(innerMacro, XYWX, "XYWX", 0x34)                            \
    macro(innerMacro, XYWY, "XYWY", 0x74)                            \
    macro(innerMacro, XYWZ, "XYWZ", 0xB4)                            \
    macro(innerMacro, XYWW, "XYWW", 0xF4)                            \
    macro(innerMacro, XZXX, "XZXX", 0x8)                             \
    macro(innerMacro, XZXY, "XZXY", 0x48)                            \
    macro(innerMacro, XZXZ, "XZXZ", 0x88)                            \
    macro(innerMacro, XZXW, "XZXW", 0xC8)                            \
    macro(innerMacro, XZYX, "XZYX", 0x18)                            \
    macro(innerMacro, XZYY, "XZYY", 0x58)                            \
    macro(innerMacro, XZYZ, "XZYZ", 0x98)                            \
    macro(innerMacro, XZYW, "XZYW", 0xD8)                            \
    macro(innerMacro, XZZX, "XZZX", 0x28)                            \
    macro(innerMacro, XZZY, "XZZY", 0x68)                            \
    macro(innerMacro, XZZZ, "XZZZ", 0xA8)                            \
    macro(innerMacro, XZZW, "XZZW", 0xE8)                            \
    macro(innerMacro, XZWX, "XZWX", 0x38)                            \
    macro(innerMacro, XZWY, "XZWY", 0x78)                            \
    macro(innerMacro, XZWZ, "XZWZ", 0xB8)                            \
    macro(innerMacro, XZWW, "XZWW", 0xF8)                            \
    macro(innerMacro, XWXX, "XWXX", 0xC)                             \
    macro(innerMacro, XWXY, "XWXY", 0x4C)                            \
    macro(innerMacro, XWXZ, "XWXZ", 0x8C)                            \
    macro(innerMacro, XWXW, "XWXW", 0xCC)                            \
    macro(innerMacro, XWYX, "XWYX", 0x1C)                            \
    macro(innerMacro, XWYY, "XWYY", 0x5C)                            \
    macro(innerMacro, XWYZ, "XWYZ", 0x9C)                            \
    macro(innerMacro, XWYW, "XWYW", 0xDC)                            \
    macro(innerMacro, XWZX, "XWZX", 0x2C)                            \
    macro(innerMacro, XWZY, "XWZY", 0x6C)                            \
    macro(innerMacro, XWZZ, "XWZZ", 0xAC)                            \
    macro(innerMacro, XWZW, "XWZW", 0xEC)                            \
    macro(innerMacro, XWWX, "XWWX", 0x3C)                            \
    macro(innerMacro, XWWY, "XWWY", 0x7C)                            \
    macro(innerMacro, XWWZ, "XWWZ", 0xBC)                            \
    macro(innerMacro, XWWW, "XWWW", 0xFC)                            \
    macro(innerMacro, YXXX, "YXXX", 0x1)                             \
    macro(innerMacro, YXXY, "YXXY", 0x41)                            \
    macro(innerMacro, YXXZ, "YXXZ", 0x81)                            \
    macro(innerMacro, YXXW, "YXXW", 0xC1)                            \
    macro(innerMacro, YXYX, "YXYX", 0x11)                            \
    macro(innerMacro, YXYY, "YXYY", 0x51)                            \
    macro(innerMacro, YXYZ, "YXYZ", 0x91)                            \
    macro(innerMacro, YXYW, "YXYW", 0xD1)                            \
    macro(innerMacro, YXZX, "YXZX", 0x21)                            \
    macro(innerMacro, YXZY, "YXZY", 0x61)                            \
    macro(innerMacro, YXZZ, "YXZZ", 0xA1)                            \
    macro(innerMacro, YXZW, "YXZW", 0xE1)                            \
    macro(innerMacro, YXWX, "YXWX", 0x31)                            \
    macro(innerMacro, YXWY, "YXWY", 0x71)                            \
    macro(innerMacro, YXWZ, "YXWZ", 0xB1)                            \
    macro(innerMacro, YXWW, "YXWW", 0xF1)                            \
    macro(innerMacro, YYXX, "YYXX", 0x5)                             \
    macro(innerMacro, YYXY, "YYXY", 0x45)                            \
    macro(innerMacro, YYXZ, "YYXZ", 0x85)                            \
    macro(innerMacro, YYXW, "YYXW", 0xC5)                            \
    macro(innerMacro, YYYX, "YYYX", 0x15)                            \
    macro(innerMacro, YYYY, "YYYY", 0x55)                            \
    macro(innerMacro, YYYZ, "YYYZ", 0x95)                            \
    macro(innerMacro, YYYW, "YYYW", 0xD5)                            \
    macro(innerMacro, YYZX, "YYZX", 0x25)                            \
    macro(innerMacro, YYZY, "YYZY", 0x65)                            \
    macro(innerMacro, YYZZ, "YYZZ", 0xA5)                            \
    macro(innerMacro, YYZW, "YYZW", 0xE5)                            \
    macro(innerMacro, YYWX, "YYWX", 0x35)                            \
    macro(innerMacro, YYWY, "YYWY", 0x75)                            \
    macro(innerMacro, YYWZ, "YYWZ", 0xB5)                            \
    macro(innerMacro, YYWW, "YYWW", 0xF5)                            \
    macro(innerMacro, YZXX, "YZXX", 0x9)                             \
    macro(innerMacro, YZXY, "YZXY", 0x49)                            \
    macro(innerMacro, YZXZ, "YZXZ", 0x89)                            \
    macro(innerMacro, YZXW, "YZXW", 0xC9)                            \
    macro(innerMacro, YZYX, "YZYX", 0x19)                            \
    macro(innerMacro, YZYY, "YZYY", 0x59)                            \
    macro(innerMacro, YZYZ, "YZYZ", 0x99)                            \
    macro(innerMacro, YZYW, "YZYW", 0xD9)                            \
    macro(innerMacro, YZZX, "YZZX", 0x29)                            \
    macro(innerMacro, YZZY, "YZZY", 0x69)                            \
    macro(innerMacro, YZZZ, "YZZZ", 0xA9)                            \
    macro(innerMacro, YZZW, "YZZW", 0xE9)                            \
    macro(innerMacro, YZWX, "YZWX", 0x39)                            \
    macro(innerMacro, YZWY, "YZWY", 0x79)                            \
    macro(innerMacro, YZWZ, "YZWZ", 0xB9)                            \
    macro(innerMacro, YZWW, "YZWW", 0xF9)                            \
    macro(innerMacro, YWXX, "YWXX", 0xD)                             \
    macro(innerMacro, YWXY, "YWXY", 0x4D)                            \
    macro(innerMacro, YWXZ, "YWXZ", 0x8D)                            \
    macro(innerMacro, YWXW, "YWXW", 0xCD)                            \
    macro(innerMacro, YWYX, "YWYX", 0x1D)                            \
    macro(innerMacro, YWYY, "YWYY", 0x5D)                            \
    macro(innerMacro, YWYZ, "YWYZ", 0x9D)                            \
    macro(innerMacro, YWYW, "YWYW", 0xDD)                            \
    macro(innerMacro, YWZX, "YWZX", 0x2D)                            \
    macro(innerMacro, YWZY, "YWZY", 0x6D)                            \
    macro(innerMacro, YWZZ, "YWZZ", 0xAD)                            \
    macro(innerMacro, YWZW, "YWZW", 0xED)                            \
    macro(innerMacro, YWWX, "YWWX", 0x3D)                            \
    macro(innerMacro, YWWY, "YWWY", 0x7D)                            \
    macro(innerMacro, YWWZ, "YWWZ", 0xBD)                            \
    macro(innerMacro, YWWW, "YWWW", 0xFD)                            \
    macro(innerMacro, ZXXX, "ZXXX", 0x2)                             \
    macro(innerMacro, ZXXY, "ZXXY", 0x42)                            \
    macro(innerMacro, ZXXZ, "ZXXZ", 0x82)                            \
    macro(innerMacro, ZXXW, "ZXXW", 0xC2)                            \
    macro(innerMacro, ZXYX, "ZXYX", 0x12)                            \
    macro(innerMacro, ZXYY, "ZXYY", 0x52)                            \
    macro(innerMacro, ZXYZ, "ZXYZ", 0x92)                            \
    macro(innerMacro, ZXYW, "ZXYW", 0xD2)                            \
    macro(innerMacro, ZXZX, "ZXZX", 0x22)                            \
    macro(innerMacro, ZXZY, "ZXZY", 0x62)                            \
    macro(innerMacro, ZXZZ, "ZXZZ", 0xA2)                            \
    macro(innerMacro, ZXZW, "ZXZW", 0xE2)                            \
    macro(innerMacro, ZXWX, "ZXWX", 0x32)                            \
    macro(innerMacro, ZXWY, "ZXWY", 0x72)                            \
    macro(innerMacro, ZXWZ, "ZXWZ", 0xB2)                            \
    macro(innerMacro, ZXWW, "ZXWW", 0xF2)                            \
    macro(innerMacro, ZYXX, "ZYXX", 0x6)                             \
    macro(innerMacro, ZYXY, "ZYXY", 0x46)                            \
    macro(innerMacro, ZYXZ, "ZYXZ", 0x86)                            \
    macro(innerMacro, ZYXW, "ZYXW", 0xC6)                            \
    macro(innerMacro, ZYYX, "ZYYX", 0x16)                            \
    macro(innerMacro, ZYYY, "ZYYY", 0x56)                            \
    macro(innerMacro, ZYYZ, "ZYYZ", 0x96)                            \
    macro(innerMacro, ZYYW, "ZYYW", 0xD6)                            \
    macro(innerMacro, ZYZX, "ZYZX", 0x26)                            \
    macro(innerMacro, ZYZY, "ZYZY", 0x66)                            \
    macro(innerMacro, ZYZZ, "ZYZZ", 0xA6)                            \
    macro(innerMacro, ZYZW, "ZYZW", 0xE6)                            \
    macro(innerMacro, ZYWX, "ZYWX", 0x36)                            \
    macro(innerMacro, ZYWY, "ZYWY", 0x76)                            \
    macro(innerMacro, ZYWZ, "ZYWZ", 0xB6)                            \
    macro(innerMacro, ZYWW, "ZYWW", 0xF6)                            \
    macro(innerMacro, ZZXX, "ZZXX", 0xA)                             \
    macro(innerMacro, ZZXY, "ZZXY", 0x4A)                            \
    macro(innerMacro, ZZXZ, "ZZXZ", 0x8A)                            \
    macro(innerMacro, ZZXW, "ZZXW", 0xCA)                            \
    macro(innerMacro, ZZYX, "ZZYX", 0x1A)                            \
    macro(innerMacro, ZZYY, "ZZYY", 0x5A)                            \
    macro(innerMacro, ZZYZ, "ZZYZ", 0x9A)                            \
    macro(innerMacro, ZZYW, "ZZYW", 0xDA)                            \
    macro(innerMacro, ZZZX, "ZZZX", 0x2A)                            \
    macro(innerMacro, ZZZY, "ZZZY", 0x6A)                            \
    macro(innerMacro, ZZZZ, "ZZZZ", 0xAA)                            \
    macro(innerMacro, ZZZW, "ZZZW", 0xEA)                            \
    macro(innerMacro, ZZWX, "ZZWX", 0x3A)                            \
    macro(innerMacro, ZZWY, "ZZWY", 0x7A)                            \
    macro(innerMacro, ZZWZ, "ZZWZ", 0xBA)                            \
    macro(innerMacro, ZZWW, "ZZWW", 0xFA)                            \
    macro(innerMacro, ZWXX, "ZWXX", 0xE)                             \
    macro(innerMacro, ZWXY, "ZWXY", 0x4E)                            \
    macro(innerMacro, ZWXZ, "ZWXZ", 0x8E)                            \
    macro(innerMacro, ZWXW, "ZWXW", 0xCE)                            \
    macro(innerMacro, ZWYX, "ZWYX", 0x1E)                            \
    macro(innerMacro, ZWYY, "ZWYY", 0x5E)                            \
    macro(innerMacro, ZWYZ, "ZWYZ", 0x9E)                            \
    macro(innerMacro, ZWYW, "ZWYW", 0xDE)                            \
    macro(innerMacro, ZWZX, "ZWZX", 0x2E)                            \
    macro(innerMacro, ZWZY, "ZWZY", 0x6E)                            \
    macro(innerMacro, ZWZZ, "ZWZZ", 0xAE)                            \
    macro(innerMacro, ZWZW, "ZWZW", 0xEE)                            \
    macro(innerMacro, ZWWX, "ZWWX", 0x3E)                            \
    macro(innerMacro, ZWWY, "ZWWY", 0x7E)                            \
    macro(innerMacro, ZWWZ, "ZWWZ", 0xBE)                            \
    macro(innerMacro, ZWWW, "ZWWW", 0xFE)                            \
    macro(innerMacro, WXXX, "WXXX", 0x3)                             \
    macro(innerMacro, WXXY, "WXXY", 0x43)                            \
    macro(innerMacro, WXXZ, "WXXZ", 0x83)                            \
    macro(innerMacro, WXXW, "WXXW", 0xC3)                            \
    macro(innerMacro, WXYX, "WXYX", 0x13)                            \
    macro(innerMacro, WXYY, "WXYY", 0x53)                            \
    macro(innerMacro, WXYZ, "WXYZ", 0x93)                            \
    macro(innerMacro, WXYW, "WXYW", 0xD3)                            \
    macro(innerMacro, WXZX, "WXZX", 0x23)                            \
    macro(innerMacro, WXZY, "WXZY", 0x63)                            \
    macro(innerMacro, WXZZ, "WXZZ", 0xA3)                            \
    macro(innerMacro, WXZW, "WXZW", 0xE3)                            \
    macro(innerMacro, WXWX, "WXWX", 0x33)                            \
    macro(innerMacro, WXWY, "WXWY", 0x73)                            \
    macro(innerMacro, WXWZ, "WXWZ", 0xB3)                            \
    macro(innerMacro, WXWW, "WXWW", 0xF3)                            \
    macro(innerMacro, WYXX, "WYXX", 0x7)                             \
    macro(innerMacro, WYXY, "WYXY", 0x47)                            \
    macro(innerMacro, WYXZ, "WYXZ", 0x87)                            \
    macro(innerMacro, WYXW, "WYXW", 0xC7)                            \
    macro(innerMacro, WYYX, "WYYX", 0x17)                            \
    macro(innerMacro, WYYY, "WYYY", 0x57)                            \
    macro(innerMacro, WYYZ, "WYYZ", 0x97)                            \
    macro(innerMacro, WYYW, "WYYW", 0xD7)                            \
    macro(innerMacro, WYZX, "WYZX", 0x27)                            \
    macro(innerMacro, WYZY, "WYZY", 0x67)                            \
    macro(innerMacro, WYZZ, "WYZZ", 0xA7)                            \
    macro(innerMacro, WYZW, "WYZW", 0xE7)                            \
    macro(innerMacro, WYWX, "WYWX", 0x37)                            \
    macro(innerMacro, WYWY, "WYWY", 0x77)                            \
    macro(innerMacro, WYWZ, "WYWZ", 0xB7)                            \
    macro(innerMacro, WYWW, "WYWW", 0xF7)                            \
    macro(innerMacro, WZXX, "WZXX", 0xB)                             \
    macro(innerMacro, WZXY, "WZXY", 0x4B)                            \
    macro(innerMacro, WZXZ, "WZXZ", 0x8B)                            \
    macro(innerMacro, WZXW, "WZXW", 0xCB)                            \
    macro(innerMacro, WZYX, "WZYX", 0x1B)                            \
    macro(innerMacro, WZYY, "WZYY", 0x5B)                            \
    macro(innerMacro, WZYZ, "WZYZ", 0x9B)                            \
    macro(innerMacro, WZYW, "WZYW", 0xDB)                            \
    macro(innerMacro, WZZX, "WZZX", 0x2B)                            \
    macro(innerMacro, WZZY, "WZZY", 0x6B)                            \
    macro(innerMacro, WZZZ, "WZZZ", 0xAB)                            \
    macro(innerMacro, WZZW, "WZZW", 0xEB)                            \
    macro(innerMacro, WZWX, "WZWX", 0x3B)                            \
    macro(innerMacro, WZWY, "WZWY", 0x7B)                            \
    macro(innerMacro, WZWZ, "WZWZ", 0xBB)                            \
    macro(innerMacro, WZWW, "WZWW", 0xFB)                            \
    macro(innerMacro, WWXX, "WWXX", 0xF)                             \
    macro(innerMacro, WWXY, "WWXY", 0x4F)                            \
    macro(innerMacro, WWXZ, "WWXZ", 0x8F)                            \
    macro(innerMacro, WWXW, "WWXW", 0xCF)                            \
    macro(innerMacro, WWYX, "WWYX", 0x1F)                            \
    macro(innerMacro, WWYY, "WWYY", 0x5F)                            \
    macro(innerMacro, WWYZ, "WWYZ", 0x9F)                            \
    macro(innerMacro, WWYW, "WWYW", 0xDF)                            \
    macro(innerMacro, WWZX, "WWZX", 0x2F)                            \
    macro(innerMacro, WWZY, "WWZY", 0x6F)                            \
    macro(innerMacro, WWZZ, "WWZZ", 0xAF)                            \
    macro(innerMacro, WWZW, "WWZW", 0xEF)                            \
    macro(innerMacro, WWWX, "WWWX", 0x3F)                            \
    macro(innerMacro, WWWY, "WWWY", 0x7F)                            \
    macro(innerMacro, WWWZ, "WWWZ", 0xBF)                            \
    macro(innerMacro, WWWW, "WWWW", 0xFF)                            \
    macro(innerMacro, XX, "XX", 0x0)                                 \
    macro(innerMacro, XY, "XY", 0x2)                                 \
    macro(innerMacro, YX, "YX", 0x1)                                 \
    macro(innerMacro, YY, "YY", 0x3)

#endif
