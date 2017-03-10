#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int global_k;
int dist, tam, tam_matriz; 

typedef struct intervalo
{
   int begin;
   int end;
}tipoIntervalo;

typedef struct intervaloMatriz
{
   int row;
   int column;
}tipoIntervaloMatriz;

typedef struct intervaloPonteiro
{
   tipoIntervaloMatriz *vector; 
   int length; 
}tipoIntervaloPonteiro; 

int global_index;
int *global_vector; 
int **global_matrix;
int **global_matrix2;
int **global_matrix3;

tipoIntervalo *global_interval_vector;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; 

void imprimeVetor(int v[], int n)
{
  int i = 0;
  while(i<n)
  {
    printf("%d\t",v[i]);
    i++;
  }
  printf("\n");
}
/*Imprime vetor do tipo Intervalo*/
void print_interval_v(tipoIntervalo v[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d(%d)\t",v[i].begin, v[i].end);
	printf("\n");
}

/*A função swap troca elemento dos vetores*/
void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp; 
}

int *geraRandomico( int n)
{
	int i,w;	
	int *v;
	v = (int*)malloc(sizeof(int)*n);
	
	for(i = 0;i < n;++i)
	    v[i] = i;
	 
	for(i = n - 1;i > 0;--i)
	{
	   w = rand() % i;     
	   swap(&v[i],&v[w]);
	}
	return v;
}

int somaVetor_semThread(int vector[], int n, double *tempoExecucao)
{
    struct timeval antes, depois ;
    *tempoExecucao = 0;
    gettimeofday (&antes, 0) ;
    int i=0, sum = 0;	

	while(i < n)
	{
	    sum = sum + vector[i]; 		
	    i++;
	}	
	gettimeofday (&depois, 0) ; 
   	*tempoExecucao =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
	return sum;
}

void close_threads(pthread_t threads_vector[], int cont_threads)
{
	int index;
	for(index=0;index<cont_threads;index++)
	{
		pthread_join(threads_vector[index] ,NULL);
	}
}

tipoIntervalo *vetor_intervalo(int n, int k, int dist)
{
	int i;	
	tipoIntervalo *interval_vector;
	interval_vector = (tipoIntervalo*)malloc(sizeof(tipoIntervalo)*k);
	interval_vector[0].begin = 0;
	interval_vector[0].end = dist;

	for(i=1;i < k;i++)
	{

		interval_vector[i].begin = interval_vector[i-1].end;
		interval_vector[i].end = interval_vector[i-1].end + dist;		
		if(interval_vector[i].end > n)
		{
			interval_vector[i].end = n;
		}
	}
	return interval_vector;
}

void *somaParticoesVetor(void *vector)
{
	tipoIntervalo *pos_vector = (tipoIntervalo*)vector;
	int pos_to_input_the_sum = pos_vector->begin; 
	int amount_of_elements_in_run = pos_vector->end-1;		
	while(amount_of_elements_in_run > pos_to_input_the_sum)	
	{						
		global_vector[pos_to_input_the_sum] = global_vector[pos_to_input_the_sum] + global_vector[amount_of_elements_in_run]; 		
		amount_of_elements_in_run--; 
	}			
}	

void calculaSomaVetor_Threads(int n,int cont_threads, double *tempoExecucao)
{
	struct timeval antes, depois ;
    *tempoExecucao = 0;
    int index;
    gettimeofday (&antes, 0) ;

	//criacao das threads para vetor
	pthread_t threads_vector[cont_threads]; 
	if(n % cont_threads == 0)
		dist = n/cont_threads;
	else dist = n/cont_threads + 1; 
		
	tipoIntervalo *interval_vector; 
	interval_vector = vetor_intervalo(n,cont_threads,dist);

	for(index=0;index<cont_threads;index++)
	{						
		pthread_create(threads_vector + index,NULL,&somaParticoesVetor,(void*)(interval_vector + index));				
	}
	gettimeofday (&depois, 0) ;
	close_threads(threads_vector,cont_threads);
	 
   	*tempoExecucao =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );	
}

int calculaTotalSomaVetor_Threads(int *vector, int n, int k)
{
	int i, sum = 0;	
	for(i=0;i<n;)
	{
		sum = sum + vector[i];		
		i = i + dist;
	}
	return sum;
}

int **cria_matriz(int N, int M)
{
	int **matrix;
	matrix = (int**)malloc(sizeof(int*)*N);
	int i;
	for(i=0;i<N;i++)
	{
		*(matrix + i) = (int*)malloc(sizeof(int)*N);
	}
	return matrix;
}


int **multMatriz_semThread(int **matrix, int **matrix2, int N, double *tempoExecucao)
{
	struct timeval antes, depois ;
    *tempoExecucao = 0;
    gettimeofday (&antes, 0) ;

	int **new_matrix;
	new_matrix = cria_matriz(N,N); 
	int sum = 0;
	int i,j,k;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			for(k=0;k<N;k++)
			{
				sum =  sum + matrix[i][k]*matrix2[k][j];				
			}
			new_matrix[i][j] = sum;
			sum = 0;
		}
	}

	gettimeofday (&depois, 0) ; 
   	*tempoExecucao =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );

	return new_matrix;
}

int **geraMatrizAleatoria( int N, int M){
	int **matrix;
	matrix = cria_matriz(N,M);
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			matrix[i][j] = rand() % 10;
		}
	}	
	return matrix;
}

void imprimeMatriz(int **matrix, int N, int M)
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++) 
		{
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");	
	}	
}

void imprimeIntervaloMatriz(tipoIntervaloMatriz *vector, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("[%d,%d]\t",vector[i].row,vector[i].column);		
	}
	printf("\n");
}
/*Calcula intervalos de vetor para intervalos de matrizes */
tipoIntervaloPonteiro *transformaVetorMatriz(tipoIntervalo *pos_interval_vector, int n, int *last_row,int *last_column)
{
	int j,cont = 0, cont2=0, i;
	
	int begin = (pos_interval_vector)->begin; 
	int end = (pos_interval_vector)->end; 	
	int length_interval_vector = end - begin;

	tipoIntervaloMatriz *pos_interval_vector_matrix;
	pos_interval_vector_matrix = (tipoIntervaloMatriz*)malloc(sizeof(tipoIntervaloMatriz)*(length_interval_vector));	
	
	tipoIntervaloPonteiro *vector_pointer;	
	vector_pointer = (tipoIntervaloPonteiro*)malloc(sizeof(tipoIntervalo));
	vector_pointer->vector = pos_interval_vector_matrix; 
	vector_pointer->length = length_interval_vector;
	
	i = *last_row; j = *last_column;
	
	while(cont < length_interval_vector)
	{				
		pos_interval_vector_matrix[cont2].row = i;
		pos_interval_vector_matrix[cont2].column = j;

		j++; 
		if(j == n)
		{	
			i++;
			j = 0;
		}		
		cont++;
		cont2++;
	}	
	*last_row = i; 
	*last_column = j;

	return vector_pointer;
}

void calculaSomaColuna(int **matrix, int **matrix2, int **matrix3,tipoIntervaloPonteiro *pointer_pos_vector,int n)
{
	tipoIntervaloMatriz *pos_vector; 
	pos_vector = pointer_pos_vector->vector; 

	int k,row, column, sum=0, cont = 0;
	
	int length_interval_vector = pointer_pos_vector->length;

	while(cont < length_interval_vector )
	{			
		row = pos_vector[cont].row; 			
		column = pos_vector[cont].column; 		

		for(k=0;k<n;k++)	
		{
			sum = sum + matrix[row][k]*matrix2[k][column];			
		}	
		matrix3[row][column] = sum;
		sum = 0;
		cont++;
	}
}


void *calculaSomaPartMatriz(void *pos_vector)
{
	tipoIntervaloPonteiro *pointer_pos_interval_vector = (tipoIntervaloPonteiro*)pos_vector; 

	int row, column; 	
	if(pointer_pos_interval_vector)
		calculaSomaColuna(global_matrix,global_matrix2,global_matrix3,pointer_pos_interval_vector,tam_matriz);
	else return;
} 

tipoIntervalo *vetor_intervalo_matrix(int n, int k, int dist)
{
	tipoIntervalo *interval_vector;
	interval_vector = (tipoIntervalo*)malloc(sizeof(tipoIntervalo)*k);

	int i;

	interval_vector[0].begin = 0;
	interval_vector[0].end = dist;

	for(i=1;i < k;i++)
	{

		interval_vector[i].begin = interval_vector[i-1].end;
		interval_vector[i].end = interval_vector[i-1].end + dist;		

		if(interval_vector[i].end > n*n)
		{			
			interval_vector[i].end = n*n;
		}
	}


	return interval_vector;
}

void multMatriz_comkThreads(int n, int cont_threads, double *tempoExecucao)
{
   struct timeval antes, depois ;
    *tempoExecucao = 0;
    int index;
    gettimeofday (&antes, 0) ;

    pthread_t threads_vector[cont_threads]; 
	if(n % cont_threads == 0) 
		dist = n*n/cont_threads;
	else dist = n*n/cont_threads+1; 

	tipoIntervalo *pos_interval_vector;
	pos_interval_vector = vetor_intervalo_matrix(n,cont_threads,dist);
	tipoIntervaloPonteiro  *pointer_interval_vector_to_matrix;
	tipoIntervaloMatriz *interval_vector_to_matrix;	


	global_matrix3 = cria_matriz(n,n);
	tam_matriz = n;

	int last_row = 0;
	int last_column = 0;
	
	for(index=0;index<cont_threads;index++)
	{			
		pointer_interval_vector_to_matrix = transformaVetorMatriz(&pos_interval_vector[index],n,&last_row,&last_column);	
		pthread_create(threads_vector + index,NULL,&calculaSomaPartMatriz,(void*)(pointer_interval_vector_to_matrix));				
	}
	gettimeofday (&depois,0) ;
	close_threads(threads_vector,cont_threads);
	 
   	*tempoExecucao =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );	
}

int main(int argc, char **argv)
{	
	if(argc == 3)
	{
		if(atoi(argv[2]) == 1)
		{
			int k;
			srand(time(NULL));
			int n = atoi(argv[1]);		
			//int *vector; 
			
			tam = n;
			printf("* Tam. entrada: %d\n",n);
			printf("* Numero de threads: %d\n",k);

			printf("\n");
				
			double tempoExecucao = 0,tempoExecucao2 = 0; // variável de contagem de tempo

			global_vector = geraRandomico(n);
			//imprimeVetor(vector,n);
			printf("* Soma dos elementos do vetor sem threads: %d\n",somaVetor_semThread(global_vector,n,&tempoExecucao));
			k=2;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Soma dos elementos do vetor com threads: %d\n",calculaTotalSomaVetor_Threads(global_vector,n,k));
			printf("* Tempo sem thread (ms): %lf\n\n",tempoExecucao);		
			
			
			printf("* Tempo com k(%d)- Threads (ms): %lf\n",k,tempoExecucao2);
			k=4;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Tempo com k(%d)- Threads (ms): %lf\n",k,tempoExecucao2);
			k=8;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Tempo com k(%d)- Threads (ms): %lf\n",k,tempoExecucao2);
			k=16;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Tempo com k(%d)-Threads (ms): %lf\n",k,tempoExecucao2);
			k=32;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Tempo com k(%d)-Threads (ms): %lf\n",k,tempoExecucao2);
			k=64;calculaSomaVetor_Threads(n,k,&tempoExecucao2);
			printf("* Tempo com k(%d)-Threads (ms): %lf\n",k,tempoExecucao2);		
			//printf("%lf\n",spent_timea2);			
		}
		else if(atoi(argv[2]) == 2)
		{
			srand(time(NULL));
			int n = atoi(argv[1]);
			if(n <= 2048)
			{	
				int k;				
				int **matrix, **matrix2, **matrix3;
				global_matrix = geraMatrizAleatoria(n,n);
				global_matrix2 = geraMatrizAleatoria(n,n);
				double tempoExecucao, tempoExecucao2;
				k=2;multMatriz_comkThreads(n,4,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				k=4;multMatriz_comkThreads(n,4,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				k=8;multMatriz_comkThreads(n,8,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				k=16;multMatriz_comkThreads(n,16,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				k=32;multMatriz_comkThreads(n,32,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				k=64;multMatriz_comkThreads(n,64,&tempoExecucao);
				printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);
				
				matrix3 = multMatriz_semThread(global_matrix,global_matrix2,n,&tempoExecucao2);
				printf("* Tempo sem thread (ms): %lf\n\n",tempoExecucao2);	
				//printf("* Tempo com k(%d)-threads (ms): %lf\n",k,tempoExecucao);	
				
				//imprimeMatriz(matrix3,n,n);

			} else 
			{
				printf("Valor de n é muito grande! Saindo..!\n");
			}			
		} else
		{
			printf("* Execute o arquivo com 2 argumentos:\n"); 	
			printf("* ./<arquivo-executavel> <tamanho do vetor> <modo>\n");	
			printf("* Modo 1: somar vetor\n");
			printf("* Modo 2: multiplicar matriz\n");
		}

	} else 
		{
			printf("* Execute o arquivo com 3 argumentos:\n"); 	
			printf("* ./<arquivo-executavel> <tamanho do vetor> <quantidade de threads> <modo>\n");	
			printf("* Modo 1: somar vetor\n");
			printf("* Modo 2: multiplicar matriz\n");
		}

	exit(0);
}
