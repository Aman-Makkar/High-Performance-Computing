//
// Created by Aman on 31/12/2020.
//
//To print the resultant matrix.

#include <stdio.h>

#define R1 10
#define C2 3

void print_matrix(int c[R1][C2])
{
    int i, j;

    printf("The resultant matrix is:\n");
    for(i = 0; i < R1; i++)
    {
        for(j = 0; j < C2; j++)
        {
            printf("%4d   ", c[i][j]);
        }
        printf("\n");
    }
}
