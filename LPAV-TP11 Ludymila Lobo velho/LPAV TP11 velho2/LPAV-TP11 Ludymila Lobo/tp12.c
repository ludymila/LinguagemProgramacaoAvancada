#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **matResult;
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

void print_mat(int **mat, int n)
{
  int i = 0; 
  int j = 0;
 for(i = 0;i < n;i++)
 {
	for(j = 0;j < n;j++)
  	{
   		 printf("%d\t",mat[i][j]);
 	 }
	printf("\n");
  }
  
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

void *calculate_two_elements_mat(void **matptr)
{	
	pthread_mutex_lock(&mutex1);	
	int i, coluna,linha,somaProd,n;	
	 n = amount_of_elements_in_run;
	int **mat = (int**)matptr;
	
	//for (linha=0; linha<n; linha++)
	//for (coluna=0; coluna<n; coluna++){
	while(amount_of_elements_in_run > 1)
	{		
		for (coluna=0; coluna<n; coluna++){		
			somaProd=0;
			for(i=0;i<n;i++) somaProd+= mat[linha][i]*mat[i][coluna];
			matResult[linha][coluna] = somaProd;
		}		
		//matResult[0] = matResult[0] + vector[amount_of_elements_in_run-1]; // Soma o primeiro	
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

int **generate_random_matrix( int n)
{
	int i,j;	
	int **matriz;
	matriz = (int**)malloc(sizeof(int*)*n);
	matResult = (int**)malloc(sizeof(int*)*n);
	for (i=0; i<n;i++) {
		matriz[i] = (int*)malloc (sizeof(int)*n);
		matResult[i] = (int*)malloc (sizeof(int)*n);
	}
	
	// Initialize the array
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			matriz[i][j] = rand() % 10;
	 
	

	return matriz;
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

//calcula multiplicacao de matriz na main
int calculate_sum_matriz_in_main(int **mat, int n, double *spent_time)
{
	struct timeval antes, depois ;
    *spent_time = 0;
    gettimeofday (&antes, 0) ;
	int sum = 0;	
	int i = 0;
	int linha,coluna;
	int somaProd=0;
	for (linha=0; linha<n; linha++)
	for (coluna=0; coluna<n; coluna++){
		somaProd=0;
		for(i=0;i<n;i++) somaProd+= mat[linha][i]*mat[i][coluna];
		mat[linha][coluna] = somaProd;
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

// Calcula multiplicacao da matriz com k threads
/*void calculate_mult_matriz_with_k_threads(int **mat, int n, int amount_of_threads, double *spent_time)
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
		pthread_create(threads_vector + index,NULL,&calculate_two_elements_mat,(void*)mat);		
	}
	close_threads(threads_vector,amount_of_threads);
	gettimeofday (&depois, 0) ; 
   	*spent_time =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );	
}*/


int main(int argc, char **argv)
{	
	if(argc == 2)
	{
		 srand(time(NULL));
		int n = atoi(argv[1]);
		//int k = atoi(argv[2]);	
		int **matriz; 
		
		printf("* Tamanho da entrada: %d\n",n);
		//printf("* Quantidade de threads: %d\n",k);
		amount_of_elements_in_run = n;
		printf("\n");
			
		double spent_time = 0,spent_time2 = 0; // variável de contagem de tempo

		matriz = generate_random_matrix(n);

		printf("* Soma dos elementos do vetor na Thread Main: %d\n",calculate_sum_matriz_in_main(matriz,n,&spent_time));
		printf("* Tempo decorrido na Thread Main (microssegundos): %lf\n\n",spent_time);
		/*
		calculate_sum_vector_with_k_threads(vector,n,k,&spent_time2);
		printf("* Soma dos elementos do vetor Com k(%d)-Threads: %d\n",k,vector[0]);
		printf("* Tempo decorrido com k(%d)-Threads (microssegundos): %lf\n",k,spent_time2);	
		printf("%lf\n",spent_time2);*/	
	} else 
	{
		printf("* Deve-se haver três argumentos de entrada!\n"); 	
		printf("* ./<arquivo-executavel> <tamanho do vetor> <quantidade de threads>\n");	
	}

	exit(0);
}
