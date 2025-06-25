/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */
    
    long n, max;

    // le o valor de n (numero de iteracoes que o laco principal (o for) executa)
    printf("Digite o valor de n (1 <= n < 100): ");
    if (scanf("%ld", &n) != 1 || n <= 0 || n >= 100) {
        fprintf(stderr, "valor invalido.\n");
        return 1;
    }

    // le o valor de max
    printf("Digite o valor de max (0 < max < 30): ");
    if (scanf("%ld", &max) != 1 || max <= 0 || max >= 30) {
        fprintf(stderr, "valor invalido.\n");
        return 1;
    }

    for (long i = 1; i <= n; i++) {
        printf("%ld: ", i);

        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        printf(" ");

        if (!valido_r(r1) || !valido_r(r2)) {
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        struct racional soma = soma_r(r1, r2);
        struct racional subtracao = subtrai_r(r1, r2);
        struct racional multiplicacao = multiplica_r(r1, r2);
        struct racional divisao = divide_r(r1, r2);

        if (!valido_r(divisao)) {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        imprime_r(soma);
        printf(" ");
        imprime_r(subtracao);
        printf(" ");
        imprime_r(multiplicacao);
        printf(" ");
        imprime_r(divisao);
        printf("\n");
    }

    return 0;

}
