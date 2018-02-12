/*
 *Library for reading and writing files
 *
 *
 *Author: Brendan Dent
 *
 */

#ifndef file_utilities_H
#define file_utilities_H

int read_file( char* filename, char **buffer );
int write_file( char* filename, char *buffer, int size);

#endif
