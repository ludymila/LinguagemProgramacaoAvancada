#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct Evento{
		int num;
}evento_t;

typedef struct Lista_eventos{
	   evento_t* evento;
	   struct Lista_eventos* proximo;
}lista_eventos_t;

lista_eventos_t *lista;
lista_eventos_t *primeiro;
int cont=0;

//adicionar evento no inicio. os valores ja estao na estrutura. novo evento ja alocado
bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){	
	lista_eventos_t *item_novo = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL) return false;
	
	item_novo->evento = evento; // Seta o novo item
	item_novo->proximo = *lista; // O próximo do novo item será a lista
	if (lista==NULL) {
		*lista = item_novo;
		primeiro = *lista;
		printf("a%d", primeiro->evento->num);
	}
	else 
		*lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
	return 1;
}

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t *temp = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // temporario
	temp = lista;
	while (temp!=NULL) {
		printf("%d\t", temp->evento->num);
		temp = temp->proximo;
	}
}

/*bool ordena(lista_eventos_t *lista){
	lista_eventos_t *temp = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // temporario
	lista_eventos_t *atual = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); 
	lista_eventos_t *percorre = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	
	int n1;
	int n2; 
	int i;
	primeiro = lista;
	for(i = 0; i<cont; ++i) { 

		atual = percorre = primeiro; //atual e percorre  no no de inicio

		while (atual->proximo != NULL) { 
		  if (atual->evento->num > atual->proximo->evento->num) { //compara atual e atual->proximo
				temp = atual->proximo; //trocar ponteiros de atual e atual->proximo
				atual->proximo = atual->proximo->proximo;
				temp->proximo = atual;

				if(atual == primeiro) //troca do primeiro elemento, preservando a head
				  primeiro = percorre = temp;
				else 
				  percorre->proximo = temp;
				atual = temp; // atual muda pra temp (trocaram de posicao)
		    }
		  percorre = atual;
		  atual = atual->proximo; 
		}
	}
	lista = atual;

	
	/*
	while(temp2!=NULL){
		n1 = temp2->evento->num;
		temp = lista;
		while (temp!=NULL) {
			if (temp->proximo!= NULL) {
				n2 = temp->proximo->evento->num;
				 if (n1>n2) {
					temp->evento->num = n2;
					temp->proximo->evento->num = n1;
				 }
			}
			temp = temp->proximo;
		}
		temp2 = temp2->proximo;
	}
}*/

bool ordena(lista_eventos_t *lista){
    lista_eventos_t *temp = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // temporario
    lista_eventos_t *atual = (lista_eventos_t*) malloc(sizeof(lista_eventos_t));
    lista_eventos_t *percorre = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // Aloca o novo item
    
    int n1;
    int n2;
    int i,j; //@Pauli
    primeiro = lista;
    int mudou; //@Pauli
    for(i = cont-1; i>=0; i--) { //@Pauli
        mudou=0;//@Pauli
        atual = percorre = primeiro; //atual e percorre  no no de inicio
        
        for (j=0;j<i;j++) { //@Pauli
        //while (atual->proximo != NULL) { //@Pauli
            if (atual->evento->num > atual->proximo->evento->num) { //compara atual e atual->proximo
                temp = atual->proximo; //trocar ponteiros de atual e atual->proximo
                atual->proximo = atual->proximo->proximo;
                temp->proximo = atual;
                
                if(atual == primeiro) //troca do primeiro elemento, preservando a head
                    primeiro = percorre = temp;
                else
                    percorre->proximo = temp;
                atual = temp; // atual muda pra temp (trocaram de posicao)
            }
            percorre = atual;
            atual = atual->proximo;
            mudou=1; //@Pauli
        }
    }
    lista = atual;
} 



int main(int argc, char *argv[]){
	int num; 
	//lista= (lista_eventos_t*) malloc (sizeof (lista_eventos_t));
	lista = NULL; primeiro = NULL;
	evento_t *eventoNovo;
	//operacoes com arquivo
	FILE* file = NULL;
	printf("%s\n", argv[1]);
    file = fopen(argv[1],"rw+");
	
	 if(NULL == file)
    {
        printf("\n fopen() Error!!!\n");
        return 1;
    }

	while(!feof (file))  
	{  
	    fscanf(file,"%d \t",&num);
        //printf("\n%3.2f %d %d", num_,alvo_,tipo_);
		eventoNovo   = (evento_t*)        malloc (sizeof (evento_t));
		//salvando as informacoes no struct evento
		eventoNovo->num = num;
		
	
		
		cont++;
		lista_eventos_adicionar_inicio(eventoNovo, &lista);	
	}
	lista_eventos_listar(lista);
	
	//printf("primeiro %d \n", primeiro->evento->num);
	ordena(lista);
	printf("\nordenado \n\n");
	lista_eventos_listar(lista);
 	
	fclose(file);   
	return 1;
}

