#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int amount_of_elements_in_run = 0; // quantidade de elementos do vetor que irá
// descrescendo conforme acontece a execução
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Mutex para evitar 
// inconsistência na região crítica
// imprime vetor
void print_v(int v[], int n)
{
  int i = 0;
  while(i<n)
  {
    printf("%d\t",v[i]);
    i++;
  }
  printf("\n");
}
// Calcula dois elementos no vetor(primeiro e ultimo) e insere no início enquanto
// A variável de contagem amount_of_elements_in_run não é 1
void *calculate_two_elements(void *vectorptr)
{	
	pthread_mutex_lock(&mutex1);	
	int i;	
	 
	int *vector = (int*)vectorptr;
	
	while(amount_of_elements_in_run > 1)
	{		
		vector[0] = vector[0] + vector[amount_of_elements_in_run-1]; // Soma o primeiro	
		// Elemento com o último
		amount_of_elements_in_run--; // Decrementa a variável de contagem
	}	
	pthread_mutex_unlock(&mutex1);
}

// troca elementos de vetores
void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp; 
}

// Gera vetor aleatório
int *generate_random_vector( int n)
{
	int *v;
	v = (int*)malloc(sizeof(int)*n);
	int i;
	// Initialize the array
	for(i = 0;i < n;++i)
		v[i] = i;
	 
	// Shuffle the array
	int w ;
	for(i = n - 1;i > 0;--i)
	{
	   w = rand() % i;     
	  swap(&v[i],&v[w]);
	}

	return v;
}
// Calcula a soma do vetor na thread main
int calculate_sum_vector_in_main(int vector[], int n, double *spent_time)
{
	struct timeval antes, depois ;
    *spent_time = 0;
    gettimeofday (&antes, 0) ;
	int sum = 0;	
	int i = 0;
	while(i < n)
	{
		sum = sum + vector[i]; 		
		i++;
	}	
	gettimeofday (&depois, 0) ; 
   	*spent_time =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
	return sum;
}
// Fecha as threads
void close_threads(pthread_t threads_vector[], int amount_of_threads)
{
	int index;
	for(index=0;index<amount_of_threads;index++)
	{
		pthread_join(threads_vector[index] ,NULL);
	}
}
// Calcula soma do vetor com k threads
void calculate_sum_vector_with_k_threads(int *vector, int n, int amount_of_threads, double *spent_time)
{
	struct timeval antes, depois ;
    *spent_time = 0;
    gettimeofday (&antes, 0) ;
    
    amount_of_elements_in_run = n; // Variável global recebe o tamanho do vetor
    // Esta variável ajudará para que a execução das threads funcionem de forma 
    // Consistente no vetor

	pthread_t threads_vector[amount_of_threads]; // Cria vetor de Threads

	int index; // Ativa cada thread do vetor. 
	for(index=0;index<amount_of_threads ;index++)
	{			
		pthread_create(threads_vector + index,NULL,&calculate_two_elements,(void*)vector);		
	}
	close_threads(threads_vector,amount_of_threads);
	gettimeofday (&depois, 0) ; 
   	*spent_time =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );	
}


int main(int argc, char **argv)
{	
	if(argc == 3)
	{
		 srand(time(NULL));
		int n = atoi(argv[1]);
		int k = atoi(argv[2]);	
		int *vector; 
		
		printf("* Tamanho da entrada: %d\n",n);
		printf("* Quantidade de threads: %d\n",k);
		amount_of_elements_in_run = n;
		printf("\n");
			
		double spent_time = 0,spent_time2 = 0; // variável de contagem de tempo

		vector = generate_random_vector(n);

		printf("* Soma dos elementos do vetor na Thread Main: %d\n",calculate_sum_vector_in_main(vector,n,&spent_time));
		printf("* Tempo decorrido na Thread Main (microssegundos): %lf\n\n",spent_time);
		
		calculate_sum_vector_with_k_threads(vector,n,k,&spent_time2);
		printf("* Soma dos elementos do vetor Com k(%d)-Threads: %d\n",k,vector[0]);
		printf("* Tempo decorrido com k(%d)-Threads (microssegundos): %lf\n",k,spent_time2);	
		printf("%lf\n",spent_time2);	
	} else 
	{
		printf("* Deve-se haver três argumentos de entrada!\n"); 	
		printf("* ./<arquivo-executavel> <tamanho do vetor> <quantidade de threads>\n");	
	}

	exit(0);
}
//./tp12 500 2 && ./tp12 500 4 && ./tp12 500 8 && ./tp12 500 16 && ./tp12 500 32 && ./tp12 500 64
//./tp12 1000 2 && ./tp12 1000 4 && ./tp12 1000 8 && ./tp12 1000 16 && ./tp12 1000 32 && ./tp12 1000 64 
//./tp12 2000 2 && ./tp12 2000 4 && ./tp12 2000 8 && ./tp12 2000 16 && ./tp12 2000 32 && ./tp12 2000 64 
//./tp12 5000 2 && ./tp12 5000 4 && ./tp12 5000 8 && ./tp12 5000 16 && ./tp12 5000 32 && ./tp12 5000 64 
//./tp12 10000 2 && ./tp12 10000 4 && ./tp12 10000 8 && ./tp12 10000 16 && ./tp12 10000 32 && ./tp12 10000 64 
//./tp12 50000 2 && ./tp12 50000 4 && ./tp12 50000 8 && ./tp12 50000 16 && ./tp12 50000 32 && ./tp12 50000 64 