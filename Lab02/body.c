#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFFSIZE 4096


int main(int argc, char *argv[]){
	const char *pathname;
	int file;	//open()
	int r;		//read()
	char ch, data[BUFFSIZE];
    int begin;
    int end;
	
	//should have 4 inputs
	if(argc != 4){
		printf("Usage: %s begin end file path \n", argv[0]);
		return 1;
	}
	
    begin = atoi(argv[1]);
    end = atoi(argv[2]);
	pathname = argv[3];
	//open the file
	file = open(pathname, O_RDWR);
	//if unsuccessful
	if(file < 0){
		perror("Error opening the file");
		return 0;
	}
    
    //check if begin > end
    if(begin > end){
        perror("Start line is greater than end line\n");
        return 1;
    }

    //reading file byte by byte
    int index = 0, lineCount = 1;
    int w;  //write()
    
	while((r = read(file,&ch,1)) != 0){
        if(r < 0){
            perror("Error while reading file\n");
            return 1;        
        }

        if(ch == '\n'){
            data[index] = ch;
            data[index+1] = '\0';
            ch = 0;
            index = 0;
            
            w = 0;
            int length = strlen(data);
            if(lineCount >= begin && lineCount <= end){
                while(w != length){
                    size_t result = write(1,data+w,length-w);
                    if(w < 0){
                        perror("Error while writing\n");
                        return 1;
                    }   
                    w += result;                          
                }
            }
            lineCount++;        
        }
        else{
            data[index++] = ch;
        }
	}
	
    
	
	close(file);
	return 1;
}
