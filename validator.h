#ifndef PARAMETER_H
#define PARAMETER_H

#include "parameter.h"
#define num_threads 27

extern int valid[27];	//Stores the validity of the area each thread is responsible for
extern int sudoku[9][9]; 	//Sudoku that needs to be solved

extern void* isRowValid(void *);
extern void* isColumnValid(void *);
extern void* is3x3Valid(void *);

#endif
