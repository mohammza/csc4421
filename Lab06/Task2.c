#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

void *print_message_function( void *ptr );

main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;
    
    /* Create independent threads each of which will execute function */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

	// use thread join function to wait for the thread thread1 to terminate 
	pthread_join(thread1, NULL);
    
    	// do the same for thread2
	pthread_join(thread2,NULL);
	// print the return value of each thread
	printf("Return value of thread1: %d\n",iret1);
	printf("Return value of thread2: %d\n",iret2);
	
    return(0);
}

void *print_message_function( void *ptr ) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}
