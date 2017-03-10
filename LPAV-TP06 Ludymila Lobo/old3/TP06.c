#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char *comandos;
char *cmd; //um unico comando
char mat[50][50];
//bool mat[50][50];
int m=1;
int n=1;
int cont=0;
int param[5] = {0,0,0,0,0};
//I M N
//Cria uma nova imagem M linhas x N colunas com todos os pixels inicialmente coloridos com zero (0).

int pegaParametro(int qtdParam){
	int casaDecimal; 
	int numCasas=0;	
         param[0] =0;param[1] =0; param[2] =0; param[3] =0; 
	int i ,j= 0;
	printf("pegacont:%c \n", comandos[cont]);
	//if (comandos[cont] != ' ') return 0; //nao deu espaco depois da letra do comando
	cont=cont+1;
	//printf("pegacont:%c \n", comandos[cont]);
	//printf("pegacontcerto:%c \n", comandos[cont+1]);
	for (i=0;i<qtdParam; i++){
		cont++;
	int teste; casaDecimal=0;
	//teste = pow(10,i);printf("teste:%d \n", teste);

		while ((comandos[cont] != ' ') && (comandos[cont] != '\n') ){
			
			//param[i] += ((comandos[cont] - '0'));//* teste);
			
			numCasas++;
			//printf("DEBUG:%d - %d\n", i, param[i]);
			casaDecimal++;
			cont++;
		}
		cont = cont - numCasas;
		for (j=0;j<numCasas;j++){
			
			param[i] = param[i]+ ((comandos[cont] - '0') * (pow(10,numCasas-j-1)));
			printf("DEBUG:%d - %d\n", j, param[i]);
			cont++;
		}
		numCasas =0;
		printf("pegaParametros:%d - %d\n", i, param[i]);
		casaDecimal=0;
		//cont++;
	}
cont++;
	//printf("FINALCONT:%c ", comandos[cont]);
	
	
}
int I(int x, int y){
	int i,j;
	//if (!(strcmp (m1,"0") || strcmp (n1,"0")) ){ //verificando se os parametros foram passados no comando
	//printf("\n %c %c \n", x,y);
	m = x;
	n = y;
	printf("\n %d %d \n", m,n);
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			mat[i][j] = '0';
			//printf("%c", mat[i][j]);
		}
		//printf("\n");
	}
	return 1;
	//}
	return 0; //parametros invalidos
}
//C
//Coloca todos os pixels da imagem com o valor zero(0). O tamanho permanece o mesmo.
int C(){
	int i,j;
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			mat[i][j] = '0';
			printf("%c",mat[i][j]);
		}
		printf("\n");
	}
}

//L X Y	C
//Colore o pixel (X,Y) com a cor C.
void L(int x, int y, char c){
		
	//strcpy(input[2], mat[atoi(input[0])][atoi(input[1])] );
	
	mat[x][y] = c;
	printf("aqui: %c\n", mat[x][y]);
}
//Desenha um segmento vertical com a cor C na coluna X, entre as linhas x1 e X2 (inclusive)
void V(int x, int y1, int y2, char c){
	//m=5; n=6;	
	int i,j;
		
	//printf("\n %c %c \n", x,y);
	
	//printf("\n %d %d \n", m,n);
	for (i=y1;i<=y2;i++){
		for (j=1;j<=n;j++){
			if (j == x) mat[i][j] = c; //else mat[i][j]='0';
		}
	}
}
void H(int x1, int x2, int y, char c){
	m=5; n=6;	
	int i,j;	
	
	//printf("\n %d %d \n", m,n);
	for (i=1;i<=m;i++){
		for (j=x1;j<=x2;j++){
			if (i == y) mat[i][j] = c; else mat[i][j]='0';
		}
	}
}
//pinta um quadrado (x1,x2) (y1,y2) da cor c
void K(int x1, int y1, int x2, int y2, char c){
	///m=5; n=6;	
	int i,j;
	
	
	for (i=x1;i<=x2;i++){
		for (j=y1;j<=y2;j++){
			mat[i][j] = c; 
		}
	}
}
int F(int x, int y, char c){
	//m=6; n=5;	
	int i,j,cont=0;
	//int x_,y_;	
	//printf("\n %c %c \n", x,y);
	//x_ = x - '0'; //coluna
	//y_ = y - '0';
	printf("\nXY %d %d \n", x,y);
	
//getchar();
	cont++;
	if (mat[x][y] == '0') mat[x][y] = c; else return 0;
	//if (cont>10) return 1;
	if ((x-1)>0)  F(x-1,y,c);  // cima
	//printf("i'm here");
	if ((y-1)>0) F(x,y-1,c);   // esquerda
	//printf("i'm here 2");
	if ((x+1)<=m)  F(x+1,y,c); // baixo
	//printf("i'm here 3");
	if ((y+1)<=n)  F(x,y+1,c); // direita
	//printf("i'm here 4");
	/*for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			mat[i][j] = c; 
		}
	}*/
	return 1;
}
//Escreve na tela o conteudo da imagem atual
void S(){
	int i,j;
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			printf("%c ",mat[i][j]);
		}
	printf("\n");
	}
}

int main(int argc, char *argv[]){

   cont = 1;
    int i,j,c;
	int param1, param2,param3,param4;
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
    comandos[n]='_'; //flag
   //printf("maximo%d\n",n); getchar();
	int aux=0;

	puts(comandos);
 if (comandos[cont+9] != '_') printf("certo");
getchar();
puts(comandos);
	aux = 1;
	//cont ta com a posicao do comando
	while(comandos[cont] != '_') {
		printf("Cont: %d \n", cont);
		while (comandos[cont+aux] =! '\n'){ //pegando a partir do espaco apos o comando
			cmd[aux] = comandos[cont+aux];
			aux++;
		}
		switch(comandos[cont]){
		case 'I': printf("Parametros: %d %d\n", param[0],param[1]); pegaParametro(2);
				I(param[0], param[1]); C(); S();
			break;
			
			case 'C': C();
			break;
			case 'L': pegaParametro(2); L(param[0], param[1], comandos[cont]); cont = cont+2; S();
			break;
			case 'V': pegaParametro(3); V(param[0], param[1], param[2], comandos[cont]); cont = cont+2; S();
			break;
			case 'H': pegaParametro(3); H(param[0], param[1], param[2], comandos[cont]); cont = cont+2; S();
			break;
			case 'K': pegaParametro(4); K(param[0], param[1], param[2], param[3], comandos[cont]); cont = cont+2; S();
			break;
			case 'F': pegaParametro(2); F(param[0], param[1], comandos[cont]); cont= cont+2; S();
			break;
			case 'S': S();
			break;
			case 'X':
			break;
			default: break;
		} 
		//cont = cont+aux +1; //pula pro proximo comando
	}
    fclose(file);
    printf("fim");
    return 0;
}
