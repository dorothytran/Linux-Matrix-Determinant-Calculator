/*
SYSC4001 Assignment 1
Dorothy Tran 101141902 
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "DET.h"

int main() 
{
    // Initialization
    int shmid, i, j;
    int value = 0;
    pid_t pid;
    struct timeval start, end;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_matrix;
    srand((unsigned int)getpid());

    // Create shared memory
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) 
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Make shared memory accessible
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) 
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nMemory attached at %X\n", (int)shared_memory);
    shared_matrix = (struct shared_use_st *)shared_memory;

    // Mandatory Test Data
    printf("\nMatrix Input Data: \n");
    int m[MATRIX_SIZE][MATRIX_SIZE] = 
    {
        {20, 20, 50},
        {10, 6, 70},
        {40, 3, 2}
    };
    
    // Save and print matrix into shared memory
    for(i = 0; i < MATRIX_SIZE; i++) 
    {
        for(j = 0; j < MATRIX_SIZE; j++)
        {
            shared_matrix->M[i][j] = m[i][j];
            printf("%3d\t", shared_matrix->M[i][j]);
        }
        printf("\n");
    }
    
    // Determining largest integer of the matrix
    for(i = 0; i < MATRIX_SIZE; i++)
    {
        for(int j = 0; j < MATRIX_SIZE; j++) 
        {
            if(shared_matrix->M[i][j] > value) {
                value = shared_matrix->M[i][j];
            }
        }
        shared_matrix->L[i] = value;
    }

    // Fork 3 Child Processes from a Parent Process
    for(i = 0; i < MATRIX_SIZE; i++)
    {
        gettimeofday(&start,NULL);
        pid = fork();
        switch(pid)
        {
        case -1:
            perror("Fork Failed");
            exit(1);
        case 0: // Child Process
            calculate_determinant(shared_matrix, i);
            gettimeofday(&end,NULL);
            printf("Elapsed Time: %ld micro sec\n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec)-(start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));
            exit(0);
        default:
            break;
        }
    }
    
    // Wait for all child processes to finish
    for(i = 0; i < MATRIX_SIZE; i++) 
    {
        wait(NULL);
    }

    printf("\nCalculated Matrix Determinant = %d\n", shared_matrix->matrix_det);
    printf("Largest Integer of the Matrix = %d\n", value);

    if (shmdt(shared_memory) == -1) 
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1) 
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void calculate_determinant(struct shared_use_st *shared_matrix, int child_num)
{
    int value = 0;
    printf("\nChild Process: working with element %d of D\n", child_num + 1);
    
    // Store the results into the array D[j] for each Gaussian Elimination calculation for each Child Process running in shared memory
    if(child_num == 0) // Child Process 1
    { 
        shared_matrix->D[0] = shared_matrix->M[0][0] * ((shared_matrix->M[1][1] * shared_matrix->M[2][2]) - (shared_matrix->M[1][2] * shared_matrix->M[2][1]));
    }
    else if(child_num == 1) // Child Process 2
    {
        shared_matrix->D[1] = shared_matrix->M[0][1] * ((shared_matrix->M[1][0] * shared_matrix->M[2][2]) - (shared_matrix->M[2][0] * shared_matrix->M[1][2]));
    }
    else if(child_num == 2) // Child Process 3
    {
        shared_matrix->D[2] = shared_matrix->M[0][2] * ((shared_matrix->M[1][0] * shared_matrix->M[2][1]) - (shared_matrix->M[2][0] * shared_matrix->M[1][1]));
    }
    printf("Calculation %d = %d\n", child_num + 1, shared_matrix->D[child_num]);

    // Save determinant matrix value into shared memory
    shared_matrix->matrix_det = shared_matrix->D[0] - shared_matrix->D[1] + shared_matrix->D[2];

    // Determining the largest integer of each row in a given matrix
    for(int j = 0; j < MATRIX_SIZE; j++) 
    {
        if(shared_matrix->M[child_num][j] > value)
        {
            value = shared_matrix->M[child_num][j];
        }
        // Store in shared memory
        shared_matrix->L[child_num] = value;
    }
    printf("Largest Integer in Row %d = %d\n", child_num + 1, shared_matrix->L[child_num]);
}