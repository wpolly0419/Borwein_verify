#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gmp.h"


int main(int argc, char *argv[]){
  int n=0;
  int i,j,k,l;
  int n_max;
  int a_size=1, a_size_prev;
  mpz_t *a;
  srand (time(NULL));
  time_t start, end;
  double time_elapsed;
  if(argc>1){
      n_max=atoi(argv[1]);
  } else {
      n_max=1000;
  }
  time(&start);
  a=(mpz_t *)malloc(sizeof(mpz_t));
  mpz_init(a[0]);
  mpz_set_ui(a[0],1);
  for(n=1;n<=n_max;n++){
    a_size_prev=a_size;
    a_size=3*n*n+1;
    a=(mpz_t *)realloc(a,a_size*sizeof(mpz_t));
    for(i=a_size_prev;i<a_size;i++){mpz_init(a[i]);}
    for(j=a_size-1;j>=0;j--){
      if(j>=3*n-2) mpz_sub(a[j],a[j],a[j-3*n+2]);
      if(j>=3*n-1) mpz_sub(a[j],a[j],a[j-3*n+1]);
      if(j>=6*n-3) mpz_add(a[j],a[j],a[j-6*n+3]);
      if(j%3==0 && mpz_sgn(a[j])==-1){
	gmp_printf("ERROR: The coefficient [q^%d]u_%d(q)=%Zd have bad sign\n",j,n,a[j]);
      }
      if(j%3!=0 && mpz_sgn(a[j])==1){
	gmp_printf("ERROR: The coefficient [q^%d]u_%d(q)=%Zd have bad sign\n",j,n,a[j]);
      }
    }
    if(n%50==0){
      time(&end);
      time_elapsed=difftime(end,start);
      printf("Checked Borwein upto n=%d, %lf seconds passed\n",n,time_elapsed);
      printf("t/(n/100)^4=%f\n",pow(n/100.0,-4)*time_elapsed);
      //      k=rand()%(a_size/4);
      //      gmp_printf("random coefficient: [q^%d]%c_%d(q)=%Zd\n",k/3,'A'+(k%3),n,a[k]);
    }
  }
  return 0;
}
      
