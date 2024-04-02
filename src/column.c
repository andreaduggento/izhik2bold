#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "neurons.h"

void *print_message_functionL( void *ptr );
void *summaryColonna();
void *lavoraLinkedColonna(column* cp);
void *lavoraColonna(void *ptr);

const unsigned long int NNEURONS = Eneurons + Ineurons ;

column* colonna[NCOLONNE];

int matriceConnessioniTraColonne[NCOLONNE][NCOLONNE]=
{  
	{0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 1, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 1, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 1, 0, 0, 0} ,
	{0, 0, 0, 0, 1, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 1, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 1, 0, 0} 
};

FILE *p0;
FILE *p1;
FILE *p2;
FILE *p3;
FILE *p4;
FILE *p5;
FILE *p6;
FILE *p7;
FILE *p8;
FILE *p9;
FILE *p10;

int main(int argc, char *argv[])
{

	if ( argc != 3 ) { printf( "usage: %s filename random", argv[0] ); exit(1);}

        FILE *file = fopen( argv[1], "r" );

	char str0[180]; strcpy(str0, argv[1]); strcat(str0, "_1..txt"); 
	char str1[180]; strcpy(str1, argv[1]); strcat(str1, "_.9.txt");
	char str2[180]; strcpy(str2, argv[1]); strcat(str2, "_.8.txt");
	char str3[180]; strcpy(str3, argv[1]); strcat(str3, "_.7.txt");
	char str4[180]; strcpy(str4, argv[1]); strcat(str4, "_.6.txt");
	char str5[180]; strcpy(str5, argv[1]); strcat(str5, "_.5.txt");
	char str6[180]; strcpy(str6, argv[1]); strcat(str6, "_.4.txt");
	char str7[180]; strcpy(str7, argv[1]); strcat(str7, "_.3.txt");
	char str8[180]; strcpy(str8, argv[1]); strcat(str8, "_.2.txt");
	char str9[180]; strcpy(str9, argv[1]); strcat(str9, "_.1.txt");
	char str10[180]; strcpy(str10, argv[1]); strcat(str10, "_.72.txt");

	int randominit;
	if(sscanf(argv[2], "%d", &randominit)!=1){ printf( "err: scan randominit"); exit(1); };

    time_t start, end;
    double first, second;
// Save user and CPU start time
     time(&start);

     srand(randominit);

     long int i,j;
     
     unsigned long int rounder= round(1./dt);

     unsigned long int rounder0= round(1000./dt);
     unsigned long int rounder1= round(900./dt);
     unsigned long int rounder2= round(800./dt);
     unsigned long int rounder3= round(700./dt);
     unsigned long int rounder4= round(600./dt);
     unsigned long int rounder5= round(500./dt);
     unsigned long int rounder6= round(400./dt);
     unsigned long int rounder7= round(300./dt);
     unsigned long int rounder8= round(200./dt);
     unsigned long int rounder9= round(100./dt);
     unsigned long int rounder10= round(720./dt);

     
     for(i=0;i<NCOLONNE;i++) for(j=0;j<NCOLONNE;j++)
	     fscanf(stdin,"%d",&matriceConnessioniTraColonne[i][j]);
     
     for(i=0;i<NCOLONNE;i++) {
     for(j=0;j<NCOLONNE;j++) {
	     fprintf(stdout,"%d ",matriceConnessioniTraColonne[i][j]);
     }
	     fprintf(stdout,"\n");

     }
     
     p0=fopen(str0,"w");
     p1=fopen(str1,"w");
     p2=fopen(str2,"w");
     p3=fopen(str3,"w");
     p4=fopen(str4,"w");
     p5=fopen(str5,"w");
     p6=fopen(str6,"w");
     p7=fopen(str7,"w");
     p8=fopen(str8,"w");
     p9=fopen(str9,"w");
     p10=fopen(str10,"w");

     // APERTURA THREADS
     pthread_t *threadlist;
     if(THREADON)     threadlist = (pthread_t *) malloc(NTHREADS*sizeof(pthread_t));
     int ti[NTHREADS];

     for (i=0;i<NCOLONNE;i++) colonna[i]=createColumn(i,Eneurons,Ineurons,connectionProbability);

     int* group; 
     if(THREADON) group=(int*)malloc(NTHREADS*sizeof(int));
     if(THREADON) for (i=0;i<NTHREADS;i++) group[i]=i;

     linkColumn(matriceConnessioniTraColonne,colonna,0.5);


    /* MAIN CYCLE */
     for (j=-round(discard/dt);j<durata/dt;j++){

	    /* Create independent threads each of which will execute one timestep on one column */

if(THREADON)	     for (i=0;i<NTHREADS;i++){
		ti[i] = pthread_create( threadlist+i , NULL, lavoraColonna, (void*) colonna[i]);
     		if(ti[i]){fprintf(stderr,"Error - pthread_create() return code: %d\n",ti[i]);exit(EXIT_FAILURE);}
	}

	    /* Join all threads */
     	if(THREADON) for (i=0;i<NTHREADS;i++){
             pthread_join(threadlist[i],NULL);
        }

if(!THREADON)     for (i=0;i<NCOLONNE;i++)	lavoraColonna( (void*) colonna[i]);

	if( j>-1 && j%rounder == 0) summaryColonna(NULL,NULL,stdout);

	if( j>-1 && j%rounder0 == 0) summaryColonna(NULL,NULL,p0);
	if( j>-1 && j%rounder1 == 0) summaryColonna(NULL,NULL,p1);
	if( j>-1 && j%rounder2 == 0) summaryColonna(NULL,NULL,p2);
	if( j>-1 && j%rounder3 == 0) summaryColonna(NULL,NULL,p3);
	if( j>-1 && j%rounder4 == 0) summaryColonna(NULL,NULL,p4);
	if( j>-1 && j%rounder5 == 0) summaryColonna(NULL,NULL,p5);
	if( j>-1 && j%rounder6 == 0) summaryColonna(NULL,NULL,p6);
	if( j>-1 && j%rounder7 == 0) summaryColonna(NULL,NULL,p7);
	if( j>-1 && j%rounder8 == 0) summaryColonna(NULL,NULL,p8);
	if( j>-1 && j%rounder9 == 0) summaryColonna(NULL,NULL,p9);
	if( j>-1 && j%rounder10 == 0) summaryColonna(NULL,NULL,p10);



     if((int)((j*dt))%100==0) fprintf(stderr," sec. %.2f / %d \r",(j*dt)/1000.,durata/1000);
//     fprintf(stderr," %d \n",j);
     }

     time(&end);
     fprintf(stderr,"Spent  %d to simulate %d seconds \n",(int)(end-start),durata/1000);

if(THREADON)     free(threadlist);

	fclose(p0);
	fclose(p1);
	fclose(p2);
	fclose(p3);
	fclose(p4);
	fclose(p5);
	fclose(p6);
	fclose(p7);
	fclose(p8);
	fclose(p9);
	fclose(p10);

     exit(EXIT_SUCCESS);
}

int printNeuron(FILE* pfile,column* C,unsigned long int neu){
		float v=C->neurons[neu].v;
		
       		fprintf(pfile,"%.1f	%.1f	%.1f	%.3f	%.3f 	%.3f	%.3f 	%.3f	%.3f   %.3f   %.3f   %.3f\n"
		,C->neurons[neu].v
		,C->neurons[neu].u
		,C->neurons[neu].w
		,C->neurons[neu].I
		,C->neurons[neu].randomI
		,C->neurons[neu].gA   
		,C->neurons[neu].gN 
		,C->neurons[neu].gGa   
		,C->neurons[neu].gGb
		,C->neurons[neu].R
		,C->neurons[neu].w
		,C->neurons[neu].gA*  ( v - 0.  ) 
		,C->neurons[neu].gN*  ( powf((v+80.)/60.,2) / ( 1.+ powf((v+80.)/60.,2) ) * ( v - 0.)  ) 
		,C->neurons[neu].gGa* ( v + 70. ) 
		,C->neurons[neu].gGb* ( v + 90. ) 
 );
     return 0;
}

int printColumn(column* C){
		int neu;

		for(neu=0;neu<20;neu++) printf("%.1f\t",C->neurons[neu].v);
       		printf("\n");
     return 0;
}

//void *summaryColonna(column* c){
void *summaryColonna(FILE* p1, FILE *p2, FILE* p3){
     unsigned long int i,j;
     float TOTspikes=0.;
     float MEANmembrane=0.;
     float TOTgAnpa=0.;
     column* c;

if(p1!=NULL){     
     for(j=0;j<NCOLONNE;j++){
	c=colonna[j];
     	TOTspikes=0.;
	for(i=0;i<(Eneurons+Ineurons);i++) TOTspikes += c->neurons[i].s;
	fprintf(p1,"%.0f ",TOTspikes);
     }
     fprintf(p1,"\n");
}

if(p2!=NULL){     
     for(j=0;j<NCOLONNE;j++){
	c=colonna[j];
     	MEANmembrane=0.;
	for(i=0;i<(Eneurons+Ineurons);i++) MEANmembrane += c->neurons[i].v;
 	MEANmembrane /= (float)(Eneurons+Ineurons);
	fprintf(p2,"%.2f ",MEANmembrane);
     }
     fprintf(p2,"\n");
}
	
if(p3!=NULL){     
     for(j=0;j<NCOLONNE;j++){
	c=colonna[j];
	fprintf(p3,"%g ",c->B_bold);
// TOTgAnpa=0.;
// for(i=0;i<(Eneurons+Ineurons);i++) TOTgAnpa += c->neurons[i].gA + c->neurons[i].gN ;
// 
// fprintf(p3,"%.0f ",TOTgAnpa);
// 
// fprintf(p3,"%f ",c->B_u);
// fprintf(p3,"%f ",c->B_s);
// fprintf(p3,"%f ",c->B_fin);
// 
// fprintf(p3,"%f ",c->B_q);	
// fprintf(p3,"%f ",c->B_v);
// fprintf(p3,"%f ",c->B_k1);
// fprintf(p3,"%f ",c->B_k2);
// fprintf(p3,"%f ",c->B_k3);
// fprintf(p3,"%f ",c->B_V0);
// fprintf(p3,"%f ",c->B_tau0);
// fprintf(p3,"%f ",c->B_fout);
// fprintf(p3,"%f ",c->B_alpha);
// fprintf(p3,"%f ",c->B_E);
// fprintf(p3,"%f ",c->B_E0);
// fprintf(p3,"%f ",c->B_e);
// fprintf(p3,"%f ",c->B_taus);
// fprintf(p3,"%f ",c->B_tauf);
     }
     fprintf(p3,"\n");
}
     return NULL;
}


void *lavoraColonna(void *ptr)
{
     unsigned long int i,j,k;
     float v,u;
     column *cP; column C;
     cP = (column*) ptr; C=*cP;
     		
     for(i=0;i<(Eneurons+Ineurons);i++){
	v=cP->neurons[i].v;
	u=cP->neurons[i].u;

	cP->neurons[i].I =  
		  cP->neurons[i].gA*  ( v - 0.  ) 
		+ cP->neurons[i].gN*  ( powf((v+80.)/60.,2) / ( 1.+ powf((v+80.)/60.,2) ) * ( v - 0.)  ) 
		+ cP->neurons[i].gGa* ( v + 70. ) 
		+ cP->neurons[i].gGb* ( v + 90. );

	cP->neurons[i].randomI += - dt* cP->neurons[i].randomI/10.;    
	if (cP->neurons[i].randomI<0.01) if(randomuniform()<(restFreq*dt/1000.)) cP->neurons[i].randomI += - 10.; 
    	cP->neurons[i].I += cP->neurons[i].randomI ; 
	
	cP->neurons[i].v += dt*( 0.04*v*v + 5.*v + 140. - u -  cP->neurons[i].I );	     
	cP->neurons[i].u += dt*( cP->neurons[i].a*(cP->neurons[i].b*v - u )  );

	cP->neurons[i].gA  += - dt * cP->neurons[i].gA / taugA ;
	cP->neurons[i].gN  += - dt * cP->neurons[i].gN / taugN ;
	cP->neurons[i].gGa += - dt * cP->neurons[i].gGa / taugGa ;
	cP->neurons[i].gGb += - dt * cP->neurons[i].gGb / taugGb ;
     	for (j=0;j<cP->nsynapses[i];j++){					// stessa colonna
		unsigned long int preId=cP->synId[i][j];
		if (cP->neurons[preId].s){
		if (preId<Eneurons){
			cP->neurons[i].gA  += cP->c[i][j] * cP->neurons[preId].R * cP->neurons[preId].w ;
			cP->neurons[i].gN  += cP->c[i][j] * cP->neurons[preId].R * cP->neurons[preId].w ;
		}
		else{
			cP->neurons[i].gGa  += cP->neurons[preId].R * cP->neurons[preId].w ;
			cP->neurons[i].gGb  += cP->neurons[preId].R * cP->neurons[preId].w ;
		}
		}	
	}
	for(k=0;k<NCOLONNE;k++) { cP->neurons[i].gA += cP->neurons[i].plusG[k]; cP->neurons[i].gN += cP->neurons[i].plusG[k]; cP->neurons[i].plusG[k]=0.; } 
     }

//     printColumn(colP);
//     printNeuron(p0,cP,0);
//     printNeuron(p1,cP,1);
//     printNeuron(p2,cP,2);
//     printNeuron(p3,cP,3);
//     printNeuron(p4,cP,4);
//     printNeuron(p5,cP,5);
//     printNeuron(p6,cP,6);

     for(i=0;i<(Eneurons+Ineurons);i++){
	if (cP->neurons[i].s){
		cP->neurons[i].s = 0;
		cP->neurons[i].tlast += dt;
	}
	else{
		if(cP->neurons[i].v>30.){
			cP->neurons[i].s = 1;
			cP->neurons[i].tlast = 0.;
			cP->neurons[i].v = cP->neurons[i].c ;
			cP->neurons[i].u += cP->neurons[i].d ;	
			cP->neurons[i].randomI = 0. ;
		}
	}

     cP->spikingstates[ i*syndelay + cP->nowstate % syndelay ] = cP->neurons[i].s;
     }

     cP->nowstate= (cP->nowstate+1)% syndelay ;
     for(i=0;i<Eneurons;i++){ 				// External synapses
	if (cP->spikingstates[ i*syndelay + cP->nowstate]) {
		for(j=0;j<cP->nExtSyn[i];j++){
			colonna[cP->IdExtCol[i]]->neurons[cP->ExtNeuId[i][j]].plusG[cP->numerocolonna]  += cP->ExtNeuCC[i][j] * cP->neurons[i].R * cP->neurons[i].w ;
		}	
	}
	
     }
      

     for(i=0;i<Eneurons;i++){
	cP->neurons[i].R += dt * (1. - cP->neurons[i].R ) / Dexcitatory ;
	if (cP->neurons[i].s) cP->neurons[i].R += - cP->neurons[i].R * cP->neurons[i].w ;
	cP->neurons[i].w += dt * (Uexcitatory - cP->neurons[i].w ) / Fexcitatory ;
	if (cP->neurons[i].s) cP->neurons[i].w += Uexcitatory * (1. - cP->neurons[i].w );
     }
     for(i=Eneurons;i<(Eneurons+Ineurons);i++){
	cP->neurons[i].R += dt * (1. - cP->neurons[i].R ) / Dinhibitory ;
	if (cP->neurons[i].s) cP->neurons[i].R += - cP->neurons[i].R * cP->neurons[i].w ;
	cP->neurons[i].w += dt * (Uinhibitory - cP->neurons[i].w ) / Finhibitory ;
	if (cP->neurons[i].s) cP->neurons[i].w += Uinhibitory * (1. - cP->neurons[i].w );
     }

     // rCBF and BOLD
	float TOT_u;
	TOT_u=0.;
	for(i=0;i<(Eneurons+Ineurons);i++) TOT_u += cP->neurons[i].gA + cP->neurons[i].gN ;
	cP->B_u = TOT_u / (Eneurons+Ineurons) ;

	cP->B_s += dt * ( cP->B_e * cP->B_u  -  cP->B_s / cP->B_taus  - (cP->B_fin - 1. )/ cP->B_tauf ); 
	
	cP->B_fin += dt * cP->B_s ; 


     // Balloon model
 	cP->B_E  = 1. - pow( 1.- cP->B_E0 , 1./cP->B_fin ) ;
	
	cP->B_q += dt / cP->B_tau0 * ( cP->B_fin * cP->B_E / cP->B_E0 - cP->B_fout * cP->B_q / cP->B_v );

	cP->B_fout = pow ( cP->B_v , 1./cP->B_alpha ) ;

	cP->B_v += dt/cP->B_tau0 * ( cP->B_fin - cP->B_fout ); 

	cP->B_k1 = 7.* cP->B_E0;
	cP->B_k3 = 2.* cP->B_E0 - 2.;

	cP->B_bold = cP->B_V0*(  cP->B_k1*(1.-cP->B_q) + cP->B_k2*(1.-cP->B_q/cP->B_v) + cP->B_k3*(1.-cP->B_v) );
		

}





























