/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "racional.h"
 
 #define MAXN 100 // número maximo de elementos no vetor
 
 /* coloque aqui as funções auxiliares que precisar neste arquivo */
 void imprime_vetor(struct racional *v[], int n);
 int  remove_invalidos(struct racional *v[], int n);
 void ordena_racionais(struct racional *v[], int n);
 struct racional *soma_vetor(struct racional *v[], int n);
 
 int main() {
     
    // le n
    int n;
     if (scanf("%d", &n) != 1 || n <= 0 || n >= MAXN) {
         fprintf(stderr, "Entrada invalida\n");
         return 1;
     }
     
     // aloca vetor
     struct racional **vetor = malloc(n * sizeof *vetor);
     if (!vetor) {
         fprintf(stderr, "Sem memoria\n"); // falha na alocacao
         return 1;
     }
     
     // le num e den e cria os racionais
     for (int i = 0; i < n; i++) {
         long num, den;
         scanf("%ld %ld", &num, &den);
         vetor[i] = cria_r(num, den); // aloca inicializa o racional
     }
     
     // impressao do vetor original
     printf("VETOR = "); imprime_vetor(vetor, n);
     
     // remove de elementos inválidos e reimpressao
     n = remove_invalidos(vetor, n);
     printf("VETOR = "); imprime_vetor(vetor, n);
     
     // ordenacao e reimpressao
     ordena_racionais(vetor, n);
     printf("VETOR = "); imprime_vetor(vetor, n);
     
     // calculo da soma de todos os racionais
     struct racional *total = soma_vetor(vetor, n);
     if (!total) {
         fprintf(stderr, "Erro na soma\n");
         // libera a memoria alocada antes de sair
         for (int i = 0; i < n; i++) destroi_r(vetor[i]);
         free(vetor);
         return 1;
     }
     
     // print do resultado da soma
     printf("SOMA = "); imprime_r(total); printf("\n");
     
     // liberacao dos racionais do vetor
     for (int i = 0; i < n; i++) {
         destroi_r(vetor[i]);
         vetor[i] = NULL; // invalida o ponteiro apos free
     }
     printf("VETOR = "); imprime_vetor(vetor, n);
     
     // liberacao do vetor de ponteiros
     free(vetor);

     // liberacao do racional da soma
     destroi_r(total);

     return 0;
 }

 // imprime os primeiros n elementos do vetor 
 void imprime_vetor(struct racional *v[], int n) {
     for (int i = 0; i < n; i++) {
         imprime_r(v[i]);
         if (i + 1 < n) putchar(' ');
     }
     putchar('\n');
 }
 
 int remove_invalidos(struct racional *v[], int n) {
    int i = 0, j = n - 1;
    // particiona: validos no inicio, invalidos no fim
    while (i <= j) {
        if (valido_r(v[i])) {
            i++;
        } else {
            destroi_r(v[i]);          // libera invalido
            v[i] = v[j];              // traz ponteiro do fim para i
            v[j] = NULL;
            j--;                      // reduz extremidade
        }
    }
    return i;  // novo tamanho (indice do primeiro invalido)
}

 // ordena o vetor de ponteiros para racionais usando insertion sort e a função compara_r
 void ordena_racionais(struct racional *v[], int n) {
     for (int i = 1; i < n; i++) {
         struct racional *key = v[i];
         int j = i - 1;
         while (j >= 0 && compara_r(v[j], key) > 0) {
             v[j + 1] = v[j];
             j--;
         }
         v[j + 1] = key;
     }
 }
 
 // soma todos os racionais do vetor, iniciando o acumulador em 0/1,retorna um ponteiro para o resultado ou NULL em caso de erro.
 struct racional *soma_vetor(struct racional *v[], int n) {
     struct racional *sum = cria_r(0, 1); // elemento neutro da soma
     if (!sum) return NULL;
     for (int i = 0; i < n; i++) {
         if (!soma_r(sum, v[i], sum)) {
             destroi_r(sum);
             return NULL;
         }
     }
     return sum;
 }