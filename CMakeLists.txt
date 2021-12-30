cmake_minimum_required(VERSION 3.17)
project(alg1 C)

set(CMAKE_C_STANDARD 11)

add_executable(alg1 main.c matrix_declaration.h product_pp.h print_matrix.h print_matrix.c product_pp.c algorithm.c algorithm.h)