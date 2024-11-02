#include "filereader.h"
#include "../initialization/corestructs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
    My guess is that I will probably be revisiting this 
    after realizing that I got something wrong with the rows and columns
    because I am currently only working in an environment where the number
    of rows is equal to the number of columns
*/

#define MAXCHAR 1000

void ReadPuzzleCSV(ButtonMaster* master)
{
    FILE* pz;
    char row[MAXCHAR];
    char* token;
    int r = 0, c = 0;

    int total = master->columns * master->rows;

    master->solutionLocations = malloc(sizeof(Vector2Int) * master->rows);
    int locationIndex = 0;

    int** csvFileInts = malloc(sizeof(int*) * total);
    for (int i = 0; i < master->rows; i++)
    {
        csvFileInts[i] = malloc(sizeof(int) * master->columns);
    }

    pz = fopen("D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv", "r");

    //File reading stuff
    printf("file opened\n");
    while (feof(pz) != true)
    {
        fgets(row, MAXCHAR, pz);

        token = strtok(row, ",");
        while (token != NULL)
        {
            char val = token[0];
            int intVal = val - '0';
            csvFileInts[r][c] = intVal;

            printf("%i\n", csvFileInts[r][c]);

            token = strtok(NULL, ",");
            c++;
        }
        c = 0;
        r++;
    }
    
    /*
        Reversing through the loop from the csv file
        because otherwise it won't match up with the coordinate
        system for our buttons because the way they are constructed
        is backwards compared to how the file reads the csv data
    */
    for (int j = 0; j < master->rows; j++)
    {
        int* temp = malloc(sizeof(int) * master->columns);
        for (int i = 0; i < master->columns; i++)
        {
            temp[i] = csvFileInts[j][master->columns - i - 1];
        }
        for (int i = 0; i < master->rows; i++)
        {
            csvFileInts[j][i] = temp[i];
        }
        free(temp);
        temp = NULL;
    }
    
    for (int i = master->rows - 1; i >= 0; i--)
    {
        
        for (int j = master->columns - 1; j >= 0; j--)
        {
            if (csvFileInts[i][j] == 1)
            {
                master->solutionLocations[locationIndex].x = i;
                master->solutionLocations[locationIndex].y = j;
                locationIndex++;
                master->numberOfSolutions++;
            }
        }
    }
    fclose(pz);
    token = NULL;
    pz = NULL;

    for (int i = 0; i < master->rows; i++)
    {
        free(csvFileInts[i]);
        csvFileInts[i] = NULL;
    }
    free(csvFileInts);
    csvFileInts = NULL;

    // for (int i = 0; i < 3; i++)
    // {
    //     printf("Location: %i: %i, %i\n", i, master->solutionLocations[i].x, master->solutionLocations[i].y);
    // }
}