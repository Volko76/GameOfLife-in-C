#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h> // Library to avoid pressing enter to validate

#define NB_ROWS 53
#define NB_COLUMNS 53

char** createMatrix() {
    char** matrix = (char**)malloc(NB_ROWS * sizeof(char*));
    for (int i = 0; i < NB_ROWS; i++) {
        matrix[i] = (char*)malloc(NB_COLUMNS * sizeof(char));
        for (int j = 0; j < NB_COLUMNS; j++) {
            matrix[i][j] = rand() % 2 == 0 ? ' ' : 'X';
        }
    }
    return matrix;
}

void printMatrix(char** matrix) {
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            printf("|%c", matrix[i][j]);
        }
        printf("|\n");
    }
}

void freeMatrix(char** matrix) {
    for (int i = 0; i < NB_ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int nbCellulesVivantesAutour(char** matrix, int posX, int posY) {
    int counter = 0;
    for (int i = posX - 1; i <= posX + 1; i++) {
        for (int j = posY - 1; j <= posY + 1; j++) {
            if (!(i == posX && j == posY) && matrix[(i + NB_ROWS) % NB_ROWS][(j + NB_COLUMNS) % NB_COLUMNS] == 'X') {
                counter++;
            }
        }
    }
    return counter;
}

void simulateGeneration(char** matrix) {
    char** newMatrix = createMatrix();
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            int neighbors = nbCellulesVivantesAutour(matrix, i, j);
            if (neighbors < 2 || neighbors > 3) {
                newMatrix[i][j] = ' ';
            } else if (neighbors == 3) {
                newMatrix[i][j] = 'X';
            } else {
                newMatrix[i][j] = matrix[i][j];
            }
        }
    }
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            matrix[i][j] = newMatrix[i][j];
        }
    }
    freeMatrix(newMatrix);
}

int main() {
    char** matrix = createMatrix();

    int choix = 1;
    int keyPressed;
    while (choix != 0) {
        simulateGeneration(matrix);
        // Clear the screen to make it beautiful
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        printMatrix(matrix);
        printf("Nouvelle generation ? (0 pour quitter || ESPACE pour continuer) : ");
        
        while (!_kbhit()) {
            // Ca permet d'attendre qu'on appuie sur un touche
        }
        
        keyPressed = _getch();
        if (keyPressed == 32) { // Check if we pressed space (32 in ASCII)
            continue;
        } else {
            choix = 0;
        }
    }

    freeMatrix(matrix);
    return 0;
}




//Le code classique (avec 0 ou 1) qui fonctionne sur n'importe quel terminal
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define NB_ROWS 8
#define NB_COLUMNS 8

int** createMatrix(){
    int** matrix = (int**)malloc(NB_ROWS * sizeof(int*));;
    for (int i = 0; i < NB_ROWS; i++)
    {
        matrix[i] = (int*)malloc(NB_COLUMNS * sizeof(int));
        for (int j = 0; j < NB_COLUMNS; j++)
        {
            matrix[i][j] = rand()%2;
        }
        
    }
    return matrix;
}

void printMatrix(int** matrix){
    for (int i = 0; i < NB_ROWS; i++)
    {
        for (int j = 0; j < NB_COLUMNS; j++)
        {
            printf("|%d", matrix[i][j]);
        }
        printf("|\n");
    }
}
void freeMatrix(int** matrix){
    for (int i = 0; i < NB_ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int nbCellulesVivantesAutour(int** matrix, int posX, int posY) {
    int counter = 0;
    for (int i = posX - 1; i <= posX + 1; i++) {
        for (int j = posY - 1; j <= posY + 1; j++) {
            if (!(i == posX && j == posY) && matrix[(i + NB_ROWS) % NB_ROWS][(j + NB_COLUMNS) % NB_COLUMNS] == 1) {
                counter++;
                //matrix[(i + NB_ROWS) % NB_ROWS][(j + NB_COLUMNS) % NB_COLUMNS] = 8; //Pour voir où on vise
            }
        }
    }
    return counter;
}

void simulateGeneration(int** matrix) {
    int** newMatrix = createMatrix(); // Create a new matrix to store the updated generation
    
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            int neighbors = nbCellulesVivantesAutour(matrix, i, j);
            
            if (neighbors < 2 || neighbors > 3) {
                newMatrix[i][j] = 0; // Any live cell with fewer than two live neighbors or more than three live neighbors dies
            } else if (neighbors == 3) {
                newMatrix[i][j] = 1; // Any dead cell with exactly three live neighbors becomes a live cell
            } else {
                newMatrix[i][j] = matrix[i][j]; // Copy unchanged cells
            }
        }
    }
    
    // Copy the new generation back to the original matrix
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLUMNS; j++) {
            matrix[i][j] = newMatrix[i][j];
        }
    }
    
    // Free the memory allocated for the new matrix
    freeMatrix(newMatrix);
}
int main(){
    int** matrix = createMatrix(); 

    int choix = 5;
    //The game
    while (choix!=0)
    {
        simulateGeneration(matrix);
        printMatrix(matrix);
        printf("Nouvelle génération ? (0 pour quitter || 1 pour continuer) : ");
        scanf("%d", &choix);
    }
    

    // Free the memory allocated for the matrix
    freeMatrix(matrix);
    return 0;
}
*/
