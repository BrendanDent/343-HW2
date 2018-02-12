/*
 *Library for reading and writing files
 *
 *
 *Author: Brendan Dent
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
*This function opens a file and puts all of the data at the given pointer
*@param filename name of the file
*@param buffer pointer to put file data
*@returns number of rows that should be in the buffer
*/
int read_file( char* filename, char **buffer ){ 
  FILE *file;
  
  int rows, cols;
  
  file = fopen(filename, "r");
  fscanf(file, "%d\n%d\n",&rows, &cols);
  
  cols = cols + 1; //to include \n
  char line[cols];
  //each row has a new line and the last row needs a null terminator
  *buffer = (char*)malloc(rows * (cols)*sizeof(char *) + 1);	
 
  
  if(fgets(line, cols + 1, file) != NULL)
    strcpy(*buffer, line);
  while(fgets(line, cols + 1, file) != NULL){
    if(strlen(line) >1)
      *buffer = strcat(*buffer, line);
    
  }
  
  fclose(file);
  return rows;
}

/**
*This function writes the given data to the given file
*@param filename name of the file
*@param buffer pointer to the file data
*@param size number of rows to be written
*@returns number of rows that should be in the buffer
*/
int write_file( char* filename, char *buffer, int size){
  FILE *file;
  file = fopen(filename, "w");
  fprintf(file, "%s", buffer);
  fclose(file);
  return 0;
}
