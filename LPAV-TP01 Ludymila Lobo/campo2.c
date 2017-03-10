#include <stdio.h>
#include <stdlib.h>


main(){
	char mat[20][20];
	int cont[20][20];
	int n,m,i,j, aux1,aux2, clickX,clickY;
	//./prog1 < input.txt
	
	//Leitura do tamanho da Matriz[n,m]
	scanf("%d", &n); 
	scanf("%d", &m);
	
	//Leitura da Matriz[n,y]
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			
			scanf("\n %c", &mat[i][j]);
			//getchar();
		}
	}
	i=0; j=0;
		

	scanf("%d", &clickX);
	scanf("%d", &clickY);

	if (mat[clickX-1][clickY-1] == '*') 
		printf("EXPLOSAO\n");
	else printf("%c\n", mat[clickX-1][clickY-1]);
}