#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 
#include <assert.h>

#include "matrix.h"

/*
struct Matrix{
    float rows;
    float cols;
    float **grid;
} Matrix;
*/

Matrix *mx_create(float rows, float cols){
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    assert(m);
    m->rows = rows;
    m->cols = cols;
    m->grid = (float **) calloc(rows, sizeof(float *));
    for(uint32_t i = 0; i < rows; i++){
        m->grid[i] = (float *) calloc(cols, sizeof(float));
    }
    
    return m;
}

void mx_delete(Matrix *m){
    for(int i = 0; i < m->rows; i++){
        free(m->grid[i]);
    }
    free(m->grid);
    free(m);
}

// return the number of columns in the Matrix
uint32_t mx_rows(Matrix *m) {
    return m->rows;
}

// return the number of row in the Matrix
uint32_t mx_cols(Matrix *m) {
    return  m->cols;
}

// print each element in the matrix, separated by a space.
// m->grid[r][c] accesses the value at each row r and column c in the matrix m.
void mx_print(Matrix *m, FILE *outfile){
    //printf("%s  %s\n ", "\u2554", "\u2557");
    
    for (uint32_t r = 0; r < m->rows; r++){
        //printf("| ");
        printf("[ ");
        //printf("%s ", "\u2551");
        for(uint32_t c = 0; c < m->cols; c++){
            printf("%10.4f ", m->grid[r][c]);
        }
        //printf("|\n");
        printf("]\n");
        //printf("%s\n", "\u2551");
    }    
    fprintf(outfile, "\n");
}

Matrix* matrix_add(Matrix* A, Matrix* B) {
    Matrix* result = mx_create(A->rows, A->cols); 
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < A->cols; j++) {
            result->grid[i][j] = A->grid[i][j] + B->grid[i][j];
        }
    }    
    return result;
}

Matrix* matrix_sub(Matrix* A, Matrix* B){
    Matrix* result = mx_create(A->rows, A->cols); 
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < A->cols; j++) {
            result->grid[i][j] = A->grid[i][j] - B->grid[i][j];
        }
    }    
    return result;
}

Matrix* matrix_mul(Matrix* A, Matrix* B){
    Matrix* result = mx_create(A->rows, A->cols); 
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < A->cols; j++) {
            result->grid[i][j] = A->grid[i][j] * B->grid[i][j];
        }
    }    
    return result;
}

