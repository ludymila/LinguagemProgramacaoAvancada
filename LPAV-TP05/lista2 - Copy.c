#include <stdio.h>
#include <stdlib.h>

struct no{
 int num;
 struct no *next;
} *primeiro, *percorre;


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


void imprime(void) {
	 percorre = primeiro;
	 while(percorre != NULL) {
		  printf("%d ", percorre->num);
		  percorre = percorre->next;
	 }
	 printf("\n");
}


void ordena(void) {
 struct no *a = NULL;
 struct no *b = NULL; 
 struct no *c = NULL;
 struct no *e = NULL; 
 struct no *aux = NULL; 

 while(e != primeiro->next) {
 c = a = primeiro;
 b = a->next;
  while(a != e) {
   if(a->num > b->num) {
    if(a == primeiro) {
     aux = b -> next;
     b->next = a;
     a->next = aux;
     primeiro = b;
     c = b;
    } else {
     aux = b->next;
     b->next = a;
     a->next = aux;
     c->next = b;
     c = b;
    }
   } else {
    c = a;
    a = a->next;
   }
   b = a->next;
   if(b == e)
    e = a;
  }
 }
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

