

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


void print_path(NodeType *aux) // imprime um caminho criado poru ma lista
{
	while(aux)
	{
		printf("L(%d,%d)->",aux->x,aux->y);
		aux = aux->next;
	}
	printf("\n");
}

void initialize_matrix(MazeType **table, int N, int M) // faz com que cada posição seja iniciada com não-assinalada
{
	int i , j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
			table[i][j].assigned = false;
	}
}

void free_matrix(MazeType ***table, int N, int M) // libera matriz da memória
{
	int i,j;
	for(i=0;i<N;i++)
	{
		free(*(*table + i));
	}
	free(*table);
}

void free_queue(NodeType **pinit) // libera fila da memória
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

void free_queue_of_queue(NodeofNType **pinit) // libera fila de filas
{
	NodeofNType *aux; 
	aux = *pinit; 
	while((*pinit))
	{
		aux = *pinit; 
		(*pinit) = (*pinit)->next;
		free_queue(&aux->pqueue);
		free(aux);
	}
}


void print_table(MazeType **table, int N, int M) // imprime tabela 
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

void insert_queue(NodeType **pinit, NodeType **pfinal, int x, int y) // insere na fila
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

void insert_queue_in_queue(NodeofNType **pqueuei, NodeofNType **pqueuef, NodeType **pinit, int k)
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

void remove_last_node_queue(NodeType **pinit,NodeType **pfinal) // remove o último elemento de uma fila
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

void copy_two_queue(NodeType **pinit, NodeType **pfinal, NodeType **pinit2) // copia uma fila para outra
{
	NodeType *aux;
	aux = *pinit2; 
	while(aux)
	{
		insert_queue(pinit,pfinal,aux->x,aux->y);
		aux = aux->next;
	}
}

bool final_position(int i,int j,int N, int M ) // verifica se está na ultima posição
{
	if(i == N-1 && j == M - 1)
		return true;
	else false;
}

void print_path_queue(NodeofNType **pqueuei, int N, int M) // imprime caminho da fila
{
	int i = 0, j = 0;
	
	NodeofNType *aux;
	aux = *pqueuei;
	NodeType *aux2;	
	while(aux)
	{
		printf("Caminho (%d): ",aux->index);		
		print_path(aux->pqueue);	
		printf("\n");
		aux = aux->next;			}			
	
}

bool valid_position_in_matrix(int i, int j, int N, int M)
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
	if(valid_position_in_matrix(i,j,N,M)==true && table[i][j].value == '0')
	{					
		assign_position_table(table,i,j); 						
		insert_queue(pinit,pfinal,i,j);

		if(final_position(i,j,N,M)==true)
		{										
			*k = *k+1;	
			
			print_table(table,N,M);											
			printf("Caminho (%d): ",*k);
			print_path(*pinit);
			
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
		//remove_last_node_queue(pinit,pfinal);							

	} 		
	return false;
	
}
// calcula todas as possibilidades
void backtracking2(MazeType **table,int i, int j, int N, int M, int *k, NodeType **pinit, NodeType **pfinal, NodeofNType **pqueuei, NodeofNType **pqueueif)
{	
	NodeType *pinitbuf = NULL, *pfinalbuf = NULL; 
	if(valid_position_in_matrix(i,j,N,M)==true && table[i][j].value == '0' && table[i][j].assigned == false)
	{			
		//printf("assinalando\n");
		assign_position_table(table,i,j); 				
		//printf("antes de insert_queue\n");
		insert_queue(pinit,pfinal,i,j);
		//print_table(table,N,M);		

		if(final_position(i,j,N,M)==true)
		{										
			*k = *k+1;	
					
			print_table(table,N,M);					
			
			copy_two_queue(&pinitbuf,&pfinalbuf,pinit);			
			insert_queue_in_queue(pqueuei,pqueueif,&pinitbuf,*k);	 
			printf("Caminho (%d): ",*k);		
			print_path((*pqueueif)->pqueue);				
			unassign_position_table(table,i,j); 	
			initialize_matrix(table,N,M);	


		}		

			backtracking2(table,i+1,j,N,M,k,pinit,pfinal,pqueuei,pqueueif);	
			backtracking2(table,i+1,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);// baixo-direita		
			backtracking2(table,i,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);	// direita		
			backtracking2(table,i-1,j+1,N,M,k,pinit,pfinal,pqueuei,pqueueif);
			backtracking2(table,i-1,j,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
			backtracking2(table,i-1,j-1,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
			backtracking2(table,i,j-1,N,M,k,pinit,pfinal,pqueuei,pqueueif);		
	
			unassign_position_table(table,i,j); 			
			remove_last_node_queue(pinit,pfinal);												
			//print_path(*pinit);	

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


void read_matrix_in_file(FILE *arq, MazeType **table, int *amount_rows, int *amount_columns)
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
	read_matrix_in_file(arq,table,amount_rows,amount_columns);
	
	return table;
}

void write_in_file(FILE *arq, NodeofNType **pqueuei) // escreve as saídas de uma fila de filas num arquivo
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
			fprintf(arq,"L(%d,%d)->",aux2->x,aux2->y);
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
		print_table(table,amount_rows,amount_columns);	
		
		int n = 1; 
		int k = 0;
		printf("0) Para sair!\n"); 
		printf("1) Para gerar apenas uma possibilidade!\n");
		printf("2) Para gerar várias possibilidades!\n");
		scanf("%d",&n);
		if(n == 0)
			return;		
		if(n==1)
		{
			backtracking(table,0,0,amount_rows,amount_columns,&k,&pinit,&pfinal);	
			if(k==0)
				printf("NÃO HÁ CAMINHO\n");
			free_queue(&pinit);// libera fila da memória
		}
		if(n==2)
		{
			backtracking2(table,0,0,amount_rows,amount_columns,&k,&pinit,&pfinal,&pqueuei,&pqueuef);
			if(k==0)
				printf("NÃO HÁ CAMINHO\n");
			FILE *arq2 = fopen("saida.txt","w+");
			write_in_file(arq2,&pqueuei);	// escreve a saída em um arquivo
			printf("Total de soluções %d\n",k);	
			printf("**Obs: Foi gerada uma saida.txt com todas as saídas conforme a especificação.\n");			
			free_queue_of_queue(&pqueuei); // liberando a fila de filas da memória
		}	
		free_matrix(&table,amount_rows,amount_columns);		
	} else 
	{
		printf("Insira uma entrada correta!\n");
	}

	return 0;
}