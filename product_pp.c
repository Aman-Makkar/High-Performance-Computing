//
// Created by Aman on 31/12/2020.
//
//To carry out multiplication on the Matrix A and Vector B, for point-point communications,
//i.e Algorithm 1 and 2.
#define R1 10
#define C1 8
#define R2 8
#define C2 3

void product_pp(int a[R1][C1], int b[R2][C2], int c[R1][C2])
{
    int i, j, k;

    for (i = 0; i < 10; i++) {
        for (k = 0; k < 3; k++) {
            c[i][k] = 0;
            for (j = 0; j < 8; j++) {
                c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        }
    }
}

