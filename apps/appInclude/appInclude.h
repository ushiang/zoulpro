#ifndef __appInclude_H__
#define __appInclude_H__

#include <stdio.h>


#ifndef GENANN_RANDOM
#define GENANN_RANDOM() (((double)rand())/RAND_MAX)
#endif


typedef double (*genann_actfun)(double a);


typedef struct genann {
    /* How many inputs, outputs, and hidden neurons. */
    int inputs, hidden_layers, hidden, outputs;

    /* Which activation function to use for hidden neurons. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_hidden;

    /* Which activation function to use for output. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_output;

    /* Total number of weights, and size of weights buffer. */
    int total_weights;

    /* Total number of neurons + inputs and size of output buffer. */
    int total_neurons;

    /* All weights (total_weights long). */
    double *weight;
    /* Stores input array and output of each neuron (total_neurons long). */
    double *output;

    /* Stores delta of each hidden and output neuron (total_neurons - inputs long). */
    double *delta;

} genann;


double * intToByte(int x);
double * generateRandChallenge();
unsigned char PUFmodel(double *challenge);

/* Creates and returns a new ann. */
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs);

/* Creates ANN from file saved with genann_write. */
genann *genann_read();

/* Sets weights randomly. Called by init. */
void genann_randomize(genann *ann);

/* Frees the memory used by an ann. */
void genann_free(genann *ann);

/* Runs the feedforward algorithm to calculate the ann's output. */
double const *genann_run(genann const *ann, double const *inputs);


double genann_act_sigmoid(double a);
//double genann_act_sigmoid_cached(double a);


#endif /*__GENANN_H__*/

