#pragma once

#include "../imagelib/image.h"

#define PRIME 2
#define RADIX 3

#define BLACK 0
#define WHITE 127
#define GRAY 64

#define MOD(a,b) ((((a)%(b))+(b))%(b))

int find_hash(Image* original, int col, int row, long long* hashes);
int change_pixels(Image* original, Image* pattern, int* to_change, int *n_tochange, int row, int col);
int col_rolling(Image* original, Image* pattern, long long* original_hashes, int next_row);
int search(Image* original, Image* pattern);
int coords2index(Image* image, int row, int col);
int index2coords(Image* image, int* row, int* col, int index);
long long power(long long a,long long n,long long m);