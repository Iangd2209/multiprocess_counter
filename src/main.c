
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

//retorna 1 se o número é primo, 0 se não
int primo (int N){
	int aux=1, div;

	if(N==0 || N==1){
		aux=0;
	} else if(N!=2) {
		for(div=2; div<N; div++){
			if(N%div==0){ aux=0; break;}
		}
	}

	return aux;
}

int main() {

	pid_t process[4];

	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;
  
	int *vetor_primos, *vetor, *tam, *k;
	int i=0, aux=0, x, contador=0;
	char verifier;
	
	vetor_primos = (int*) mmap(NULL, 15*sizeof(int), protection, visibility, 0, 0);
	vetor = (int*) mmap(NULL, 15*sizeof(int), protection, visibility, 0, 0);
	tam = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	k = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);

	if((long int)vetor_primos==-1)	printf("Erro de alocação\n");
	(*vetor_primos)=0;
	(*vetor)=0;
	(*tam)=0;
	(*k)=0;

	while(verifier!='\n'){
		scanf("%d", &x);
		vetor[(*tam)]=x;
		(*tam)++;
		scanf("%c", &verifier);
	}
	
	while((*k)<(*tam))
		for(i=0; i<4; i++){
			if((*k)<=(*tam)){
				process[i]=fork();
				
				if(process[i]==0){
					x=vetor[(*k)];
					aux=primo(x);
					vetor_primos[(*k)]=aux;
		
					(*k)++;
					
					exit(0);
				}

				waitpid(process[i], NULL, 0);
			}
		}		

	for((*k)=0; (*k)<(*tam); (*k)++){
		if(vetor_primos[(*k)]==1) contador++;
	}
		
	printf("%d\n", contador);
	
	return 0;
}
