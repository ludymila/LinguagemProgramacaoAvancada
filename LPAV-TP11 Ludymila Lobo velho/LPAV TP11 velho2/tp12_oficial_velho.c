#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX_THREAD 64
#define NDIM 100

double          a[NDIM][NDIM];
double          b[NDIM][NDIM];
double          c[NDIM][NDIM];

int **matResult;
int amount_of_elements_in_run = 0; // quantidade de elementos do vetor que irá
// descrescendo conforme acontece a execução
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; // Mutex para evitar 
// inconsistência na região crítica
// imprime vetor

//---------------------------------MAT.C--------------------
typedef struct
{
	int             id;
	int             noproc;
	int             dim;
	double	(*a)[NDIM][NDIM],(*b)[NDIM][NDIM],(*c)[NDIM][NDIM];
}               parm;

void mm(int me_no, int noproc, int n, double a[NDIM][NDIM], double b[NDIM][NDIM], double c[NDIM][NDIM])
{
	int             i,j,k;
	double sum;
	i=me_no;
	while (i<n) {

		for (j = 0; j < n; j++) {
			sum = 0.0;
			for (k = 0; k < n; k++) {
				sum = sum + a[i][k] * b[k][j];
			}
			c[i][j] = sum;

		}
		i+=noproc;
	}
}

void * worker(void *arg)
{
	parm           *p = (parm *) arg;
	mm(p->id, p->noproc, p->dim, *(p->a), *(p->b), *(p->c));
	return NULL;
}

//---------------------------------MAT.C---------------------




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
	int opcao=0;
	printf("1-Calculo de multiplicacao SEM THREAD/n");
	printf("2-Calculo de multiplicacao COM THREAD/n");
	while ((opcao!=1) && (opcao!=2))
		scanf("%d", &opcao);
		
	if (opcao ==1){
	
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
	}
	else {
		int j, k, noproc, me_no;
		double sum;
		double t1, t2;
		struct timeval antes, depois ;
		double spent_time = 0;
		
		pthread_t *threads;
		pthread_attr_t pthread_custom_attr;

		parm *arg;
		int n, i;

		for (i = 0; i < NDIM; i++)
			for (j = 0; j < NDIM; j++)
			{
				a[i][j] = i + j;
				b[i][j] = i + j;
			}

		if (argc != 2)
		{
			printf("Usage: %s n\n  where n is no. of thread\n", argv[0]);
			exit(1);
		}
		n = atoi(argv[1]);

		if ((n < 1) || (n > MAX_THREAD))
		{
			printf("The no of thread should between 1 and %d.\n", MAX_THREAD);
			exit(1);
		}
		threads = (pthread_t *) malloc(n * sizeof(pthread_t));
		pthread_attr_init(&pthread_custom_attr);

		arg=(parm *)malloc(sizeof(parm)*n);
		/* setup barrier */

		/* Start up thread */

		/* Spawn thread */
		gettimeofday (&antes, 0) ;
		for (i = 0; i < n; i++)
		{
			arg[i].id = i;
			arg[i].noproc = n;
			arg[i].dim = NDIM;
			arg[i].a = &a;
			arg[i].b = &b;
			arg[i].c = &c;
			pthread_create(&threads[i], &pthread_custom_attr, worker, (void *)(arg+i));
		}

		for (i = 0; i < n; i++)
		{
			pthread_join(threads[i], NULL);

		}
		/* print_matrix(NDIM); */
	gettimeofday (&depois, 0) ; 
		spent_time =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );	
		check_matrix(NDIM);
		free(arg);
		printf("TIME %lf\n",spent_time);
		
		
	}
	
	exit(0);
}


print_matrix(dim)
int dim;
{
	int i,j;

	printf("The %d * %d matrix is\n", dim,dim);
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++)
			printf("%lf ",  c[i][j]);
		printf("\n");
	}
}

check_matrix(dim)
int dim;
{
	int i,j,k;
	int error=0;

	printf("Now checking the results\n");
	for(i=0;i<dim;i++)
		for(j=0;j<dim;j++) {
			double e=0.0;

			for (k=0;k<dim;k++)
				e+=a[i][k]*b[k][j];

			if (e!=c[i][j]) {
				printf("(%d,%d) error\n",i,j);
				error++;
			}
		}
	if (error)
		printf("%d elements error\n",error);
		else
		printf("success\n");
}

