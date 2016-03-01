#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char ** argv){
	int i, val;
	int num=atoi(argv[1]);
	int c,ris=0,pr=0;
	for(val=2; val<=num; val++){
		
	for(i=1; i<=val; i++){
		c=val%i;
		if(c==0)
			pr++;
	}
		if (pr==2){
			
			ris++;
        }
        pr=0;
	}
	printf("n. primi= %d \n", ris);
	
	
	
}
