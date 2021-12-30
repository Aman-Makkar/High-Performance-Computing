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
    //For MPI wait, needed to have the next process wait until the previous one is completed.
    MPI_Request request[6];

    //to set the number of worker nodes and keep 1 node free as a master node
    worker_nodes = comm_sz - 1;

    start = MPI_Wtime();

    if (my_rank == 0) {
        //Send messages to worker nodes to carry out the calculations.
        for (dest = 1; dest <= worker_nodes; dest++) {
            MPI_Isend(&a, R1 * C1, MPI_INT, dest, 1, MPI_COMM_WORLD, &request[0]);
            MPI_Isend(&b, R2 * C2, MPI_INT, dest, 2, MPI_COMM_WORLD, &request[1]);

            //Wait for the messages to be completed.
            MPI_Wait(&request[0], &status);
            MPI_Wait(&request[1], &status);
        }
        //Receive the completed multiplication from worker nodes.
        for (i = 1; i <= worker_nodes; i++) {
            MPI_Irecv(&c, R1 * C2, MPI_INT, i, 3, MPI_COMM_WORLD, &request[5]);
            //Wait for the messages to be completed.
            MPI_Wait(&request[5], &status);
        }
        //Print the resultant matrix.
        print_matrix(c);
    }

    if (my_rank > 0) {
        //Receive messages from the master node to carry out the multiplication.
        MPI_Irecv(&a, R1 * C1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request[2]);
        MPI_Irecv(&b, R2 * C2, MPI_INT, 0, 2, MPI_COMM_WORLD, &request[3]);

        //Wait for the messages to be completed.
        MPI_Wait(&request[2], &status);
        MPI_Wait(&request[3], &status);

        //Carry out the multiplication.
        product_pp(a, b, c);

        //Send the multiplication to master node.
        MPI_Isend(&c, R1 * C2, MPI_INT, 0, 3, MPI_COMM_WORLD, &request[4]);

        //Wait for the messages to be completed.
        MPI_Wait(&request[4], &status);
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
