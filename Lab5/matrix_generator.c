#include <stdio.h>
#include<stdlib.h>
#include<sys/time.h>

int main(void)
{
    // Asks user for n as input and creates a square matrix of size nxn populating it with random integers
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int matrix1[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix1[i][j] = rand() % 100;
        }
    }
    int matrix2[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix2[i][j] = rand() % 100;
        }
    }
    int matrix3[n][n];
    struct timeval t1, t2;
    double time_taken;
    gettimeofday(&t1, NULL);
    for (int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            matrix3[i][j] = matrix2[i][j] + matrix1[i][j];
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Row by row took %f seconds to execute\n", time_taken);
    gettimeofday(&t1, NULL);
    for (int j=0; j<n; j++)
        for(int i=0; i<n; i++)
            matrix3[i][j] = matrix2[i][j] + matrix1[i][j];
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Column by column took %f seconds to execute\n", time_taken);
    return 0;
}