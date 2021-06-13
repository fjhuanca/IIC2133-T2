#pragma once

#include "../imagelib/image.h"

#define PRIME 997
#define RADIX 3

#define BLACK 0
#define WHITE 127
#define GRAY 64

/*
Definimos este operador para imitar el operador módulo de Python (%), de tal
manera que se comporte bien con números negativos también.
Basado en: https://www.lemoda.net/c/modulo-operator/
*/
#define MOD(a,b) ((((a)%(b))+(b))%(b))


void find_hash(Image* original, int col, int row, long* hashes);
int change_pixels(Image* original, Image* pattern, Image* out_image, int row, int col);
void col_rolling(Image* original, Image* pattern, long* original_hashes, int next_row);
void search(Image* original, Image* out_image, Image* pattern);
int coords2index(Image* image, int row, int col);
long power(long a, long n, long m);