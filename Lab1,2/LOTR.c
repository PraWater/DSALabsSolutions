#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("LOTR.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char str1[500];
    const char str2[] = "hobbit";
    const char s[2] = " ";
    int count = 0;
    while (fgets(str1, 500, fp))
    {
        char *token = strtok(str1, s);
        while (token != NULL)
        {
            if (strcasecmp(token, str2) == 0)
                ++count;
            token = strtok(NULL, s);
        }
    }
    fclose(fp);
    printf("No of hobbits : %d\n", count);
    return 0;
}
