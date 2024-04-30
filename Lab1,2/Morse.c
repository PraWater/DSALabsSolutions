#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *morse[36];
    morse[0] = ".-";
    morse[1] = "-...";
    morse[2] = "-.-.";
    morse[3] = "-..";
    morse[4] = ".";
    morse[5] = "..-.";
    morse[6] = "--.";
    morse[7] = "....";
    morse[8] = "..";
    morse[9] = ".---";
    morse[10] = "-.-";
    morse[11] = ".-..";
    morse[12] = "--";
    morse[13] = "-.";
    morse[14] = "---";
    morse[15] = ".--.";
    morse[16] = "--.-";
    morse[17] = ".-.";
    morse[18] = "...";
    morse[19] = "-";
    morse[20] = "..-";
    morse[21] = "...-";
    morse[22] = ".--";
    morse[23] = "-..-";
    morse[24] = "-.--";
    morse[25] = "--..";
    morse[26] = "-----";
    morse[27] = ".----";
    morse[28] = "..---";
    morse[29] = "...--";
    morse[30] = "....-";
    morse[31] = ".....";
    morse[32] = "-....";
    morse[33] = "--...";
    morse[34] = "---..";
    morse[35] = "----.";
    FILE *fp = fopen("msg.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    const char space[2] = " ";
    char token[50];
    for (int i = 0; i < 6; ++i)
    {
        fscanf(fp, "%[^/]/", token);
        char *tok = strtok(token, space);
        while (tok != NULL)
        {
            for (int i = 0; i < 36; ++i)
            {
                if (strcmp(tok, morse[i]) == 0)
                {
                    if (i < 26)
                        printf("%c", 'A' + i);
                    else
                        printf("%c", '0' + i - 26);
                    break;
                }
            }
            tok = strtok(NULL, space);
        }
        printf(" ");
    }
    printf("\n");
    fclose(fp);
    return 0;
}