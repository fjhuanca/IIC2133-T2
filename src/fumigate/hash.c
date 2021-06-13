#include "hash.h"
#include<string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int find_hash(Image* original, int col, int row, long long* hashes){
    long long suma = 0;
    int valor;
    for (int j=0; j<col; j++){
        for (int i=row-1; i>=0; i--){
            int index = coords2index(original, i, j);
            if(original->pixels[index] == BLACK){
                valor = 1;
            }
            else{
                valor = 2;
            }
            long long pot = pow(RADIX, (row - i - 1));
            suma = suma + MOD ((pot * valor), PRIME);
        }
        hashes[j] = MOD(suma, PRIME);
        suma = 0;
    }
    return 0;
}


int change_pixels(Image* original, Image* pattern, int* tochange, int *n_tochange, int row, int col){
    int org_pixels[pattern->pixel_count];
    int counter = 0;
    bool equal = true;
    for (int i=0; i<pattern->height; i++){
        for (int j=0; j<pattern->width; j++){
            int org_index = coords2index(original, row + i, col + j);
            if(pattern->pixels[counter] != original->pixels[org_index]){
                bool equal = false;
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
                    tochange[*n_tochange] = org_index;
                    *n_tochange = *n_tochange + 1; 
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

int col_rolling(Image* original, Image* pattern, long long* original_hashes, int next_row){
    for (int j=0; j<original->width; j++){
        int org_index = coords2index(original, next_row, j);
        int value = original->pixels[org_index];
        if(original->pixels[org_index] == BLACK){
            value = 1;
        }
        else{
            value = 2;
        }
        original_hashes[j] = MOD(original_hashes[j] * RADIX + value, PRIME);
        long long pot = pow(RADIX, pattern->height);        

        org_index = coords2index(original, next_row - pattern->height, j);
        value = original->pixels[org_index];
        if(original->pixels[org_index] == BLACK){
            value = 1;
        }
        else{
            value = 2;
        }
        original_hashes[j] = MOD(original_hashes[j] - (pot * value), PRIME);
        original_hashes[j] = MOD(original_hashes[j], PRIME);
    }
    return 0;
}
int search(Image* original, Image* pattern){
    int tochange[original->pixel_count];
    int n_tochange = 0;
    long long pattern_hashes[pattern->width];
    long long original_hashes[original->width];
    long long pattern_hash_value = 0;
    long long original_hash_value = 0;
    int flag = 0;
    int col = 0;

    find_hash(original, original->width, pattern->height, original_hashes);
    find_hash(pattern, pattern->width, pattern->height, pattern_hashes);
    for (int i=0; i<pattern->width; i++){
        long long pot = pow(RADIX, pattern->width - i - 1);
        pattern_hash_value = pattern_hash_value + MOD(pot * pattern_hashes[i], PRIME);
    }
    pattern_hash_value = MOD(pattern_hash_value, PRIME);

    for (int i=pattern->height-1; i<original->height; i++){
        col = 0;
        original_hash_value = 0;

        for (int j=0; j<pattern->width; j++){
            long long pot = pow(RADIX, pattern->width - j - 1);
            original_hash_value = original_hash_value + MOD((pot * original_hashes[j]), PRIME);
        }
        original_hash_value = MOD(original_hash_value, PRIME);

        if (original_hash_value == pattern_hash_value){
            flag = change_pixels(original, pattern, tochange, &n_tochange, i + 1 - pattern->height, col);
        }
        for (int k=pattern->width; k<original->width; k++){
            
            original_hash_value = original_hash_value * RADIX + MOD(original_hashes[k], PRIME);
            long long pot = pow(RADIX, pattern->width);
            original_hash_value = original_hash_value - MOD(pot * original_hashes[k - pattern->width], PRIME);
            original_hash_value = MOD(original_hash_value, PRIME);
            col = col + 1;
            // printf("%lld, %lld\n", original_hash_value, pattern_hash_value);
            if (original_hash_value == pattern_hash_value){
                flag = change_pixels(original, pattern, tochange, &n_tochange, i + 1 - pattern->height, col);
            }
        }
        if (i + 1 < original->height){
            col_rolling(original, pattern, original_hashes, i + 1);
        }
    }
    for (int p=0; p<n_tochange; p++){
        original->pixels[tochange[p]] = GRAY;
    }   
    // printf("\n");
}


int coords2index(Image* matrix, int row, int col){
    return row * matrix->width + col;
}

int index2coords(Image* matrix, int* row, int* col, int index){
    *col = index % matrix->width;
    *row = index / matrix->width;
    return 0;
}