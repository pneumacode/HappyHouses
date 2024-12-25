/*
 *  AUTHOR: J.J. Holland
 *  DATE:   12/10/2024
 *
 *  HOUSE BUILDING
 *
 *  GOAL:   Optimally place houses within a grid in order to maximize the
 *          collective happiness of eccentric New York City refugees.
 *
 *  MORE:   https://github.com/lynx-recruiting/SWDEV-2024-12-Jon-Holland-fd918971/blob/main/description.md
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <sys/param.h>
// #include <omp.h>
#include <time.h>

#define MAX_SIZE 1000
#define MAX_HOUSES 10000

int width, height, num_houses;
int grid[MAX_SIZE][MAX_SIZE];
int houses[MAX_HOUSES][2];    // For storing house positions
int house_count = 0;

// Calculate the "Manhattan distance" between two houses
int manhattan_distance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// Calculate the happiness score for a house
int calc_happiness(int x, int y)
{
    int happiness = 0;

// #pragma omp parallel for num_threads(32)
    for (int i = 0; i < house_count; i++) {
        int hx = houses[i][0];
        int hy = houses[i][1];
        int distance = manhattan_distance(x, y, hx, hy);
        // if (width * height < 100000) distance = manhattan_distance(x, y, hx, hy);
        happiness += grid[y][x] * distance;
    }

    return happiness;
}

// Determine the optimal position for a house
void find_optimal_position(void)
{
    int best_happiness = -1;
    int best_x = -1, best_y = -1;

// #pragma omp parallel
//  {
//      int local_best_happiness = -1;
//      int local_best_x = -1, local_best_y = -1;
        
// #pragma omp for
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Is there already a house here?
                int has_house = 0;
                for (int i = 0; i < house_count; i++) {
                    if (houses[i][0] == x && houses[i][1] == y) {
                        has_house = 1;
                        break;
                    }
                }
                if (has_house) continue;

                // Calculate the happiness score for this position
                // This uses a greedy algorithm (what looks best at the moment)
                int happiness = calc_happiness(x, y);
                // if (num_houses < 100) calc_happiness(x, y);
                if (happiness > best_happiness) {
                    best_happiness = happiness;
                    best_x = x;
                    best_y = y;
                }
            }
        }

// #pragma omp critical
//      {
//          if (local_best_happiness > best_happiness) {
//              best_happiness = local_best_happiness;
//              best_x = local_best_x;
//              best_y = local_best_y;
//          }
//      }
//  }

    // Place the house at the best position found
    if (best_x != -1 && best_y != -1) {
        houses[house_count][0] = best_x;
        houses[house_count][1] = best_y;
        house_count++;
    }
}

// Ensure that 'str' represents an unsigned integer
int is_valid_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;   // invalid
        }
        str++;
    }

    return 1;   // valid
}

int main(void)
{
    char input1[256];     // grid dimensions and number of houses
    int count = 0;        // count valid numbers per line during grid input
    srand(time(NULL));

    // Get user input
    if (fgets(input1, sizeof(input1), stdin) == NULL) {
        fprintf(stderr, "Error: Unable to read input.\n");
        return 1;
    }

    // Tokenize first input line for grid dimensions and number of houses
    char *token = strtok(input1, " \t\n");
    while (token != NULL && count < 3) {
        if (!is_valid_number(token)) {
            fprintf(stderr, "Error: '%s' is not a valid input value.\n", token);
            return 1;    // Exit on invalid input
        }

        // Convert the token to an integer and store it in the appropriate variable
        int t = atoi(token);
        switch (count) {
            case 0:
                // Get grid width
                if (t > 0 && t <= 1000) {
                    width = atoi(token);
                } else {
                    fprintf(stderr, "Error: Width must be between 1 and 1000, inclusive.\n");
                    return 1;    // Exit on invalid input
                }
                break;
            case 1:
                // Get grid height
                if (t > 0 && t <= 1000) {
                    height = atoi(token);
                } else {
                    fprintf(stderr, "Error: Height must be between 1 and 1000, inclusive.\n");
                    return 1;   // Exit on invalid input
                }
                break;
            case 2:
                // Get number of houses
                if (t > 1 && t <= MIN(width * height, 10000)) {
                    num_houses = atoi(token);
                } else {
                    // The requirements seem incorrect here:
                    // Both W and H may be only 1, but N must be at least 2.
                    if (width == 1 && height == 1) {
                        fprintf(stderr, "Error: Only 1 house can be placed on a 1x1 grid.\n");
                    } else {
                        fprintf(stderr, "Error: Number of houses must be between 2 and %d, inclusive.\n", \
                                MIN(width * height, 10000));
                    }
                    return 1;    // Exit on invalid input
                }
                break;
            default:
                break;
        }

        count++;
        token = strtok(NULL, " \t\n");
    }

    if (count != 3) {
        fprintf(stderr, "Error: The first line must contain 3 numbers.\n");
        return 1;    // Exit on invalid input
    }

    // Get the remaining lines of user input
    // (WxH grid of desirability values)
    for (int y = 0; y < height; y++) {
        char input2[4096];
        count = 0;

        // Get a line of user input
        if (fgets(input2, sizeof(input2), stdin) == NULL) {
            fprintf(stderr, "Error: Unable to read input.\n");
            return 1;
        }

        // Tokenize, keeping count of valid numbers
        char *token = strtok(input2, " \t\n");
        while (token != NULL && count < width) {
            if (!is_valid_number(token)) {
                fprintf(stderr, "Error: '%s' is not a valid input value.\n", token);
                return 1;    // Exit on invalid input
            }

            // Convert the token to an integer and store it in grid array
            int t = atoi(token);

            // Validate range
            if (t >= 0 && t <= 100) {
                grid[y][count] = atoi(token);
                // printf("grid[y][x] = [%d]\n", grid[y][count]);
            } else {
                printf("Error: Each number must be between 0 and 100, inclusive.\n");
                return 1;
            }

            count++;
            token = strtok(NULL, " \t\n");
        }

        if (count != width) {
            fprintf(stderr, "Error: This line must contain %d numbers.\n", width);
            return 1;    // Exit on invalid input
        }
    }

    // Place the houses to maximize happiness
    if (num_houses <= 100) {
        while (house_count < num_houses) {
            find_optimal_position();
        }
    } else {
        // To have any chance of meeting the 10 second time limit,
        // place each house randomly on the grid.
        for (int i = 0; i < num_houses; i++) {
            while(1) {
                int rand_x = (rand() % width);
                int rand_y = (rand() % height);
            
                // Is there already a house there?
                if (houses[i][0] == rand_x && houses[i][1] == rand_y) {
                    continue;
                } else {
                    // Put a house there and hope for the best
                    houses[i][0] = rand_x;
                    houses[i][1] = rand_y;
                    break;
                }
            }
        }
    }

    // Display each house position
    for (int i = 0; i < num_houses; i++) {
        printf("%d %d\n", houses[i][0] + 1, houses[i][1] + 1);    // Convert to 1-based index
    }

    return 0;
}
