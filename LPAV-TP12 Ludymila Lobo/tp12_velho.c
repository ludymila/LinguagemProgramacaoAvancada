#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int zero(int x)
{
	return (x==0); 
}
int zeroLong(long int x)
{
	return (x==0); 
}

int decr(int x)
{
	return (--x); 
}

long int decrLong(long int x)
{
	return (--x); 
}

int incr(int x)
{	
	return (++x);
}

long int incrLong(long int x)
{	
	return (++x);
}

int iguais(int x, int y)
{
	if(zero(x) == 1 && zero(y) == 1)
	{
		return 1; 
	} else 	
	if(( zero(x) == 1 && zero(y) == 0 )|| (zero(x) == 0 && zero(y) == 1))
	{
		return 0;
	}		
	else 
	{		
		return iguais(decr(x),decr(y));
	}
}

int simetrico(int x)
{
	if(zero(x))
	{
		return 0; 
	} else return decr(simetrico(decr(x)));
}

long int soma(int x, int y)
{			
	if(zero(x) == 1 && zero(y) == 0)
	{	
		return y;
		//return incr(soma(x,decr(y)));
	} 
	else if(zero(x) == 0 && zero(y) == 1)
	{	
		return x;	
		//return incr(soma(decr(x),y));
	}
	else if(zero(x) == 1 && zero(y) == 1)
	{		
		return 0; 
	} else 
		return incr(incr(soma(decr(x),decr(y))));
}

long int somaLong(long int x, long int y)
{			
	if(zeroLong(x) == 1 && zeroLong(y) == 0)
	{	
		return y;
		//return incr(soma(x,decr(y)));
	} 
	else if(zeroLong(x) == 0 && zeroLong(y) == 1)
	{	
		return x;	
		//return incr(soma(decr(x),y));
	}
	else if(zeroLong(x) == 1 && zeroLong(y) == 1)
	{		
		return 0; 
	} else 
		return incrLong(incrLong(somaLong(decrLong(x),decrLong(y))));
}

long int multiplica(int x, int y)
{
	if(zero(x))
		return 0;
	else return soma(multiplica(decr(x),y),y); 
}

long int multiplicaLong(long int x, long int y)
{
	if(zeroLong(x))
		return 0;
	else return somaLong(multiplicaLong(decrLong(x),y),y); 
}
float soma2(float x, float y)
{
	return x + y;
}

float somatorio(float n)
{
	//printf("valor de n %f\n",n);
	if(zero(n))
		return 0;
	else return soma2(somatorio(decr(n)),1/n);
}

float somatorio2(int n)
{
	float i = 1;
	float soma = 0;
	while(i<=n)
	{
		soma = soma + 1/i;
		printf("i %f\n",i);
		printf("soma %f\n",soma);
		i++;		
	}

	return soma;
}

long int calcula_algo(long int n)
{
	if(zeroLong(n))
		return 0;
	if( zeroLong(decrLong(n)) == 1)
		return 1;
	if( zeroLong(decrLong(decrLong(n))) == 1)
		return 2; 
	else return somaLong(  multiplicaLong(2,calcula_algo(decrLong(n))) , multiplicaLong(3,calcula_algo(decrLong(decrLong(n)))) ); 

}

int geraAleatorio(int max){ 
	
	return rand() % max+1; 
}
long int euclides(int a, int b){
	if (b ==0)
		return a;
	else return euclides(b, a % b);
}
void printPermutacao(int v[], const int size){
	int i;	
	if (v !=0) {
		for (i=0;i<size; i++){
			printf("%4d", v[i]);
		}
		printf("\n");
	}
}
int contUnico=0;
void printCombinacao(int v[], const int size, int repeticao){
	const int tam = repeticao;
	int i;
	const int tam2 = size;
	int combinacoes[tam];
	int aux[tam2];	
	int iguais;
	iguais=0;
	if (v !=0) {

		for (i=0;i<size; i++){
				if (v[i] == aux[i])
					iguais++;
		}

		//printf("\niguais %d, size:%d \n", iguais, size);
		for (i=0;i<size; i++){
			if (iguais!= size) {
				printf("%4d", v[i]);
				aux[i] = v[i];
			}
		}
	}

		//if (repetido(v[i]) ==0){			
		//		printf("%4d", v[i]);
		//		combinacoes[contUnico] = v[i];
		//}

		if (iguais!= size)  printf("\n");
	//}
}

void permutacao(int v[], const int start, const int n, int repeticao){
	int i;	
	if (start == n-1){
		if (repeticao==1) printPermutacao(v,n);
		else printCombinacao(v,n,repeticao);
	}
	else{
		for (i=start; i<n;i++) {
			int tmp = v[i];
			v[i]=v[start];
			v[start]=tmp;
			if (repeticao==1) permutacao(v,start+1,n,1);
				     else permutacao(v,start+1,n,repeticao);
			v[start] = v[i];
			v[i]=tmp;
		}
	}
}



void questao1()
{
	
	int i,x, y;
	int max = 1000;
	for (i=0;i<10;i++){
		x = geraAleatorio(max);
		y = geraAleatorio(max);
		printf("X: %d ",x);
		printf("Y: %d\n",y);

		if(iguais(x,y))
			printf("Iguais\n");
		else printf("Diferentes\n");
	}
}

void questao2()
{
	int i,max = 150,num;
	for (i=0;i<10;i++) {
		num=geraAleatorio(max);
		printf("Numero, Valor simetrico: %d , %d\n",num,simetrico(num));
	}
	
}

void questao3()
{
	int i,max = 100;	
	int x=0 , y=0 ; 
	x=0; y=0;
	for (i=0;i<15;i++){
		x=0; y=0;		
		while (x<=10) x = geraAleatorio(max); //entre 10 e 100
		while (y<=10) y = geraAleatorio(max);		
		printf("X: %d ",x);
		printf("Y: %d\n",y);
		printf("Soma: %ld\n",soma(x,y));
	}
}

void questao4()
{
	int i;
	int max = 40;	
	int x=0; int y=0;
	
	for (i=0;i<20;i++){
		x=0; y=0;
		while (x<=4) x = geraAleatorio(max); //entre 4 e 40
		while (y<=4) y = geraAleatorio(max);
		printf("X: %d ",x);
		printf("Y: %d\n",y);
		printf("Multiplicação: %ld\n",multiplica(x,y));	
	}
}

void questao5(int n)
{
	printf("N: %d\n",n);
	printf("Somatorio %f\n",somatorio(n));	
		
}
void questao6(int vet[], int tam){
	//int v[] = {1,2,3,4};
	int i;
	//printf("na 6\n");
	for (i=0;i<tam-2;i++) {
		//vet[i-1] = atoi(argv[i]);
		//printf("%d ", vet[i]);
	}
	//printf("tam %d %d\n", tam, sizeof(vet));
	//printf("na 6: %d %d %d %d",v[0], v[1], v[2], v[3]);
	printf("\nPermutacao:\n");
	permutacao(vet,0,(tam-2),1);
}
//placar
void questao7(int m, int n){
const int tam = m + n;
int i;
int vet[tam];
for (i=0;i<m;i++)
	vet[i]=0;
for (i=m;i<n+m;i++)
	vet[i]=1;
permutacao(vet,0,m+n,m*n);
}

void questao8(int n)
{
	
	printf("N: %d\n",n);
	printf("valor da funcao %ld\n",calcula_algo(n));	
}
void questao9(int m, int n){
	
	printf("Euclides (%d, %d):\n",m,n);
	printf("%ld\n", euclides(m,n));
}
void questao10(int k, int n)
{
	printf("X: %d ",k);
	printf("Y: %d\n",n);
	printf("Multiplicação: %ld\n",multiplica(k,n));		
}


int main(int argc, char **argv)
{
	srand(time(NULL));	
	int n = 0;
	
		

			
		if(atoi(argv[1]) == 1)
			questao1();
		if(atoi(argv[1]) == 2)
			questao2();
		if(atoi(argv[1]) == 3)
			questao3();
		if(atoi(argv[1]) == 4)
			questao4();
		if(atoi(argv[1])  == 5){
			if(argc == 3) 
				questao5(atoi(argv[2]));			
			else {
				printf("* Para a questao 5, execute o arquivo com 3 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <valor_n>\n");	
				exit(1);
			}
		}
		if(atoi(argv[1]) == 6){
			if(argc >= 3) 
			{
				const int tam = argc; int i;
				int vet[tam];
				for (i=1;i<argc-1;i++) {
					vet[i-1] = atoi(argv[i+1]);
					//printf("%d ", vet[i-1]);
				}  
			
					questao6(vet, argc);
			}			
			else {
				printf("* Para a questao 6, execute o arquivo com pelo menos 3 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <caracter>\n");
				printf("* Sao aceitos um ou mais caracteres\n");	
				exit(1);
			}
		}
		if(atoi(argv[1]) == 7){
			if(argc == 4) 
				questao7(atoi(argv[2]),atoi(argv[3]));			
			else {
				printf("* Para a questao 7, execute o arquivo com 4 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <valor_M> <valor_N>\n");	
				exit(1);
			}
		}
		if(atoi(argv[1]) == 8){
			if(argc == 3) 
				questao8(atoi(argv[2]));			
			else {
				printf("* Para a questao 8, execute o arquivo com 3 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <valor_n>\n");	
				exit(1);
			}
		}
		if(atoi(argv[1]) == 9){
			if(argc == 4) 
				questao9(atoi(argv[2]),atoi(argv[3]));			
			else {
				printf("* Para a questao 9, execute o arquivo com 4 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <valor_M> <valor_N>\n");	
				exit(1);
			}
		}
		if(atoi(argv[1]) == 10){
			if(argc == 4) 
				questao10(atoi(argv[2]),atoi(argv[3]));			
			else {
				printf("* Execute o arquivo com 4 argumentos:\n"); 	
				printf("* ./<arquivo-executavel> <numero_questao> <valor_K> <valor_N>\n");	
				exit(1);
			}
		}

		

	
	/*else
		{
			printf("* Execute o arquivo com 2 ou 3 argumentos:\n"); 	
			printf("* ./<arquivo-executavel> <numero_questao> <param_extra_se_houver>\n");	
		}*/
	
	return 0;
}
