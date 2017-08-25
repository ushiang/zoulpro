#include "appInclude.h"

#include <stdlib.h>
//#include <string.h>
//#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <random.h>

//#include <contiki.h>


//#define LOOKUP_SIZE 4096
//PUF model
double exp61(int a61)
{
    double e61 = 2.71828182845904523536; // We want e61^a61
    
    double T = 1;
    int k;
    for(k=1; k<=abs(a61); k++)
    T = T*e61;
    T = (a61<0) ? 1/T : T;
    return T;
}
double * intToByte(int x)
{
    static double k[16];
    int i;
    i=0;
    while(i<=16)
    {
        k[i]=(x%2);
        //printf("k[]:%ld",k[i]);
        x=x/2;
        i++;
    }
    return k;
}
double * generateRandChallenge()
{
    double *C;
    //srand(rand()*time(NULL));//srand(time(NULL)); //normal c random doesnot work
    //double random = GENANN_RANDOM()*1000; //iki kez rand kullanmak bozuyor genandan gelen outputu
    //printf("%lf\n",random);
    random_init (random_rand());
    unsigned short random = random_rand();
    C=intToByte(abs(random));//converts random numbers into binary format
    return C;//challenge
}
unsigned char PUFmodel(double *challenge)
{///////////////////////////LOAD TRAINED ANN//////////////////////////////
        genann *ann = genann_init(16,1,4,2);
        if (!ann) 
        {
            printf("Error loading ANN frm code");
        }
///////////////////////////LOAD TRAINED ANN//////////////////////////////
///////////////////////////TEST LOADED TRAINED ANN//////////////////////////////
    int intResponse=0;
    unsigned char response;

    //int i;for(i=16;i>=0;i--)printf("%ld\n",challenge[i]);//shows challenge
    double output = *genann_run(ann, challenge);
    intResponse=output+0.5;//if(output <= 0.5)response=1;else response=0;
    response=(unsigned char)!intResponse;//printf("response=%d", response);
///////////////////////////TEST LOADED TRAINED ANN//////////////////////////////
    genann_free(ann);

    return response;
}
//Puf model
double genann_act_sigmoid(double a) 
{
    if (a < -45.0) return 0;
    if (a > 45.0) return 1;
    return 1.0 / (1 + exp61(-a));
}
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs) 
{
    if (hidden_layers < 0) return 0;
    if (inputs < 1) return 0;
    if (outputs < 1) return 0;
    if (hidden_layers > 0 && hidden < 1) return 0;


    const int hidden_weights = hidden_layers ? (inputs+1) * hidden + (hidden_layers-1) * (hidden+1) * hidden : 0;
    const int output_weights = (hidden_layers ? (hidden+1) : (inputs+1)) * outputs;
    const int total_weights = (hidden_weights + output_weights);

    const int total_neurons = (inputs + hidden * hidden_layers + outputs);

    /* Allocate extra size for weights, outputs, and deltas. */
    const int size = sizeof(genann) + sizeof(double) * (total_weights + total_neurons + (total_neurons - inputs));
    genann *ret;//genann *ret=malloc(size);
    
    if((ret=malloc(size))==NULL) //if((ret=mmem_alloc(&ret,size))==0) //if((ret=malloc(size))==NULL) 
    {
        printf("memory allocation failed\n");
    }
    if (!ret) 
    {
        return 0;
    }

    ret->inputs = inputs;
    ret->hidden_layers = hidden_layers;
    ret->hidden = hidden;
    ret->outputs = outputs;

    ret->total_weights = total_weights;
    ret->total_neurons = total_neurons;

    /* Set pointers */
    ret->weight = (double*)((char*)ret + sizeof(genann));//ret->weight = malloc( sizeof(double)*total_weights);
    ret->output = ret->weight + ret->total_weights;//ret->output = malloc( sizeof(double)*total_neurons);
    ret->delta = ret->output + ret->total_neurons;//ret->delta = malloc( sizeof(double)*(total_neurons - inputs));

    genann_randomize(ret);//gereksiz gibi

    ret->activation_hidden = genann_act_sigmoid;
    ret->activation_output = genann_act_sigmoid;

    ret->weight[0]=90753494625550501507e-01;
    ret->weight[2]=-2.61937258385988788745e-02;
    ret->weight[3]=2.94972605583576574784e-01;
    ret->weight[4]=2.97058986931817925470e-01;
    ret->weight[5]=4.45719547976406393897e-01;
    ret->weight[6]=-2.93582363381281463699e-01;
    ret->weight[7]=-2.26811212794486377620e-01;
    ret->weight[8]=3.48942827590810411564e-01;
    ret->weight[9]=-1.59966073795332175411e-01;
    ret->weight[10]=2.08798902712254118297e-02;
    ret->weight[11]=-1.38625739103493891835e-03;
    ret->weight[12]=1.98763026571433770728e-01;
    ret->weight[13]=-2.34615284268348989194e-01;
    ret->weight[14]=-2.99078021243545585928e-02;
    ret->weight[15]=4.90575591003209465768e-01;
    ret->weight[16]=4.90862178720399777720e-01;
    ret->weight[17]=1.54276745006146048800e-01;
    ret->weight[18]=1.87358407979689806089e-01;
    ret->weight[19]=-3.26377081344670250118e-01;
    ret->weight[20]=1.25689072358955405972e-01;
    ret->weight[21]=-4.70676738239268366293e-01;
    ret->weight[22]=-2.43527361678397086253e-01;
    ret->weight[23]=-3.51811105838901350129e-01;
    ret->weight[24]=2.84291869771266303424e-01;
    ret->weight[25]=-3.08546633844766993171e-01;
    ret->weight[26]=-7.20363824938116265040e-02;
    ret->weight[27]=-3.66491627704757017003e-01;
    ret->weight[28]=5.25169175611414851268e-01;
    ret->weight[29]=-3.04550951034722849897e-01;
    ret->weight[30]=-6.19392397266577653114e-03;
    ret->weight[31]=3.61691501303627316322e-01;
    ret->weight[32]=1.35823423875990695331e-01;
    ret->weight[33]=-1.95286229372243796965e-01;
    ret->weight[34]=2.87544641823069879738e-01;
    ret->weight[35]=-5.72197169908524538862e-01;
    ret->weight[36]=-8.19442271327063334607e-03;
    ret->weight[37]=5.44522236721364349954e-01;
    ret->weight[38]=-3.74460496987050528439e-01;
    ret->weight[39]=4.05823203715285685256e-01;
    ret->weight[40]=7.22345277902831761629e-01;
    ret->weight[41]=-4.23354403287463099126e-01;
    ret->weight[42]=-4.49534101859125567735e-01;
    ret->weight[43]=6.68470305678739662447e-01;
    ret->weight[44]=-1.09231858391969402500e-01;
    ret->weight[45]=-6.42439835184495655618e-01;
    ret->weight[46]=1.50520893243074982415e+00;
    ret->weight[47]=9.68135471458941521128e-01;
    ret->weight[48]=-7.78581388109105487771e-01;
    ret->weight[49]=-2.42219708493622898349e-01;
    ret->weight[50]=-2.93398425791016548292e-01;
    ret->weight[51]=-3.26336241211178157418e-01;
    ret->weight[52]=-7.87447848699161734309e-01;
    ret->weight[53]=1.91131837559686351691e-01;
    ret->weight[54]=5.08018511659579008466e-01;
    ret->weight[55]=-9.40692448908184153389e-02;
    ret->weight[56]=-2.62159492012130901362e-01;
    ret->weight[57]=2.29925136414606025304e-02;
    ret->weight[58]=-5.40286917246000308879e-01;
    ret->weight[59]=-5.58861074844115734983e-01;
    ret->weight[60]=-4.13046932687949897023e-02;
    ret->weight[61]=4.86716881783902433067e-01;
    ret->weight[61]=-9.57386055751714565298e-02;
    ret->weight[63]=1.24151051248265664739e+00;
    ret->weight[64]= 1.80867886260069499205e-01;
    ret->weight[65]=-2.02305400189769113428e-01;
    ret->weight[66]=-3.06469422399775204280e-01;
    ret->weight[67]=-4.09502541779528939081e-02;
    ret->weight[68]=-4.44168384642521618666e-01;
    ret->weight[69]=8.64555155983877665626e-01;
    ret->weight[70]=3.62199884537435790044e-01;
    ret->weight[71]=-2.03618337962750484138e+00;
    ret->weight[72]=-8.08365709615571526037e-01;
    ret->weight[73]=8.08318005948425954976e-01;
    ret->weight[74]=-2.80938316220057660022e-01;
    ret->weight[75]=-1.34685602173862828401e-01;
    ret->weight[76]=1.60427318570503940620e+00;
    ret->weight[77]=1.09965063517207140009e+00;

    return ret;
}
/*genann *genann_read() {
    //int inputs, hidden_layers, hidden, outputs;
    //fscanf(in, "%d %d %d %d", &inputs, &hidden_layers, &hidden, &outputs);

    genann *ann = genann_init(16,1,4,2);
    ann->weight[0]=90753494625550501507e-01;
    ann->weight[2]=-2.61937258385988788745e-02;
    ann->weight[3]=2.94972605583576574784e-01;
    ann->weight[4]=2.97058986931817925470e-01;
    ann->weight[5]=4.45719547976406393897e-01;
    ann->weight[6]=-2.93582363381281463699e-01;
    ann->weight[7]=-2.26811212794486377620e-01;
    ann->weight[8]=3.48942827590810411564e-01;
    ann->weight[9]=-1.59966073795332175411e-01;
    ann->weight[10]=2.08798902712254118297e-02;
    ann->weight[11]=-1.38625739103493891835e-03;
    ann->weight[12]=1.98763026571433770728e-01;
    ann->weight[13]=-2.34615284268348989194e-01;
    ann->weight[14]=-2.99078021243545585928e-02;
    ann->weight[15]=4.90575591003209465768e-01;
    ann->weight[16]=4.90862178720399777720e-01;
    ann->weight[17]=1.54276745006146048800e-01;
    ann->weight[18]=1.87358407979689806089e-01;
    ann->weight[19]=-3.26377081344670250118e-01;
    ann->weight[20]=1.25689072358955405972e-01;
    ann->weight[21]=-4.70676738239268366293e-01;
    ann->weight[22]=-2.43527361678397086253e-01;
    ann->weight[23]=-3.51811105838901350129e-01;
    ann->weight[24]=2.84291869771266303424e-01;
    ann->weight[25]=-3.08546633844766993171e-01;
    ann->weight[26]=-7.20363824938116265040e-02;
    ann->weight[27]=-3.66491627704757017003e-01;
    ann->weight[28]=5.25169175611414851268e-01;
    ann->weight[29]=-3.04550951034722849897e-01;
    ann->weight[30]=-6.19392397266577653114e-03;
    ann->weight[31]=3.61691501303627316322e-01;
    ann->weight[32]=1.35823423875990695331e-01;
    ann->weight[33]=-1.95286229372243796965e-01;
    ann->weight[34]=2.87544641823069879738e-01;
    ann->weight[35]=-5.72197169908524538862e-01;
    ann->weight[36]=-8.19442271327063334607e-03;
    ann->weight[37]=5.44522236721364349954e-01;
    ann->weight[38]=-3.74460496987050528439e-01;
    ann->weight[39]=4.05823203715285685256e-01;
    ann->weight[40]=7.22345277902831761629e-01;
    ann->weight[41]=-4.23354403287463099126e-01;
    ann->weight[42]=-4.49534101859125567735e-01;
    ann->weight[43]=6.68470305678739662447e-01;
    ann->weight[44]=-1.09231858391969402500e-01;
    ann->weight[45]=-6.42439835184495655618e-01;
    ann->weight[46]=1.50520893243074982415e+00;
    ann->weight[47]=9.68135471458941521128e-01;
    ann->weight[48]=-7.78581388109105487771e-01;
    ann->weight[49]=-2.42219708493622898349e-01;
    ann->weight[50]=-2.93398425791016548292e-01;
    ann->weight[51]=-3.26336241211178157418e-01;
    ann->weight[52]=-7.87447848699161734309e-01;
    ann->weight[53]=1.91131837559686351691e-01;
    ann->weight[54]=5.08018511659579008466e-01;
    ann->weight[55]=-9.40692448908184153389e-02;
    ann->weight[56]=-2.62159492012130901362e-01;
    ann->weight[57]=2.29925136414606025304e-02;
    ann->weight[58]=-5.40286917246000308879e-01;
    ann->weight[59]=-5.58861074844115734983e-01;
    ann->weight[60]=-4.13046932687949897023e-02;
    ann->weight[61]=4.86716881783902433067e-01;
    ann->weight[61]=-9.57386055751714565298e-02;
    ann->weight[63]=1.24151051248265664739e+00;
    ann->weight[64]= 1.80867886260069499205e-01;
    ann->weight[65]=-2.02305400189769113428e-01;
    ann->weight[66]=-3.06469422399775204280e-01;
    ann->weight[67]=-4.09502541779528939081e-02;
    ann->weight[68]=-4.44168384642521618666e-01;
    ann->weight[69]=8.64555155983877665626e-01;
    ann->weight[70]=3.62199884537435790044e-01;
    ann->weight[71]=-2.03618337962750484138e+00;
    ann->weight[72]=-8.08365709615571526037e-01;
    ann->weight[73]=8.08318005948425954976e-01;
    ann->weight[74]=-2.80938316220057660022e-01;
    ann->weight[75]=-1.34685602173862828401e-01;
    ann->weight[76]=1.60427318570503940620e+00;
    ann->weight[77]=1.09965063517207140009e+00;

    return ann;
}*/
void genann_randomize(genann *ann) {
    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        double r = GENANN_RANDOM();
        /* Sets weights from -0.5 to 0.5. */
        ann->weight[i] = r - 0.5;
    }
}

void genann_free(genann *ann) {
    /* The weight, output, and delta pointers go to the same buffer. */
    free(ann);
}
double const *genann_run(genann const *ann, double const *inputs) {
    double const *w = ann->weight;
    double *o = ann->output + ann->inputs;
    double const *i = ann->output;

    /* Copy the inputs to the scratch area, where we also store each neuron's
     * output, for consistency. This way the first layer isn't a special case. */
    memcpy(ann->output, inputs, sizeof(double) * ann->inputs);

    int h, j, k;

    const genann_actfun act = ann->activation_hidden;
    const genann_actfun acto = ann->activation_output;

    /* Figure hidden layers, if any. */
    for (h = 0; h < ann->hidden_layers; ++h) {
        for (j = 0; j < ann->hidden; ++j) {
            double sum = 0;
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    sum += *w++ * -1.0;
                } else {
                    sum += *w++ * i[k-1];
                }
            }
            *o++ = act(sum);
        }


        i += (h == 0 ? ann->inputs : ann->hidden);
    }

    double const *ret = o;

    /* Figure output layer. */
    for (j = 0; j < ann->outputs; ++j) {
        double sum = 0;
        for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
            if (k == 0) {
                sum += *w++ * -1.0;
            } else {
                sum += *w++ * i[k-1];
            }
        }
        *o++ = acto(sum);
    }

    /* Sanity check that we used all weights and wrote all outputs. */
    assert(w - ann->weight == ann->total_weights);
    assert(o - ann->output == ann->total_neurons);

    return ret;
}
/*double genann_act_sigmoid_cached(double a) {
    // If you're optimizing for memory usage, just
    // delete this entire function and replace references
    // of genann_act_sigmoid_cached to genann_act_sigmoid

    const double min = -15.0;
    const double max = 15.0;
    static double interval;
    static int initialized = 0;
    static double lookup[LOOKUP_SIZE];

    // Calculate entire lookup table on first run. 
    if (!initialized) {
        interval = (max - min) / LOOKUP_SIZE;
        int i;
        for (i = 0; i < LOOKUP_SIZE; ++i) {
            lookup[i] = genann_act_sigmoid(min + interval * i);
        }
        // This is down here to make this thread safe. 
        initialized = 1;
    }

    int i;
    i = (int)((a-min)/interval+0.5);
    if (i <= 0) return lookup[0];
    if (i >= LOOKUP_SIZE) return lookup[LOOKUP_SIZE-1];
    return lookup[i];
}*/




