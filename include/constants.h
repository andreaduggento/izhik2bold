
#ifndef CONSTANTS_FILE
#define CONSTANTS_FILE

#define Eneurons 800
#define Ineurons 200
#define NCOLONNE 20
#define NTHREADS 20
#define STR1	 NNEURONS
#define connectionProbabilityINTRA 0.2
#define connectionProbabilityINTER 0.2
#define THREADON 1

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

#define nnInterconn 20
#define syndelay 10   	// measured in dt
#define hh 5 	 	// measured in ms
#define dt 1. 	 	// measured in ms
#define restFreq 2.1

#define durata 1200000	// measured in ms
#define discard 20000

#define constB_V0	0.02
#define constB_fin	1.
#define constB_fout	1.
#define constB_alpha	0.2
#define constB_E	1.
#define constB_E0	0.8

#define constB_s	0.
#define constB_e	0.0001
#define constB_taus	800.
#define constB_tauf	400.
#define constB_tau0	1000.

#define randdelayRescaleMin	1. 
#define randdelayRescaleScale   3.

#endif

