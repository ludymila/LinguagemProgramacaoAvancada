#include <stdio.h> 
#include <stdlib.h> 


typedef enum {false, true} bool; 

typedef struct No{
	int x,y;	
	struct No *prox; 
} NoTipo;

typedef struct pNo{
	int index; 
	NoTipo *pFila; 
	struct pNo *prox;
} NoTipoN;

typedef struct No1{
	char value; 
	bool assigned;
} Labirinto;

// imprime um caminho criado por uma lista
void imprimirCaminho(NoTipo *aux) {
	while(aux)
	{
		printf("L(%d,%d)\n",aux->x +1,aux->y +1);
		aux = aux->prox;
	}
	printf("\n");
}

// faz com que cada posição seja iniciada com não-assinalada
void inicializarMatriz(Labirinto **mat, int N, int M){
	int i , j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			mat[i][j].assigned = false;
	}
}

// libera matriz da memória
void liberarMatriz(Labirinto ***mat, int N, int M){
	int i,j;
	for(i=0;i<N;i++)
	{
		free(*(*mat + i));
	}
	free(*mat);
}

// libera fila da memória
void liberarFila(NoTipo **pInicial){
	NoTipo *aux; 
	aux = *pInicial;
	while((*pInicial))
	{
		aux = *pInicial;
		(*pInicial) = (*pInicial)->prox;
		free(aux);

	}
}

// libera fila de filas
void liberarFilaFila(NoTipoN **pInicial){
	NoTipoN *aux; 
	aux = *pInicial; 
	while((*pInicial))
	{
		aux = *pInicial; 
		(*pInicial) = (*pInicial)->prox;
		liberarFila(&aux->pFila);
		free(aux);
	}
}

// imprime matriz
void imprimirMatriz(Labirinto **mat, int N, int M){
	int i = 0, j= 0;	
	printf("\t");
	for(j=0;j<M;j++)
		printf("[%d]\t",j);
	printf("\n");
	for(i=0;i<N;i++)
	{
		printf("[%d]	",i);
		for(j=0;j<M;j++)
		{
			
			if(mat[i][j].value != '\t')
				printf("%c\t",mat[i][j].value);
		}			
		printf("\n");

	}
		
}

// insere na fila
void inserirFila(NoTipo **pInicial, NoTipo **pFinal, int x, int y){
	NoTipo *new; 
	new = (NoTipo*)malloc(sizeof(NoTipo)); 
	new->prox = NULL;
	new->x = x;
	new->y = y;	
	if(!*pInicial)
	{	
		*pInicial = new; 
		*pFinal = new; 
	} else 
	{
		(*pFinal)->prox = new; 
		(*pFinal) = new;
	}
}
// fila da fila
void inserirFilaFila(NoTipoN **pFilai, NoTipoN **pFilaf, NoTipo **pInicial, int k){
	NoTipoN *new;
	new = (NoTipoN*)malloc(sizeof(NoTipoN));
	new->index = k;
	new->prox = NULL;
	new->pFila = *pInicial;
	if(!*pFilai)
	{
		*pFilai = new;
		*pFilaf = new; 
	} else 
	{
		(*pFilaf)->prox = new;
		(*pFilaf) = new;
	}
}

// remove o último elemento de uma fila
void removerUltimoFila(NoTipo **pInicial,NoTipo **pFinal){
	if(!*pInicial)
		return;
	if((*pInicial)->prox == NULL)
	{
		free(*pInicial);		
		*pInicial = NULL;	
		*pFinal = NULL;
	}
	else if(*pFinal != NULL && pInicial != NULL)
	{
		NoTipo *aux, *aux2;		
		aux = *pInicial;		
		while(aux->prox!=*pFinal)
		{
			aux = aux->prox; 
		}		
		*pFinal = aux;	
		aux2 = aux->prox;
		aux->prox = NULL;		
		free(aux2);

	} 
}
// copia uma fila para outra
void copiarFila(NoTipo **pInicial, NoTipo **pFinal, NoTipo **pInicial2){
	NoTipo *aux;
	aux = *pInicial2; 
	while(aux)
	{
		inserirFila(pInicial,pFinal,aux->x,aux->y);
		aux = aux->prox;
	}
}

// verifica se está na ultima posição
bool posicao_final(int i,int j,int N, int M ){
	if(i == N-1 && j == M - 1)
		return true;
	else false;
}

// imprime caminho da fila
void imprimirCaminho_fila(NoTipoN **pFilai, int N, int M){
	int i = 0, j = 0;
	
	NoTipoN *aux;
	aux = *pFilai;
	NoTipo *aux2;	
	while(aux)
	{
		printf("Caminho (%d): \n",aux->index);		
		imprimirCaminho(aux->pFila);	
		printf("\n");
		aux = aux->prox;			}			
	
}

bool validaPosMatriz(int i, int j, int N, int M){
	if(i == N  || j == M || i < 0 || j < 0)
		return false;
	else return true;
}

void atribuirPosMatriz(Labirinto **mat,int i,int j){
	mat[i][j].value = 'x'; 	
	mat[i][j].assigned = true;
}

void removerPosMatriz(Labirinto **mat, int i, int j){
	mat[i][j].value = '0'; 
	mat[i][j].assigned = false;
}
//calcula apenas uma possibildade
bool validaCaminho(Labirinto **mat,int i, int j, int N, int M, int *k, NoTipo **pInicial, NoTipo **pFinal){
	NoTipo *pInicialbuf = NULL, *pFinalbuf = NULL; 	
	if(validaPosMatriz(i,j,N,M)==true && mat[i][j].value == '0')
	{					
		atribuirPosMatriz(mat,i,j); 						
		inserirFila(pInicial,pFinal,i,j);

		if(posicao_final(i,j,N,M)==true)
		{										
			*k = *k+1;	
			
			imprimirMatriz(mat,N,M);											
			printf("Caminho (%d): \n",*k);
			imprimirCaminho(*pInicial);
			
			return true;

		}
		
		if(validaCaminho(mat,i+1,j,N,M,k,pInicial,pFinal)==true)
			return true;  // baixo		
		if(validaCaminho(mat,i+1,j+1,N,M,k,pInicial,pFinal)==true)
			return true; // baixo-direita		
		if(validaCaminho(mat,i,j+1,N,M,k,pInicial,pFinal)==true)
			return true; // direita		
		if(validaCaminho(mat,i-1,j+1,N,M,k,pInicial,pFinal)==true)
			return true; //cima-direita	
		if(validaCaminho(mat,i-1,j,N,M,k,pInicial,pFinal)==true)
			return true; //cima		
		if(validaCaminho(mat,i-1,j-1,N,M,k,pInicial,pFinal)==true)
			return true; //cima-esquerad
		if(validaCaminho(mat,i,j-1,N,M,k,pInicial,pFinal)==true)
			return true;  // esquerda

		removerPosMatriz(mat,i,j); 			
		//removerUltimoFila(pInicial,pFinal);							

	} 		
	return false;
	
}
// calcula todas as possibilidades
void validaCaminho2(Labirinto **mat,int i, int j, int N, int M, int *k, NoTipo **pInicial, NoTipo **pFinal, NoTipoN **pFilai, NoTipoN **pFilaif){
	NoTipo *pInicialbuf = NULL, *pFinalbuf = NULL; 
	if(validaPosMatriz(i,j,N,M)==true && mat[i][j].value == '0' && mat[i][j].assigned == false)
	{			
		//printf("assinalando\n");
		atribuirPosMatriz(mat,i,j); 				
		//printf("antes de inserirFila\n");
		inserirFila(pInicial,pFinal,i,j);
		//imprimirMatriz(mat,N,M);		

		if(posicao_final(i,j,N,M)==true)
		{										
			*k = *k+1;	
					
			imprimirMatriz(mat,N,M);					
			
			copiarFila(&pInicialbuf,&pFinalbuf,pInicial);			
			inserirFilaFila(pFilai,pFilaif,&pInicialbuf,*k);	 
			printf("Caminho (%d): \n",*k);		
			imprimirCaminho((*pFilaif)->pFila);				
			removerPosMatriz(mat,i,j); 	
			inicializarMatriz(mat,N,M);	


		}		

			validaCaminho2(mat,i+1,j,N,M,k,pInicial,pFinal,pFilai,pFilaif);	
			validaCaminho2(mat,i+1,j+1,N,M,k,pInicial,pFinal,pFilai,pFilaif);// baixo-direita		
			validaCaminho2(mat,i,j+1,N,M,k,pInicial,pFinal,pFilai,pFilaif);	// direita		
			validaCaminho2(mat,i-1,j+1,N,M,k,pInicial,pFinal,pFilai,pFilaif);
			validaCaminho2(mat,i-1,j,N,M,k,pInicial,pFinal,pFilai,pFilaif);		
			validaCaminho2(mat,i-1,j-1,N,M,k,pInicial,pFinal,pFilai,pFilaif);		
			validaCaminho2(mat,i,j-1,N,M,k,pInicial,pFinal,pFilai,pFilaif);		
	
			removerPosMatriz(mat,i,j); 			
			removerUltimoFila(pInicial,pFinal);												
			//imprimirCaminho(*pInicial);	

	} 			
	return;
	
}

// cria uma matriz dinamicamente
Labirinto **cria_mat( int N, int M) {
	Labirinto **mat;
	
	mat = (Labirinto**)malloc(N*sizeof(Labirinto*)); // aloca vetor de linhas
	int i;	
	for(i=0;i<N;i++) // alocar elementos de cima a baixo , M é quantidade de linhas
		*(mat + i) = (Labirinto*)malloc(M*sizeof(Labirinto)); 

	return mat;
}


// cria uma matriz a partir da prmeira linha da entrada
Labirinto **criaMatriz(FILE *arq, int *contLin, int *contCol){
	Labirinto **mat; 
	fscanf(arq,"%d\t%d\n",contLin,contCol);	
	mat = cria_mat(*contLin,*contCol);

	return mat;
}


void leMatriz(FILE *arq, Labirinto **mat, int *contLin, int *contCol){
	int i = 0, j = 0;
	char pos ; 
	while(i < *contLin)
	{		
		while(j < *contCol)
		{		
			fscanf(arq,"%c",&pos);									
			if(pos != '\0' && pos != '\n')
			{							
				if(pos != '	') // se o caracter for diferente de tab
				{
					mat[i][j].value = pos; 					
					j++;
				}	
			}		
		}		
		j = 0;
		
		i++;
	}	
}

// le um arquivo e insere na matriz
Labirinto **leArquivo(FILE *arq, int *contLin, int *contCol) {
	rewind(arq);	
	Labirinto **mat; 
    // le a primeira linha
	mat = criaMatriz(arq,contLin,contCol);
	leMatriz(arq,mat,contLin,contCol);
	
	return mat;
}

// escreve as saídas de uma fila de filas num arquivo
void EscreverArquivo(FILE *arq, NoTipoN **pFilai) {
	NoTipoN *aux;
	aux = *pFilai;
	NoTipo *aux2;	
	while(aux!=NULL)
	{
		fprintf(arq,"Caminho (%d): ",aux->index);		
		aux2 = aux->pFila;
		while(aux2)
		{
			fprintf(arq,"L(%d,%d)\n",aux2->x,aux2->y);
			aux2 = aux2->prox;
		}
		fprintf(arq,"\n");		
		aux = aux->prox;		
	}			
	
}

int main(int argc, char **argv) {
	if(argc == 2)
	{
		Labirinto **mat; 
		NoTipo *pInicial, *pFinal;
		NoTipoN *pFilai,*pFilaf;
		pFilai = NULL;
		pFilaf = NULL;
		pInicial = NULL;
		pFinal = NULL;
		FILE *arq; 
		arq = fopen(argv[1],"r");	
		int contLin, contCol;
		
		mat = leArquivo(arq,&contLin,&contCol);
		printf("Matriz antes\n");
		imprimirMatriz(mat,contLin,contCol);	
		
		int n = 1; 
		int k = 0;
	
		validaCaminho2(mat,0,0,contLin,contCol,&k,&pInicial,&pFinal,&pFilai,&pFilaf);
		if(k==0)
			printf("Nao existe caminho!\n");
		FILE *arq2 = fopen("saida.txt","w+");
		EscreverArquivo(arq2,&pFilai);	// escreve a saída em um arquivo
		printf("Total de soluções %d\n",k);	
					
		liberarFilaFila(&pFilai); // liberando a fila de filas da memória
		
		liberarMatriz(&mat,contLin,contCol);		
	} else 
	{
		printf("Insira entrada valida!\n");
	}

	return 0;
}
