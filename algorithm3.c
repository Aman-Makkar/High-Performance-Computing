#include <stdio.h>
#include "mpi.h"
#include "print_matrix.h"
#include "product_cc.h"
#include "matrix_declaration.h"

void algorithm(void)
{
    int comm_sz,        //number of processes
    my_rank,            //My process rank
    i, j, k,            //for looping purposes
    source,             // to be able to receive information from all the worker nodes.
    worker_nodes,       // the number of working nodes the work will be distributed to.
    dest;               //to be able to send work to worker nodes.
    double start, finish, global, duration;   //Variables to measure execution times.

    //Initialise MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Status status;

    //to set the number of worker nodes and keep 1 node free as a master node
    worker_nodes = comm_sz-1;

    start = MPI_Wtime();

    int aRows[R1];      //To save the rows from matrix A.
    int cRows[R1];      //To save the resultant matrix.

    //Scatter rows from Matrix A.
    MPI_Scatter(a, R1/worker_nodes, MPI_INT, aRows, R1/worker_nodes, MPI_INT, 0, MPI_COMM_WORLD);

    //Broadcast matrix B to all the processes.
    MPI_Bcast(b, R2 * C2, MPI_INT, 0, MPI_COMM_WORLD);

    //Carry out the multiplication.
    product_cc(a, b, c, cRows);

    //Gather data from all the processes and save it in matrix C.
    MPI_Gather(cRows, R1/worker_nodes, MPI_INT, c, R1/worker_nodes, MPI_INT, 0, MPI_COMM_WORLD);

    //Print the resultant matrix.
    if(my_rank == 1) {
        print_matrix(c);
    }
    //To measure run time of the algorithm.
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    duration = finish - start;
    MPI_Reduce(&duration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if(my_rank == 0)
        printf("The run time is: %f\n", global);

    MPI_Finalize();
}