#include<pthread.h>
#include<stdio.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid); 
    pthread_exit(NULL);
}
int main (int argc, char *argv[])
{
	// create an array of thread struct instances with appropriate length
	pthread_t tIDs[NUM_THREADS];
	int rc;
    
    long t;
    for(t=0; t<NUM_THREADS; t++){
	pthread_join(tIDs[t-1],NULL);
        printf("In main: creating thread %ld\n", t);
        // start a new thread and call the appropriate routine with. You need to handle errors.
        // args of the routine should be cast as (void *)t
	if(rc = pthread_create(&tIDs[t], NULL, PrintHello, (void *)t)){
		printf("Thread creation failed: %d\n", rc);
	}
    }
    /* Last thing that main() should do */
    pthread_exit(NULL);
}
