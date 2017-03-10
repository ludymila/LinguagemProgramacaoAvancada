#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct Evento{
		double tempo;
		int alvo;
		int tipo;
}evento_t;

typedef struct Lista_eventos{
	   evento_t* evento;
	   struct Lista_eventos* proximo;
}lista_eventos_t;

lista_eventos_t *lista;

//adicionar evento no inicio. os valores ja estao na estrutura. novo evento ja alocado
bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){	
	lista_eventos_t *item_novo = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL) return false;
	item_novo->evento = evento; // Seta o novo item
	item_novo->proximo = *lista; // O próximo do novo item será a lista
	*lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
	return 1;
}

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t *temp = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // temporario
	temp = lista;
	while (temp!=NULL) {
		printf("%3.2f\t", temp->evento->tempo);
		printf("%d\t", temp->evento->alvo);
		printf("%d\t\n", temp->evento->tipo);
		temp = temp->proximo;
	}
}

int main(int argc, char *argv[]){
	double tempo_; 
	int    alvo_;
	int    tipo_;
	
	//lista= (lista_eventos_t*) malloc (sizeof (lista_eventos_t));
	lista = NULL;
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
	    fscanf(file,"%lf \t %d \t %d \n",&tempo_,&alvo_,&tipo_);
        //printf("\n%3.2f %d %d", tempo_,alvo_,tipo_);

		eventoNovo   = (evento_t*)        malloc (sizeof (evento_t));
		//salvando as informacoes no struct evento
		eventoNovo->tempo = tempo_;
		eventoNovo->alvo = alvo_;
		eventoNovo->tipo = tipo_;

		lista_eventos_adicionar_inicio(eventoNovo, &lista);	
	}
	lista_eventos_listar(lista);
 	
	fclose(file);   
	return 1;
}

