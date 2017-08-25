#include "appInclude.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <random.h>

#define LOOKUP_SIZE 4096
//PUF model



double * intToByte(int x)
{
    double k[16];
    int i;
    i=0;
    while(i<2)
    {
        i++;
        k[i]=x%2;
        x=x/2;
    }
    return k;
}
double * generateRandChallenge()
{
    
    double *C11;
    //srand(rand()*time(NULL));//srand(time(NULL));   
	//random_init(clock_time());        
    double random = 1;//random_rand(); //iki kez rand kullanmak bozuyor genandan gelen outputu
    //printf("%lf\n",random);
    C11=intToByte(random);//converts random numbers into binary format
    return C11;//challenge
}

void appincludeprint()
{
	printf("burdasin\n");
}

int PUFmodel ()
{///////////////////////////LOAD TRAINED ANN//////////////////////////////
int j;
    double *challenge;
    int response=0;
        
    return response;
}
//Puf model








