#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    char mat[50][50];
    char *comandos;
    int m=1;
    int n=1;
    int i,j,c;

    FILE* file = NULL;
    printf("%s\n", argv[1]);
    file = fopen(argv[1],"rw+");
     
    if(NULL == file)
    {
        printf("\n fopen() Error!!!\n");
        return 1;
    }
    comandos = malloc (1000);
    while ((c = fgetc(file)) != EOF) {
	comandos[n++] = (char) c;
    }
    comandos[n]='\0';
    //return comandos;
    //while(!feof (file)) 
    // { 	
    //fscanf(file, &buffer);
    //Leitura da Matriz[m,n] comecando de 1,1
    //for (i=1; i<=m; i++) {
    //for (j=1; j<5; j++) {

    //fflush(stdin);
    //__fpurge(stdin);
    //fgets(&mat[1][1],&mat[1][2], 2,file);
    //fgets(&mat[1][2], 2,file);

    //carname[j] = strdup(buffer);
    //printf("este: %c", carname[j]);
    //printf("este: %c", mat[1][1]);
     printf("este: %c", comandos[1]);
     printf("este: %c", comandos[3]);
     printf("este: %c", comandos[4]);
     printf("este: %c", comandos[5]);
            
     //	}
     //  }
     //}

    fclose(file);
    printf("fim");
    return 0;
}
