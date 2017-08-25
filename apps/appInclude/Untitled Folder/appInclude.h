#ifndef __APPINCLUDE_H__
#define __APPINCLUDE_H__

#include "sys/dsc.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GENANN_RANDOM
/* We use the following for uniform random numbers between 0 and 1.
 * If you have a better function, redefine this macro. */
#define GENANN_RANDOM() (((double)rand())/RAND_MAX)
#endif


double * intToByte(int x);
double * generateRandChallenge();
void appincludeprint();
int PUFmodel ();

#ifdef __cplusplus
}
#endif

#endif /*__GENANN_H__*/
