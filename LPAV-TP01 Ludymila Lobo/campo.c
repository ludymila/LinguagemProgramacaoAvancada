#include <stdio.h>
#include <stdlib.h>
int valido(int aux1,int aux2, int n, int m){
	if ((aux1>=0 && aux1<n) && (aux2>=0 && aux2<m)) return 1;
	else return 0;
}
main(){
	char mat[20][20];
	int cont[20][20];
	int n,m,i,j, aux1,aux2, clickX,clickY;
	
	//Leitura do tamanho da Matriz[n,m]
	scanf("%d", &n); 
	scanf("%d\n", &m);
	
	
	//Leitura da Matriz[n,y]
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			scanf("%c\n", &mat[i][j]);
		}
	}
fflush(stdin);

	scanf("%d", &clickX);
	scanf("%d", &clickY);
	i=0; j=0;

	/*for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}*/


	//loop para percorrer todos os nos da matriz
		for (i=0; i<n; i++) {
			for (j=0; j<m; j++) {
				cont[i][j]=0;
				//loop para Contagem de bombas adjacentes
				for (aux1= i-1; aux1<=i+1 ; aux1++){
					for (aux2= j-1; aux2<=j+1 ; aux2++){
						if (mat[i][j] != '*'){
							if (valido(aux1,aux2,n,m) && (!((aux1==i) && (aux2==j))))  { //
								if (mat[aux1][aux2] == '*') {
									cont[i][j]++;
								}
							}
						} else cont[i][j]=-1;
					}
				}
			}
		}

printf("%d ", n); 
printf("%d\n", m);

for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			if (cont[i][j]!= -1) printf("%d", cont[i][j]);
			else printf("*");
		}
		printf("\n");
	}

printf("%d ", clickX);
printf("%d\n", clickY);

}
