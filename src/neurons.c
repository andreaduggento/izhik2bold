#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neurons.h"

void  initExcitatoryNeuron(neuron* p)
{
	float r = randomuniform();
	float r2 = r*r;
	unsigned int i;
	p->I=0.;
	p->gA=.1;
	p->gN=.1;
	p->gGa=.1;
	p->gGb=.1;
	p->tlast=1000.;
	p->R=1.;
	p->w=.2;
	p->randomI=0.;
	p->s=0;
	p->a=0.02;
	p->b=0.2;
	p->c=-65. + 15.*r2;
	p->d=8.- 6.*r2;	
	for (i=0;i<NCOLONNE;i++) p->plusG[i]=0.;
	

	p->v= p->c;
	p->u= (p->b) * (p->c);
	return;
}

void  initInhibitoryNeuron(neuron* p)
{
	float r = randomuniform();
	float r2 = r*r;
	unsigned int i;
	p->I=0.;
	p->I=0.;
	p->gA=.1;
	p->gN=.1;
	p->gGa=.1;
	p->gGb=.1;
	p->tlast=1000.;
	p->R=1.;
	p->w=.2;
	p->randomI=0.;
	p->s=0;
	p->a=0.02 + 0.08*r;
	p->b=0.25 - 0.05*r;
	p->c=-65.;
	p->d=2.;	
	for (i=0;i<NCOLONNE;i++) p->plusG[i]=0.;

	p->v= p->c;
	p->u= (p->b) * (p->c);
	return;
}


column* createColumn(int id, long unsigned int eneurons, long unsigned int ineurons,float connectionprobability)
{
	long unsigned int i,j;
	long unsigned int totN=eneurons+ineurons;
	int tempC[totN];

	column * col;
	if((col=(column*) malloc(sizeof(column)))!=NULL ){} else return NULL;

	col->numerocolonna=id;
	col->neurons = (neuron*) malloc(totN*sizeof(neuron));	
	col->nsynapses = (unsigned int*) malloc(totN*sizeof(unsigned int));	
	col->synId = (long unsigned int **) malloc(totN*sizeof(unsigned long int*));	
	col->c = (float**) malloc(totN*sizeof(float*));
	col->spikingstates = (unsigned int*) malloc(totN*syndelay*sizeof(unsigned int));
	for(i=0;i<totN;i++) for(j=0;j<syndelay;j++) col->spikingstates[i*syndelay+j]=0;
	col->nowstate=0;

	col->nExtCol=0;

	// wiring
	for(i=0;i<totN;i++){
		unsigned int conn=0;
		for(j=0;j<totN;j++) if(randomuniform()<connectionprobability) { tempC[j]=1; conn++; }  else tempC[j] = 0 ;
		col->nsynapses[i] = conn; 
		col->synId[i] = (unsigned long int*) malloc(conn*sizeof(unsigned long int));
		col->c[i] = (float*) malloc(conn*sizeof(float));
		conn=0;		
		for(j=0;j<totN;j++) if( tempC[j]==1) { col->synId[i][conn]=j;  col->c[i][conn]=0.5; conn++; }  else {} ;
	}

	for(i=0;i<eneurons;i++)	initExcitatoryNeuron(col->neurons+i);
	for(i=eneurons;i<eneurons+ineurons;i++)	initInhibitoryNeuron(col->neurons+i);

	int neu;

	for(neu=0;neu<10;neu++)

//      printf("%.3f	%.3f	%.3f	%.3f 	%.3f	%.3f 	%.3f\n",col->numerocolonna,col->neurons[neu].v,col->neurons[neu].u,col->neurons[neu].w,col->neurons[neu].I
// 		,col->neurons[neu].gA   
// 		,col->neurons[neu].gN 
// 		,col->neurons[neu].gGa   
// 		,col->neurons[neu].gGb  
// 
//  );
// 
// Baloon variables
	col->B_bold	=0.;	
	col->B_q	=1.;	
	col->B_v	=1.;
	col->B_k1	=7.;
	col->B_k2	=2.;
	col->B_k3	=1.8;
	col->B_V0	=0.02;
	col->B_tau0	=1000.;
	col->B_fin	=1.;
	col->B_fout	=1.;
	col->B_alpha	=0.36;
	col->B_E	=1.;
	col->B_E0	=0.8;
// rCBF variables
	col->B_s	=0.;
	col->B_e	=0.00005;
	col->B_taus	=800.;
	col->B_tauf	=400.;

	return col;
}

void linkColumn(int ExtC[NCOLONNE][NCOLONNE],column* cP[NCOLONNE],float connectionprobability)
{

	unsigned int i,j;
	unsigned int ii,jj;
	unsigned int totN=Eneurons+Ineurons;
	int tempC[totN];

	ii=1; jj=2;

	// DA FINIRE CON UN CICLO SU ii jj
	
	for(ii=0;ii<NCOLONNE;ii++)	
		for(jj=0;jj<NCOLONNE;jj++)
			if( ExtC[ii][jj]>0.)
	{
			//connetti ii -> jj
			for(i=0;i<nnInterconn;i++) cP[ii]->IdExtCol[ i ] = jj;		// Indica i neuroni connessi alla colonna jj
			for(i=0;i<nnInterconn;i++){
				unsigned int conn=0;
				for(j=0;j<totN;j++) if(randomuniform()<connectionprobability) { tempC[j]=1; conn++; }  else tempC[j] = 0 ;
				cP[ii]->nExtSyn[i] = conn;
		
			//fprintf(stdout,"%d\n",cP[ii]->nExtSyn[i]);
		
				// Conta quante connessioni uscenti per ogni neurone uscente
				cP[ii]->ExtNeuId[i] = (unsigned long int*) malloc(conn*sizeof(unsigned long int));
				cP[ii]->ExtNeuCC[i] = (float*) malloc(conn*sizeof(float));
				conn=0;		
				for(j=0;j<totN;j++) if( tempC[j]==1) { cP[ii]->ExtNeuId[i][conn]=j;  cP[ii]->ExtNeuCC[i][conn]=0.5; conn++; }  else {} ;
			}
		cP[ii]->nExtCol++;
	}

	return;
}

float randomuniform()
{
	return (((float)rand())/RAND_MAX);
}
























