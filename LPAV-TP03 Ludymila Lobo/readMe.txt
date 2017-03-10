Para compilar:
gcc binPuzzle.c -o binPuzzle
binPuzzle matrizValida.txt

Testes
MatrizValida: ja esta completa, apenas para testar a funcao de validacao
MatrizInvalida: tem valores ja invalidos, nao 'e possivel preencher com os metodos 4 e 5, e q ualquer numero inserido na opcao 3 retorna invalido (pq a mtriz ja esta invalida)

Os arquivos abaixo tem algumas posicoes contendo "-1", que representam espacos vazios.
Ao usar a opcao 3, sera retornado que a matriz esta invalida (por que a matriz tem varios -1. Portanto, so 'e possivel testar a opcao 3 quando a matriz de input 'e valida ou tem apenas uma casa faltando completar e a tentativa de insercao 'e feita nessa casa)
As opcoes 4 e 5 retornam a matriz completa seguindo as regras do jogo puzzle binario, com os metodos forca bruta e refinado, respectivamente.
-MatrizIncompleta
-MatrizIncompleta2
-MatrizIncompleta3

Para visualizar o metodo Forca Bruta sendo construido, tire de comentario as linhas:
271 e 283
(ou procure pelo comentario contendo "@DEBUG")
Foi colocado em comentario para agilizar o processamento da Forca Bruta.

