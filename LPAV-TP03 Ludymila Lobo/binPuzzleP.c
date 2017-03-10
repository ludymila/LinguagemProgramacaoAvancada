#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int mat[6][6]; 			//Matriz tem sempre tamanho 6,6
const int tam = 6;
int binario[36] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //36 é o numero maximo de casas
int binPosicao=36;
int binX[36], binY[36]; //salva a posicao X,Y (respectivamente) das casas vazias
int qtdVazia=0 ;			//conta quantas casas vazias tem na matriz de entrada (quantidade de -1)
bool fim=0;
//-------------------------------------------------------------------------------------------------------------------------------
bool numValido(int x, int y, int num){
	//contando numeros consecutivamente iguais ao redornumV
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

void procuraVazio(){
int i,j;
qtdVazia=0;
for (i=0;i<6;i++){
			for (j=0;j<6;j++){ 
				 if ((mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
					binX[qtdVazia]= i;
					binY[qtdVazia]= j;
					//printf("QTDVAZIA %d\n", qtdVazia);
					qtdVazia++;
					
				 }
				 
			}
			
	}
}

//monta a matriz trocando as posicoes vazias pelos numeros gerados na forcaBruta 
void montaMatriz(){
	int aux=0;
	aux = 0;
	while (aux < qtdVazia) {
		mat[binX[aux]][binY[aux]] = binario[aux];
		aux++;
	}
}

//Procura uma posicao na qual um dos numeros (0 ou 1) infrinja a regra. Preencher matriz com numero oposto ao que infringe
bool preenche(){
	//printf("oi\n");
    int i,j;
	//REGRA ADJACENCIA: tenta achar posicao na qual 1 seja invalido. Se achar, preenche com 0
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 if (!numValido(i,j,1) && (mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
				mat[i][j] = 0;
				return true;
			 }
		}
	}
	
	//REGRA ADJACENCIA: tenta achar posicao na qual 0 seja invalido. Se achar, preenche com 1
	for (i=0;i<6;i++){
		for (j=0;j<6;j++){
			 if (!numValido(i,j,0) && (mat[i][j] == -1)) { //se a posicao estiver ainda faltando preencher
				mat[i][j] = 1;
				return true;
			 }
		}
	}
	int p;
	/*for(p=0;p<qtdVazia;p++){
					printf("binario: %d \n", binario[p]);
				}*/
	//se chegar aqui, nao da pra usar mais nenhuma regra de adjacencia para preencher
	//REGRA DA QTD 0s e 1s POR LINHA E COLUNA
	int k,l,cont1=0,cont0=0;
	cont1=0; 
	cont0=0;
	
	procuraVazio(); 

	//confere na mesma linha da casa vazia
	if (qtdVazia>0) {
		for (j=0;j<6;j++){
			if (mat[binX[0]][j] == 0) cont0++; 
			if (mat[binX[0]][j] == 1) cont1++; 
		}
		if (cont0 ==3) {
			mat[binX[0]][binY[0]] = 1; //ja tem 3 0s em uma linha. se faltar um numero, vai ser 1
			//printf("contou0"); 
			//montaMatriz(); 
			
			return true;
		}     
		else if (cont1 ==3) {
			mat[binX[0]][binY[0]] = 0; //ja tem 3 1s em uma linha. se faltar um numero, vai ser 0
			//printf("contou1"); 
			//montaMatriz(); 
			
			return true;
		} 
		cont0=0; cont1 = 0;
		//confere na mesma coluna
		for (i=0;i<6;i++){
			if (mat[i][binY[0]] == 0) cont0++; 
			if (mat[i][binY[0]] == 1) cont1++; 
		}
		if (cont0 ==3) {
			mat[binX[0]][binY[0]] = 1;   //ja tem 3 0s em uma linha. se faltar um numero, vai ser 1
			//montaMatriz(); 
			//printf("contou0J\n"); 
			return true;
		}    
		else if (cont1 ==3) {
			mat[binX[0]][binY[0]] = 0;  //ja tem 3 1s em uma linha. se faltar um numero, vai ser 0
			//montaMatriz(); 
			//printf("contou1J\n"); 
			return true;
		} 
	}
	return false; //se retornar falso, nao 'e possivel realizar uma jogada
}

//imprime a matriz
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

//verifica se matriz completa esta de acordo com as 4 regras 
bool validaMatriz(){
	if (valida0ou1()){
		if (validaAdjacencias() && validaLinhasColunas() && validaIguais()) 
			return true;
	}
	return false;
}



//funcao para somar +1 em um numero binario
bool somaBinario(){
	int p=0;
	binPosicao = qtdVazia; //sempre comeca a somar da ultima posicao
	p=qtdVazia;
	//printf("soma\n");
	while(true){
		while((binario[binPosicao] == 1) && (binPosicao>0)){ //ao tentar somar, se tiver um 1, transforma em 0 e vai pra posicao anterior
			binario[binPosicao] = 0;
			binPosicao--;
		}
		
		if (binario[binPosicao] == 0 )  { 					 //ao tentar somar, se achar um 0, troca pra 1 e sai
			binario[binPosicao] = 1;
			return true;
		}
		fim = 1;
		return false; //chegou em todos igual a 1
	}
}


	
void preencheforcaBruta(){
	int i,j, p=0;
	
	
	procuraVazio();
		
	do{	
		montaMatriz();
		//@DEBUG: Retire o imprime() do comentario para ver a matriz sendo construida pelo metodo Forca Bruta
		//imprime();
		if (validaMatriz()) {
			printf("Metodo Forca Bruta: Matriz solucao encontrada!\n");
			break;
		}			
		else {
				//printf("%d %d %d\n", qtdVazia, binX[0], binY[0]);
				//printf("%d %d %d\n", qtdVazia, binX[1], binY[1]);
				
				somaBinario();
				for(p=0;p<qtdVazia;p++){
					//@DEBUG: Retire a linha abaixo de comentario para ver os numeros binarios sendo gerados para o metodo Forca Bruta
					//printf("Binario: %d \n", binario[p]);
				}
		}
		
	}while(!fim);
	if (fim) printf("Matriz input invalida! Impossivel encontrar solucao\n");
}


	
//------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	
	int i,j,x,y,num,escolha=0;
	
	//--------------------------------PARTE1
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
    	//Leitura da Matriz[6,6] comecando de 0,0
        for (i=0; i<tam; i++) {
			for (j=0; j<tam; j++) {
        		fscanf(file,"%d\t",&mat[i][j]);
        	}
        }
    }
	
	
	//--------------------------------PARTE2
	
	if (validaMatriz()) 
		printf("\nMatriz de entrada: VALIDA\n");
	else printf("\nMatriz de entrada: INVALIDA\n");
	imprime();
	while ((escolha!=3) && (escolha!=4) && (escolha!=5)){
		printf("3 - Testar se numero pode ser colocado na posicao X,Y (somente para matrizes de input validas) \n");
		printf("4 - Preenche a matriz com o metodo forca bruta\n");
		printf("5 - Preenche a matriz usando pre-processamento\n");
		printf("Deseja testar parte 3,4 ou 5?");
		scanf("%d", &escolha);
		printf("\n");
	}
	
//-------------------------------PARTE 3
//Verifica se insercao em X,Y 'e valida
	if (escolha==3){
		printf("Posicao X,Y na qual deseja inserir um numero \n");
		printf("\nDigite a posicao x: ");
		scanf("%d", &x); 
		printf("\nDigite a posicao y: ");
		scanf("%d", &y);
		printf("\nNumero que deseja inserir (0 ou 1): ");
		scanf("%d", &num);     
		if ((num==0) || (num==1)){
			qtdVazia = 1;
			binX[0] = x-1; binY[0] = y-1;
			binario[0] = num;
			montaMatriz();
			if (validaMatriz()) printf("\nApos inserir numero, matriz VALIDA\n"); else printf("\nApos inserir numero, matriz INVALIDA\n");
			
			
		} else printf("\nInvalido. Apenas 0 ou 1 sao entradas validas\n");
	}
	
//-------------------------------PARTE 4
// Preenchimento com Forca Bruta
	else if (escolha==4) {
		preencheforcaBruta();
		//if (validaMatriz()) printf("\n sim \n"); else printf("\n nao\n");
		imprime();
	}
//-------------------------------PARTE 5
// Preenchimento com Pre-Processamento
	else if (escolha==5){
		
		while (preenche()) {
			preenche();
		}
		imprime();
		if (validaMatriz()) printf("\n MAtriz Valida pelo metodo com pre-processamento \n"); else printf("\n Matriz invalida\n");
	}
	fflush(file);
	fclose(file);
	exit;
}
