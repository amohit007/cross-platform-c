#include "cpc_sudoku.h"

#include "cpc_mem.h"
#include "cpc_base.h"

typedef struct {
	bool dim1[9][9];
	bool dim2[9][9];
	bool subgrid[9][9];
} CPCSudokuSolver;

CPC_NEVER_INLINE static bool cpc_sudoku_solve_internal(char board[9][9], CPCSudokuSolver *solver) {
	CPC_ASSERT(solver != NULL);
	#pragma unroll
	for (unsigned char i = 0; i < 9; i++) {
		#pragma unroll
		for (unsigned char j = 0; j < 9; j++) {
			if (board[i][j] == CPC_SUDOKU_EMPTY_CHAR) {
				#pragma unroll
				for (unsigned char v = 0; v < 9; v++) {
					if (!solver->dim1[i][v] && !solver->dim2[j][v] && !solver->subgrid[(i / 3) * 3 + j / 3][v]) {
						board[i][j] = (char)v + '1';
						solver->dim1[i][v] = true;
						solver->dim2[j][v] = true;
						solver->subgrid[(i / 3) * 3 + j / 3][v] = true;
						if (cpc_sudoku_solve_internal(board, solver)) return true;
						board[i][j] = CPC_SUDOKU_EMPTY_CHAR;
						solver->dim1[i][v] = false;
						solver->dim2[j][v] = false;
						solver->subgrid[(i / 3) * 3 + j / 3][v] = false;
					}
				}
				return false;
			}
		}
	}
	return true;
}

bool cpc_sudoku_solve(char board[9][9]) {
	CPCSudokuSolver solver;
	cpc_mem_zero(&solver, sizeof(solver), CPC_ALIGN_OF(CPCSudokuSolver));
	#pragma unroll
	for (unsigned char i = 0; i < 9; i++) {
		#pragma unroll
		for (unsigned char j = 0; j < 9; j++) {
			if (board[i][j] != CPC_SUDOKU_EMPTY_CHAR) {
				CPC_ASSERT('1' <= board[i][j] && board[i][j] <= '9');
				unsigned char v = (unsigned char)(board[i][j] - '1');
				if (solver.dim1[i][v] | solver.dim2[j][v] | solver.subgrid[(i / 3) * 3 + j / 3][v]) return false;
				solver.dim1[i][v] = true;
				solver.dim2[j][v] = true;
				solver.subgrid[(i / 3) * 3 + j / 3][v] = true;
			}
		}
	}
	return cpc_sudoku_solve_internal(board, &solver);
}
