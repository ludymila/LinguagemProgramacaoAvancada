#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int mat[6][6]; //Matriz tem sempre tamanho 6,6
const int tam = 6;
int binario[22] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int binPosicao=22;
int binX[22];
int binY[22];
int qtdVazia=0;
int fim=0;
//------------------------------------------------------------------------------------------------
bool numValido(int x, int y, int num){
	//contando numeros consecutivamente iguais ao redor
	//BAIXO
	if ( ((x+1)<6) && (mat[x+1][y] == num))  {
			if (( (x+2)<6) && (mat[x+2][y] == num) )  return false; //verificando se tem 2 numeros iguais nas 2 casas consecutivas abaixo
			if (( (x-1)>=0) && (num == mat[x-1][y]) ) return false; //verificando sem tem numeros iguais em baixo e em cima
	}
	
	//CIMA	
	if ( ((x-1)>=0) && (num == mat[x-1][y]) ) {
			if (( (x-2)>=0) && (num == mat[x-2][y]) ) return false; //verificando se tem 2 numeros iguais nas 2 casas consecutivas acima
			if (( (x+1)<6) && (num == mat[x+1][y]) ) return false; //verificando sem tem numeros iguais em cima e em baixo
	}
	//DIREITA
	if ( ((y+1)<6) && (num == mat[x][y+1]) ) {
			if (( (y+2)<6) && (num == mat[x][y+2]) ) return false;
			if (( (y-1)>0) && (num == mat[x][y-1]) ) return false;
	}
	//ESQUERDA	
	if ( ((y-1)>=0) && (num == mat[x][y-1]) ) {
			if (( (y-2)>=0) && (num == mat[x][y-2]) ) return false;
			if (( (y+1)<6) && (num == mat[x][y+1]) ) return false;
	}
	
	//CIMA && BAIXO

	return true;
}

//Verificacao1: Cada caixa deve conter um 0 ou 1
bool valida0ou1(){
int i,j;
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			if ( (mat[i][j]!=1) && (mat[i][j]!=0) ) return false;
		}
	}
	return true;
}

//Verificacao2: Nao mais do que DOIS numeros iguais do lado ou abaixo
bool validaAdjacencias(){
	int i,j;
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			if (!numValido(i,j,mat[i][j])) return false;
		}
	}
	return true;
}
//Verificacao 3: 0s e 1s devem estar em mesma quantidade em linhas e colunas
bool validaLinhasColunas(){
	int i,j;
	char cont[2] = {0,0};
	//linhas
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 cont[mat[i][j]]++;
		}
		if (cont[0] != cont[1]) return false;
		cont[0] = cont[1] = 0;
	}
	//colunas
	for (j=0;j<6;j++){
		for (i=0;i<6;i++){
			 cont[mat[i][j]]++;
		}
		if (cont[0] != cont[1]) return false;
		cont[0] = cont[1] = 0;
	}
	return true;
}

//Verificacao 4: Cada linha e coluna deve ser unica
bool validaIguais(){
	int i,j;
	int aux[6];

	//linhas
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 aux[i]+= (mat[i][j] * pow(10,i)); 
		}
	}
	if (aux[0] != aux[1] != aux[2] != aux[3] != aux[4] != aux[5] != aux [6]) { //linhas sao diferentes
		aux[0] = aux[1] = aux[2] = aux[3] = aux[4] = aux[5] = aux[6];
		//colunas
		for (j=0;j<6;j++){
			for (i=0;i<6;i++){
				 aux[j]+= (mat[i][j] * pow(10,j));
			}
		}
	}
	else return false;
	if (aux[0] != aux[1] != aux[2] != aux[3] != aux[4] != aux[5] != aux [6]) 
		return true;
	else return false;
}

bool preenche(){
    int i,j;
	//achar uma posicao na qual um dos numeros (0 ou 1) infrinja a regra. Preencher matriz com numero oposto
	
	//tenta achar posicao na qual 1 seja invalido. Se achar, preenche com 0
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 if (!numValido(i,j,1) && (mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
				mat[i][j] = 0;
				return true;
			 }
		}
	}
	
	//tenta achar posicao na qual 0 seja invalido. Se achar, preenche com 1
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 if (!numValido(i,j,0) && (mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
				mat[i][j] = 1;
				return true;
			 }
		}
	}
	return false; //se retornar falso, nao 'e possivel realizar uma jogada
}

void imprime(){
 int i,j;
	for (i=0; i<tam; i++) {
		for (j=0; j<tam; j++) {
			printf("%d \t", mat[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------------------------\n\n");
}

bool validaMatriz(){
	if (validaAdjacencias() && validaLinhasColunas() && valida0ou1() && validaIguais()) 
		return true;
	else return false;
}

void montaMatriz(){
	int aux=0;
	aux = 0;
	while (aux != qtdVazia+1) {
		mat[binX[aux]][binY[aux]] = binario[aux];
		aux++;
		printf("mudei \n");
	}
	//imprime();
	
}

bool somaBinario(){
	//se tiver um 0, troca pra um 1
		int p=0;
		binPosicao = qtdVazia;
		p=qtdVazia;
		if (fim!=1) {
		/*while (p!=0)
		{
				if (binario[p]==1){
					p--;
					
				}else break; //se achou um 0, break pq ainda tem numero p somar
		}
		if (p==0) {
		fim=1;
		return false;
		}*/
		
		while(true){
			while((binario[binPosicao] == 1) && (binPosicao>=0)){
				binario[binPosicao] = 0;
				binPosicao--;
			}
			if (binario[binPosicao] == 0 )  {
				binario[binPosicao] = 1;
				return true;
			}
			fim = 1;
			return false; //cheguei em todos igual a 1
		}
		}
}
	
	
void preencheforcaBruta(){
	int i,j;
	
	qtdVazia=0;
	
	for (i=0;i<6;i++){
			for (j=0;j<6;j++){
				 if ((mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
					binX[qtdVazia]= i;
					binY[qtdVazia]= j;
					qtdVazia++;
					printf("QTDVAZIA %d\n", qtdVazia);
				 }
				 
			}
			
	}
	qtdVazia--;
	printf("QTDVAZIA %d\n", qtdVazia);
	//montaMatriz();
	//validaMatriz();
	int p=0;
	
	do{	
		montaMatriz();
		if (validaMatriz()) 
			printf("ACHEI!\n"); 
		else {
				printf("%d %d %d\n", qtdVazia, binX[0], binY[0]);
				printf("%d %d %d\n", qtdVazia, binX[1], binY[1]);
				for(p=0;p<=qtdVazia;p++){
					printf("binario: %d \n", binario[p]);
				}
				getchar();
				printf("nao ");
		}
		somaBinario();
	}while(fim==0);
	
	
}


	
//------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	
	int i,j,x,y,num;
	
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
    	//Leitura da Matriz[6,6] comecando de 0,0
        for (i=0; i<tam; i++) {
			for (j=0; j<tam; j++) {
        		fscanf(file,"%d\t",&mat[i][j]);
        	}
        }
    }
	

	
	
	//--------------------------------PARTE2
	/*
	if (validaMatriz()) 
		printf("Matriz valido\n");
	else printf("Matriz Invalida\n");
	*/
	
	
	//-------------------------------PARTE 3
	//OBS: a funcao de verificaLinhasColunas e verificaIguais so fazem sentido se a matriz estiver completamente preenchida
	//se ela estiver incompleta, pode ser sim que uma linha incompleta seja igual aos valores de outra linha incompleta
	//por isso, para testar insercao de numeros em tabuleiro, eu somente testo se ele 'e valido pelos numeros que fazem fronteira com ele
	//caso a matriz esteja completamente preenchida, pode ser testada com a funcao verificaMatriz();
	/*
	printf("Posicao X,Y na qual deseja inserir um numero  (o ou 1) \n");
	printf("\nDigite a posicao x: ");
	scanf("%d", &x); 
	printf("\nDigite a posicao y: ");
	scanf("%d", &y);
	printf("\nNumero que deseja inserir: ");
	scanf("%d", &num);     
	if (numValido(x-1,y-1,num))  //diminuindo 1 pra poder corresponder a posicao que comeca em 0,0
		printf("\nNumero valido\n");
	else printf("\nInvalido\n");
	*/
	//--------------------------------------
	//PARTE 5
	imprime();
	/*
	while (preenche()) {
		preenche();
	}*/
	preencheforcaBruta();
	imprime();
	int p;
	for(p=0;p<=qtdVazia;p++){
				printf("binario: %d \n", binario[p]);
		}
	
	
	
}
