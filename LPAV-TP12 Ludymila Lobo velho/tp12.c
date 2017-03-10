#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int zero(int x)
{
	return (x==0); 
}

int decr(int x)
{
	return (--x); 
}

int incr(int x)
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

int soma(int x, int y)
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

int multiplica(int x, int y)
{
	if(zero(x))
		return 0;
	else return soma(multiplica(decr(x),y),y); 
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

int calcula_algo(int n)
{
	if(zero(n))
		return 0;
	if( zero(decr(n)) == 1)
		return 1;
	if( zero(decr(decr(n))) == 1)
		return 2; 
	else return soma(  multiplica(2,calcula_algo(decr(n))) , multiplica(3,calcula_algo(decr(decr(n)))) ); 

}

int geraAleatorio(int max){ 
	
	return rand() % max+1; 
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
	int i,max = 150;
	for (i=0;i<10;i++)
		printf("Valor simetrico: %d\n",simetrico(geraAleatorio(max)));
	
}

void questao3()
{
	int i,max = 100;	
	int x=0 , y=0 ;
	for (i=0;i<15;i++){
		while (x<=10) x = geraAleatorio(max); //entre 10 e 100
		while (y<=10) y = geraAleatorio(max);
		printf("X: %d ",x);
		printf("Y: %d\n",y);
		printf("Soma: %d\n",soma(x,y));
	}
}

void questao4()
{
	int i;
	int max = 40;	
	int x=0; int y=0;
	
	for (i=0;i<20;i++){
		while (x<=4) x = geraAleatorio(max); //entre 4 e 40
		while (y<=4) y = geraAleatorio(max);
		printf("X: %d ",x);
		printf("Y: %d\n",y);
		printf("Multiplicação: %d\n",multiplica(x,y));	
	}
}

void questao5(int n)
{

	//n = atoi(argv[1]);
	printf("N: %d\n",n);
	printf("Somatorio %f\n",somatorio(n));	
		
}
void questao6(){
}
void questao7(){
}

void questao8(int n)
{
	
	printf("N: %d\n",n);
	printf("valor da funcao %d\n",calcula_algo(n));	
}
void questao9(){
}
void questao10(){
}


int main(int argc, char **argv)
{
	srand(time(NULL));	
	int n = 0;
	while(1!=0)
	{
		printf("* Insira um número para selecionar uma das questões para ser executadas!\n");
		printf("* 0) Para sair\n");
		printf("* 1) Questao 1 - Verifica igual\n");
		printf("* 2) Questao 2 - Retorna simetrico\n");
		printf("* 3) Questao 3 - Retorna soma\n");
		printf("* 4) Questao 4 - Retorna multiplicacao\n");
		printf("* 5) Questao 5 - Retorna valor do somatorio\n");
		printf("* 6) Questao 6 - \n");
		printf("* 7) Questao 7 - \n");
		printf("* 8) Questao 8 - Retorna valor do numero n da sequencia\n");
		printf("* 9) Questao 9 - \n");
		printf("*10) Questao 10 -\n");
		scanf("%d",&n);
		if(n == 0)
			break;
		if(n == 1)
			questao1();
		if(n == 2)
			questao2();
		if(n == 3)
			questao3();
		if(n == 4)
			questao4();
		if(n == 5)
			questao5(atoi(argv[1]));
		if(n == 6)
			questao6();
		if(n == 7)
			questao7();
		if(n == 8)
			questao8(atoi(argv[1]));
		if(n == 9)
			questao9();
		if(n == 10)
			questao10();

		printf("Saindo..\n");
		getchar();

	}
	
	return 0;
}
