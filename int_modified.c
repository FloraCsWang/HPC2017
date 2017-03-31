#include <stdio.h>
#include <mpi.h>
#include "util.h"

int main(int argc, char *argv[])
{
    int rank, tag = 99;
    int N = atoi(argv[1]);
    int destination;
    int origin;
    
    timestamp_type time1, time2;
    get_timestamp(&time1);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int Z = 2000000;
    int n;
    char *message_out = calloc(Z, sizeof(char));
    char *message_in = calloc(Z, sizeof(char));
  
    for(n = 0; n < Z; ++n)
        message_out[n] = 'h';
    
    for (int i = 0; i < N; i++){
   
        if (rank == 0)
        {
            //message_out = 0 ;
            destination = 1;
            origin = 5;
            MPI_Send(message_out, Z, MPI_CHAR, destination, tag, MPI_COMM_WORLD);
            MPI_Recv(message_in,  Z, MPI_CHAR, origin,      tag, MPI_COMM_WORLD, &status);
            printf("the final message is %s \n", message_in);
        } else  {
            
            destination = (rank + 1) % 6;
            origin = rank -1;
            MPI_Recv(message_in,  Z, MPI_CHAR, origin,      tag, MPI_COMM_WORLD, &status);
            message_out = message_in;
            MPI_Send(message_out, Z, MPI_CHAR, destination, tag, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    
    if (rank == 0){
        get_timestamp(&time2);
        double elapsed = timestamp_diff_in_seconds(time1,time2);
        printf("Time elapsed is %f seconds.\n", elapsed);
    }
    
    
    

    return 0;
}
