#pragma bank 255

#include "hUGEDriver.h"
#include <stddef.h>
#include "hUGEDriverRoutines.h"

static const unsigned char order_cnt = 2;
static const unsigned char song_pattern_0[] = {
    DN(Cs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(Cs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Cs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(Cs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
};
static const unsigned char song_pattern_1[] = {
    DN(Fs6, 1, 0xE03),
    DN(___, 0, 0x0B4),
    DN(Fs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xE03),
    DN(___, 0, 0x0E0),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
};
static const unsigned char song_pattern_2[] = {
    DN(Fs6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(E_6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(E_6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC03),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC03),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC03),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(Fs6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(E_6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(E_6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0xC03),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0xC40),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(Ds6, 1, 0xC03),
    DN(___, 0, 0x000),
    DN(B_5, 1, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(B_5, 1, 0xC07),
    DN(___, 0, 0x000),
    DN(B_5, 1, 0xC03),
    DN(___, 0, 0x000),
};
static const unsigned char song_pattern_3[] = {
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(B_6, 1, 0xC04),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(B_6, 1, 0xC04),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(B_6, 1, 0xC04),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(Ds7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE03),
    DN(___, 0, 0x000),
    DN(B_6, 1, 0xC04),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
};
static const unsigned char noise_0_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_1_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_2_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_3_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_4_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_5_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_6_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_7_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_8_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_9_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_10_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_11_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_12_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_13_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char noise_14_subpattern[] = {
    DN(___, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 0, 0x000),
    DN(36, 7, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 1, 0x000),
};
static const unsigned char* const order1[] = {song_pattern_0};
static const unsigned char* const order2[] = {song_pattern_1};
static const unsigned char* const order3[] = {song_pattern_2};
static const unsigned char* const order4[] = {song_pattern_3};
static const hUGEDutyInstr_t duty_instruments[] = {
    { 0x00, 0x00, 0xB0, 0, 0x80 },
    { 0x00, 0x40, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0xC0, 0xF0, 0, 0x80 },
    { 0x00, 0x00, 0xF1, 0, 0x80 },
    { 0x00, 0x40, 0xF1, 0, 0x80 },
    { 0x00, 0x80, 0xF1, 0, 0x80 },
    { 0x00, 0xC0, 0xF1, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
    { 0x00, 0x80, 0xF0, 0, 0x80 },
};
static const hUGEWaveInstr_t wave_instruments[] = {
    { 0x00, 0x20, 0x00, 0, 0x80 },
    { 0x00, 0x20, 0x01, 0, 0x80 },
    { 0x00, 0x20, 0x02, 0, 0x80 },
    { 0x00, 0x20, 0x03, 0, 0x80 },
    { 0x00, 0x20, 0x04, 0, 0x80 },
    { 0x00, 0x20, 0x05, 0, 0x80 },
    { 0x00, 0x20, 0x06, 0, 0x80 },
    { 0x00, 0x20, 0x07, 0, 0x80 },
    { 0x00, 0x20, 0x08, 0, 0x80 },
    { 0x00, 0x20, 0x09, 0, 0x80 },
    { 0x00, 0x20, 0x0A, 0, 0x80 },
    { 0x00, 0x20, 0x0B, 0, 0x80 },
    { 0x00, 0x20, 0x0C, 0, 0x80 },
    { 0x00, 0x20, 0x0D, 0, 0x80 },
    { 0x00, 0x20, 0x0E, 0, 0x80 },
};
static const hUGENoiseInstr_t noise_instruments[] = {
    { 0x90, noise_0_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_1_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_2_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_3_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_4_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_5_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_6_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_7_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_8_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_9_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_10_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_11_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_12_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_13_subpattern, 0x00, 0, 0 },
    { 0xF0, noise_14_subpattern, 0x00, 0, 0 },
};
static const unsigned char waves[] = {
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF,
    0x7A, 0xCD, 0xDB, 0x75, 0x21, 0x13, 0x68, 0xBD, 0xDC, 0x97, 0x41, 0x01, 0x47, 0x9C, 0xDD, 0xB8,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0xFE, 0xFC, 0xFA, 0xF8, 0xF6, 0xF4, 0xF2, 0xF0, 0xF2, 0xF4, 0xF6, 0xF8, 0xFA, 0xFC, 0xFE, 0xFF,
    0xFE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x8A, 0xBD, 0xF1, 0x24, 0x57, 0x8A, 0xBD, 0xEE,
    0x84, 0x11, 0x61, 0xED, 0x57, 0x47, 0x5A, 0xAD, 0xCE, 0xA3, 0x17, 0x79, 0xDD, 0x20, 0x03, 0x47,
    0x20, 0xB4, 0xAC, 0x80, 0x7A, 0x09, 0x88, 0xD5, 0xD0, 0xB1, 0xBA, 0xC8, 0x81, 0x88, 0xCA, 0x04,
    0x17, 0x77, 0x32, 0x9B, 0x1D, 0xC9, 0x62, 0x2D, 0x6B, 0xC8, 0x95, 0x6A, 0x08, 0xA0, 0x75, 0xBC,
    0xA7, 0xD1, 0xD8, 0x24, 0x8B, 0xA1, 0xA6, 0xA8, 0x0A, 0x58, 0x51, 0xE1, 0x3D, 0xB7, 0x76, 0xE3,
    0xA6, 0xE0, 0x1D, 0x38, 0xC0, 0x17, 0x93, 0x19, 0x8E, 0x86, 0x58, 0x7E, 0xC1, 0x07, 0xB6, 0x49,
    0x25, 0xE5, 0x92, 0x3E, 0x40, 0xE5, 0x57, 0x95, 0xE3, 0xCE, 0xC8, 0x90, 0xA9, 0x68, 0x39, 0xDC,
};

const void __at(255) __bank_song_rulz_outside_0_Data;
const hUGESong_t song_rulz_outside_0_Data = {
    8,
    &order_cnt,
    order1, order2, order3, order4,
    duty_instruments, wave_instruments, noise_instruments,
    routines,
    waves
};
