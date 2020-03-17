#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 10
int main(void) {
    char bufin[BUFSIZE] = "empty";
    char bufout[] = "hello";
    int bytesin;
    pid_t childpid;
    int fd[2]; // 0 - refers to read, 1 - refers to write
    if (pipe(fd) == -1) { /* create a pipe */
        perror("Failed to create the pipe");
        return 1;
    }
    bytesin = strlen(bufin);
    childpid = fork();
    if (childpid < 0) {
        perror("Failed to fork");
        return 1;
    }
    if (childpid == 0){
    /* child code */
	close(fd[0]);	//close unused read end
        write(fd[1], bufout, strlen(bufout)+1);
	close(fd[1]);
	//exit(NULL);
	}
    else{
    /* parent code */
	//wait(NULL);
	close(fd[1]);
        bytesin = read(fd[0], bufin, BUFSIZE);
	close(fd[0]);
	}
    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s}\n", (long)getpid(), bytesin, bufin, bufout);
    return 0;
}
