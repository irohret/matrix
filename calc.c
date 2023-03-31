
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>

// headers
#include "matrix.h"

#define OPTIONS "asmhi:o:"


void print_help(void){
    fprintf(stderr, 
    "SYNOPSIS\n"
    "    A look at Matrices\n"
    "\n"
    "USAGE\n"
    "    ./matrix a:s:m:d:i:o:n:h\n"
    "\n"
    "OPTIONS\n"
    "    -h             Display program help and usage.\n"
    "    -a             Create n x n addition matrix\n"
    "    -s             Create n x n subtraction matrix\n"
    "    -m             Create n x n multiplication matrix\n"
    "    -n {number}    Number of matrix to compute [default: 2]\n"
    "    -i {file}      Input file [default: stdin]\n"
    "    -o {file}      Output file [default: stdout\n");
return;
}

// Read in matrix A

void matrix_A(Matrix *A){
    printf("Enter the values for matrix A:\n");
    for (uint32_t i = 0; i < mx_rows(A); i++) {
        for (uint32_t j = 0; j < mx_cols(A); j++) {
            scanf("%f", &(A->grid[i][j]));
        }
    }
}

/*
void matrix_A(Matrix *A, FILE *input){
    printf("Enter the values for matrix A:\n");
    for (uint32_t i = 0; i < mx_rows(A); i++) {
        for (uint32_t j = 0; j < mx_cols(A); j++) {
            fscanf(input, "%f", &(A->grid[i][j]));
        }
    }
}*/


// Read in matrix B

void matrix_B(Matrix *B){
    printf("Enter the values for matrix B:\n");
    for (uint32_t i = 0; i < mx_rows(B); i++) {
        for (uint32_t j = 0; j < mx_cols(B); j++) {
            scanf("%f", &(B->grid[i][j]));
        }
    }
}

/*
void matrix_B(Matrix *B, FILE *input){
    printf("Enter the values for matrix B:\n");
    for (uint32_t i = 0; i < mx_rows(B); i++) {
        for (uint32_t j = 0; j < mx_cols(B); j++) {
            fscanf(input, "%f", &(B->grid[i][j]));
        }
    }
}*/


void read_matrix(Matrix *A, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }
    for (uint32_t i = 0; i < mx_rows(A); i++) {
        for (uint32_t j = 0; j < mx_cols(A); j++) {
            fscanf(file, "%f", &(A->grid[i][j]));
        }
    }
    fclose(file);
}

int main(int argc, char **argv){
    bool add = false, sub = false, mul = false; 

    uint32_t rows = 0, cols = 0;
    int opt = 0;
    int infile = STDIN_FILENO; // 0
    int outfile = STDOUT_FILENO; // 1
    //bool read_from_stdin = false; // flag to check if the user wants to read from stdin


    while ((opt = getopt(argc, argv, "asmhi:o:")) != -1){
        switch(opt){
            case 'a':
                add = true;              
                break;
            case 's':
                sub = true;
                break;
            case 'm':
                mul = true;
                break;
             case 'i':
                //read_from_stdin = true; // user wants to read from a file
                // O_RDONLY is read only
                if ((infile = open(optarg, O_RDONLY)) == -1) {
                    fprintf(stderr, "Failed to open %s.\n", optarg);
                    close(outfile);
                    exit(1);
                 }

                break;
            case 'o':
                /*
                O_WRONLY = write only 
                O_CREAT = create if it doesn't exist 
                O_TRUNC = truncated (shorted) if it exists
                */
                if ((outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC)) == -1) {
                    fprintf(stderr, "Failed to open %s.\n", optarg);
                    close(infile);
                    exit(1);
                }

                break;
            case 'h':
                print_help();
                break;
            default:
                print_help();
                return -1;
            }    
    }
    
    
    
      // read in matrix A and B
      printf("Enter the number of rows and columns for the matrices: ");
      //scanf("%" SCNu32 " %" SCNu32, &rows, &cols); // use SCNu32 to read uint32_t
      if (scanf("%" SCNu32 " %" SCNu32, &rows, &cols) != 2 || rows == 0 || cols == 0){
          fprintf(stderr, "Invalid matrix size.\n");
    
          return 1;
      }
      
      
     // create matrix A and B
      Matrix *A = mx_create(rows, cols);
      Matrix *B = mx_create(rows, cols);
      
      
      // read in matrix A and B
      matrix_A(A);
      matrix_B(B);
      
      // Add the matrices and print the result
      if(add){
          printf("Sum of matrix A + B:\n");
          Matrix *C = matrix_add(A, B);
          mx_print(C, stdout);
          mx_delete(C);
      }
      
      // sub the matrices and print the result
      if(sub){
          printf("Sum of matrix A - B:\n");
          Matrix *C = matrix_sub(A, B);
          mx_print(C, stdout);
          mx_delete(C);
      }
      
      // mul the matrices and print the result
      if(mul){
          printf("Sum of matrix A * B:\n");
          Matrix *C = matrix_mul(A, B);
          mx_print(C, stdout);
          mx_delete(C);
      }
    

    mx_delete(A);
    mx_delete(B);
    
   
    return 0;
}
