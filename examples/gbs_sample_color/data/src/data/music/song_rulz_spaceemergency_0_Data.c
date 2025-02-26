#pragma bank 255

#include "hUGEDriver.h"
#include <stddef.h>
#include "hUGEDriverRoutines.h"

static const unsigned char order_cnt = 2;
static const unsigned char song_pattern_0[] = {
    DN(___, 0, 0x8ED),
    DN(C_5, 1, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(C_5, 1, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0xE00),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
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
    DN(___, 0, 0x000),
    DN(C_5, 2, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(C_5, 2, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0x102),
    DN(___, 0, 0xE00),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
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
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0x000),
    DN(___, 0, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(___, 0, 0x000),
    DN(C_7, 1, 0xE02),
    DN(C_7, 1, 0xE02),
    DN(C_7, 1, 0x000),
    DN(___, 0, 0xE02),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
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
static const unsigned char song_pattern_3[] = {
    DN(___, 0, 0x000),
    DN(As7, 1, 0xC0A),
    DN(A_7, 1, 0xC09),
    DN(Gs7, 1, 0xC08),
    DN(G_7, 1, 0xC08),
    DN(Fs7, 1, 0xC07),
    DN(F_7, 1, 0xC06),
    DN(E_7, 1, 0xC06),
    DN(Ds7, 1, 0xC05),
    DN(D_7, 1, 0xC05),
    DN(Cs7, 1, 0xC04),
    DN(C_7, 1, 0xC03),
    DN(B_6, 1, 0xC03),
    DN(As6, 1, 0xC02),
    DN(A_6, 1, 0xC01),
    DN(Gs6, 1, 0xC01),
    DN(G_6, 1, 0xC01),
    DN(___, 0, 0x000),
    DN(___, 0, 0xE00),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
    DN(___, 0, 0x000),
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
    { 0x00, 0x00, 0xF0, 0, 0x80 },
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
    { 0xB0, noise_0_subpattern, 0x00, 0, 0 },
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
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
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
    0x44, 0x8A, 0x32, 0x1B, 0x08, 0x8A, 0x4C, 0x42, 0x2E, 0xA7, 0x83, 0x49, 0x29, 0x37, 0xAC, 0xAD,
    0x8A, 0x3A, 0x88, 0x28, 0x4C, 0x47, 0x00, 0x2C, 0x85, 0x22, 0x87, 0x0C, 0xDA, 0x2E, 0x93, 0x69,
    0x3A, 0xD7, 0xBE, 0x25, 0x68, 0x43, 0x91, 0xE8, 0xD3, 0xB1, 0x5E, 0xB6, 0x0A, 0x12, 0x5B, 0x1B,
    0x0E, 0xA0, 0x3A, 0x7E, 0xC2, 0x5B, 0xB0, 0x5C, 0x31, 0xC2, 0x27, 0x6B, 0xC4, 0xA7, 0x3C, 0x54,
    0x77, 0x05, 0x5B, 0xE3, 0x03, 0x09, 0xC7, 0x4A, 0xA9, 0xB7, 0x72, 0x07, 0xAE, 0x66, 0xA1, 0x00,
};

const void __at(255) __bank_song_rulz_spaceemergency_0_Data;
const hUGESong_t song_rulz_spaceemergency_0_Data = {
    8,
    &order_cnt,
    order1, order2, order3, order4,
    duty_instruments, wave_instruments, noise_instruments,
    routines,
    waves
};
