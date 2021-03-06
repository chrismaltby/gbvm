#pragma bank 255

// Font

#include "gbs_types.h"

const void __at(255) __bank_font_image;

const unsigned char font_image[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 64, 64, 64, 64, 64, 64, 64, 64, 0, 0, 64, 64, 0, 0,
  0, 0, 108, 108, 36, 36, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 36, 36, 126, 126, 36, 36, 36, 36, 126, 126, 36, 36, 0, 0,
  16, 16, 56, 56, 84, 84, 80, 80, 56, 56, 20, 20, 84, 84, 56, 56,
  0, 0, 0, 0, 36, 36, 8, 8, 16, 16, 36, 36, 0, 0, 0, 0,
  0, 0, 48, 48, 72, 72, 80, 80, 32, 32, 84, 84, 72, 72, 52, 52,
  0, 0, 24, 24, 8, 8, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 0, 0,
  0, 0, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 0, 0,
  0, 0, 0, 0, 16, 16, 84, 84, 56, 56, 84, 84, 16, 16, 0, 0,
  0, 0, 0, 0, 16, 16, 16, 16, 124, 124, 16, 16, 16, 16, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 96, 96, 32, 32, 64, 64, 0, 0,
  0, 0, 0, 0, 0, 0, 124, 124, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 64, 0, 0,
  0, 0, 2, 2, 4, 4, 8, 8, 16, 16, 32, 32, 64, 64, 0, 0,
  0, 0, 60, 60, 98, 98, 82, 82, 74, 74, 70, 70, 60, 60, 0, 0,
  0, 0, 24, 24, 40, 40, 8, 8, 8, 8, 8, 8, 60, 60, 0, 0,
  0, 0, 60, 60, 66, 66, 2, 2, 60, 60, 64, 64, 126, 126, 0, 0,
  0, 0, 124, 124, 2, 2, 12, 12, 2, 2, 2, 2, 126, 126, 0, 0,
  0, 0, 64, 64, 64, 64, 72, 72, 126, 126, 8, 8, 8, 8, 0, 0,
  0, 0, 126, 126, 64, 64, 124, 124, 2, 2, 2, 2, 124, 124, 0, 0,
  0, 0, 60, 60, 64, 64, 124, 124, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 126, 126, 2, 2, 4, 4, 8, 8, 16, 16, 32, 32, 0, 0,
  0, 0, 60, 60, 66, 66, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 60, 60, 66, 66, 66, 66, 62, 62, 2, 2, 60, 60, 0, 0,
  0, 0, 24, 24, 24, 24, 0, 0, 0, 0, 24, 24, 24, 24, 0, 0,
  0, 0, 24, 24, 24, 24, 0, 0, 24, 24, 24, 24, 8, 8, 16, 16,
  0, 0, 0, 0, 12, 12, 48, 48, 64, 64, 48, 48, 12, 12, 0, 0,
  0, 0, 0, 0, 0, 0, 124, 124, 0, 0, 124, 124, 0, 0, 0, 0,
  0, 0, 0, 0, 96, 96, 24, 24, 4, 4, 24, 24, 96, 96, 0, 0,
  0, 0, 48, 48, 72, 72, 8, 8, 48, 48, 0, 0, 32, 32, 0, 0,
  0, 0, 28, 28, 34, 34, 77, 77, 85, 85, 85, 85, 46, 46, 0, 0,
  0, 0, 60, 60, 66, 66, 66, 66, 126, 126, 66, 66, 66, 66, 0, 0,
  0, 0, 124, 124, 66, 66, 124, 124, 66, 66, 66, 66, 124, 124, 0, 0,
  0, 0, 60, 60, 66, 66, 64, 64, 64, 64, 66, 66, 60, 60, 0, 0,
  0, 0, 124, 124, 66, 66, 66, 66, 66, 66, 66, 66, 124, 124, 0, 0,
  0, 0, 126, 126, 64, 64, 124, 124, 64, 64, 64, 64, 126, 126, 0, 0,
  0, 0, 126, 126, 64, 64, 64, 64, 124, 124, 64, 64, 64, 64, 0, 0,
  0, 0, 60, 60, 66, 66, 64, 64, 78, 78, 66, 66, 62, 62, 0, 0,
  0, 0, 66, 66, 66, 66, 66, 66, 126, 126, 66, 66, 66, 66, 0, 0,
  0, 0, 124, 124, 16, 16, 16, 16, 16, 16, 16, 16, 124, 124, 0, 0,
  0, 0, 124, 124, 16, 16, 16, 16, 16, 16, 16, 16, 96, 96, 0, 0,
  0, 0, 68, 68, 72, 72, 80, 80, 112, 112, 72, 72, 68, 68, 0, 0,
  0, 0, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 126, 126, 0, 0,
  0, 0, 66, 66, 102, 102, 90, 90, 66, 66, 66, 66, 66, 66, 0, 0,
  0, 0, 66, 66, 98, 98, 82, 82, 74, 74, 70, 70, 66, 66, 0, 0,
  0, 0, 60, 60, 66, 66, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 124, 124, 66, 66, 66, 66, 124, 124, 64, 64, 64, 64, 0, 0,
  0, 0, 60, 60, 66, 66, 66, 66, 74, 74, 68, 68, 58, 58, 0, 0,
  0, 0, 124, 124, 66, 66, 66, 66, 124, 124, 66, 66, 66, 66, 0, 0,
  0, 0, 62, 62, 64, 64, 60, 60, 2, 2, 66, 66, 60, 60, 0, 0,
  0, 0, 124, 124, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0,
  0, 0, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 68, 68, 68, 68, 68, 68, 40, 40, 40, 40, 16, 16, 0, 0,
  0, 0, 66, 66, 66, 66, 66, 66, 90, 90, 102, 102, 66, 66, 0, 0,
  0, 0, 66, 66, 36, 36, 24, 24, 24, 24, 36, 36, 66, 66, 0, 0,
  0, 0, 68, 68, 40, 40, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0,
  0, 0, 124, 124, 4, 4, 8, 8, 16, 16, 32, 32, 124, 124, 0, 0,
  0, 0, 24, 24, 16, 16, 16, 16, 16, 16, 16, 16, 24, 24, 0, 0,
  0, 0, 64, 64, 32, 32, 16, 16, 8, 8, 4, 4, 2, 2, 0, 0,
  0, 0, 24, 24, 8, 8, 8, 8, 8, 8, 8, 8, 24, 24, 0, 0,
  0, 0, 16, 16, 40, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 60, 0, 0,
  0, 0, 32, 32, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 60, 60, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  0, 0, 64, 64, 120, 120, 68, 68, 68, 68, 68, 68, 120, 120, 0, 0,
  0, 0, 0, 0, 60, 60, 64, 64, 64, 64, 64, 64, 60, 60, 0, 0,
  0, 0, 4, 4, 60, 60, 68, 68, 68, 68, 68, 68, 60, 60, 0, 0,
  0, 0, 0, 0, 56, 56, 68, 68, 124, 124, 64, 64, 60, 60, 0, 0,
  0, 0, 56, 56, 64, 64, 64, 64, 120, 120, 64, 64, 64, 64, 0, 0,
  0, 0, 0, 0, 56, 56, 68, 68, 68, 68, 60, 60, 4, 4, 120, 120,
  0, 0, 64, 64, 120, 120, 68, 68, 68, 68, 68, 68, 68, 68, 0, 0,
  0, 0, 16, 16, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0,
  0, 0, 8, 8, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 48, 48,
  0, 0, 64, 64, 68, 68, 72, 72, 112, 112, 72, 72, 68, 68, 0, 0,
  0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0,
  0, 0, 0, 0, 108, 108, 84, 84, 68, 68, 68, 68, 68, 68, 0, 0,
  0, 0, 0, 0, 88, 88, 100, 100, 68, 68, 68, 68, 68, 68, 0, 0,
  0, 0, 0, 0, 56, 56, 68, 68, 68, 68, 68, 68, 56, 56, 0, 0,
  0, 0, 0, 0, 120, 120, 68, 68, 68, 68, 68, 68, 120, 120, 64, 64,
  0, 0, 0, 0, 60, 60, 68, 68, 68, 68, 68, 68, 60, 60, 4, 4,
  0, 0, 0, 0, 88, 88, 100, 100, 64, 64, 64, 64, 64, 64, 0, 0,
  0, 0, 0, 0, 60, 60, 64, 64, 56, 56, 4, 4, 120, 120, 0, 0,
  0, 0, 64, 64, 64, 64, 120, 120, 64, 64, 64, 64, 56, 56, 0, 0,
  0, 0, 0, 0, 68, 68, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  0, 0, 0, 0, 68, 68, 68, 68, 40, 40, 40, 40, 16, 16, 0, 0,
  0, 0, 0, 0, 68, 68, 68, 68, 68, 68, 84, 84, 108, 108, 0, 0,
  0, 0, 0, 0, 68, 68, 40, 40, 16, 16, 40, 40, 68, 68, 0, 0,
  0, 0, 0, 0, 68, 68, 68, 68, 68, 68, 40, 40, 16, 16, 96, 96,
  0, 0, 0, 0, 124, 124, 8, 8, 16, 16, 32, 32, 124, 124, 0, 0,
  0, 0, 8, 8, 16, 16, 16, 16, 32, 32, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  0, 0, 16, 16, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 16, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 50, 50, 76, 76, 0, 0, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  0, 0, 56, 56, 64, 64, 112, 112, 112, 112, 64, 64, 56, 56, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  0, 0, 0, 0, 0, 0, 0, 0, 96, 96, 32, 32, 64, 64, 0, 0,
  0, 0, 0, 0, 12, 12, 16, 16, 56, 56, 16, 16, 96, 96, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 108, 108, 36, 36, 72, 72, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 84, 0, 0,
  0, 0, 0, 0, 32, 32, 112, 112, 32, 32, 32, 32, 0, 0, 0, 0,
  0, 0, 0, 0, 32, 32, 112, 112, 32, 32, 112, 112, 32, 32, 0, 0,
  0, 0, 16, 16, 40, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 72, 72, 16, 16, 32, 32, 74, 74, 0, 0, 0, 0,
  40, 40, 16, 16, 60, 60, 64, 64, 56, 56, 4, 4, 120, 120, 0, 0,
  0, 0, 0, 0, 8, 8, 16, 16, 32, 32, 16, 16, 8, 8, 0, 0,
  0, 0, 62, 62, 72, 72, 78, 78, 72, 72, 72, 72, 62, 62, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  40, 40, 16, 16, 124, 124, 8, 8, 16, 16, 32, 32, 124, 124, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  0, 0, 6, 6, 4, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 96, 96, 32, 32, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 54, 54, 36, 36, 18, 18, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 108, 108, 36, 36, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 24, 24, 60, 60, 60, 60, 24, 24, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 56, 56, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 124, 124, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 20, 20, 40, 40, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 122, 122, 46, 46, 42, 42, 0, 0, 0, 0, 0, 0,
  40, 40, 16, 16, 60, 60, 64, 64, 56, 56, 4, 4, 120, 120, 0, 0,
  0, 0, 0, 0, 32, 32, 16, 16, 8, 8, 16, 16, 32, 32, 0, 0,
  0, 0, 0, 0, 0, 0, 60, 60, 74, 74, 76, 76, 62, 62, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  40, 40, 16, 16, 124, 124, 8, 8, 16, 16, 32, 32, 124, 124, 0, 0,
  0, 0, 40, 40, 0, 0, 68, 68, 40, 40, 16, 16, 16, 16, 16, 16,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  0, 0, 64, 64, 0, 0, 64, 64, 64, 64, 64, 64, 64, 64, 0, 0,
  0, 0, 16, 16, 60, 60, 80, 80, 80, 80, 80, 80, 60, 60, 16, 16,
  0, 0, 56, 56, 68, 68, 64, 64, 240, 240, 64, 64, 124, 124, 0, 0,
  0, 0, 0, 0, 68, 68, 56, 56, 40, 40, 56, 56, 68, 68, 0, 0,
  68, 68, 40, 40, 16, 16, 124, 124, 16, 16, 124, 124, 16, 16, 0, 0,
  16, 16, 16, 16, 16, 16, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16,
  28, 28, 32, 32, 120, 120, 68, 68, 56, 56, 8, 8, 112, 112, 0, 0,
  0, 0, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  60, 60, 66, 66, 153, 153, 161, 161, 161, 161, 153, 153, 66, 66, 60, 60,
  56, 56, 72, 72, 88, 88, 104, 104, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 20, 20, 40, 40, 80, 80, 40, 40, 20, 20, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 60, 60, 4, 4, 0, 0, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  60, 60, 66, 66, 185, 185, 165, 165, 185, 185, 165, 165, 66, 66, 60, 60,
  0, 0, 0, 0, 0, 0, 120, 120, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 48, 48, 72, 72, 72, 72, 48, 48, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 16, 16, 56, 56, 16, 16, 0, 0, 56, 56, 0, 0,
  48, 48, 72, 72, 16, 16, 32, 32, 120, 120, 0, 0, 0, 0, 0, 0,
  112, 112, 8, 8, 56, 56, 8, 8, 112, 112, 0, 0, 0, 0, 0, 0,
  4, 4, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 64, 64, 72, 72, 72, 72, 72, 72, 116, 116, 64, 64, 0, 0,
  0, 0, 58, 58, 122, 122, 122, 122, 58, 58, 10, 10, 10, 10, 0, 0,
  0, 0, 0, 0, 0, 0, 24, 24, 24, 24, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 4, 4, 8, 8,
  0, 0, 96, 96, 32, 32, 32, 32, 112, 112, 0, 0, 0, 0, 0, 0,
  0, 0, 48, 48, 72, 72, 72, 72, 48, 48, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 40, 40, 20, 20, 10, 10, 20, 20, 40, 40, 0, 0,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170, 85, 85, 170, 170,
  0, 0, 16, 16, 0, 0, 48, 48, 64, 64, 72, 72, 48, 48, 0, 0,
  32, 32, 16, 16, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  4, 4, 8, 8, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  24, 24, 36, 36, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  20, 20, 40, 40, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  0, 0, 36, 36, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  24, 24, 24, 24, 0, 0, 60, 60, 66, 66, 126, 126, 66, 66, 0, 0,
  0, 0, 30, 30, 24, 24, 40, 40, 62, 62, 72, 72, 78, 78, 0, 0,
  0, 0, 60, 60, 66, 66, 64, 64, 64, 64, 66, 66, 60, 60, 8, 8,
  32, 32, 16, 16, 0, 0, 126, 126, 64, 64, 124, 124, 64, 64, 126, 126,
  4, 4, 8, 8, 0, 0, 126, 126, 64, 64, 124, 124, 64, 64, 126, 126,
  20, 20, 40, 40, 0, 0, 126, 126, 64, 64, 124, 124, 64, 64, 126, 126,
  0, 0, 36, 36, 0, 0, 126, 126, 64, 64, 124, 124, 64, 64, 126, 126,
  32, 32, 16, 16, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 40, 40, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  0, 0, 40, 40, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  0, 0, 124, 124, 66, 66, 66, 66, 242, 242, 66, 66, 124, 124, 0, 0,
  20, 20, 40, 40, 0, 0, 98, 98, 82, 82, 74, 74, 70, 70, 0, 0,
  32, 32, 16, 16, 0, 0, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  4, 4, 8, 8, 0, 0, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  24, 24, 36, 36, 0, 0, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  20, 20, 40, 40, 0, 0, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 36, 36, 0, 0, 60, 60, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 0, 0, 68, 68, 40, 40, 16, 16, 40, 40, 68, 68, 0, 0,
  0, 0, 62, 62, 70, 70, 74, 74, 82, 82, 98, 98, 124, 124, 0, 0,
  32, 32, 16, 16, 66, 66, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  4, 4, 8, 8, 66, 66, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  24, 24, 36, 36, 0, 0, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  0, 0, 36, 36, 0, 0, 66, 66, 66, 66, 66, 66, 60, 60, 0, 0,
  4, 4, 8, 8, 68, 68, 40, 40, 16, 16, 16, 16, 16, 16, 0, 0,
  0, 0, 64, 64, 112, 112, 72, 72, 72, 72, 112, 112, 64, 64, 0, 0,
  0, 0, 120, 120, 68, 68, 72, 72, 68, 68, 68, 68, 88, 88, 0, 0,
  32, 32, 16, 16, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  4, 4, 8, 8, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  24, 24, 36, 36, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  20, 20, 40, 40, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  0, 0, 36, 36, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  24, 24, 24, 24, 0, 0, 60, 60, 68, 68, 76, 76, 52, 52, 0, 0,
  0, 0, 0, 0, 0, 0, 60, 60, 74, 74, 92, 92, 46, 46, 0, 0,
  0, 0, 0, 0, 60, 60, 64, 64, 64, 64, 64, 64, 60, 60, 8, 8,
  32, 32, 16, 16, 0, 0, 56, 56, 68, 68, 124, 124, 64, 64, 60, 60,
  4, 4, 8, 8, 0, 0, 56, 56, 68, 68, 124, 124, 64, 64, 60, 60,
  24, 24, 36, 36, 0, 0, 56, 56, 68, 68, 124, 124, 64, 64, 60, 60,
  0, 0, 36, 36, 0, 0, 56, 56, 68, 68, 124, 124, 64, 64, 60, 60,
  32, 32, 16, 16, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  8, 8, 16, 16, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 40, 40, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  0, 0, 40, 40, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  0, 0, 10, 10, 4, 4, 58, 58, 68, 68, 68, 68, 56, 56, 0, 0,
  20, 20, 40, 40, 0, 0, 88, 88, 100, 100, 68, 68, 68, 68, 0, 0,
  32, 32, 16, 16, 0, 0, 56, 56, 68, 68, 68, 68, 56, 56, 0, 0,
  8, 8, 16, 16, 0, 0, 56, 56, 68, 68, 68, 68, 56, 56, 0, 0,
  16, 16, 40, 40, 0, 0, 56, 56, 68, 68, 68, 68, 56, 56, 0, 0,
  20, 20, 40, 40, 0, 0, 56, 56, 68, 68, 68, 68, 56, 56, 0, 0,
  0, 0, 40, 40, 0, 0, 56, 56, 68, 68, 68, 68, 56, 56, 0, 0,
  0, 0, 0, 0, 16, 16, 0, 0, 124, 124, 0, 0, 16, 16, 0, 0,
  0, 0, 0, 0, 60, 60, 76, 76, 84, 84, 100, 100, 120, 120, 0, 0,
  32, 32, 16, 16, 0, 0, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  8, 8, 16, 16, 0, 0, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  16, 16, 40, 40, 0, 0, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  0, 0, 40, 40, 0, 0, 68, 68, 68, 68, 76, 76, 52, 52, 0, 0,
  8, 8, 16, 16, 0, 0, 68, 68, 68, 68, 40, 40, 16, 16, 96, 96,
  0, 0, 64, 64, 96, 96, 80, 80, 80, 80, 96, 96, 64, 64, 0, 0,
  0, 0, 40, 40, 0, 0, 68, 68, 68, 68, 40, 40, 16, 16, 96, 96
};
