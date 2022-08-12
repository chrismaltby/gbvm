#include "math.h"

const int8_t sine_wave[256] = {
    0,3,6,9,12,16,19,22,25,28,31,34,37,40,43,46,49,51,54,57,60,
    63,65,68,71,73,76,78,81,83,85,88,90,92,94,96,98,100,102,104,
    106,107,109,111,112,113,115,116,117,118,120,121,122,122,123,
    124,125,125,126,126,126,127,127,127,127,127,127,127,126,126,
    126,125,125,124,123,122,122,121,120,118,117,116,115,113,112,
    111,109,107,106,104,102,100,98,96,94,92,90,88,85,83,81,78,76,
    73,71,68,65,63,60,57,54,51,49,46,43,40,37,34,31,28,25,22,19,
    16,12,9,6,3,0,-3,-6,-9,-12,-16,-19,-22,-25,-28,-31,-34,-37,
    -40,-43,-46,-49,-51,-54,-57,-60,-63,-65,-68,-71,-73,-76,-78,
    -81,-83,-85,-88,-90,-92,-94,-96,-98,-100,-102,-104,-106,-107,
    -109,-111,-112,-113,-115,-116,-117,-118,-120,-121,-122,-122,
    -123,-124,-125,-125,-126,-126,-126,-127,-127,-127,-127,-127,
    -127,-127,-126,-126,-126,-125,-125,-124,-123,-122,-122,-121,
    -120,-118,-117,-116,-115,-113,-112,-111,-109,-107,-106,-104,
    -102,-100,-98,-96,-94,-92,-90,-88,-85,-83,-81,-78,-76,-73,-71,
    -68,-65,-63,-60,-57,-54,-51,-49,-46,-43,-40,-37,-34,-31,-28,
    -25,-22,-19,-16,-12,-9,-6,-3
};

const uint8_t atan2_table[20][18] = {
    { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 },
    {  0, 32, 45, 51, 54, 56, 57, 58, 59, 59, 60, 60, 61, 61, 61, 61, 61, 62 },
    {  0, 19, 32, 40, 45, 48, 51, 53, 54, 55, 56, 57, 57, 58, 58, 59, 59, 59 },
    {  0, 13, 24, 32, 38, 42, 45, 48, 49, 51, 52, 53, 54, 55, 55, 56, 56, 57 },
    {  0, 10, 19, 26, 32, 37, 40, 43, 45, 47, 48, 50, 51, 52, 53, 53, 54, 55 },
    {  0,  8, 16, 22, 27, 32, 36, 39, 41, 43, 45, 47, 48, 49, 50, 51, 52, 52 },
    {  0,  7, 13, 19, 24, 28, 32, 35, 38, 40, 42, 44, 45, 46, 48, 48, 49, 50 },
    {  0,  6, 11, 16, 21, 25, 29, 32, 35, 37, 39, 41, 42, 44, 45, 46, 47, 48 },
    {  0,  5, 10, 15, 19, 23, 26, 29, 32, 34, 37, 38, 40, 42, 43, 44, 45, 46 },
    {  0,  5,  9, 13, 17, 21, 24, 27, 30, 32, 34, 36, 38, 39, 41, 42, 43, 44 },
    {  0,  4,  8, 12, 16, 19, 22, 25, 27, 30, 32, 34, 36, 37, 39, 40, 41, 42 },
    {  0,  4,  7, 11, 14, 17, 20, 23, 26, 28, 30, 32, 34, 35, 37, 38, 39, 41 },
    {  0,  3,  7, 10, 13, 16, 19, 22, 24, 26, 28, 30, 32, 34, 35, 37, 38, 39 },
    {  0,  3,  6,  9, 12, 15, 18, 20, 22, 25, 27, 29, 30, 32, 34, 35, 36, 37 },
    {  0,  3,  6,  9, 11, 14, 16, 19, 21, 23, 25, 27, 29, 30, 32, 33, 35, 36 },
    {  0,  3,  5,  8, 11, 13, 16, 18, 20, 22, 24, 26, 27, 29, 31, 32, 33, 35 },
    {  0,  3,  5,  8, 10, 12, 15, 17, 19, 21, 23, 25, 26, 28, 29, 31, 32, 33 },
    {  0,  2,  5,  7,  9, 12, 14, 16, 18, 20, 22, 23, 25, 27, 28, 29, 31, 32 },
    {  0,  2,  5,  7,  9, 11, 13, 15, 17, 19, 21, 22, 24, 25, 27, 28, 30, 31 },
    {  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 21, 23, 24, 26, 27, 29, 30 }
};

const point8_t dir_lookup[4] = {
    { .x =  0, .y =  1 },
    { .x =  1, .y =  0 },
    { .x =  0, .y = -1 },
    { .x = -1, .y =  0 }
};

const UBYTE dir_angle_lookup[4] = {
    128,
    64,
    0,
    192,
};

UBYTE isqrt(uint16_t x) NONBANKED {
    uint16_t m, y, b;
    m = 0x4000;
    y = 0;
    while (m != 0) {
        b = y | m;
        y >>= 1;
        if (x >= b) {
            x -= b;
            y |= m;
        }
        m >>= 2;
    }
    return (UBYTE)y;
}

uint8_t atan2(int16_t y, int16_t x) NONBANKED {
    x = (x > 19) ? 19 : x;
    y = (y > 17) ? 17 : y;

    if (x >= 0 && y <= 0) {
        return 64 - atan2_table[x][y * -1];
    } else if (x >= 0 && y >= 0) {
        return 64 + atan2_table[x][y];
    } else if (x <= 0 && y >= 0) {
        return 192 - atan2_table[x * -1][y];
    } else {
        return 192 + atan2_table[x * -1][y * -1];
    }
}
