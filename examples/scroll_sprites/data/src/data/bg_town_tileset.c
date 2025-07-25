#pragma bank 255

// Tileset: bg_town_tileset

#include "gbs_types.h"

BANKREF(bg_town_tileset)

const struct tileset_t bg_town_tileset = {
    .n_tiles = 87,
    .tiles = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xE6, 0x19, 0xC0, 0x7F, 0x80, 0x1F, 0xE0, 0xC4, 0x3B, 0xFF, 0x00, 0xFF, 0x00, 0x7F, 0x80,
        0x00, 0x67, 0x98, 0x03, 0xFE, 0x01, 0xF8, 0x07, 0x23, 0xDC, 0xFF, 0x00, 0xFF, 0x00, 0xFE, 0x01,
        0x00, 0xFC, 0x03, 0xF0, 0x07, 0xF0, 0x0F, 0xE0, 0x0F, 0xE0, 0x17, 0xE8, 0x03, 0xDC, 0x31, 0x8E,
        0x00, 0x3C, 0x81, 0x00, 0xC3, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0x3F, 0xC0, 0x0F, 0xE0, 0x0F, 0xF0, 0x07, 0xF0, 0x07, 0xE8, 0x17, 0xC0, 0x3B, 0x8C, 0x71,
        0x78, 0x07, 0x7E, 0x01, 0xBF, 0x40, 0x9F, 0x60, 0x87, 0x78, 0x80, 0x7F, 0x60, 0x9F, 0x1F, 0xE0,
        0x18, 0xE7, 0x3C, 0xC3, 0xFF, 0x00, 0xFF, 0x00, 0xC3, 0x3C, 0x00, 0xFF, 0x18, 0xE7, 0xE7, 0x18,
        0x1E, 0xE0, 0x7E, 0x80, 0xFD, 0x02, 0xF9, 0x06, 0xE1, 0x1E, 0x01, 0xFE, 0x06, 0xF9, 0xF8, 0x07,
        0x00, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xBD, 0xE7, 0xB8, 0xFF, 0xA0, 0xFF, 0xB0, 0xEF, 0xBF, 0xF0,
        0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFD, 0x07, 0xF8, 0xFF, 0x20, 0xFF, 0x70, 0xAF, 0xDF, 0x70,
        0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFD, 0x07, 0xFD, 0xFF, 0x25, 0xFF, 0x75, 0xAF, 0xDD, 0x77,
        0xAF, 0xFF, 0xA2, 0xFF, 0xA7, 0xFA, 0xBD, 0xE7, 0xB8, 0xFF, 0xA0, 0xFF, 0xB0, 0xEF, 0xBF, 0xF0,
        0x8F, 0xFF, 0x02, 0xFF, 0x07, 0xFA, 0xFD, 0x07, 0xF8, 0xFF, 0x20, 0xFF, 0x70, 0xAF, 0xDF, 0x70,
        0x00, 0xFF, 0xFF, 0xFF, 0x81, 0x81, 0xFF, 0xFF, 0xFE, 0xC3, 0x42, 0xC3, 0x42, 0xC3, 0xC3, 0x42,
        0xCD, 0xFF, 0x05, 0xFF, 0x05, 0xFF, 0xFD, 0x07, 0xFD, 0xFF, 0x25, 0xFF, 0x75, 0xAF, 0xDD, 0x77,
        0x00, 0xFF, 0x00, 0xFF, 0x03, 0xFF, 0x0F, 0xFF, 0x07, 0xFF, 0x3F, 0xFF, 0x1F, 0xFF, 0x3F, 0xFF,
        0x0F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xF0, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00, 0xFF, 0x00, 0xFF, 0xC0, 0xFF, 0xF0, 0xFF, 0xE0, 0xFF, 0xFC, 0xFF, 0xF8, 0xFF, 0xFC, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x0C, 0x04, 0x07, 0x3B, 0x3C, 0x16, 0x19, 0x24, 0x3F,
        0x00, 0x0F, 0x0F, 0x70, 0x7F, 0x80, 0xCE, 0x31, 0x31, 0xCE, 0x7B, 0x84, 0x31, 0xCE, 0x84, 0x7B,
        0x00, 0xF0, 0xF0, 0x0E, 0xFE, 0x01, 0x73, 0x8C, 0x8C, 0x73, 0xDE, 0x21, 0x8C, 0x73, 0x21, 0xDE,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x30, 0x20, 0xE0, 0xDC, 0x3C, 0x68, 0x98, 0x24, 0xFC,
        0xEF, 0xBF, 0xA2, 0xFF, 0xE7, 0xBA, 0xBD, 0xE7, 0xF8, 0xBF, 0xE0, 0xBF, 0xF5, 0xAA, 0xFF, 0xB0,
        0x8F, 0xFF, 0x02, 0xFF, 0x07, 0xFA, 0xFD, 0x07, 0xF8, 0xFF, 0x20, 0xFF, 0x75, 0xAA, 0xFF, 0x70,
        0xCF, 0xFD, 0x05, 0xFF, 0x07, 0xFD, 0xFD, 0x07, 0xFF, 0xFD, 0x27, 0xFD, 0x77, 0xAD, 0xFF, 0x75,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFE, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x51, 0x6E, 0xDB, 0xE4, 0x30, 0x3F, 0xC4, 0xFB, 0xAE, 0xD1, 0x68, 0x7F, 0x91, 0xEE, 0xBB, 0xC4,
        0x8E, 0x71, 0x8E, 0x71, 0x20, 0xDF, 0x71, 0x8E, 0xF3, 0x0C, 0x00, 0xFF, 0x0C, 0xF3, 0xDE, 0x21,
        0x71, 0x8E, 0x71, 0x8E, 0x04, 0xFB, 0x8E, 0x71, 0xCF, 0x30, 0x00, 0xFF, 0x30, 0xCF, 0x7B, 0x84,
        0x8A, 0x76, 0xDB, 0x27, 0x0C, 0xFC, 0x23, 0xDF, 0x75, 0x8B, 0x16, 0xFE, 0x89, 0x77, 0xDD, 0x23,
        0x7F, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0x81, 0xFF, 0x81, 0xFF, 0xFD, 0x83, 0x80, 0xFF, 0xEF, 0x90, 0xEF, 0x90, 0xD7, 0xB8,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x7D, 0x83, 0x00, 0xFF, 0xEF, 0x10, 0xEF, 0x10, 0xD7, 0x38,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x7D, 0x83, 0x01, 0xFF, 0xEF, 0x11, 0xEF, 0x11, 0xD7, 0x39,
        0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF,
        0x7B, 0x44, 0x73, 0x7F, 0x84, 0xFB, 0xBE, 0xC1, 0x7C, 0x73, 0x49, 0x7E, 0x43, 0x7C, 0x59, 0x66,
        0xDC, 0x23, 0x01, 0xFE, 0x21, 0xDE, 0xFB, 0x04, 0xF1, 0x8E, 0x55, 0xFB, 0x8E, 0x71, 0xDC, 0x23,
        0x3B, 0xC4, 0x80, 0x7F, 0x84, 0x7B, 0xDF, 0x20, 0x8F, 0x71, 0xAA, 0xDF, 0x71, 0x8E, 0x3B, 0xC4,
        0xDE, 0x22, 0xCE, 0xFE, 0x21, 0xDF, 0x7D, 0x83, 0x3E, 0xCE, 0x92, 0x7E, 0xC2, 0x3E, 0x9A, 0x66,
        0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF,
        0x80, 0xFF, 0xFE, 0x81, 0xFE, 0x81, 0xFD, 0x83, 0x80, 0xFF, 0xEF, 0x90, 0xEF, 0x90, 0xD7, 0xB8,
        0xFF, 0xFF, 0xA1, 0xDF, 0xC3, 0xBD, 0xFB, 0x81, 0xDF, 0x81, 0xBD, 0x81, 0xFB, 0x81, 0xFF, 0xFF,
        0x01, 0xFF, 0xFF, 0x01, 0xFF, 0x01, 0x7D, 0x83, 0x01, 0xFF, 0xEF, 0x11, 0xEF, 0x11, 0xD7, 0x39,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0xE0, 0x87, 0xE7, 0x8F, 0xEF, 0x8F, 0xE6,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xBF, 0x36, 0xFF, 0xB6, 0xFF, 0x3E,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7B, 0x73, 0xFF, 0xFB, 0xFF, 0xDB,
        0xFF, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x07, 0xE1, 0xC7, 0xF1, 0xE7, 0xF1, 0x67,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF,
        0xFC, 0xFF, 0xF8, 0xFF, 0xF8, 0xFF, 0xF8, 0xFF, 0xF0, 0xFF, 0x80, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0x39, 0x3F, 0x14, 0x1B, 0x17, 0x18, 0x12, 0x1D, 0x0F, 0x0F, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x8C, 0xFF, 0x21, 0xDE, 0xFF, 0x84, 0xBB, 0xCE, 0x71, 0xFF, 0x11, 0xFF, 0xFE, 0xFF, 0x0F, 0x0F,
        0x31, 0xFF, 0x84, 0x7B, 0xFF, 0x21, 0xDD, 0x73, 0x8E, 0xFF, 0x88, 0xFF, 0x7F, 0xFF, 0xF0, 0xF0,
        0x9C, 0xFC, 0x28, 0xD8, 0xE8, 0x18, 0x48, 0xB8, 0xF0, 0xF0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x3F, 0xFF, 0x1F, 0xFF, 0x1F, 0xFF, 0x1F, 0xFF, 0x0F, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0x00, 0xFF, 0xFE, 0x01, 0xFE, 0x01, 0x7D, 0x83, 0x00, 0xFF, 0xEF, 0x10, 0xEF, 0x10, 0xD7, 0x38,
        0x87, 0xE3, 0x8F, 0xEF, 0x8F, 0xE7, 0x87, 0xE0, 0xFF, 0xFF, 0x10, 0xFF, 0xEF, 0x10, 0xD7, 0x38,
        0xBF, 0x3E, 0xFF, 0xB6, 0xFF, 0x36, 0xBF, 0x00, 0xFF, 0xFF, 0x10, 0xFF, 0xEF, 0x10, 0xD7, 0x38,
        0xDF, 0xDB, 0xFF, 0xFB, 0xFF, 0x73, 0x7B, 0x00, 0xFF, 0xFF, 0x10, 0xFF, 0xEF, 0x10, 0xD7, 0x38,
        0xF1, 0xE7, 0xF1, 0xC7, 0xE1, 0x07, 0x81, 0x07, 0xFF, 0xFF, 0x10, 0xFF, 0xEF, 0x10, 0xD7, 0x38,
        0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF,
        0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF,
        0x0C, 0x0F, 0x0D, 0x0F, 0x0B, 0x0C, 0x09, 0x0E, 0x0B, 0x0C, 0x0B, 0x0C, 0x09, 0x0E, 0x09, 0x0E,
        0x30, 0xF0, 0x70, 0xF0, 0x90, 0x70, 0xD0, 0x30, 0x50, 0xB0, 0x50, 0xB0, 0xD0, 0x30, 0x90, 0x70,
        0x07, 0xFF, 0xF8, 0x1F, 0xE7, 0x3F, 0x5C, 0xFF, 0x54, 0xFF, 0xA4, 0xFF, 0xA4, 0xFF, 0xBF, 0xFF,
        0xE0, 0xFF, 0x1E, 0xF9, 0xE6, 0xFD, 0x9B, 0xFF, 0x9A, 0xFF, 0x95, 0xFF, 0x95, 0xFF, 0xFD, 0xFF,
        0x0B, 0x0C, 0x0A, 0x0D, 0x0B, 0x0C, 0x09, 0x0E, 0x0B, 0x0C, 0x0B, 0x0C, 0x09, 0x0E, 0x09, 0x0E,
        0xD0, 0x30, 0x90, 0x70, 0x90, 0x70, 0xD0, 0x30, 0x50, 0xB0, 0x50, 0xB0, 0xD0, 0x30, 0x90, 0x70,
        0x00, 0xFF, 0xB6, 0x49, 0x77, 0x88, 0x88, 0x77, 0x6D, 0x92, 0xC4, 0x3B, 0x80, 0xFF, 0x00, 0xFF,
        0x00, 0xC0, 0xD0, 0x30, 0x6E, 0x9E, 0xA6, 0x5A, 0x9A, 0x66, 0xDF, 0x25, 0x5B, 0xFF, 0x01, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x18, 0x66, 0x00, 0x3C, 0x18, 0x18, 0x3C, 0x3C,
        0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x80, 0xFF, 0xFE, 0x81, 0xFE, 0x81, 0xFD, 0x83, 0x80, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF,
        0x00, 0xFF, 0xFE, 0x01, 0xFE, 0x01, 0x7D, 0x83, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
        0x90, 0xFF, 0xAF, 0xEF, 0xB9, 0xFF, 0xA9, 0xFF, 0xA9, 0xFF, 0xBF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF,
        0x01, 0xFF, 0xFD, 0xFF, 0x25, 0xFF, 0x25, 0xFF, 0x25, 0xFF, 0xFD, 0xFF, 0x01, 0xFF, 0xFF, 0xFF,
        0x01, 0xFF, 0xFF, 0x01, 0xFF, 0x01, 0x7D, 0x83, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x24, 0x00, 0x45, 0x00, 0xAA, 0x45,
        0x00, 0x01, 0x01, 0x0E, 0x77, 0x78, 0xB0, 0xCF, 0x6B, 0x74, 0xFE, 0xA5, 0x5A, 0x7F, 0x80, 0xFF,
        0x0B, 0x0C, 0x0B, 0x0C, 0x0B, 0x0C, 0x0A, 0x0D, 0x3E, 0x31, 0xF6, 0xCD, 0xDD, 0xBB, 0xFF, 0xFF,
        0x50, 0xB0, 0x50, 0xB0, 0xD0, 0x30, 0x90, 0x70, 0xFC, 0x0C, 0x6F, 0xB3, 0xBB, 0xDD, 0xFF, 0xFF,
        0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xF6, 0x09, 0xAA, 0x5D, 0x5D, 0xFF, 0xDF, 0xFF,
        0x19, 0xFF, 0x84, 0xFF, 0x64, 0xFF, 0x9A, 0xFF, 0x4D, 0xFF, 0xBB, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF,
        0xFB, 0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF
    }
};
