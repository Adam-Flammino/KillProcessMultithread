/* Adam Flammino
SDEV385
2/21/18
Multithreaded program to determine what happens to threads when a process is killed

Written and tested in Debian 9.3

base program from https://www.thegeekstuff.com/2012/04/create-threads-in-linux/?utm_source=feedburner
*/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing.\n");
	for (int i = 0; i < 1000; i++){
	  printf("\nThread one is running. %d remaining.", 25 - i);
	  sleep(1);
	  if (i == 25){
	    printf("\nThread one stopped on its own.");// If this doesn't print, the thread was killed before it completed the loop because it stopped when the process was killed.
	  }
	}
    }
    else
    {
        printf("\n Second thread processing.\n");
	for (int i = 0; i < 1000; i++){
	  printf("\nThread two is running. %d remaining.", 25 - i);
	  sleep(1);
	  if (i == 25){
	    printf("\nThread two stopped on its own"); // If this doesn't print, the thread was killed before it completed the loop because it stopped when the process was killed.
	  }
	}
    }

    for(i=0; i<(0xFFFFFFFF);i++);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\nThread created successfully\n");

        i++;
    }
    sleep(5);
    printf("\nProcess exiting...");
    exit(0); // Exits process
    return 0;
}
