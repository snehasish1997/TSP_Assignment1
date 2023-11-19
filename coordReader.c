#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

// ... (The rest of the header comments remain unchanged.)

int readNumOfCoords(char *fileName);
double **readCoords(char *filename, int numOfCoords);
void writeTourToFile(int *tour, int tourLength, char *filename);

int readNumOfCoords(char *filename){
    FILE *file = fopen(filename, "r");
    int numOfCoords = 0;

    if(file == NULL){
        return -1; // Indicate file opening error.
    }

    char line[100];
    while(fgets(line, sizeof(line), file) != NULL){
        numOfCoords++;
    }

    fclose(file); // Close the file after reading the number of coordinates.
    return numOfCoords;
}

double **readCoords(char *filename, int numOfCoords){
    FILE *file = fopen(filename,"r");
    char line[100];

    if(file == NULL) {
        printf("Unable to open file: %s", filename);
        return NULL;
    }

    double **coords = (double **)malloc(numOfCoords * sizeof(double *));
    if (coords == NULL) {
        perror("Memory Allocation Failed for Coordinates Array");
        return NULL;
    }

    for(int i = 0; i < numOfCoords; i++){
        coords[i] = (double *)malloc(2 * sizeof(double));
        if (coords[i] == NULL){
            perror("Memory Allocation Failed for Coordinate Pair");
            // Properly free previously allocated memory
            for(int j = 0; j < i; j++) {
                free(coords[j]);
            }
            free(coords);
            return NULL;
        }
    }

    int lineNum = 0;
    while(fgets(line, sizeof(line), file) != NULL){
        double x, y;
        if (sscanf(line, "%lf,%lf", &x, &y) == 2){
            coords[lineNum][0] = x;
            coords[lineNum][1] = y;
            lineNum++;
        }
    }

    fclose(file); // Close the file after reading the coordinates.
    return coords;
}

void writeTourToFile(int *tour, int tourLength, char *filename){
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        printf("Unable to open file: %s", filename);
        return; // Exit the function if file opening fails.
    }

    fprintf(file, "%d\n", tourLength); // Write the tour length.
    for(int i = 0; i < tourLength; i++) {
        fprintf(file, "%d ", tour[i]);
    }

    fclose(file); // Close the file after writing the tour.
}
