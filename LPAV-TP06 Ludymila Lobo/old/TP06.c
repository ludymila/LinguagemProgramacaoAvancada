#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	char mat[50][50];

	char comando[6] = {1,1,1,1,1,1};
	int m=1;
    int n=1;
    int i,j;

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
    	
    	//Leitura da Matriz[m,n] comecando de 1,1
        //for (i=1; i<=m; i++) {
		//	for (j=1; j<=n; j++) {
        		//fflush(stdin);
                //__fpurge(stdin);
                fgets(&mat[1][1],1,file);
                printf("%c", mat[1][1]);
            
        //	}
      //  }
    }

    fclose(file);
    printf("fim");


	
	return 0;
}