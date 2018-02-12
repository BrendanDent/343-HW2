/*
 *Simulates Conway's game of life
 *
 *
 *Author: Brendan Dent
 *
 */

#include "file_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int displayBoard(char** board, int rows);
int menu(char*** board, int* rows, int* cols);
int save(char** board, int rows, int cols, char* filename);
int load(char*** board, int* rows, int* cols, char* filename);
int advance(char*** board, int rows, int cols, int generations);


int main (int argc,char** argv){
  char** board;
  int rows, cols, i = 0;
  
  load(&board, &rows, &cols, argv[1]);
  menu(&board, &rows, &cols);
  for(i = 0; i < rows; i++)
    free(board[i]);
  free(board);
  
  
  return 0;
}
/**
*This function displays the current board
*@param board the board to be displayed
*@param rows gives number of rows for looping purposes
*@returns 0 for successful completion
*/
int display(char** board, int rows){
  int i;
  system("clear");
  for(i = 0; i < rows; i++){
    printf("%s\n", board[i]);
  }
  return 0;
  
}
/**
*This function effectively runs the program. It accepts input and acts.
*@param board the current board
*@param rows number of rows
*@param cols number of columns
*@returns 0 for successful completion
*/
int menu(char*** board, int* rows, int* cols){
  char choice = '0';
  int generations;
  char line[100], filename[100];
  while(choice != '4'){
    display(*board, *rows);
    printf("\nPlease select an option:\n1.Advance\n");
	printf("2.Save Game\n3.Load Game\n4.Quit\n>");
    fgets(line, 100, stdin);
    sscanf(line, "%c", &choice);
    switch(choice){ 
    case '1':
      printf("Advance how many generations?\n");
      scanf("%d", &generations);
      while(generations <= 0){
	printf("Invalid input. Advance how many generations?\n");
	scanf("%d", &generations);
      }
      advance(board, *rows, *cols, generations);
      break;
      
    case '2':
      printf("Enter name of file to save to.\n");
      fgets(line, 100, stdin);
      sscanf(line,"%s\n", filename);
      save(*board, *rows, *cols, filename);
      break;
      
    case '3':
      printf("Enter name of file to load.\n");
      fgets(line, 100, stdin);
      sscanf(line,"%s\n", filename);
      load(board, rows, cols, filename);
      break;
      
    case '4':
      break;
    default:
      printf("Invalid choice\n");
    }
  }
  return 0;
}
/**
*This function formats the board and sends it to the write_file function
*@param board the current board
*@param rows number of rows
*@param cols number of columns
*@param filename name of file
*@returns 0 for successful completion
*/
int save(char** board, int rows, int cols, char* filename){
  char* buffer;
  int i, len;
  buffer = (char*)malloc(rows*cols*sizeof(char)+sizeof(int)*2+sizeof(char)*2);
  buffer[0] = (char) rows;			// size of board and row and col numbers
  sprintf(buffer, "%d\n%d\n", rows, cols-1);
  for(i = 0; i < rows; i++){
    strcat(buffer, board[i]);
    len = strlen(buffer);
    buffer[len] = '\n';
    buffer[len+1] = '\0';
    printf( "%s", buffer);}
  
  
  write_file(filename, buffer, rows); 
  printf("File saved\n");
  free(buffer);
  return 0;
}
/**
*This function uses the read_file function and formats the board accordingly
*@param board the current board
*@param rows number of rows
*@param cols number of columns
*@param filename name of file
*@returns 0 for successful completion
*/
int load(char*** board, int* rows, int* cols, char* filename){
  char* input;
  char* tok;
  int i = 0;
  
  *rows = read_file(filename, &input);
  *board = (char **)malloc(*rows * sizeof(char *));
  *cols = (strlen(input)+1)/(*rows);
  tok = strtok(input, "\n");
  while(tok != NULL && i < *rows){
    (*board)[i] = (char *)malloc(*cols * sizeof(char));
    strcpy((*board)[i++], tok);
    tok = strtok(NULL, "\n");
  }
  free(input);
  return 0;
}

/**
*This function runs the board through a number of generations
*@param board the current board
*@param rows number of rows
*@param cols number of columns
*@param generations number of generations to run
*@returns 0 for successful completion
*/
int advance(char *** board, int rows, int cols, int generations){
  int i, j, count, neighbors;
  char** snapshot;
  for(count = 0; count < generations; count++){
    snapshot = (char **)malloc(rows * sizeof(char *));
    for(i = 0; i < rows; i++){
      snapshot[i] = (char *)malloc(cols*sizeof(char));
      strcpy(snapshot[i], (*board)[i]);
    }
    
    for(i = 0; i < rows; i++){
      for(j = 0; j < cols; j++){
	neighbors = 0;
	if(i > 0 && snapshot[i-1][j] == 'C'){
	  neighbors++;
	}
	if(j > 0 && snapshot[i][j-1] == 'C'){
	  neighbors++;
	}
	if(i < rows-1 && snapshot[i+1][j] == 'C'){
	  neighbors++;
	}
	if(j < cols && snapshot[i][j+1] == 'C'){
	  neighbors++;
	}
	if(i > 0 && j > 0 && snapshot[i-1][j-1] == 'C'){
	  neighbors++;
	}
	if(i > 0 && j < cols && snapshot[i-1][j+1] =='C'){
	  neighbors++;
	}
	if(i < rows-1 && j > 0 && snapshot[i+1][j-1] =='C'){
	  neighbors++;
	}
	if(i < rows-1 && j < cols && snapshot[i+1][j+1] =='C'){
	  neighbors++;
	}
	
	if(neighbors < 2 && snapshot[i][j] =='C'){
	  (*board)[i][j] = 'x';
	}
	
	if(neighbors > 3 && snapshot[i][j] =='C'){
	  (*board)[i][j] = 'x';
	}
	
	if(neighbors == 3){
	  (*board)[i][j] = 'C';
	}
      }
    }
    free(snapshot);
  }
  return 0;
}
