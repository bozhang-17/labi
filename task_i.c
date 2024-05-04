#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    #define N 201
    #define M 3
    double data[N][M];

    #define MAXCHAR 100
    char buffer[MAXCHAR];
    int row = 0;
    int column = 0;
    char *ptr;

    char fn[] = "data.csv";
    FILE *fptr;
    fptr = fopen(fn, "r");
    if (fptr == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
    while (fgets(buffer, MAXCHAR, fptr)) {
        column = 0;
        row++;
        if (row == 1) {
            continue;  // Skip the header row
        }
        char* value = strtok(buffer, ", ");
        while (value) {  
            data[row-2][column] = strtod(value,&ptr);
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fptr);

    // Calculate median for each column
    double median[M];
    for (int j = 0; j < M; j++) {
        // Sort the column
        for (int i = 0; i < N - 1; i++) {
            for (int k = 0; k < N - i - 1; k++) {
                if (data[k][j] > data[k + 1][j]) {
                    double temp = data[k][j];
                    data[k][j] = data[k + 1][j];
                    data[k + 1][j] = temp;
                }
            }
        }
        // Calculate median
        if (N % 2 == 0) {
            median[j] = (data[N / 2 - 1][j] + data[N / 2][j]) / 2.0;
        } else {
            median[j] = data[N / 2][j];
        }
    }

    // Display median values
    for (int j = 0; j < M; j++) {
        printf("%.2f", median[j]);
        if (j < M - 1) {
            printf(",");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}