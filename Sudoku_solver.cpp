#include <iostream>
#include <vector>
//This functions checkes whether the c(number 1-9) is valid to fill or not inside the current block
bool checker(int i, int j, std::vector<std::vector<char>>& board, char c) {
    //column check
    for(int k = 0; k < 9; k++) {
        if(board[i][k] == c) return false;
    }
    //row check
    for(int k = 0; k < 9; k++) {
        if(board[k][j] == c) return false;
    }
    //subgrid check
    for(int ki = i - i % 3; ki < (i - i % 3 + 3); ki++) {
        for(int kj = j - j % 3; kj < (j - j % 3 + 3); kj++) {
            if(board[ki][kj] == c) return false;
        }
    }
    return true;
}

bool solve(int i, int j, std::vector<std::vector<char>>& board) {
    if(i == 9) return true; 
    //Switching to next row
    if(j == 9) return solve(i + 1, 0, board); 
    //Skips to next cell(or box)
    if(board[i][j] != '.') return solve(i, j + 1, board); 
    // Fills out the black space with a valid number
    for(char c = '1'; c <= '9'; c++) {
        // checker checks if the number is valid or not
        if(checker(i, j, board, c) == false) continue; 
        board[i][j] = c;
        bool result = solve(i, j + 1, board);
        if(result == true) return true;
        // If a number intrupting while solving a sudoku the control backtrack to that number while replacing filled numbers by '.' and change that number
        board[i][j] = '.';
    }
    return false;
}

void solveSudoku(std::vector<std::vector<char>>& board) {
    solve(0, 0, board);
}

int main() {
    // Fill the numbers here | blank is denoted by '.' (dot)
    std::vector<std::vector<char>> board = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '6', '2', '.', '8', '.', '5'},
        {'.', '.', '4', '.', '5', '8', '.', '2', '1'},
        {'.', '8', '.', '5', '.', '7', '.', '.', '3'},
        {'1', '.', '.', '.', '.', '.', '.', '7', '.'},
        {'.', '9', '.', '4', '.', '2', '.', '.', '6'},
        {'.', '.', '1', '.', '9', '5', '.', '8', '4'},
        {'.', '.', '.', '8', '4', '.', '6', '.', '7'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
    };

    solveSudoku(board);
    // Outputs the solved sudoku
    std::cout << "Solved Sudoku:" << std::endl;
    for(const auto& row : board) {
        for(char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}