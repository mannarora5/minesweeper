// Assignment 1 21T2 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by Mann Arora (z5360526)
// on 29/6/21
//
// Version 1.0.0 (2021-06-19): Assignment released.



#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE            8
              

// The possible command codes.
#define DETECT_ROW      1
#define DETECT_SQUARE   2
#define REVEAL_CROSS    3
#define GAME_MODE       4
#define FLAG_MINE       5
#define DEFUSE          6

// Add any extra #defines here.
#define ROW 8
#define COLUMN 8

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.

int main(void) {
    int minefield[SIZE][SIZE];
    //Stage 01 Code 

    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");
    
    // variables are assigned below for scanning coordinates of mines, 
    // the number of mines and placing them on the minefield. 
    int xcord;
    int ycord;
    int num_mines_placed;
    
    // This line used to scan number of mines. 
    scanf("%d", &num_mines_placed); 
    printf("Enter pairs:\n");

    // While loop used to scan the coordinates of the mine. 
    int loop1 = 0;
    while (loop1 < num_mines_placed) {
        scanf("%d %d", &xcord, &ycord);
        
        // if statements used to implement accepted boundaries for coordinates
        // and to let that coordinate be the number 2 on the minefield. 
        if (xcord >= 0 && xcord < SIZE) {
            if (ycord >= 0 && ycord < SIZE) {
                minefield[xcord][ycord] = HIDDEN_MINE;
            }
        }
        loop1++;
    }
    printf("Game Started\n");
    print_debug_minefield(minefield);
    
    // DETECT-ROW Command.
    // Variables assigned below are going to be used to count the number of 
    // mines in the row.
    int detect_command; 
    int detect_row;  
    int detect_column;
    int detect_length;
  
    // This scans input till EOF. 
    // The values of row, column and length are scanned and assigned in the loop
    while (scanf("%d", &detect_command) == 1) {
        scanf("%d", &detect_row); 
        scanf("%d", &detect_column);
        scanf("%d", &detect_length); 
        
        // If statements used here to account for entered coordinates that do not
        // lie in the minefield. 
        if (detect_row < 0 || detect_row > (SIZE - 1)) {
            printf("Coordinates not on map\n");
        } 
        
        else if (detect_column < 0 || detect_column > (SIZE - 1)) {
            printf("Coordinates not on map\n");
        }
         
        else if (detect_column + detect_length >= (SIZE + 1)) {
            printf("Coordinates not on map\n");
        }
        
        // If user enters "1", detect row command is initiated.
        else if (detect_command == HIDDEN_SAFE) {
            // number of mines is initialised at 0.
            int mines_in_row = 0;
            int loop_counter2 = 0;
            
            while (loop_counter2 < detect_length) {
                // If statement used so that if the specified coordinate is a 2
                // (Hidden Mine), then number of mines in row will increase by 1
                if (minefield[detect_row][detect_column] == HIDDEN_MINE) {
                    mines_in_row++;
                }
                //column goes up by 1 every loop. 
                detect_column++; 
                loop_counter2++;
            }
            detect_column = detect_column - detect_length;
            // The values of each variable at this point is stored within 
            // the variable, so we can now print the following statement to show 
            // how many mines were counted.
            printf("There are %d mine(s) in row %d, from column %d to %d\n", 
        mines_in_row, detect_row, detect_column, 
        detect_column + detect_length - 1);
        }         
        // Stage 02 code
        
        // if the user inputs the number 2, detect square command is initiated.   
        if (detect_command == DETECT_SQUARE) {
            
            // boundary for valid coordinates being set using an if statement.
            if (detect_row < 0 || detect_row > (SIZE - 1) || detect_column < 0 
               || detect_column > (SIZE - 1)) {
                printf("Coordinates not on map\n");
            }
            // these variables are for counting mines
            // yp means y-positive, yn means y-negative.. and similar for x. 
            int mines_in_square_yp = 0;
            int mines_in_square_yn = 0;
            int mines_in_square_xp = 0;
            int mines_in_square_xn = 0;
            int loop_ypositive = 0;
            while (loop_ypositive <= detect_length) {
                // counting number of mines in the positive y direction from
                // the centre.  
                if (minefield[detect_row][detect_column + loop_ypositive - 1] 
                    == HIDDEN_MINE) {
                    //mines go up by 1 for pos-y
                    mines_in_square_yp++; 
                }
                loop_ypositive++;
            }
            int loop_ynegative = 0;
            while (loop_ynegative <= detect_length) {
                // counting number of mines in the negative y direction from 
                // the centre.
                if (minefield[detect_row][detect_column - loop_ynegative - 1] 
                    == HIDDEN_MINE) {
                    //mines go up by 1 for neg-y
                    mines_in_square_yn++; 
                }
                loop_ynegative++;
            }
            int loop_xpositive = 0;
            while (loop_xpositive <= detect_length) {
                // counting number of mines in the positive x direction from 
                // the centre.
                if (minefield[detect_row + loop_xpositive - 1][detect_column] 
                    == HIDDEN_MINE) {
                    //mines go up by 1 for pos-x
                    mines_in_square_xp++; 
                }
                loop_xpositive++;
            }
        
            int loop_xnegative = 0;
            while (loop_xnegative <= detect_length) {
                // counting number of mines in the negative x direction from
                // the centre.
                if (minefield[detect_row - loop_xnegative - 1][detect_column] 
                    == HIDDEN_MINE) {
                    //mines go up by 1 for neg-x
                    mines_in_square_xn++; 
                }
                loop_xnegative++;
            }
            // print out the statement with all the stored variables.
            printf("There are %d mine(s) in the square centered at row %d,"
                   "column %d of size %d\n", 
                   mines_in_square_yp + mines_in_square_yn + mines_in_square_xn
                   + mines_in_square_xp + 1, detect_row, detect_column, 
                   detect_length);
        }
        print_debug_minefield(minefield);
    }
  
    return 0;
}

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}
