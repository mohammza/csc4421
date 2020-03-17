#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 1000

int main(int argc, char *argv[]){
	const char *pathname;
	int file;	//open()
	int r;		//read()
	char data[BUFFSIZE];
	
	//should have two inputs
	if(argc != 2){
		printf("Usage: %s file path \n", argv[0]);
		return 1;
	}
	
	pathname = argv[1];
	//open the file
	file = open(pathname, O_RDONLY);
	//if unsuccessful
	if(file < 0){
		perror("Error opening the file");
		return 0;
	}
	
	//reading the file and writing
	while((r = read(file,data,40)) > 0){
		//printf("%s",&data);
        
		if(write(1, data, r) < 0)
			perror("An error has occured\n");
	}
	
	if(r < 0)
		perror("An error has occured\n");
	
	close(file);
	return 1;
}
