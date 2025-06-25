/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>      
#include "racional.h"   

#define MAXN 100

/* coloque aqui as funções auxiliares que precisar neste arquivo */
void imprime_vetor(struct racional v[], int n);
int remove_invalidos(struct racional v[], int n);
void ordena_racionais(struct racional v[], int n);
int soma_vetor(struct racional v[], int n, struct racional *resultado);

/* programa principal */
int main() {
  struct racional vetor[MAXN];
  int n;

  /* leia n (0 < n < 100) */
  if (scanf("%d", &n) != 1 || n <= 0 || n >= MAXN) {
      fprintf(stderr, "Entrada invalida\n");
      return 1;
  }

  /* leia n racionais (num den) no vetor */
  for (int i = 0; i < n; i++) {
      long num, den;
      scanf("%ld %ld", &num, &den);
      vetor[i] = cria_r(num, den);
  }

  /* imprime vetor lido */
  printf("VETOR = ");
  imprime_vetor(vetor, n);

  /* remove inválidos e imprime */
  n = remove_invalidos(vetor, n);
  printf("VETOR = ");
  imprime_vetor(vetor, n);

  /* ordena e imprime */
  ordena_racionais(vetor, n);
  printf("VETOR = ");
  imprime_vetor(vetor, n);

  /* soma todos e imprime */
  struct racional total;
  if (!soma_vetor(vetor, n, &total)) {
      fprintf(stderr, "Erro na soma\n");
      return 1;
  }
  printf("SOMA = ");
  imprime_r(total);
  printf("\n");

  return 0;
}


/* imprime v[0..n-1] separados por espaco e muda de linha */
void imprime_vetor(struct racional v[], int n) {
  for (int i = 0; i < n; i++) {
      imprime_r(v[i]);
      if (i + 1 < n) putchar(' ');
  }
  putchar('\n');
}

/* remove de v todos os racionais invalidos, retorna o novo tamanho */
int remove_invalidos(struct racional v[], int n) {
  int j = 0;
  for (int i = 0; i < n; i++) {
      if (valido_r(v[i])) {
          v[j++] = v[i];
      }
  }
  return j;
}

/* ordena v[0..n-1] usando compara_r */
void ordena_racionais(struct racional v[], int n) {
  for (int i = 1; i < n; i++) {
      struct racional key = v[i];
      int j = i - 1;
      // insira v[i] na posição correta em v[0..i-1]
      while (j >= 0 && compara_r(v[j], key) == 1) {
          v[j + 1] = v[j];
          j--;
      }
      v[j + 1] = key;
  }
}

/* soma todos os v[0..n-1] em *resultado. retorna 1 se ok, 0 se erro */
int soma_vetor(struct racional v[], int n, struct racional *resultado) {
  if (resultado == NULL) return 0;
  // começa em zero
  *resultado = cria_r(0, 1);
  for (int i = 0; i < n; i++) {
      struct racional temp;
      if (!soma_r(*resultado, v[i], &temp))
          return 0;
      *resultado = temp;
  }
  return 1;
}
