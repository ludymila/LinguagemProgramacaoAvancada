#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	int **mat;
	typedef struct matType {
		int x;
		int y;
	} Tmat;
	
	Tmat **matAdj;
	int cont0=0;
	int iVertice=1;
       //int mat[50][50];
	int caminhoX[50];
	int caminhoY[50];
	int aux, aux2; 
	int n,m,i,j, buscaX=1,buscaY=1, cont=0, achou=0,x;
	 //./prog1 < input.txt
	 //operacoes com arquivo
    FILE* file = NULL;
    //printf("%s\n", argv[1]);
    file = fopen(argv[1],"rw+");
     
     if(NULL == file)
    {
        printf("\n fopen() Error!!!\n");
        return 1;
    }
 	
    while(!feof (file)) 
    { 	
    	//Leitura do tamanho da Matriz[m,n]
    	fscanf(file,"%d\t%d\n",&m,&n);
	mat = (int**) malloc (sizeof(int*)*m);
	for (i=1; i<=m; i++) 
		mat[i] = (int*) malloc (sizeof(int)*n);

    	//Leitura da Matriz[m,n] comecando de 1,1
        for (i=1; i<=m; i++) {
			for (j=1; j<=n; j++) {
        		fscanf(file,"%d \t",&mat[i][j]);
			if (mat[i][j] == 0) cont0++;
        	}
        }
    }
	//printf("cont0: %d \n", cont0);
	//A lista de Adjacencia tem numero de linhas igual ao numero de vertices, representados por 0
	//cont0 = numero de 0s = numero de vertices
	matAdj = (Tmat**) malloc (sizeof(Tmat*)*cont0);
	//cada no tem no maximo 8 adjacencias, e mais o proprio vertice = 9
	for (i=1; i<=cont0; i++) 
		matAdj[i] = (Tmat*) malloc (sizeof(Tmat)*9);
	
	//salvando as posicoes X,Y dos vertices 0
	//coluna 1 = posicoes dos vertices
	iVertice=1;
	for (i=1; i<=m; i++) {
		for (j=1; j<=n; j++) {
			if (mat[i][j] == 0) {
				matAdj[iVertice][1].x = i;
				matAdj[iVertice][1].y = j;
				iVertice++; 
			}
        	}
        }	

	/*for (i=1; i<=m; i++) {
		for (j=1; j<=n; j++) {
			printf("%d \t", mat[i][j]);
			//getchar();
		}
		printf("\n");
	}*/


	//printf("valor %d \n" ,mat[2][2]);
	i=1; j=1; int k;  
	//HEURISTICA DE BUSCA: SUL, LESTE, SUDESTE.
	//poderia ter feito um for, mas quis garantir a ordem de precedencia das coordenadas
	int vi, vj; //verticeI, verticeJ	
	//while ((i<=m) && (j<=n)) {
	int contAdj=2;
	iVertice=0;
	for ( k=1; k<=cont0; k++){ //repete para cada Vertice				
		iVertice++;		
		i = matAdj[iVertice][1].x; //printf("i: %d \n", i); 
		j = matAdj[iVertice][1].y; //printf("j: %d \n", j); 

		
		contAdj=2;
		//printf("I,J: %d %d \n", i,j);
		
		if ((i-1>=1) && (j-1>=1) && (mat[i-1][j-1] == 0))  { //SUDOESTE
			matAdj[iVertice][contAdj].x = i-1; 
			matAdj[iVertice][contAdj].y = j-1;
			contAdj++;
		}
		if ((i-1>=1) && (j>=1) && (mat[i-1][j] == 0))  { 
			matAdj[iVertice][contAdj].x = i-1; 
			matAdj[iVertice][contAdj].y = j;
			contAdj++;
		}
		if ((j+1<=n) && (i-1>=1) && (mat[i-1][j+1] == 0)) { //NORDESTE
			matAdj[iVertice][contAdj].x = i-1; 
			matAdj[iVertice][contAdj].y = j+1;
			contAdj++;
		}
		if ((j-1>=1) && (mat[i][j-1] == 0)) { //OESTE
			matAdj[iVertice][contAdj].x = i; 
			matAdj[iVertice][contAdj].y = j-1;
			contAdj++;
		}		
		
		if ((j+1<=n) && (mat[i][j+1] == 0)) { //LESTE
			matAdj[iVertice][contAdj].x = i; 
			matAdj[iVertice][contAdj].y = j+1;
			contAdj++;
		}


		
		if ((i+1<=m) && (j-1>=1) && (mat[i+1][j-1] == 0))  { //SUDESTE
			matAdj[iVertice][contAdj].x = i+1; 
			matAdj[iVertice][contAdj].y = j-1;
			contAdj++;
		}
		
		if ((i+1<=m) && (mat[i+1][j] == 0)) { //SUL
			
			matAdj[iVertice][contAdj].x = i+1; 
			matAdj[iVertice][contAdj].y = j;
			contAdj++;
		} 
		
		if ((j+1<=n) && (i+1<=m) &&(mat[i+1][j+1] == 0))  { //SUDESTE
			matAdj[iVertice][contAdj].x = i+1; 
			matAdj[iVertice][contAdj].y = j+1;
			contAdj++;
		}

		//printf("%d ", caminhoX[cont-1]);
		//printf(" %d \n", caminhoY[cont-1]);
	
		//getchar();

		/*for (aux=1; aux<=m; aux++) {
		for (aux2=1; aux2<=n; aux2++) {
			printf("%d \t", mat[aux][aux2]);
			//getchar();
		}
		printf("\n");
	}*/

 		//transformo o 0 em 1, pq nao quero que ele volte
		

		//if (contAdj<8) {
			//matAdj[iVertice][contAdj].x = ;-1 
			//matAdj[iVertice][contAdj].y = j-1;	
	//	}
		//printf("ij:%d %d %d\n", i,j,m);
		
		
		
	}
	for (i=1; i<=cont0; i++) {
		for (j=1; j<=9; j++) {
				if (matAdj[i][j].x!=0){
					if (j==1) {					
						printf("[%d_", matAdj[i][j].x );
						printf("%d]: ", matAdj[i][j].y );
					}
					else {					
						printf("%d_", matAdj[i][j].x );
						printf("%d ", matAdj[i][j].y );
					}
				}
				//iVertice++;
			
        	}
		printf("\n");
        }	
	
	return 0;
}
