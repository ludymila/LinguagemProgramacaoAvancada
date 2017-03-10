#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <time.h> 

/*------------------------------------------------------------------------------------------------------*/
void merge(int v[], int n,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes) {
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
/*------------------------------------------------------------------------------------------------------*/
void gerarAleatorio(int v[], int n) 
{
	srand (time(NULL));
	int a,i;	
	for(i=0; i < n; i++)
		v[i] =  rand () % 100 + 1;		
}


void gerarCrescente(int v[], int n)
{
	int i;
	for(i=0;i<n;i++)
		v[i] = i; 
}

void gerarDecrescente(int v[], int n)
{
	int i;
	for(i=n;i>=0;i--)
		v[n-i] = i; 
}
/*----------------------------------------------------------------------------------------------------*/

void troca(int *pos_a, int *pos_b)
{
	int aux; 
	aux = *pos_a; 
	*pos_a = *pos_b;
	*pos_b = aux; 
}


int partition(int v[], int inicio, int fim,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes)
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


void printInfos(double tempo_gasto, unsigned long long int qtd_trocas, unsigned long long int qtd_comparacoes, int n)
{ 
	printf("* Quantidade de comparações: %llu\n", qtd_comparacoes);
	printf("* Quantidade de trocas: %llu\n", qtd_trocas);	
	printf("* Tempo gasto (Microssegundos): %lf\n",tempo_gasto);
}
	


void BubbleSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes) {
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

void insertionSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes) 
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


void mergeSortv1(int v[], int n,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes) {
	
	int meio;
	if(n > 1)
	{
		meio = n/2;
	  	mergeSortv1(v,meio,qtd_trocas,qtd_comparacoes);
	  	mergeSortv1(v+meio,n-meio,qtd_trocas,qtd_comparacoes);
	  	merge(v,n,qtd_trocas,qtd_comparacoes); 
	} 
 }

void mergeSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes)
{
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;	
	gettimeofday (&antes, 0) ;
	mergeSortv1(v,n,qtd_trocas,qtd_comparacoes);
 	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}

void selectionSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes)
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


void quickSortv1(int v[], int inicio, int fim,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes)
{
    int r;
 	
    if (fim > inicio)
    {
        r = partition(v, inicio, fim,qtd_trocas,qtd_comparacoes);
        quickSortv1(v, inicio, r - 1,qtd_trocas,qtd_comparacoes);
        quickSortv1(v, r + 1, fim,qtd_trocas,qtd_comparacoes);
    }
}
//codigo inspirado em pt.wikipedia.org/?title=Heapsort
void heapSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes) 
{
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;
	
	gettimeofday (&antes, 0) ;  

	int i = n/2;
	int pai, filho, t;

	for (;;) 
	{
		if (i>0) 
		{
			i--;
			t = v[i];
		}
		else 
		{
			n--;
			if (n==0)
			   return;
			t = v[n];
			v[n] = v[0];
			*qtd_trocas = *qtd_trocas + 1;

		}
		pai = i;

		filho = i*2;

		while(filho<n)
		{
			*qtd_comparacoes = *qtd_comparacoes + 1;
			if ((filho + 1 <n) && (v[filho+1] > v[filho]))
				filho++;
			*qtd_comparacoes = *qtd_comparacoes + 1;
			if (v[filho] >t)
			{			
				v[pai] = v[filho];
				*qtd_trocas = *qtd_trocas + 1;
				pai = filho;
				filho = pai*2 + 1;
			} 
			else
			  break;	
		}
		v[pai] = t;
	}
	
	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );

}
void quickSort(int v[], int n, double *tempo_gasto,unsigned long long int *qtd_trocas, unsigned long long int *qtd_comparacoes)
{
	*qtd_trocas = 0;
	*qtd_comparacoes = 0;
	*tempo_gasto = 0;
	struct timeval antes, depois ;	
	gettimeofday (&antes, 0) ;
	quickSortv1(v,0,n-1,qtd_comparacoes,qtd_trocas);
	gettimeofday (&depois, 0) ; 
	*tempo_gasto =  (double)( (depois.tv_sec * 1000000 + depois.tv_usec) - (antes.tv_sec * 1000000 + antes.tv_usec) );
}



void ImpressaoBubbleSort(int v[], int n)
{
	printf("** BUBBLE SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		BubbleSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gerarCrescente(v,n);
	BubbleSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	BubbleSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);			
}

void ImpressaoInsertionSort(int v[], int n)
{
	printf("** INSERTION SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto = 0.0 ;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		insertionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gerarCrescente(v,n);
	insertionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	insertionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);			
}

void ImpressaoMergeSort(int v[], int n)
{
	printf("** MERGE SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto = 0.0 ;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		mergeSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gerarCrescente(v,n);
	mergeSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	mergeSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void ImpressaoSelectionSort(int v[], int n)
{
	printf("** SELECTION SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto = 0.0;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		selectionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("Vetor crescente\n"); 
	gerarCrescente(v,n);
	selectionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	selectionSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void ImpressaoQuickSort(int v[], int n)
{
	printf("QUICK SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto = 0.0;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		quickSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gerarCrescente(v,n);
	quickSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	quickSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}

void ImpressaoHeapSort(int v[], int n)
{
	printf("HEAP SORT\n\n");
	unsigned long long int qtd_comparacoes = 0, qtd_trocas = 0;
	int i, soma_tempo = 0, soma_trocas = 0, soma_comparacoes = 0,media_tempo = 0, media_trocas = 0,media_comparacoes = 0; 
	double tempo_gasto = 0.0;
	for(i=0;i<10;i++)
	{
		gerarAleatorio(v,n); 
		heapSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);			
		soma_tempo = soma_tempo + tempo_gasto; 
		soma_trocas = soma_trocas + qtd_trocas; 
		soma_comparacoes = soma_comparacoes + qtd_comparacoes;
	}	
	media_tempo = soma_tempo/10; 
	media_trocas = soma_trocas/10; 
	media_comparacoes = soma_comparacoes/10; 
	
	printf("** Vetor aleatório\n");	
	printInfos(media_tempo,media_trocas,media_comparacoes,n);
	printf("\n");
	printf("** Vetor crescente\n"); 
	gerarCrescente(v,n);
	quickSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);
	printf("\n");
	printf("** Vetor decrescente\n"); 
	gerarDecrescente(v,n);
	quickSort(v,n,&tempo_gasto,&qtd_trocas,&qtd_comparacoes);	
	printInfos(tempo_gasto,qtd_trocas,qtd_comparacoes,n);				
}


void ordenacoes()
{
	int n = 1000;
	int *v;
	v = (int*) malloc(n * sizeof(int));
	printf("\n**** PARA TAMANHO 1000\n");
	printf("\n\n");	
	
	ImpressaoBubbleSort(v,n);
	printf("\n\n");
	ImpressaoSelectionSort(v,n);
	printf("\n\n");
	ImpressaoInsertionSort(v,n);	
	printf("\n\n");
	ImpressaoMergeSort(v,n);
	printf("\n\n");	
	ImpressaoQuickSort(v,n);
	printf("\n\n");
	ImpressaoHeapSort(v,n);
	printf("\n\n");
	printf("\n\n**** PARA TAMANHO 5000\n");
	free(v);
	n = 5000;
	v = (int*) malloc(n * sizeof(int));
	ImpressaoBubbleSort(v,n);
	printf("\n\n");
	ImpressaoSelectionSort(v,n);
	printf("\n\n");
	ImpressaoInsertionSort(v,n);	
	printf("\n\n");
	ImpressaoMergeSort(v,n);
	printf("\n\n");	
	ImpressaoQuickSort(v,n);
	printf("\n\n");	
	ImpressaoHeapSort(v,n);
	printf("\n\n");	
	printf("\n\n**** PARA TAMANHO 10000\n");
	free(v);
	n = 10000;
	v = (int*) malloc(n * sizeof(int));
	ImpressaoBubbleSort(v,n);
	printf("\n\n");
	ImpressaoSelectionSort(v,n);
	printf("\n\n");
	ImpressaoInsertionSort(v,n);	
	printf("\n\n");
	ImpressaoMergeSort(v,n);
	printf("\n\n");	
	ImpressaoQuickSort(v,n);
	printf("\n\n");
	ImpressaoHeapSort(v,n);
	printf("\n\n");
	printf("\n\n**** PARA TAMANHO 20000\n");
	free(v);
	n = 20000;
	v = (int*) malloc(n * sizeof(int));
	ImpressaoBubbleSort(v,n);
	printf("\n\n");
	ImpressaoSelectionSort(v,n);
	printf("\n\n");
	ImpressaoInsertionSort(v,n);	
	printf("\n\n");
	ImpressaoMergeSort(v,n);
	printf("\n\n");	
	ImpressaoQuickSort(v,n);
	printf("\n\n");
	ImpressaoHeapSort(v,n);
	printf("\n\n");
	printf("\n\n**** PARA TAMANHO 50000\n");
	free(v);
	n = 50000;
	v = (int*) malloc(n * sizeof(int));
	ImpressaoBubbleSort(v,n);
	printf("\n\n");
	ImpressaoSelectionSort(v,n);
	printf("\n\n");
	ImpressaoInsertionSort(v,n);	
	printf("\n\n");
	ImpressaoMergeSort(v,n);
	printf("\n\n");	
	ImpressaoQuickSort(v,n);
	printf("\n\n");
	ImpressaoHeapSort(v,n);


}



int main()
{
	printf("LPAV\n");
	ordenacoes();
	return 0;
}




