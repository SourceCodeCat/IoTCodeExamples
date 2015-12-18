#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int keepAlive = 1;

void* doSomeThing(void *arg)
{
    int i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
    }
    //for(i=0; i<(0xFFFFFFFF);i++);
    while(keepAlive == 1)
    {
	printf("seconds:%d \n",i);
	i++;
	sleep(1);
    }
    printf("BYE! from thread..\n");
    return NULL;
}

int main(void)
{
    //int i = 0;
    int err;
    int command = 1;
    int waitingForCommand = 1;

    //while(i < 2)
    //{
    //    err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
    //    if (err != 0)
    //        printf("\ncan't create thread :[%s]", strerror(err));
    //    else
    //        printf("\n Thread created successfully\n");

    //    i++;
    //}

    err = pthread_create(&(tid[0]), NULL, &doSomeThing, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");

     
    printf("\n type 0 to exit: \n");
    while(waitingForCommand == 1)
    {
    	scanf("%d",&command);
        if(command == 0)
	{
	   keepAlive = 0;
           waitingForCommand = 0;
	   printf("Shutting down thread..\n");	 
	}
    }
    sleep(2);    
    return 0;
}
