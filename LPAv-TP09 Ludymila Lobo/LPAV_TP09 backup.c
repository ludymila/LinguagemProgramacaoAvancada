
/*Definindo bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Biblioteca para cálculo de tempo
#include <time.h> 
/*Definindo valores para criação de vetores*/
#define N1k 1000
#define N5k 5000
#define N10k 10000
#define N20k 20000
#define N50k 50000
/*** Funções básicas */
void gerar_vetor_aleatorio(int v[], int n) 
{
	srand (time(NULL));
	int a,i;	
	for(i=0; i < n; i++)
		v[i] =  rand () % 100 + 1;		
}

void troca(int *pos_a, int *pos_b)
{
	int aux; 
	aux = *pos_a; 
	*pos_a = *pos_b;
	*pos_b = aux; 
}


void merge(int v[], int n, int *qtd_trocas, int *qtd_comparacoes) {
  int meio;
  int i, j, k;
  int *temp;
 
  temp = (int*) malloc(n * sizeof(int));
  if (temp == NULL) {
    exit(1);
  }
 
  meio = n / 2;
 
  i = 0;
  j = meio;
  k = 0;

  while (i < meio && j < n) {
  	
  	*qtd_comparacoes = *qtd_comparacoes + 1;
    if (v[i] <= v[j]) {
		*qtd_trocas = *qtd_trocas + 1;
      temp[k] = v[i];
      i++;
    }
    else {
      temp[k] = v[j];
      *qtd_trocas = *qtd_trocas + 1;
      j++;
    }
    ++k;
  }
 
  if (i == meio) 
  {
    while (j < n) 
    {    	
    	*qtd_trocas = *qtd_trocas + 1;
    	temp[k] = v[j];	
    	j++;
    	k++;
    }      
  }
  else 
  {
    while (i < meio) 
    {
    	*qtd_trocas = *qtd_trocas + 1;
    	temp[k] = v[i];    	
    	i++;
    	k++;
    }    	
      
  }
  for (i = 0; i < n; ++i) {
    v[i] = temp[i];
  }
  free(temp);
}

int partition(int v[], int inicio, int fim, int *qtd_trocas, int *qtd_comparacoes)
{
    int i, j;
 
    i = inicio;
    for (j = inicio + 1; j <= fim; ++j)
    {
    	*qtd_comparacoes = *qtd_comparacoes + 1;
        if (v[j] < v[inicio])
        {
            i++;
            *qtd_trocas = *qtd_trocas + 1;
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[inicio], &v[i]);
 
    return i;
}


void imprime_vetor(int v[], int n)
{
	int i; 
	for(i=0;i<n;i++)
		printf("%d ",v[i]);
}

void gera_vetor_crescente(int v[], int n)
{
	int i;
	for(i=0;i<n;i++)
		v[i] = i; 
}

void gera_vetor_decrescente(int v[], int n)
{
	int i;
	for(i=n;i>=0;i--)
		v[n-i] = i; 
}

void imprime_relatorio(double tempo_gasto, int qtd_trocas, int qtd_comparacoes, int n)
{
	//printf("* Tamanho do vetor: %d\n",n);	
	printf("* Quantidade de trocas: %d\n", qtd_trocas);
	printf("* Quantidade de comparações: %d\n", qtd_comparacoes);
	printf("* Tempo gasto (Microssegundos): %lf\n",tempo_gasto);
}
	

/*** Algoritmos de Ordenação*/

void bubble_sort(int v[], int n, double *tempo_gasto, int *qtd_trocas, int *qtd_comparacoes) {
    int i, j, aux; 
    *qtd_trocas = 0;
    *qtd_comparacoes = 0;
    *tempo_gasto = 0;
    struct timeval antes, depois ;

    gettimeofday (&antes, 0) ;
	for(i=0;i < n-1;i++)
	{			
		for(j=0;j<n-i-1;j++)
		{		
			*qtd_comparacoes = *qtd_comparacoes + 1;
			//printf("qtd comparações %d\n",*qtd_comparacoes);		
			if(v[j] > v[j+1])		
			{			
				troca(&v[j],&v[j+1]);			
				*qtd_trocas = *qtd_trocas + 1;
			}				
		}
	}

	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}

void insertion_sort(int v[], int n, double *tempo_gasto, int *qtd_trocas, int *qtd_comparacoes) 
{
   *qtd_trocas = 0;
    *qtd_comparacoes = 0;
    *tempo_gasto = 0;
    struct timeval antes, depois ;
   int i, j, pivot, temp; 
   gettimeofday (&antes, 0) ;

   for (i = 1; i < n; i++) 
   {
            j = i;
            while (j > 0 && v[j - 1] > v[j]) 
            {
        		 *qtd_comparacoes = *qtd_comparacoes + 1;
        		 *qtd_trocas = *qtd_trocas + 1;
                  temp = v[j];
                  v[j] = v[j - 1];
                  v[j - 1] = temp;
                  j--;
            }
  }
   gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}


void merge_sort_0(int v[], int n, int *qtd_trocas, int *qtd_comparacoes) {
	
	int meio;
	if(n > 1)
	{
		meio = n/2;
	  	merge_sort_0(v,meio,qtd_trocas,qtd_comparacoes);
	  	merge_sort_0(v+meio,n-meio,qtd_trocas,qtd_comparacoes);
	  	merge(v,n,qtd_trocas,qtd_comparacoes); 
	} 
 }

void merge_sort(int v[], int n, double *tempo_gasto, int *qtd_trocas, int *qtd_comparacoes)
{
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;	
	gettimeofday (&antes, 0) ;
	merge_sort_0(v,n,qtd_trocas,qtd_comparacoes);
 	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}

void selection_sort(int v[], int n, double *tempo_gasto, int *qtd_trocas, int *qtd_comparacoes)
{ 
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;
	
	gettimeofday (&antes, 0) ;  
	int i, j, menor, temp;
	for (i = 0; i < (n-1); i++) 
	{
		menor = i;
		for (j = (i+1); j < n; j++) 
		{
			 *qtd_comparacoes = *qtd_comparacoes + 1;        		 
			if(v[j] < v[menor]) 
			{				
        		menor = j;
      		}
    	}
	    if (i != menor) {
	      *qtd_trocas = *qtd_trocas + 1;
	      temp = v[i];
	      v[i] = v[menor];
	      v[menor] = temp;
	    }
  	}
	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}


void quick_sort_0(int v[], int inicio, int fim, int *qtd_trocas, int *qtd_comparacoes)
{
    int r;
 	
    if (fim > inicio)
    {
        r = partition(v, inicio, fim,qtd_trocas,qtd_comparacoes);
        quick_sort_0(v, inicio, r - 1,qtd_trocas,qtd_comparacoes);
        quick_sort_0(v, r + 1, fim,qtd_trocas,qtd_comparacoes);
    }
}

void quick_sort(int v[], int n, double *tempo_gasto, int *qtd_trocas, int *qtd_comparacoes)
{
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;	
	gettimeofday (&antes, 0) ;
	quick_sort_0(v,0,n-1,qtd_comparacoes,qtd_trocas);
	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}


/* Funções que fazem o calculo requerido para o trabalho 2
	* Calcula a ordenação para cada caso: Vetor aleatório, descrescente e crescente, além de dar resultado 
		da quantidade de trocas, tempo e quantidade de comparações.*/
void calcula_todo_relatorio_bubblesort_imprime(int v[], int n)
{
	printf("** BUBBLE SORT\n\n");
	int qtd_comparacoes, qtd_trocas;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerar_vetor_aleatorio(v,n); 
		bubble_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	imprime_relatorio(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gera_vetor_crescente(v,n);
	bubble_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gera_vetor_decrescente(v,n);
	bubble_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);			
}

void calcula_todo_relatorio_insertionsort_imprime(int v[], int n)
{
	printf("** INSERTION SORT\n\n");
	int qtd_comparacoes, qtd_trocas;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerar_vetor_aleatorio(v,n); 
		insertion_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	imprime_relatorio(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gera_vetor_crescente(v,n);
	insertion_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gera_vetor_decrescente(v,n);
	insertion_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);			
}

void calcula_todo_relatorio_mergesort_imprime(int v[], int n)
{
	printf("** MERGE SORT\n\n");
	int qtd_comparacoes, qtd_trocas;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerar_vetor_aleatorio(v,n); 
		merge_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	imprime_relatorio(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gera_vetor_crescente(v,n);
	merge_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gera_vetor_decrescente(v,n);
	merge_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void calcula_todo_relatorio_selectionsort_imprime(int v[], int n)
{
	printf("** SELECTION SORT\n\n");
	int qtd_comparacoes, qtd_trocas;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerar_vetor_aleatorio(v,n); 
		selection_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	imprime_relatorio(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gera_vetor_crescente(v,n);
	selection_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gera_vetor_decrescente(v,n);
	selection_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void calcula_todo_relatorio_quicksortsort_imprime(int v[], int n)
{
	printf("** QUICKSORT SORT\n\n");
	int qtd_comparacoes, qtd_trocas;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerar_vetor_aleatorio(v,n); 
		quick_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	imprime_relatorio(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gera_vetor_crescente(v,n);
	quick_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gera_vetor_decrescente(v,n);
	quick_sort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	imprime_relatorio(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void calcula_todas_ordenacoes_todos_os_tamanhos()
{
	int n = N1k;
	int *v;
	v = (int*) malloc(n * sizeof(int));
	printf("**** PARA TAMANHO 1000 ");
	calcula_todo_relatorio_bubblesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_insertionsort_imprime(v,n);	
	printf("\n\n");
	calcula_todo_relatorio_mergesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_selectionsort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_quicksortsort_imprime(v,n);
	printf("**** PARA TAMANHO 5000 ");
	free(v);
	n = N5k;
	v = (int*) malloc(n * sizeof(int));
	calcula_todo_relatorio_bubblesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_insertionsort_imprime(v,n);	
	printf("\n\n");
	calcula_todo_relatorio_mergesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_selectionsort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_quicksortsort_imprime(v,n);
	printf("**** PARA TAMANHO 10000 ");
	free(v);
	n = N10k;
	v = (int*) malloc(n * sizeof(int));
	calcula_todo_relatorio_bubblesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_insertionsort_imprime(v,n);	
	printf("\n\n");
	calcula_todo_relatorio_mergesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_selectionsort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_quicksortsort_imprime(v,n);
	printf("**** PARA TAMANHO 20000 ");
	free(v);
	n = N20k;
	v = (int*) malloc(n * sizeof(int));
	calcula_todo_relatorio_bubblesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_insertionsort_imprime(v,n);	
	printf("\n\n");
	calcula_todo_relatorio_mergesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_selectionsort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_quicksortsort_imprime(v,n);
	printf("**** PARA TAMANHO 50000 ");
	free(v);
	n = N50k;
	v = (int*) malloc(n * sizeof(int));
	calcula_todo_relatorio_bubblesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_insertionsort_imprime(v,n);	
	printf("\n\n");
	calcula_todo_relatorio_mergesort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_selectionsort_imprime(v,n);
	printf("\n\n");
	calcula_todo_relatorio_quicksortsort_imprime(v,n);
}

int main()
{
	calcula_todas_ordenacoes_todos_os_tamanhos();
	return 0;
}




