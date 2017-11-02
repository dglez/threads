

/*-----------------------------------------------------------------------------+ 
File Name:  main.c
+------------------------------------------------------------------------------+

+------------------------------------------------------------------------------+
   OS COP-4610
   Author: Daniel Gonzalez P#4926400
   assignment 3: threads
   Date: 11/2/2017


  +-------------------------------------------------------------------------+
  | I Daniel Gonzalez #4926400 hereby certify that this collective work is  |
  | my own and none of it is the work of any other person or entity.        |  
  | This shell extends the Dr. Raju Rangaswami's original 4338              |
  | demo and modified to fit into our lecture.                              |
  +-------------------------------------------------------------------------+
  

  how to compile and execute:
    1.Open the terminal
        Go to the program folder
        Run the following command "make"
    OR
    2.Open the terminal
        Go to the program folder
        Run the following command 
        "gcc -Wall -w main.c threads.c -o threads"

    Program execution:
    From the executable directory in terminal enter:
    “./threads [number of threads]" 
    

+-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "threads.h";

#define ERR_ARGS "Invalid arguments. Argument most be one positive integer"
#define BASE 10


#include <pthread.h> 
#include <time.h>

#define NTHREADS 4
#define MEGEXTRA 1000000
#define PTHREAD_SYNC



// Global variables -----------------------------------------------------------+
int SharedVariable = 0;
pthread_mutex_t lock_v;
pthread_barrier_t barrier;




void SimpleThread(int which) {
	srand(time(0));
	int num, val;
	int *thread_id = (int *) which;
	if (*thread_id > max_t) max_t = *thread_id; 
	printf("*********** Max Thread %d started *************\n", max_t);
	for(num = 0; num < 20; num++)
	{
		if (rand() > RAND_MAX / 2)
			usleep(10);

		#ifdef PTHREAD_SYNC
			pthread_mutex_lock(&lock_v);
		#endif
		

		val = SharedVariable;
		printf("*** Thread %d sees value %d\n", *thread_id, val);
		SharedVariable = val + 1;
		

		#ifdef PTHREAD_SYNC
			pthread_mutex_unlock(&lock_v);
		#endif
	}

	#ifdef PTHREAD_SYNC
		pthread_barrier_wait(&barrier);
	#endif

	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *thread_id, val);
	pthread_exit(NULL);
}






int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf(ERR_ARGS);
		return EXIT_SUCCESS;
	}
	
	char *endptr;
	int threads_amt = strtol(argv[1], &endptr, BASE);
	
	if (strcmp(endptr,"") != 0 || threads_amt <= 0)
	{
		printf(ERR_ARGS);
		return EXIT_SUCCESS;
	}
	
	pthread_t threads[threads_amt];
	int count, thread_id[threads_amt];
	for (count = 0; count < threads_amt; count++){
		thread_id[count] = count + 1;
	}

	pthread_mutex_init(&lock_v, NULL);
	pthread_barrier_init(&barrier, NULL, threads_amt);


	for (count = 0; count < threads_amt; count++){
		pthread_create(&threads[count], NULL, &SimpleThread, &thread_id[count]);
	}

	

	for (count = 0; count < threads_amt; count++){
    	pthread_join(threads[count], NULL);
  	}
	return EXIT_SUCCESS;

}









