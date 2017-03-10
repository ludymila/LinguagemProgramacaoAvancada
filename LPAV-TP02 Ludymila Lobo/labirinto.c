#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int mat[20][20];
	int caminhoX[20];
	int caminhoY[20];
	int n,m,i,j, buscaX=1,buscaY=1, cont=0;
	//./prog1 < input.txt
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
    	//Leitura do tamanho da Matriz[m,n]
    	fscanf(file,"%d \t %d \n",&m,&n);
    	//Leitura da Matriz[m,n] comecando de 1,1
        for (i=1; i<=m; i++) {
			for (j=1; j<=n; j++) {
        		fscanf(file,"%d \t",&mat[i][j]);
        	}
        }
    }


	for (i=1; i<=m; i++) {
		for (j=1; j<=n; j++) {
			printf("%d \t", mat[i][j]);
			//getchar();
		}
		printf("\n");
	}


	printf("valor %d \n" ,mat[2][2]);
	i=1; j=1;
	//HEURISTICA DE BUSCA: SUL, LESTE, SUDESTE.
	while ((i<m) && (j<n)) {
	
		if (mat[i+1][j] == 0) { //SUL
			i= i+1;
			caminhoX[cont] = i;
			caminhoY[cont] = j;
			cont++;
			printf("oi\n");
			
		} 
		else if (mat[i][j+1] == 0) { //LESTE
			j= j+1;
			caminhoX[cont] = i;
			caminhoY[cont] = j;
			cont++;
		}
		else if (mat[i+1][j+1] == 0)  { //SUDESTE
			i=i+1;
			j=j+1;
			caminhoX[cont] = i;
			caminhoY[cont] = j;
			cont++;
			printf("oi\n");
		}
		printf("%d ", caminhoX[cont]);
		printf(" %d \n", caminhoY[cont]);
		getchar();
		getchar();
		
	}
	printf("oi.\n");
	//imprimindo coordenadas
	for (i=0; i<cont; i++) {
			
			printf("%d ", caminhoX[i]);
			printf(" %d \n", caminhoY[i]);
			//getchar();
		}
	printf("End.");
	return 0;
}