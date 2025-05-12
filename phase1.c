#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 40
#define MEMORY_ROWS 100
#define MEMORY_COLS 4

char buffer[BUFFER_SIZE];
char Memory[MEMORY_ROWS][MEMORY_COLS];
char IR[MEMORY_COLS];
char R[MEMORY_COLS];
int16_t IC;
int SI;
int8_t C;
FILE *infile, *outfile;

void init();
void resetBuffer();
void masterMode();
void READ();
void WRITE();
void TERMINATE();
void LOAD();
void MOSstartexe();
void executeUserProgram();
void displayMemoryAndRegister();

void displayMemoryAndRegister()
{
    int i, j;
    printf("Memory:\n");
    for (i = 0; i < MEMORY_ROWS; i++)
    {
        printf("M[%d]: ", i);
        int empty = 1;
        for (j = 0; j < MEMORY_COLS; j++)
        {
            if (Memory[i][j] != '\0')
            {
                putchar(Memory[i][j]);
                empty = 0;
            }
        }
        if (empty)
            printf("****");
        printf("\n");
    }
    printf("\nIC: %d, C: %d, SI: %d\n", IC, C, SI);
}

void init()
{
    memset(buffer, '\0', BUFFER_SIZE); // memset- c library to fill a block of memory with a particualr value
    memset(Memory, '\0', MEMORY_ROWS * MEMORY_COLS);
    memset(IR, '\0', MEMORY_COLS);
    memset(R, '\0', MEMORY_COLS);
    IC = 0;
    C = 1;
    SI = 0;
}

void resetBuffer()
{
    memset(buffer, '\0', BUFFER_SIZE);
}

void masterMode()
{
    switch (SI)
    {
    case 1:
        READ();
        break;
    case 2:
        WRITE();
        break;
    case 3:
        TERMINATE();
        break;
    }
    SI = 0;
}

// systemcall implem...
void READ()
{
    if (fgets(buffer, BUFFER_SIZE, infile))
    {
        int buff = 0, mem_ptr = (IR[2] - '0') * 10;
        while (buff < BUFFER_SIZE && buffer[buff] != '\0')
        {
            for (int i = 0; i < MEMORY_COLS; i++)
            {
                Memory[mem_ptr][i] = buffer[buff];
                buff++;
            }
            mem_ptr++;
        }
    }
    resetBuffer();
}

void WRITE()
{
    outfile = fopen("output.txt", "a");
    for (int i = (IR[2] - '0') * 10; i < (IR[2] - '0' + 1) * 10; i++)
    {
        for (int j = 0; j < MEMORY_COLS; j++)
        {
            if (Memory[i][j] != '\0')
            {
                fputc(Memory[i][j], outfile);
            }
        }
    }
    fclose(outfile);
}

void TERMINATE()
{
    outfile = fopen("output.txt", "a");
    fputs("\n\n", outfile);
    fclose(outfile);
}

void LOAD()
{
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, infile))
    {
        if (strncmp(line, "$AMJ", 4) == 0)
        {
            init();
        }
        else if (strncmp(line, "$DTA", 4) == 0)
        {
            resetBuffer();
            MOSstartexe();
        }
        else if (strncmp(line, "$END", 4) == 0)
        {
            if (feof(infile))
            {
                return;
            }
        }
        else
        {
            int len = strlen(line);
            resetBuffer();
            memcpy(buffer, line, len);
            int buff = 0;
            while (buff < BUFFER_SIZE && buffer[buff] != '\0')
            {
                for (int j = 0; j < MEMORY_COLS; j++)
                {
                    if (buffer[buff] == 'H')
                    {
                        Memory[IC][j] = 'H';
                        buff++;
                        break;
                    }
                    Memory[IC][j] = buffer[buff];
                    buff++;
                }
                IC++;
            }
        }
    }
    fclose(infile);
}

void MOSstartexe()
{
    IC = 0;
    executeUserProgram();
}

void executeUserProgram()
{
    while (IC < 99 && Memory[IC][0] != '\0')
    {
        memcpy(IR, Memory[IC], MEMORY_COLS);
        IC++;
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            masterMode();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            masterMode();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            masterMode();
            return;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            memcpy(R, Memory[(IR[2] - '0') * 10 + (IR[3] - '0')], MEMORY_COLS);
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            memcpy(Memory[(IR[2] - '0') * 10 + (IR[3] - '0')], R, MEMORY_COLS);
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            C = memcmp(Memory[(IR[2] - '0') * 10 + (IR[3] - '0')], R, MEMORY_COLS) == 0;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C)
            {
                IC = (IR[2] - '0') * 10 + (IR[3] - '0');
            }
        }
    }
}

int main()
{
    infile = fopen("input.txt", "r");
    if (!infile)
    {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    init();
    LOAD();
    printf("\nAfter execution of program\n");
    displayMemoryAndRegister();
    return 0;
}