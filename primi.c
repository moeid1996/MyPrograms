/*
 * http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

/* Compiling with: -Wall -pedantic -lpthread*/

#define MAX 100*1000 /*limite numeri primi*/
#define nThread 2
#define deb 1
#define DIM 500

/*global vars*/

int cont=1;
int k=3;

/*locking vars*/
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2=PTHREAD_MUTEX_INITIALIZER;


void threads(int nThreads);
void * Baby (void * ptr);

int main(int argc,char * argv[])
{
	int nThreads;	
	clockid_t clk;
	struct timespec tpi,tpf;
	long nseci,nsecf;
	
	if(deb>=1) printf("Argc= %d \n",argc);

	if(argc>=2)
	{
		if(deb>1) printf("args ::  %s %s \n",argv[0],argv[1]);
		nThreads=atoi(argv[1]);
		if(deb>1)printf("in arg evaluation: NChildren= %d \n ",nThreads);
		
		if(nThreads<1)
		{
			printf("\nError retriving NC from arg. Set it at %d default value.\n",nThread);
			nThreads=nThread;
		}
		/* else if(NChildren>NChild)	NChildren=NChild; */
	
	}
	else 
	{
	nThreads=nThread;
	}
	
	clock_gettime(clk,&tpi);	
	nseci=tpi.tv_nsec;
	
	threads(nThreads);	
	 
	printf("\nPrimi: %d  \n",cont); 
	clock_gettime(clk,&tpf);	
	nsecf=tpf.tv_nsec;
	nsecf=nsecf-nseci+1000000000*(tpf.tv_sec-tpi.tv_sec);
	printf("nsec passati %li usec %li msec %li \n",nsecf,nsecf/1000,nsecf/1000000);
		
	exit(1);
}

void threads(int nThreads)
{
	int i,iret;
	pthread_t thread[nThreads];
	/* if (deb==1)	*/
		printf("  threads()  ::  Numero di threads= %i.\n",nThreads);
	/* Create independent threads each of which will execute function */
	for(i=0;i<nThreads;i++)
		iret=pthread_create(&thread[i],NULL,Baby,(void*) &i);

	printf("  threads :: Waiting for babies. \n");
	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	 for(i=0;i<nThreads;i++)
		pthread_join(thread[i],NULL);
}

void * Baby(void *ptr)
{
	int cn; 
	int i,j=2, q;
	bool primo=true;
	
	if(ptr==NULL)
		printf("Error!!! ptr == NULL!!!!\n");
	else 
		cn= * (int *) ptr; 
		
	i=1;
	if (deb==1) printf("Baby %i: i=%i \n",cn,i);
	
	pthread_mutex_lock(&m2);
	for(;k<MAX;)
	{	
		
		q=k;
		k+=2;
		pthread_mutex_unlock(&m2);
		primo=true;
		
		for(;j<q;j++)
		{
		  if(q%j==0)			
		  {					
		   primo=false;    
		   break;
		  }		
		}
		j=2;
	
		if(primo==true)
		{	
		  pthread_mutex_lock(&m1);
		  cont++;
	       	 pthread_mutex_unlock(&m1);
		}
		
		pthread_mutex_lock(&m2);
	}
	
	pthread_mutex_unlock(&m2);
	
	while (i<DIM)
	{
		i++;	
	}
	if (deb==1) 
		printf("Baby %i: Ended\n",cn);
	
}

	
