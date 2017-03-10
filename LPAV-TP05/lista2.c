#include <stdio.h>
#include <stdlib.h>

typedef struct no{
 int num;
 struct no *next;
} lista;

lista *primeiro, *percorre;

void adicionar(struct no **novo, int num) {
 struct no *aux; 
 aux = *novo;

 if(*novo == NULL) {
  *novo = malloc(sizeof(struct no));
   aux = *novo;
 } else {
  
  while(aux->next != NULL)
   aux = aux->next;

  //adiciona no final
   aux->next = malloc(sizeof(struct no));
   aux = aux->next;
 }

 aux->num = num;
 aux->next = NULL;
}

void ordena(void) {
 struct no *a1,*a2,*a3,*ordenado,*aux;
 ordenado = NULL;
 aux = NULL;
 while(ordenado != primeiro->next) {
 a3 = a1 = primeiro;
 a2 = a1->next;
  while(a1 != ordenado) 
  {
   if(a1->num > a2->num) {
		if(a1 == primeiro) {
			 aux = a2 -> next;
			 a2->next = a1;
			 a1->next = aux;
			 primeiro = a2;
			 a3 = a2;
		} 
		else {
			 aux = a2->next;
			 a2->next = a1;
			 a1->next = aux;
			 a3->next = a2;
			 a3 = a2;
		}
   } 
   else {
    a3 = a1;
    a1 = a1->next;
   }
   a2 = a1->next;
   
   if(a2 == ordenado){
	 ordenado = a1;
  }
  }
 }
}


void imprime() {
	 percorre = primeiro;
	 while(percorre != NULL) {
		  printf("%d ", percorre->num);
		  percorre = percorre->next;
	 }
	 printf("\n");
}

int main(int argc, char *argv[]) {
	 struct no *novo = NULL;
	 int num;  
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
		adicionar(&novo,num);
	}

	 primeiro = novo;
	 printf("Antes da ordenacao:\n");
	 imprime();
	 
	 printf("Depois da ordenacao:\n");
	 ordena();
	 imprime();
	 return 0;
}

