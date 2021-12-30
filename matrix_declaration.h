#ifndef ALG1_MATRIX_DECLARATION_H
#define ALG1_MATRIX_DECLARATION_H
//Matrix A, Vector B and resultant Matrix C declarations.

int a[R1][C1] = {
        {1, 2, 0, 0, 3, 0, 0, 4},
        {5, 6, 7, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 9, 0},
        {0, 10, 11, 12, 0, 0, 0, 0},
        {0, 0, 13, 14, 0, 0, 0, 0},
        {15, 0, 0, 0, 16, 17, 0, 18},
        {19, 0, 0, 0, 20, 0, 0, 21},
        {0, 0, 0, 0, 22, 23, 24, 0},
        {0, 0, 0, 0, 0, 25, 26, 0},
        {27, 0, 0, 0, 28, 0, 0, 29}
};

int b[R2][C2] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18},
        {19, 20, 21},
        {22, 23, 24}
};

int c[R1][C2];          //Resultant array
#endif //ALG1_MATRIX_DECLARATION_H