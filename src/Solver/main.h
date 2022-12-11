#pragma once

void read_sudoku(char *filename);
void read_hexadoku(char *filename);
void print_sudoku();
void print_hexadoku();
void save_sudoku(char *filename);
void save_hexadoku(char *filename);
int main_solver(char* sudoku);
int main_solver_hexa(char* sudoku);
