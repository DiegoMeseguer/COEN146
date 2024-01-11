//
//  Created by Behnam Dezfouli
//  CSEN, Santa Clara University
//
//
// This program offers two options to the user:
// -- Option 1: enables the user to copy a file to another file. 
// The user needs to enter the name of the source and destination files.
// -- Option 2: enables the user to measure the performance of file copy. 
// In addition to the name of source and destination files, the user needs to enter the maximum source file size as well as the step size to increment the source file size.
//
//
// double copier(FILE *s_file, FILE *d_file)
// Precondition: s_file is a pointer to a file opened in read mode, d_file is a file pointer opened in write mode
// Postcondition: Copies the contents of the file pointed to by s_file to the file pointed to by d_file
//


#include <stdio.h>
#include <stdlib.h> // For exit()
#include <time.h>

#define SIZE 1
#define DUM_CHAR 'A'


double copier(FILE *s_file, FILE *d_file)
{

    
}




int main()
{
    
    if ( option == 1 ) // File copy
    {

        
    }
    
    else if ( option == 2 ) // File copy with performance measurement
    {

    }
    
    else
    {
        printf("Invalid option!");
        return 0;
    }
    
    return 0;
}

