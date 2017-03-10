#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	char mat[50][50];
	char comando[6];
	int m=1,n=1;
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
 	//I M N
 	//Cria uma	nova imagem M linhas x N colunas com todos os pixels inicialmente coloridos	com zero (0).
    int I(char m1, char n1){
    	int i,j;
    	if (!(strcmp (m1,0) || strcmp (n1,0)) ){ //verificando se os parametros foram passados no comando
    		m = atoi(m1);
    		n = atoi(n1);
    		for (i=0;i<m;i++){
    			for (j=0;j<n;j++){
    				mat[i][j] = "0";
    			}
    		}
    		return 1;
    	}
    	return 0; //parametros invalidos
    }
    //C
    //Coloca todos os pixels da imagem com o valor zero(0). O tamanho permanece o mesmo.
    int C(){
    	for (i=0;i<m;i++){
    			for (j=0;j<n;j++){
    				mat[i][j] = "0";
    			}
    		}
    }
    //L	X Y	C
    //Colore	o	pixel	(X,Y)	com	a	cor	C.
    void L(char *input[]){
    	strcpy(input[2], mat[atoi(input[0])][atoi(input[1])] );
    }
    void V(){
    	
    }
    void H(){
    	
    }
    void K(){
    	
    }
    void F(){
    	
    }
    while(!feof (file)) 
    { 	
    	while()
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