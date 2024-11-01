#include "filereader.h"
#include "../initialization/corestructs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXCHAR 1000

void ReadPuzzleCSV(void)
{
    FILE* pz;
    char row[MAXCHAR];
    char* token;
    int r = 0, c = 0;
    

    Vector2Int* validLocations = malloc(sizeof(Vector2Int) * 3);
    int locationIndex = 0;

    pz = fopen("D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv", "r");

    printf("file opened\n");
    while (feof(pz) != true)
    {
        fgets(row, MAXCHAR, pz);
        printf("Row: %s\n", row);

        token = strtok(row, ",");
        while (token != NULL)
        {
            char val = token[0];
            int intVal = val - '0';
            if (intVal == 1)
            {
                printf("%i\n", locationIndex);
                Vector2Int loc = {r, c};
                validLocations[locationIndex] = loc;
                locationIndex++;
            }
            else
            {
                printf("not correct\n");
            }
            token = strtok(NULL, ",");
            c++;
        }
        r++;
    }
    fclose(pz);
    token = NULL;
    pz = NULL;

    for (int i = 0; i < 3; i++)
    {
        printf("Location: %i: %i, %i\n", i, validLocations[locationIndex].x, validLocations[locationIndex].y);
    }
    free(validLocations);
    validLocations = NULL;
}