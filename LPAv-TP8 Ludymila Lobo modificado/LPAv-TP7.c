#include <stdio.h> 
#include <stdlib.h> 


typedef enum {false, true} bool; 

typedef struct No
{
	int x,y;	
	struct No *next; 
} NodeType;

typedef struct pnode
{
	int index; 
	NodeType *pqueue; 
	struct pnode *next;
} NodeofNType;

typedef struct No1
{
	char value; 
	bool assigned;
} MazeType;


void imprimir_caminho(NodeType *aux) // imprime um caminho criado poru ma lista
{
	while(aux)
	{
		printf("L(%d,%d)\n",aux->x +1,aux->y +1);
		aux = aux->next;
	}
	printf("\n");
}

void inicializar_matriz(MazeType **table, int N, int M) // faz com que cada posição seja iniciada com não-assinalada
{
	int i , j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			table[i][j].assigned = false;
	}
}

void liberar_matriz(MazeType ***table, int N, int M) // libera matriz da memória
{
	int i,j;
	for(i=0;i<N;i++)
	{
		free(*(*table + i));
	}
	free(*table);
}

void liberar_fila(NodeType **pinit) // libera fila da memória
{
	NodeType *aux; 
	aux = *pinit;
	while((*pinit))
	{
		aux = *pinit;
		(*pinit) = (*pinit)->next;
		free(aux);

	}
}

void liberar_fila_de_fila(NodeofNType **pinit) // libera fila de filas
{
	NodeofNType *aux; 
	aux = *pinit; 
	while((*pinit))
	{
		aux = *pinit; 
		(*pinit) = (*pinit)->next;
		liberar_fila(&aux->pqueue);
		free(aux);
	}
}


void imprimir_tabela(MazeType **table, int N, int M) // imprime tabela 
{
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
			
			if(table[i][j].value != '\t')
				printf("%c\t",table[i][j].value);
		}			
		printf("\n");

	}
		
}

void inserir_fila(NodeType **pinit, NodeType **pfinal, int x, int y) // insere na fila
{
	NodeType *new; 
	new = (NodeType*)malloc(sizeof(NodeType)); 
	new->next = NULL;
	new->x = x;
	new->y = y;	
	if(!*pinit)
	{	
		*pinit = new; 
		*pfinal = new; 
	} else 
	{
		(*pfinal)->next = new; 
		(*pfinal) = new;
	}
}

void inserir_fila_na_fila(NodeofNType **pqueuei, NodeofNType **pqueuef, NodeType **pinit, int k)
{
	NodeofNType *new;
	new = (NodeofNType*)malloc(sizeof(NodeofNType));
	new->index = k;
	new->next = NULL;
	new->pqueue = *pinit;
	if(!*pqueuei)
	{
		*pqueuei = new;
		*pqueuef = new; 
	} else 
	{
		(*pqueuef)->next = new;
		(*pqueuef) = new;
	}
}

void remover_ultimo_no_fila(NodeType **pinit,NodeType **pfinal) // remove o último elemento de uma fila
{
	if(!*pinit)
		return;
	if((*pinit)->next == NULL)
	{
		free(*pinit);		
		*pinit = NULL;	
		*pfinal = NULL;
	}
	else if(*pfinal != NULL && pinit != NULL)
	{
		NodeType *aux, *aux2;		
		aux = *pinit;		
		while(aux->next!=*pfinal)
		{
			aux = aux->next; 
		}		
		*pfinal = aux;	
		aux2 = aux->next;
		aux->next = NULL;		
		free(aux2);
		
		//printf("valor do *pfinal %p\n",*pfinal);
		//printf("saindo do free\n");
	} 
}

void copiar_fila(NodeType **pinit, NodeType **pfinal, NodeType **pinit2) // copia uma fila para outra
{
	NodeType *aux;
	aux = *pinit2; 
	while(aux)
	{
		inserir_fila(pinit,pfinal,aux->x,aux->y);
		aux = aux->next;
	}
}

bool posicao_final(int i,int j,int N, int M ) // verifica se está na ultima posição
{
	if(i == N-1 && j == M - 1)
		return true;
	else false;
}

void imprimir_caminho_fila(NodeofNType **pqueuei, int N, int M) // imprime caminho da fila
{
	int i = 0, j = 0;
	
	NodeofNType *aux;
	aux = *pqueuei;
	NodeType *aux2;	
	while(aux)
	{
		printf("Caminho (%d): \n",aux->index);		
		imprimir_caminho(aux->pqueue);	
		printf("\n");
		aux = aux->next;			}			
	
}

bool posicao_valida_matriz(int i, int j, int N, int M)
{	
	if(i == N  || j == M || i < 0 || j < 0)
		return false;
	else return true;
}

void assign_position_table(MazeType **table,int i,int j)
{
	table[i][j].value = 'x'; 	
	table[i][j].assigned = true;
}

void unassign_position_table(MazeType **table, int i, int j)
{
	table[i][j].value = '0'; 
	table[i][j].assigned = false;
}
//calcula apenas uma possibildade
bool backtracking(MazeType **table,int i, int j, int N, int M, int *k, NodeType **pinit, NodeType **pfinal)
{	
	NodeType *pinitbuf = NULL, *pfinalbuf = NULL; 	
	if(posicao_valida_matriz(i,j,N,M)==true && table[i][j].value == '0')
	{					
		assign_position_table(table,i,j); 						
		inserir_fila(pinit,pfinal,i,j);

		if(posicao_final(i,j,N,M)==true)
		{										
			*k = *k+1;	
			
			imprimir_tabela(table,N,M);											
			printf("Caminho (%d): \n",*k);
			imprimir_caminho(*pinit);
			
			return true;

		}
		
		if(backtracking(table,i+1,j,N,M,k,pinit,pfinal)==true)
			return true;  // baixo		
		if(backtracking(table,i+1,j+1,N,M,k,pinit,pfinal)==true)
			return true; // baixo-direita		
		if(backtracking(table,i,j+1,N,M,k,pinit,pfinal)==true)
			return true; // direita		
		if(backtracking(table,i-1,j+1,N,M,k,pinit,pfinal)==true)
			return true; //cima-direita	
		if(backtracking(table,i-1,j,N,M,k,pinit,pfinal)==true)
			return true; //cima		
		if(backtracking(table,i-1,j-1,N,M,k,pinit,pfinal)==true)
			return true; //cima-esquerad
		if(backtracking(table,i,j-1,N,M,k,pinit,pfinal)==true)
			return true;  // esquerda

		unassign_position_table(table,i,j); 			
		//remover_ultimo_no_fila(pinit,pfinal);							

	} 		
	return false;
	
}
// calcula todas as possibilidades
void backtracking2(MazeType **table,int i, int j, int N, int M, int *k, NodeType **pinit, NodeType **pfinal, NodeofNType **pqueuei, NodeofNType **pqueueif)
{	
	NodeType *pinitbuf = NULL, *pfinalbuf = NULL; 
	if(posicao_valida_matriz(i,j,N,M)==true && table[i][j].value == '0' && table[i][j].assigned == false)
	{			
		//printf("assinalando\n");
		assign_position_table(table,i,j); 				
		//printf("antes de inserir_fila\n");
		inserir_fila(pinit,pfinal,i,j);
		//imprimir_tabela(table,N,M);		

		if(posicao_final(i,j,N,M)==true)
		{										
			*k = *k+1;	
					
			imprimir_tabela(table,N,M);					
			
			copiar_fila(&pinitbuf,&pfinalbuf,pinit);			
			inserir_fila_na_fila(pqueuei,pqueueif,&pinitbuf,*k);	 
			printf("Caminho (%d): \n",*k);		
			imprimir_caminho((*pqueueif)->pqueue);				
			unassign_position_table(table,i,j); 	
			inicializar_matriz(table,N,M);	


		}		

			backtracking2(table,i+1,j,N,M,k,pinit,pfinal,pqueuei,pqueueif);	
			backtracking2(table,i+1,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);// baixo-direita		
			backtracking2(table,i,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);	// direita		
			backtracking2(table,i-1,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);
			backtracking2(table,i-1,j,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
			backtracking2(table,i-1,j-1,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
			backtracking2(table,i,j-1,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
	
			unassign_position_table(table,i,j); 			
			remover_ultimo_no_fila(pinit,pfinal);												
			//imprimir_caminho(*pinit);	

	} 			
	return;
	
}

MazeType **create_table( int N, int M) // cria uma matriz dinamicamente
{
	MazeType **table;
	
	table = (MazeType**)malloc(N*sizeof(MazeType*)); // aloca vetor de linhas
	int i;	
	for(i=0;i<N;i++) // alocar elementos de cima a baixo , M é quantidade de linhas
		*(table + i) = (MazeType*)malloc(M*sizeof(MazeType)); 

	return table;
}



MazeType **creating_table_of_the_file(FILE *arq, int *amount_rows, int *amount_columns) // cria uma matriz a partir da prmeira linha da entrada
{
	MazeType **table; 
	fscanf(arq,"%d\t%d\n",amount_rows,amount_columns);	
	table = create_table(*amount_rows,*amount_columns);

	return table;
}


void ler_matriz_no_arquivo(FILE *arq, MazeType **table, int *amount_rows, int *amount_columns)
{
	int i = 0, j = 0;
	char pos ; 
	while(i < *amount_rows)
	{		
		while(j < *amount_columns)
		{		
			fscanf(arq,"%c",&pos);									
			if(pos != '\0' && pos != '\n')
			{							
				if(pos != '	') // se o caracter for diferente de tab
				{
					table[i][j].value = pos; 					
					j++;
				}	
			}		
		}		
		j = 0;
		
		i++;
	}	
}

MazeType **read_entry_file(FILE *arq, int *amount_rows, int *amount_columns) // le um arquivo e insere na matriz
{
	rewind(arq);	
	MazeType **table; 

	table = creating_table_of_the_file(arq,amount_rows,amount_columns);	// le a primeira linha
	ler_matriz_no_arquivo(arq,table,amount_rows,amount_columns);
	
	return table;
}

void EscreverArquivo(FILE *arq, NodeofNType **pqueuei) // escreve as saídas de uma fila de filas num arquivo
{			
	NodeofNType *aux;
	aux = *pqueuei;
	NodeType *aux2;	
	while(aux!=NULL)
	{
		fprintf(arq,"Caminho (%d): ",aux->index);		
		aux2 = aux->pqueue;
		while(aux2)
		{
			fprintf(arq,"L(%d,%d)\n",aux2->x,aux2->y);
			aux2 = aux2->next;
		}
		fprintf(arq,"\n");		
		aux = aux->next;		
	}			
	
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		MazeType **table; 
		NodeType *pinit, *pfinal;
		NodeofNType *pqueuei,*pqueuef;
		pqueuei = NULL;
		pqueuef = NULL;
		pinit = NULL;
		pfinal = NULL;
		FILE *arq; 
		arq = fopen(argv[1],"r");	
		int amount_rows, amount_columns;
		
		table = read_entry_file(arq,&amount_rows,&amount_columns);
		printf("Matriz antes\n");	
		imprimir_tabela(table,amount_rows,amount_columns);	
		
		int n = 1; 
		int k = 0;
	
		backtracking2(table,0,0,amount_rows,amount_columns,&k,&pinit,&pfinal,&pqueuei,&pqueuef);
		if(k==0)
			printf("NÃO HÁ CAMINHO\n");
		FILE *arq2 = fopen("saida.txt","w+");
		EscreverArquivo(arq2,&pqueuei);	// escreve a saída em um arquivo
		printf("Total de soluções %d\n",k);	
					
		liberar_fila_de_fila(&pqueuei); // liberando a fila de filas da memória
		
		liberar_matriz(&table,amount_rows,amount_columns);		
	} else 
	{
		printf("Insira uma entrada correta!\n");
	}

	return 0;
}
