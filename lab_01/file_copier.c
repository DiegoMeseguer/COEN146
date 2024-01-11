#include <stdio.h>
#include <stdlib.h> // For exit()
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1
#define DUM_CHAR 'A'

double copier_with_function_calls(FILE *s_file, FILE *d_file) {

	char *buffer;
	int total;
	int maxSize = 100000;
    
	if(s_file == NULL || d_file == NULL) {
		printf("Error\n");
 		return -1;
	}
    
	buffer = (char*)malloc(sizeof(char) * maxSize);
	total = fread(buffer, sizeof(char), maxSize, s_file);
	fwrite(buffer, sizeof(char), total, d_file);   
    
	fclose(s_file);
	fclose(d_file);

	return 0;
}	

double copier_with_sys_calls(const char *s_file, const char *d_file) {

	int s_fd, d_fd;
	int maxSize = 100000;
        char *buffer;
	size_t total;

        buffer = (char*)malloc(sizeof(char) * maxSize);

	s_fd = open(s_file, O_RDONLY);
	d_fd = open(d_file, O_WRONLY);
	
	total = read(s_fd, buffer, maxSize);
	write(d_fd, buffer, total);

	return 0;
}	

int main(int argc, char **argv) {
    
	int option;

	for(int i = 0; i < argc; i++) {
		option = atoi(argv[i]);
 	}

	if ( option == 1 ) {      // File copy
        	char source[99];
        	char destination[99];

        	printf("Please enter name of source file: ");
        	scanf("%s", source);
        	printf("Please enter name of destination file: ");
        	scanf("%s", destination);

        	FILE *s_file = fopen(source, "r");
        	FILE *d_file = fopen(destination, "w");

        	//copier_with_function_calls(s_file, d_file);
        	copier_with_sys_calls(source, destination);
	}	
    
	else if ( option == 2 ) { // File copy with performance measurement

        	char source[99];
        	char destination[99];
		char *buffer;
        	int maxFileSize, stepSize, totalRead, start, end, totalTime;
        	int currentSize = 0;

		start = clock(); // Start to measure time

        	printf("Please enter name of source file: ");
        	scanf("%s", source);
        	printf("Please enter name of destination file: ");
        	scanf("%s", destination);
        	printf("Please enter maximum file fize (in bytes): ");
        	scanf("%i", &maxFileSize);
        	printf("Plese enter step size (in bytes): ");
        	scanf("%i", &stepSize);

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
			totalRead = fread(buffer, sizeof(char), currentSize, s_file);
			printf("Total bytes read: %i\n", totalRead);
			fwrite(buffer, sizeof(char), currentSize, d_file);
			fclose(s_file);

                	end = clock(); //Record time for this round
                	totalTime = ((double)(end -start)) / CLOCKS_PER_SEC;
                	printf("Total time: %d\n", totalTime);
            	}	
        }

    	else {
        	printf("Invalid option!");
        	return 0;
	}
    
	return 0;
}


