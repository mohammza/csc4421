#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define ARG_LENGTH 10

int main()
{
	int PID;
	char lineGot[256];
	char *cmd;
    	char *call;

    
	while (1){
		//char path[FILENAME_MAX]; //for use in getcwd(char *path); FILENAME_MAX defined in unistd.h
		//getcwd(path, FILENAME_MAX);
		char *args[ARG_LENGTH]; //default max parameters = 9; to edit max parameters change var ARG_LENGTH
		printf("Lab04 > ");	//prompts the user for a command
		fgets(lineGot, 256, stdin); // Get a string from user (includes \n)
		cmd = strtok(lineGot, "\n"); // Get the string without the \n
        	call = strtok(cmd, " "); //get initial command
		args[0] = call;	//args must contain call as well as parameters
        	int i = 1;	//counter to put arguments in the array 
        	while(1){
            		if((args[i] = strtok(NULL, " ")) == NULL)
                		break;
			//printf("Arg %d: %s\n", i, args[i]);     uncomment for debugging purposes       		
			i++;
        	}
		//if (args[i] == NULL) printf("Arg %d: NULL\n", i);	uncomment for debugging purposes
        
		if( strcmp(cmd, "e") == 0 ) // loop terminates when "e" is typed
			exit (0);
		// creates a new process. Parent gets the child's process ID. Child gets 0.
		if ( (PID=fork()) > 0)
		{
			wait(NULL);
		}
		else if (PID == 0) /* child process */
		{
            		if(args[0] == NULL)
			   	execlp (call, call, NULL);
            		if(execvp(call, args) == -1){
			    	/* exec cannot return. If so do the following */
			    	fprintf (stderr, "Cannot execute %s\n", call);
			    	exit(1); /* exec failed */
            		}
			
		}
		else if ( PID == -1)
		{
			fprintf (stderr, "Cannot create a new process\n");
			exit (2);
		}
	}
}
