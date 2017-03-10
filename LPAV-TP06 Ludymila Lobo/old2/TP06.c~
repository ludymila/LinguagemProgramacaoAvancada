#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *comandos;
char mat[50][50];
//bool mat[50][50];
int m=1;
int n=1;
//I M N
//Cria uma nova imagem M linhas x N colunas com todos os pixels inicialmente coloridos com zero (0).
int I(char x, char y){
	int i,j;
	//if (!(strcmp (m1,"0") || strcmp (n1,"0")) ){ //verificando se os parametros foram passados no comando
	printf("\n %c %c \n", x,y);
	m = x - '0';
	n = y - '0';
	printf("\n %d %d \n", m,n);
	for (i=1;i<=m;i++){
		for (j=1;j<=n;j++){
			mat[i][j] = '0';
			printf("%c", mat[i][j]);
		}
		printf("\n");
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
void L(char x, char y, char c){
	int x1,y1;	
	//strcpy(input[2], mat[atoi(input[0])][atoi(input[1])] );
	x1 = x - '0';
	y1 = y - '0';
	mat[x1][y1] = c;
	printf("aqui: %c\n", mat[x1][y1]);
}
//Desenha um segmento vertical com a cor C na coluna X, entre as linhas x1 e X2 (inclusive)
void V(char x, char y1, char y2, char c){
	m=5; n=6;	
	int i,j;
	int x_, y1_,y2_;	
	//printf("\n %c %c \n", x,y);
	x_ = x - '0'; //coluna
	y1_ = y1 - '0';
	y2_ = y2 - '0';
	printf("\n %d %d \n", m,n);
	for (i=y1_;i<=y2_;i++){
		for (j=1;j<=n;j++){
			if (j == x_) mat[i][j] = c; else mat[i][j]='0';
		}
	}
}
void H(char x1, char x2, char y, char c){
	m=5; n=6;	
	int i,j;
	int x1_, x2_,y_;	
	//printf("\n %c %c \n", x,y);
	x1_ = x1 - '0'; //coluna
	x2_ = x2 - '0';
	y_ = y - '0';
	//printf("\n %d %d \n", m,n);
	for (i=1;i<=m;i++){
		for (j=x1_;j<=x2_;j++){
			if (i == y_) mat[i][j] = c; else mat[i][j]='0';
		}
	}
}
//pinta um quadrado (x1,x2) (y1,y2) da cor c
void K(char x1, char y1, char x2, char y2, char c){
	m=5; n=6;	
	int i,j;
	int x1_, x2_,y1_,y2_;	
	//printf("\n %c %c \n", x,y);
	x1_ = x1 - '0'; //coluna
	x2_ = x2 - '0';
	y1_ = y1 - '0';
	y2_ = y2 - '0';
	//printf("\n %d %d \n", m,n);
	
	for (i=x1_;i<=x2_;i++){
		for (j=y1_;j<=y2_;j++){
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
 
    printf("este: %c", comandos[1]);
    switch(comandos[1]){
	case 'I': I(comandos[3], comandos[5]);
	break;
	case 'C': C();
	break;
	case 'L': L(comandos[3], comandos[5], comandos[7]);
	break;
	case 'V': V(comandos[3], comandos[5], comandos[7], comandos[9]); S();
	break;
	case 'H': H(comandos[3], comandos[5], comandos[7], comandos[9]); S();
	break;
	case 'K': K(comandos[3], comandos[5], comandos[7], comandos[9],comandos[11]); S();
	break;
	case 'F': I('5','6');C(); F(comandos[3] - '0', comandos[5] - '0', comandos[7]);S();
	break;
	case 'S': S();
	break;
	case 'X':
	break;
	default: break;
    } 
    
    fclose(file);
    printf("fim");
    return 0;
}
