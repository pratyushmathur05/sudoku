#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
using namespace std;

const int N = 9;

// Function to check if a number is safe to place in a specific position
bool isSafe(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++)
        if (board[row][i] == num || board[i][col] == num)
            return false;

    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + boxRowStart][j + boxColStart] == num)
                return false;

    return true;
}

// Function to print the Sudoku board
void printBoard(int grid[N][N]) {
    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers (represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col == 3 || col == 6)
                cout << " | ";
            cout << grid[row][col] << " ";
        }
        if (row == 2 || row == 5) {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}

// Function to check if the board is full
bool isFull(int board[N][N]) {
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (board[row][col] == 0)
                return false;
    return true;
}

// Function to solve the Sudoku puzzle
bool solveSudoku(int board[N][N], int row, int col) {
    if (row == N - 1 && col == N)
        return true;

    if (col == N) {
        row++;
        col = 0;
    }

    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1))
                return true;
            board[row][col] = 0; // Backtrack
        }
    }

    return false;
}

// Function to generate a valid random Sudoku board
void generateRandomBoard(int board[N][N]) {
    memset(board, 0, sizeof(int) * N * N); // Initialize the board with zeros
    srand(time(0)); // Seed the random number generator

    // Fill the diagonal boxes
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            vector<int> nums;
            for (int k = 1; k <= 9; k++)
                nums.push_back(k);

            random_shuffle(nums.begin(), nums.end()); // Shuffle numbers
            for (int r = 0; r < 3; r++)
                for (int c = 0; c < 3; c++)
                    board[i + r][j + c] = nums[r * 3 + c];
        }
    }

    // Solve the board to make it valid
    solveSudoku(board, 0, 0);

    // Remove some numbers to create the puzzle (for example, remove 40 numbers)
    for (int i = 0; i < 40; i++) {
        int row = rand() % N;
        int col = rand() % N;
        while (board[row][col] == 0) { // Ensure we remove a filled number
            row = rand() % N;
            col = rand() % N;
        }
        board[row][col] = 0; // Remove the number
    }
}

// Game loop where the user plays Sudoku
void playGame(int board[N][N]) {
    int row, col, num;
    while (true) {
        printBoard(board);
        cout << endl << endl;
        cout << "Unable to solve? Enter -1 as row, col, and num to view the solved Sudoku." << endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;

        if (row == -1 || col == -1 || num == -1) {
            if (solveSudoku(board, 0, 0)) {
                printBoard(board);
            } else {
                cout << "No solution found." << endl;
            }
            cout << "Better luck next time!!!" << endl;
            return;
        }

        row--; col--; // Adjust user input for 0-based indexing
        if (!isSafe(board, row, col, num)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row][col] = num;
        if (isFull(board))
            break;
    }

    cout << "Congratulations! You have solved the puzzle." << endl;
    printBoard(board);
}

int main() {
    system("title Sudoku Game @copyassignment");
    system("color B0");

    int board[N][N];

    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers (represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    while (true) {
        int choice;
        cout << endl << endl;
        cout << "\t\t[1] Play Sudoku" << endl;
        cout << "\t\t[2] View the solved Sudoku" << endl;
        cout << "\t\t[3] Generate a new Sudoku board" << endl;
        cout << "\t\t[4] Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                generateRandomBoard(board); // Generate a new board before playing
                playGame(board);
                break;
            case 2:
                if (solveSudoku(board, 0, 0)) {
                    cout << "Completely Solved Sudoku is:" << endl;
                    printBoard(board);
                } else {
                    cout << "No solution found." << endl;
                }
                break;
            case 3:
                generateRandomBoard(board);
                cout << "A new Sudoku board has been generated!" << endl;
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

