#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// typedef struct Matrix Matrix;
typedef struct Matrix{
    float rows;
    float cols;
    float **grid;
} Matrix;

Matrix *mx_create(float rows, float cols);

void mx_delete(Matrix *m);

uint32_t mx_rows(Matrix *m);

uint32_t mx_cols(Matrix *m);

void mx_print(Matrix *m, FILE *outfile);

Matrix* matrix_add(Matrix* A, Matrix* B);

Matrix* matrix_sub(Matrix* A, Matrix* B);

Matrix* matrix_mul(Matrix* A, Matrix* B);

Matrix* matrix_div(Matrix* A, Matrix* B);


