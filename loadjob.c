#include <stdio.h>
#include <string.h>

#define ROWS 100
#define COLS 4
#define DEFAULT_CHAR '-'

// Function to initialize memory with default character
void initializeMemory(char memory[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            memory[i][j] = DEFAULT_CHAR;
        }
    }
}

// Function to display memory contents
void displayMemory(char memory[ROWS][COLS])
{
    printf("Memory Contents:\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%02d: ", i);
        for (int j = 0; j < COLS; j++)
        {
            printf("%c ", memory[i][j]);
        }
        printf("\n");
    }
}

// Function to load job into memory from input file
void loadJob(char memory[ROWS][COLS], const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    char line[256];
    int memIndex = 0;
    int loadingInstructions = 0;
    int loadingData = 0;

    while (fgets(line, sizeof(line), fp))
    {
        // Remove trailing newline
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "$AMJ") == 0)
        {
            // Start of job instructions
            loadingInstructions = 1;
            loadingData = 0;
            memIndex = 0;
            continue;
        }
        else if (strcmp(line, "$DTA") == 0)
        {
            // Start of data section
            loadingInstructions = 0;
            loadingData = 1;
            continue;
        }
        else if (strcmp(line, "$END") == 0)
        {
            // End of job
            break;
        }

        if (loadingInstructions || loadingData)
        {
            // Load line into memory 4 chars per row
            int len = strlen(line);
            for (int i = 0; i < len; i += COLS)
            {
                for (int j = 0; j < COLS; j++)
                {
                    if (i + j < len)
                    {
                        memory[memIndex][j] = line[i + j];
                    }
                    else
                    {
                        memory[memIndex][j] = ' ';
                    }
                }
                memIndex++;
                if (memIndex >= ROWS)
                {
                    printf("Memory overflow while loading job\n");
                    fclose(fp);
                    return;
                }
            }
        }
    }

    fclose(fp);
}

int main()
{
    char memory[ROWS][COLS];

    // Initialize memory
    initializeMemory(memory);

    // Display memory before loading
    printf("Memory before loading job:\n");
    displayMemory(memory);

    // Load job from input file "input.txt"
    loadJob(memory, "input.txt");

    // Display memory after loading
    printf("\nMemory after loading job:\n");
    displayMemory(memory);

    // Clear memory again
    initializeMemory(memory);

    // Display memory after clearing
    printf("\nMemory after clearing:\n");
    displayMemory(memory);

    return 0;
}
