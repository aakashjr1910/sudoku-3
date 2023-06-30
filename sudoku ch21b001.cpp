  #include <iostream>
using namespace std;

// Size of the Sudoku grid
#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if the current digit is safe to place at the given position
bool isSafe(int grid[N][N], int row, int col, int digit) {
    // Check if the digit is already present in the current row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == digit || grid[i][col] == digit) {
            return false;
        }
    }

    // Check if the digit is already present in the current 3x3 box
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[boxRow + i][boxCol + j] == digit) {
                return false;
            }
        }
    }

    return true; // The digit can be placed at the given position
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find the first unassigned position in the grid
    bool isUnassigned = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isUnassigned = true;
                break;
            }
        }
        if (isUnassigned) {
            break;
        }
    }

    // If all positions are assigned, the Sudoku puzzle is solved
    if (!isUnassigned) {
        return true;
    }

    // Try placing digits 1 to 9 in the unassigned position
    for (int digit = 1; digit <= 9; digit++) {
        // Check if the digit is safe to place at the current position
        if (isSafe(grid, row, col, digit)) {
            // Assign the digit to the current position
            grid[row][col] = digit;

            // Recursively solve the remaining Sudoku grid
            if (solveSudoku(grid)) {
                return true; // The Sudoku puzzle is solved
            }

            // If placing the current digit doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // No solution exists for the Sudoku puzzle
}

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku grid (0 for empty cells):\n";
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> grid[row][col];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle.\n";
    }

    return 0;
}
