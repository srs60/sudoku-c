#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELIMITER			","
#define ERROR_FILE_OPEN		printf("\n * * * File opening failed * * *\n")
#define PRINTON

int check(int row, int col, int digit);
int setCell(int row, int col);
int getSudoku();
int writeSudoku();
int print_sudoku();

int steps = 0, sudoku[9][9];

// ----------------------------------------------------------------------
int main()
{
	getSudoku();
#ifdef PRINTON
	print_sudoku();
#endif

    if(setCell(0, 0)) writeSudoku();
    else
		printf("\n* * * NO SOLUTION * * *\n");

#ifdef PRINTON
	print_sudoku();
#endif
    return 0;
}
// ----------------------------------------------------------------------
int check(int row, int col, int digit)
{
int i, SrowBox, ScolBox;

    SrowBox = (row / 3) * 3;
    ScolBox = (col / 3) * 3;

    for(i = 0; i < 9; i++)
    {
        if (sudoku[row][i] == digit) return 0;      //  check row for digits
        if (sudoku[i][col] == digit) return 0;      //  check col for digits
        if (sudoku[SrowBox + (i % 3)][ScolBox + (i / 3)] == digit) return 0;
    }												//	check box for digits
    return 1;
}
// ----------------------------------------------------------------------
int setCell(int row, int col)
{
int i;

    steps++;

	if(row < 9 && col < 9)
    {
        if(sudoku[row][col] != 0)
        {
            if((col+1) < 9)
                return setCell(row, col+1);
            else if((row+1) < 9)
                return setCell(row+1, 0);
            else
                return 1;
        }
        else
        {
            for(i = 0; i < 9; i++)
            {
                if(check(row, col, i+1))
                {
                    sudoku[row][col] = i+1;
                    if((col+1) < 9)
                    {
                        if(setCell(row, col+1))
                            return 1;
                        else
                            sudoku[row][col] = 0;
                    }
                    else if((row+1) < 9)
                    {
                        if(setCell(row+1, 0)) return 1;
                        else sudoku[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}
// ----------------------------------------------------------------------
int getSudoku()
{
char buffer[255] ;
char *record, *line;
int i = 0, j = 0;

	FILE *fs = fopen("sudokuIn.txt","r");
	if (fs == NULL)
    {
        ERROR_FILE_OPEN; exit(-1);
    }
    while((line=fgets(buffer,sizeof(buffer),fs))!= NULL)
    {
        record = strtok(line,DELIMITER);
        while(record != NULL)
        {
            sudoku[i][j++] = atoi(record) ;
            record = strtok(NULL,DELIMITER);
        }
        i++ ; j = 0;
    }
	return 0;
}
// ----------------------------------------------------------------------
int writeSudoku()
{
int i, j;

	FILE *fs = fopen("sudokuOut.txt", "w");
	if (fs == NULL)
	{
		ERROR_FILE_OPEN; exit(-1);
	}
    for(i = 0; i < 9; i++)
    {
		for(j = 0; j < 9; j++) fprintf(fs," %d,", sudoku[i][j]);
		fprintf(fs,"\n");
    }
    fclose(fs);
	return 0;
}
// ----------------------------------------------------------------------
int print_sudoku()
{
int i, j;

	printf("\n----------------------------\n");
    for(i = 0; i < 9; i++)
    {
		for(j = 0; j < 9; j++) printf(" %d,", sudoku[i][j]);
        printf("\n");
    }
    printf("----------------------------\n");
	if (steps > 0) printf("\nSolved in %d steps\n", steps);
    return 0;
}
// ----------------------------------------------------------------------
