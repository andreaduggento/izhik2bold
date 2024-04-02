#define Eneurons 800
#define Ineurons 200
#define NCOLONNE 20
#define NTHREADS 9
#define NNODI	 9
#define STR1	 NNEURONS
#define connectionProbability 0.2
#define THREADON 0

#define taugA 5                                                                                                            
#define taugN 150                                                                                               
#define taugGa 6                                                                               
#define taugGb 150  

#define Uexcitatory 0.5
#define Dexcitatory 800
#define Fexcitatory 1000

#define Uinhibitory 0.2
#define Dinhibitory 700
#define Finhibitory 20

#define nnInterconn 100
#define syndelay 50   	// measured in dt
#define dt 0.2  	// measured in ms
#define restFreq 2.1

#define durata 1200000
#define discard 5000


typedef struct neuron neuron;
typedef struct column column;
struct neuron {
	float v,u,I,gA,gN,gGa,gGb,tlast,R,w;
	float a,b,c,d;
	float plusG[NCOLONNE];
	float randomI;
	short int s;
	unsigned int nsynaps;
	float* syn_c;
	neuron** preList;	
};

struct column {
	int numerocolonna;
	neuron* neurons;
	unsigned int * nsynapses;
	long unsigned int ** synId;
	float ** c;
	unsigned int nowstate;
	unsigned int * spikingstates;
	
	unsigned int   nExtCol;
	
	unsigned int  nExtSyn[Eneurons];
	unsigned int  IdExtCol[Eneurons];
	long unsigned int * ExtNeuId[Eneurons];
	float * ExtNeuCC[Eneurons];
// Baloon variables
	float B_bold;	
	float B_q;	
	float B_v;
	float B_k1;
	float B_k2;
	float B_k3;
	float B_V0;
	float B_tau0;
	float B_fin;
	float B_fout;
	float B_alpha;
	float B_E;
	float B_E0;
// rCBF variables
	float B_u;
	float B_s;
	float B_e;
	float B_taus;
	float B_tauf;
};

void  initExcitatoryNeuron(neuron* p);
void  initInhibitoryNeuron(neuron* p);

column* createColumn(int , long unsigned int , long unsigned int ,float );

void linkColumn(int ExtC[NCOLONNE][NCOLONNE], column* cP[NCOLONNE],float);

float randomuniform();


