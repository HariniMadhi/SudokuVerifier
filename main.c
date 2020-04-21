#include "validator.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

int main()
{
        system("clear");
        pthread_t threads[num_threads];
        char opt;
        printf("Input Manually? ");
        scanf("%c",&opt);
        int threadIndex = 0;
        int i,j;
        srand(time(0));
        for(i = 0 ; i < 9 ; i++)
        {
                for(j = 0; j < 9; j++)
                {
                        gotoxy(j*3+5 + 2*(j/3), i*2+3 + i/3);
                        if(opt=='Y'||opt=='y')
                                scanf("%d", &sudoku[i][j]);
                        else
                        {
                                sudoku[i][j]=rand()%9+1;
                                printf("%d", sudoku[i][j]);
                        }
                }
        }
        printf("\n\n");
        // Create 9 threads for 9 3x3 subsections, 9 threads for 9 columns and 9 threads for 9 rows.
        // This will end up with a total of 27 threads.
        for (i = 0; i < 9; i++)
                for (j = 0; j < 9; j++)
                {
                        if (i%3 == 0 && j%3 == 0)
                        {
                                parameters *data = (parameters *) malloc(sizeof(parameters));
                                data->row = i;
                                data->column = j;
                                pthread_create(&threads[threadIndex++], NULL, is3x3Valid, data); // 3x3 subsection threads
                        }

			if (i == 0)
                        {
                                parameters *columnData = (parameters *) malloc(sizeof(parameters));
                                columnData->row = i;
                                columnData->column = j;
                                pthread_create(&threads[threadIndex++], NULL, isColumnValid, columnData);       // column threads
                        }

                        if (j == 0)
                        {
                                parameters *rowData = (parameters *) malloc(sizeof(parameters));
                                rowData->row = i;
                                rowData->column = j;
                                pthread_create(&threads[threadIndex++], NULL, isRowValid, rowData); // row threads
                        }
                }

        for (i = 0; i < num_threads; i++)
        {
                pthread_join(threads[i], NULL);                 // Wait for all threads to finish
        }

        // If any of the entries in the valid array are 0, then the sudoku solution is invalid
        for (i = 0; i < num_threads; i++)
        {
                if (valid[i] == 0)
                {
                        printf("Sudoku solution is invalid!\n");
                        return EXIT_SUCCESS;
                }
        }
        printf("Sudoku solution is valid!\n");
        return EXIT_SUCCESS;
}

