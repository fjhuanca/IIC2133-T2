/* Author: Fernando Huanca
 * email: fjhuanca@uc.cl
 * Description: Citando un meme, solo Dios y yo sabemos como funciona este 
 * código, esperemos que ahora tú, ayudante que lo lee, también sepas que 
 * fue lo que quise hacer. Al menos funciona y, a mi parecer, eficientemente.
 */

#include "hash.h"
#include<string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


/* Función principal, recibe la imagen original, la de salida  y el patrón
   encuentra los hashes del patrón y de la imagen original y luego va iterando
   sobre el hash de la original encontrando coincidencias con el del patrón.
   Si encuentra una, revisa que realmente coincidan mediante la función
   change_pixels. Se basa en el algoritmo de Rabin-Karp para matrices.

   Fuentes:
   https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
   https://www.youtube.com/watch?v=BQ9E-2umSWc
   https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
 */

void search(Image* original, Image* out_image, Image* pattern){
    long pattern_hashes[pattern->width];
    long original_hashes[original->width];
    long pattern_hash_value = 0;
    long original_hash_value = 0;
    int col = 0;

    find_hash(original, original->width, pattern->height, original_hashes);
    find_hash(pattern, pattern->width, pattern->height, pattern_hashes);
    for (int i=0; i<pattern->width; i++){
        long pot = power(RADIX, pattern->width - i - 1, PRIME);
        pattern_hash_value = pattern_hash_value + pot * MOD(pattern_hashes[i], PRIME);
    }
    pattern_hash_value = MOD(pattern_hash_value, PRIME);

    for (int i=pattern->height-1; i<original->height; i++){
        col = 0;
        original_hash_value = 0;

        for (int j=0; j<pattern->width; j++){
            long pot = power(RADIX, pattern->width - j - 1, PRIME);
            original_hash_value = original_hash_value + pot * MOD( original_hashes[j], PRIME);
        }
        original_hash_value = MOD(original_hash_value, PRIME);

        if (original_hash_value == pattern_hash_value){
            change_pixels(original, out_image, pattern, i + 1 - pattern->height, col);
        }
        for (int k=pattern->width; k<original->width; k++){
            
            original_hash_value = original_hash_value * RADIX + MOD(original_hashes[k], PRIME);
            long pot = power(RADIX, pattern->width, PRIME);
            original_hash_value = original_hash_value - pot * MOD(original_hashes[k - pattern->width], PRIME);
            original_hash_value = MOD(original_hash_value, PRIME);
            col = col + 1;
            // printf("%lld, %lld\n", original_hash_value, pattern_hash_value);
            if (original_hash_value == pattern_hash_value){
                change_pixels(original, out_image, pattern, i + 1 - pattern->height, col);
            }
        }
        if (i + 1 < original->height){
            col_rolling(original, pattern, original_hashes, i + 1);
        }
    }  
    // printf("\n");
}

void find_hash(Image* original, int col, int row, long* hashes){
    long suma = 0;
    int valor;
    for (int j=0; j<col; j++){
        for (int i=row-1; i>=0; i--){
            int index = coords2index(original, i, j);
            if(original->pixels[index] == BLACK) valor = 1;
            else valor = 2;
            long pot = power(RADIX, (row - i - 1), PRIME);
            suma = suma + MOD ((pot * valor), PRIME);
        }
        hashes[j] = MOD(suma, PRIME);
        suma = 0;
    }
}


int change_pixels(Image* original, Image* out_image, Image* pattern, int row, int col){
    int counter = 0;
    bool equal = true;
    for (int i=0; i<pattern->height; i++){
        for (int j=0; j<pattern->width; j++){
            int org_index = coords2index(original, row + i, col + j);
            if(pattern->pixels[counter] != original->pixels[org_index]){
                return 0;
            };
            counter = counter + 1;
        }
    }

    if (equal){
        counter = 0;
        for (int i=0; i<pattern->height; i++){
            for (int j=0; j<pattern->width; j++){
                int org_index = coords2index(original, row + i, col +j);
                if (original->pixels[org_index] == BLACK){  
                    out_image->pixels[org_index] = GRAY;
                }
                counter = counter + 1;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

void col_rolling(Image* original, Image* pattern, long* original_hashes, int next_row){
    for (int j=0; j<original->width; j++){
        int org_index = coords2index(original, next_row, j);
        int value = original->pixels[org_index];
        if(original->pixels[org_index] == BLACK) value = 1;
        else value = 2;
        original_hashes[j] = MOD(original_hashes[j] * RADIX + value, PRIME);
        long pot = power(RADIX, pattern->height, PRIME);        

        org_index = coords2index(original, next_row - pattern->height, j);
        value = original->pixels[org_index];
        if(original->pixels[org_index] == BLACK) value = 1;
        else value = 2;
        original_hashes[j] = MOD(original_hashes[j] - (pot * value), PRIME);
        original_hashes[j] = MOD(original_hashes[j], PRIME);
    }
}


//Función que retorna el índice del pixel, dada una fila y una columna.
int coords2index(Image* matrix, int row, int col){
    return row * matrix->width + col;
}


/*
Función obtenida de https://www.geeksforgeeks.org/ para obtener el módulo de
 la potencia de a a la n en base a m.
 Basado de:
 https://www.geeksforgeeks.org/find-power-power-mod-prime/
 https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
*/
long power(long a, long n, long m){
  if(n == 0) return 1;
  if(n == 1) return a%m;

  long pow2 = power(a, n/2, m);
  if(n&1) return ((a%m)*(pow2)%m * (pow2)%m)%m;
  else return ((pow2)%m * (pow2)%m)%m;
}