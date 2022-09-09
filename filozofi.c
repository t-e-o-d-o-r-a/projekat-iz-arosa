#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t soba;  //counting semaphore jer u sobu moze da udje vise filozofa u 			isto vreme
sem_t stapic[5];  //binarni semafor


void* filozof(void* arg);
void jede(int f);

int main(){

	int br[5]; //odnosi se na broj svakog filozofa
	pthread_t nit[5];  //5 niti = 5 filozofa = 5 procesa 
			//oni su niti jer treba da se izvrsavaju istovremeno
	
	sem_init(&soba, 0, 4); //nula u sredini znaci da vise niti deli 						ovaj semafor
	//u sobu smeju samo 4 filozofa da ne bi doslo do deadlock-a	
	
	for (int i = 0; i<5; i++){
		sem_init(&stapic[i], 0, 1);
	}
	for (int i = 0; i<5; i++){
		br[i] = i;
		pthread_create(&nit[i], NULL, filozof, (void*)&br[i]);
	}
	for(int i = 0; i<5; i++){
		pthread_join(nit[i], NULL);
	}

	return 0;
}

void* filozof(void* arg){
	int f = *(int *)arg;

	sem_wait(&soba);
	printf("Filozof %d je usao u sobu.\n", f);
	
	sem_wait(&stapic[f]);
	sem_wait(&stapic[(f+1)%5]);
	
	jede(f);
	sleep(2);
	printf("Filozof %d je zavrsio sa jelom.\n", f);
	
	sem_post(&stapic[(f+1)%5]);
	sem_post(&stapic[f]);
	sem_post(&soba);
}

void jede(int f){
	printf("Filozof %d jede.\n", f);
}





