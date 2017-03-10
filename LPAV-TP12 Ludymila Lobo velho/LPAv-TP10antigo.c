#include <stdio.h>
#include <stdlib.h>

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

void questao1()
{
	int x, y;
	printf("Insira o valor de x.\n");
	scanf("%d",&x);
	printf("Insira o valor de y.\n");
	scanf("%d",&y);
	printf("valor de x: %d\n",x);
	printf("valor de y: %d\n",y);

	if(iguais(x,y))
		printf("Os números são iguais.\n");
	else printf("Os números são diferentes.\n");
}

void questao2()
{
	int a; 
	printf("Insira um valor para retornar o simétrico.\n");
	scanf("%d",&a);
	printf("Valor simetrico: %d\n",simetrico(a));
}

void questao3()
{
	int x , y ;
	printf("Insira o valor de x.\n");
	scanf("%d",&x);
	printf("Insira o valor de y.\n");
	scanf("%d",&y);
	printf("valor de x: %d\n",x);
	printf("valor de y: %d\n",y);
	printf("valor da soma %d\n",soma(x,y));
}

void questao4()
{
	int x , y ;
	printf("Insira o valor de x.\n");
	scanf("%d",&x);
	printf("Insira o valor de y.\n");
	scanf("%d",&y);
	printf("valor de x: %d\n",x);
	printf("valor de y: %d\n",y);
	printf("valor da multiplicação %d\n",multiplica(x,y));	
}

void questao5()
{
	float n ;
	printf("Insira o valor de n.\n");
	scanf("%f",&n);
	printf("valor de n: %f\n",n);
	printf("valor do somatorio %f\n",somatorio(n));	
	//printf("valor do somatorio2 %f\n",somatorio2(n));	
}

void questao6()
{
	int n ;
	printf("Insira o valor de n.\n");
	scanf("%d",&n);
	printf("valor de n: %d\n",n);
	printf("valor da funcao %d\n",calcula_algo(n));	
}



int main()
{
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
		printf("* 6) Questao 6 - Retorna valor do numero n da sequencia\n");
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
			questao5();
		if(n == 6)
			questao6();

		printf("Questao executada\n");
		getchar();
		printf("Pressione qualquer tecla!\n");
		getchar();
	}
	
	return 0;
}
