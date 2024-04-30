#include "stack.h"
#include "heap_usage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
Element iftoe (int i, float f);
int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    char *line = malloc(100); 
    /* 
    Here we used malloc() and not myalloc() because as do not want to track 
    the memory usage of the line variable. We only want to track the heap
    usage of the stack.
    */

    /*
        Write code to initialize a stack and a time-performance variable
    */
    Stack *s = newStack();
    struct timeval t1, t2;
    double time_taken=0;
    double temp_time=0;
    int score = 0;
    float cg = 0;
    int i = 0;
    while(fgets(line, 100, fp) != NULL)
    {
        char *token;
        token = strtok(line, ",");
        score = atoi(token);
        token = strtok(NULL, ",");
        cg = atof(token);
        // printf("%d: Score: %d, CG: %f\n", i, score, cg);
        // You can uncomment the above line to print the values read from the file

        /*
            Write code to push the score and cg values into the stack while tracking the time and heap performance
        */
        gettimeofday(&t1, NULL);
        push(s, iftoe(score, cg));
        gettimeofday(&t2, NULL);
        temp_time = (t2.tv_sec - t1.tv_sec) * 1e6;
        temp_time = (temp_time + (t2.tv_usec - t1.tv_usec)) * 1e-6;
        time_taken += temp_time;
        i++;
    }
    fclose(fp);

    /*
        Write code to print the time taken and heap space utilized for pushing the values into the stack
    */
    printf("Pushing values took %f seconds to execute\n", time_taken);
    printf("Pushing values consumed %ld bytes to execute\n", heapMemoryAllocated);

    /*
        Write code to empty the stack and print and measure the time taken for the emptying process
    */
    gettimeofday(&t1, NULL);
    freeStack(s);
    gettimeofday(&t2, NULL);
    temp_time = (t2.tv_sec - t1.tv_sec) * 1e6;
    temp_time = (temp_time + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    time_taken += temp_time;
    /*
        Print the total time taken for the entire process and the maximum heap usage throughout the process
    */
    printf("Total %f seconds to execute\n", time_taken);
}
Element iftoe (int i, float f)
{
    Element e;
    e.int_value = i;
    e.float_value = f;
    return e;
}