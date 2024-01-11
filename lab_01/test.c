#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	FILE *s_file;
	int total;
	char *buffer;
	
	s_file = fopen("orig.txt", "r");	
	buffer = (char*)malloc(sizeof(char) * 1000);
	total = fread(buffer, sizeof(char), 1000, s_file);
	
	
	printf("Size of text file is: %i\n", total);




	return 0;
}
