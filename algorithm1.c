#include <stdio.h>
#include "mpi.h"
#include "print_matrix.h"
#include "product_pp.h"
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
    worker_nodes = comm_sz - 1;

    //Send messages to the worker nodes.
    //Alg1
    start = MPI_Wtime();

    if (my_rank == 0) {
        //Send messages to worker nodes to carry out the calculations.
        for (dest = 1; dest <= worker_nodes; dest++) {
            MPI_Send(&a, R1 * C1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&b, R2 * C2, MPI_INT, dest, 1, MPI_COMM_WORLD);
        }

        //Receive the completed multiplication from the worker nodes
        for (i = 1; i <= worker_nodes; i++) {
            source = i;
            MPI_Recv(&c, R1 * C2, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
        }
        //print the resultant matrix
        print_matrix(c);
    } else {
        //Receive messages from the master node to carry out the multiplication.
        MPI_Recv(&a, R1 * C1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, R2 * C2, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        //Carry out the multiplication.
        product_pp(a, b, c);

        //Send the multiplication to the master node.
        MPI_Send(&c, R1 * C2, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
    //To measure run time of the algorithm.
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    duration = finish - start;
    MPI_Reduce(&duration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (my_rank == 0)
        printf("The run time is: %f\n", global);

    MPI_Finalize();
}
