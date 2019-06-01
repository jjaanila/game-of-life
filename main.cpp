#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <unistd.h>

const int gridWidth = 200;
const int gridHeight = 100;
using grid = std::array<std::array<int, gridWidth>, gridHeight>;

void initialize_grid(grid& grid) {
    srand(time(NULL));
    for (int i = 1; i < gridHeight - 1; ++i) {
        for (int k = 1; k < gridWidth - 1; ++k) {
            grid[i][k] = rand() % 2;
        }
    }
}

void clear_screen() {
    std::system("clear");
}

void print_grid(grid& grid) {
    clear_screen();
    for (int i = 1; i < gridHeight - 1; ++i) {
        for (int k = 1; k < gridWidth - 1; ++k) {
            std::cout << (grid[i][k] ? "*" : " ");
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void get_next_gen(grid& lastGenGrid, grid& nextGenGrid) {
    for (int i = 1; i < gridHeight - 1; ++i) {
        for (int k = 1; k < gridWidth - 1; ++k) {
            int neighbours[8] = {
                lastGenGrid[i][k - 1],
                lastGenGrid[i][k + 1],
                lastGenGrid[i - 1][k],
                lastGenGrid[i + 1][k],
                lastGenGrid[i - 1][k - 1],
                lastGenGrid[i + 1][k + 1],
                lastGenGrid[i + 1][k - 1],
                lastGenGrid[i - 1][k + 1],
            };
            int nOfAliveNeighbours = 0;
            for (int i = 0; i < 8; ++i) {
                if (neighbours[i]) {
                    ++nOfAliveNeighbours;
                }
            }
            if (lastGenGrid[i][k]) { // Was alive
                if (nOfAliveNeighbours < 2) {
                    nextGenGrid[i][k] = 0;
                } else if (nOfAliveNeighbours < 4) {
                    nextGenGrid[i][k] = 1;
                } else {
                    nextGenGrid[i][k] = 0;
                }   
            } else { // Was dead
                if (nOfAliveNeighbours == 3) {
                    nextGenGrid[i][k] = 1;
                }
            }
        }
    }
}

int main() {
    grid lastGenGrid = {0};
    grid nextGenGrid = {0};
    initialize_grid(lastGenGrid);
    while (true) {
        get_next_gen(lastGenGrid, nextGenGrid);
        print_grid(nextGenGrid);
        lastGenGrid = nextGenGrid;
        usleep(100000);
    }
    return 0;
}