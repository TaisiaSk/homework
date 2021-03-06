#pragma once
#include "BmpStructures.h"

RgbImg read_rgb_img(char const filename[]);
void write_rgb_img(char const filename[], RgbImg const& img);
void print_rgb_img_info(char const filename[]);
RgbImg black_white(RgbImg const& img);
RgbImg blur(RgbImg const& img, const int arg);