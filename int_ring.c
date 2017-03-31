#include <stdio.h>
#include <mpi.h>
#include "util.h"


int main(int argc, char *argv[])
{
    int rank, tag = 99;
    int N = atoi( argv[1]);
    
    
    
    timestamp_type time1, time2;
    get_timestamp(&time1);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    
    int message_out = 0;
    int message_in;
    for (int i = 0; i < N; i++){
        //printf("iteratr %d\n", i);
                int destination;
        int origin;
        if (rank == 0)
        {
            destination = 1;
            //printf("data send is %d \n", message_out);
            MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
            
        } else  {
            destination = (rank + 1) % 6;
            origin = rank -1;
            MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
            //printf("receiving data for rank %d\n", rank);
            //printf("data received is %d \n", message_in);
            message_out = message_in + rank;
            //printf("data send is %d \n", message_out);
            MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        }
        
        if (rank == 0){
            origin = 5;
            MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
            printf("final messsage is %d\n ", message_in);
        }
        
        
        
    }
    MPI_Finalize();
    
   
    if (rank == 0){
        get_timestamp(&time2);
        double elapsed = timestamp_diff_in_seconds(time1,time2);
        printf("Time elapsed is %f seconds.\n", elapsed);
        
        int res = 0;
        for (int j = 0; j < 6 ; j++ ){
                res = res + j;
        }
        
        
        if (message_in == res){
            printf("All processors seccessfully finished\n");
        }else{
            printf("not all processors sucessful\n");
            printf("res is %d ", message_in);
        }

        
    }
     
    
    
    
    return 0;
}
