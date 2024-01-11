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
        char source[200];
        char destination[200];

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
	char source[] = "orig.txt"; 
	char destination[] = "dest.txt"; 
	char *buffer;
        int maxFileSize, stepSize, totalRead, start, end, totalTime;
        int currentSize = 0;

	start = clock(); // Start to measure time
	
	maxFileSize = 500000;
	stepSize = 100;
	int size = maxFileSize / stepSize;
	int dataArray[size];
	int timeArray[size];
	int counter;

        FILE *d_file = fopen(destination, "w");
        buffer = (char*)malloc(sizeof(char) * maxFileSize);
	
	counter = 0;
        while(currentSize < maxFileSize) {
		
		currentSize = currentSize + stepSize;
		FILE *s_file = fopen(source, "w");
		for(int i = 0; i < currentSize; i++) {
			fputc('A', s_file);
		}	
		fclose(s_file);
		s_file = fopen(source, "r");
		totalRead = fread(buffer, sizeof(char), currentSize, s_file);
		
		dataArray[counter] = totalRead;
		//printf("Total bytes read: %i\n", totalRead);
		fwrite(buffer, sizeof(char), currentSize, d_file);
		fclose(s_file);

                end = clock(); //Record time for this round
                totalTime = ((double)(end -start)) / CLOCKS_PER_SEC;
		timeArray[counter] = totalTime;
                //printf("%d\t", totalTime);
                counter++;		
	}
	
       for(int i = 0; i < size; i++) {
	   printf("%i\t", dataArray[i]);
       }
	
       printf("\n");

       for(int i = 0; i < size; i++) {
	   printf("%i\t", timeArray[i]);
       }

    } 

    else
    {
        printf("Invalid option!");
        return 0;
    }
	
    
    return 0;
}
// graph, how graph was implemented, why graph looks the way it does, describe code
// socket = bridge between client and server to transfer data
// socket() -> creates socket
// bind() -> specify ip address and port
// listen() -> manage workflow, helps define #clients for server
// accept system all -> connect to various clients who are requesting
// read and write
// give server a port >1024
// star client, give locsl IP addrr (loopback) and port and src and dst files
// client sends name of destination file
// there is a source and dest file
// they should have same data at the end
// do not ssh, port will not work, only ssh if you have Linux/MacOS??
//
//
