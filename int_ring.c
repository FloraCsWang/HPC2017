#include <stdio.h>
#include <mpi.h>
#include "util.h"

int main(int argc, char *argv[])
{
    int rank, tag = 99;
    int N = atoi( argv[1]);
    int destination;
    int origin;
    
    timestamp_type time1, time2;
    get_timestamp(&time1);
    
   
    int message_in;
    int message_out;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    for (int i = 0; i < N; i++){
        
        if (rank == 0)
        {
            message_out = 0;
            destination = 1;
            origin = 5;
            MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
            MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
        } else  {
            message_in = message_out + rank;
            destination = (rank + 1) % 6;
            origin = rank -1;
            MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
            MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        }
        
        
    }
    
    MPI_Finalize();

    get_timestamp(&time2);
    double elapsed = timestamp_diff_in_seconds(time1,time2);
    printf("Time elapsed is %f seconds.\n", elapsed);
    
    int res = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 6 ; j++ ){
            res = res + j;
        }
    }
    
    if (message_in == res){
        printf("all processors seccessfully finished");
    }else{
        printf("not all processors sucessful");
        printf("res is %d ", message_in);
    }
    

    return 0;
}
