#include <stdio.h>
#include <stdlib.h> // For exit()
#include <time.h>

#define SIZE 1
#define DUM_CHAR 'A'

double copier(FILE *s_file, FILE *d_file)
{

    if(s_file == NULL || d_file == NULL) {
        printf("Error\n");
        return -1;
    }

    char c;
    while((c = fgetc(s_file)) != EOF) {
        fputc(c, d_file);
    }

    fclose(s_file);
    fclose(d_file);

    return 0;
}

int main(int argc, char **argv)
{
    
    int option;

    for(int i = 0; i < argc; i++) {
        option = atoi(argv[i]);
    }

    if ( option == 1 ) // File copy
    {
        char source[999];
        char destination[999];

        printf("Please enter name of source file: ");
        scanf("%s", source);
        printf("Please enter name of destination file: ");
        scanf("%s", destination);

        FILE *s_file = fopen(source, "r");
        FILE *d_file = fopen(destination, "w");

        copier(s_file, d_file);

    }
    
    else if ( option == 2 ) // File copy with performance measurement
    {
        char source[999];
        char destination[999];
        int maxFileSize, stepSize;
        int currentSize = 0;
        char *buffer;
	int totalRead;

        printf("Please enter name of source file: ");
        scanf("%s", source);
        printf("Please enter name of destination file: ");
        scanf("%s", destination);
        printf("Please enter maximum file fize (in bytes): ");
        scanf("%i", &maxFileSize);
        printf("Plese enter step size (in bytes): ");
        scanf("%i", &stepSize);

        //FILE *s_file = fopen(source, "r");
        FILE *d_file = fopen(destination, "w");
        buffer = (char*)malloc(sizeof(char) * maxFileSize);
	
        while(currentSize < maxFileSize) {
		
		currentSize = currentSize + stepSize;
		FILE *s_file = fopen(source, "w");
		for(int i = 0; i < currentSize; i++) {
			fputc('A', s_file);
		}	
		fclose(s_file);
		s_file = fopen(source, "r");
		totalRead = fread(buffer, sizeof(char), stepSize, s_file);
		printf("Total bytes read: %i\n", totalRead);
		fwrite(buffer, sizeof(char), stepSize, d_file);
            	//currentSize = currentSize + stepSize;
		fclose(s_file);
            }

        }

            // for(int i = 0; i < stepSize; i++) {
            //     buffer[i] = DUM_CHAR;
            // }
 
            // for(int i = 0; i < stepSize + 5; i++) {
            //     printf("char is: %c\n", buffer[i]);
            // }

            // for(int i = 0; i < stepSize + 5; i++) {
            //     printf("char is: %c\n", buffer[i]);
            // } 

    
    else
    {
        printf("Invalid option!");
        return 0;
    }
    
    return 0;
}


