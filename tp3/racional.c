/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>     
#include "racional.h"   

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b) {

  // valores absolutos para que o MDC seja positivo.
  a = labs(a);
  b = labs(b);

  // caso base: se b é zero, o MDC é a.
  if (b == 0)
      return a;
  // chamada recursiva: MDC de (b, a % b)
  return mdc(b, a % b);

}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b) {
  
  if (a == 0 || b == 0)
  return 0;

  //  produto absoluto de a e b / MDC.
  return labs(a * b) / mdc(a, b);

}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r) {
  
  // verifica ponteiro e validade
  if (r == NULL || r->den == 0) {
      return 0;
  }

  long num = r->num;
  long den = r->den;

  // mdc
  long d = mdc(labs(num), labs(den));

  // simplifica
  num /= d;
  den /= d;

  // ajusta sinal 
  if (den < 0) {
      num = -num;
      den = -den;
  }

  // se numerador for zero, denominador = 1
  if (num == 0) {
      den = 1;
  }

  // atualiza o struct
  r->num = num;
  r->den = den;

  return 1;

}

struct racional *cria_r (long numerador, long denominador) {
  
  //aloca a struct 
  struct racional *r = malloc(sizeof *r);
  if(!r) return NULL; // sem memoria 

  r->num = numerador;
  r->den = denominador;

  return r;

}

void destroi_r (struct racional *r) {
  
  if(r) {
    free(r);
  }

}

int valido_r (struct racional *r) {

  if (r == NULL) {
    return 0;
  }

  long den = r->den;

  if(den == 0) {
    return 0;
  }

  return 1;

}

void imprime_r(struct racional *r) {
  if (r == NULL) {
      // caso ponteiro nulo
      printf("NULL");
      return;
  }
  if (!valido_r(r)) {
      // caso racional inválido
      printf("NaN");
      return;
  }

  // simplifica antes de imprimir
  simplifica_r(r);

  long num = r->num;
  long den = r->den;

  if (num == 0) {
      printf("0");
  } 

  else if (den == 1) {
      printf("%ld", num);
  } 

  else if (num == den) {
      printf("1");
  } 

  else if (den < 0) {
      // sinal migrado pelo simplifica, mas só para garantir:
      printf("%ld/%ld", -num, -den);
  } 
  
  else {
      printf("%ld/%ld", num, den);
  }

}

int compara_r (struct racional *r1, struct racional *r2) {
  
  // racionais invalidos?
  if (!valido_r(r1) || !valido_r(r2)) {
    return -2;
  }

  // simplifica antes de comparar 
  simplifica_r(r1);
  simplifica_r(r2);

  // multiplicacao cruzada para comparar sem ponto flutuante:
  //    r1 < r2  <=>  r1.num/r1.den < r2.num/r2.den
  //    <=>  r1.num * r2.den < r2.num * r1.den
  long esquerda  = r1->num * r2->den;
  long direita = r2->num * r1->den;

  if (esquerda < direita)  return -1;
  if (esquerda > direita)  return +1;
  return 0;  // esquerda == direita

}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3) {

  // verifica os ponteiros 
  if (!r1 || !r2 || !r3) return 0;
  // verifica os operandos
  if (!valido_r(r1) || !valido_r(r2)) return 0;

  // simplifica operandos 
  simplifica_r(r1);
  simplifica_r(r2);

  //calcula numerador e denominador
  long den = mmc(r1->den, r2->den);
  long num = r1->num * (den / r1->den)
           + r2->num * (den / r2->den);

  //armazena no struct apontado por r3
  r3->num = num;
  r3->den = den;

  // simplifica o resultado e retorna
  return simplifica_r(r3);

}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3) {
   
  if (!r1 || !r2 || !r3) return 0;

  if (!valido_r(r1) || !valido_r(r2)) return 0;
 
  simplifica_r(r1);
  simplifica_r(r2);

  long den = mmc(r1->den, r2->den);
  long num = r1->num * (den / r1->den)
           - r2->num * (den / r2->den);

  r3->num = num;
  r3->den = den;

  return simplifica_r(r3);

}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3) {

  if (!r1 || !r2 || !r3) return 0;

  if (!valido_r(r1) || !valido_r(r2)) return 0;

  simplifica_r(r1);
  simplifica_r(r2);

  long num = r1->num * r2->num;
  long den = r1->den * r2->den;

  r3->num = num;
  r3->den = den;

  return simplifica_r(r3);

}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3) {
  
  if (!r1 || !r2 || !r3) return 0;

  if (!valido_r(r1) || !valido_r(r2)) return 0;

  // verifica divisao por 0 
  if (r2->num == 0) {
    return 0;
  }

  simplifica_r(r1);
  simplifica_r(r2);

  long num = r1-> num * r2->den;
  long den = r1->den * r2->num;

  r3->num = num;
  r3->den = den;

  return simplifica_r(r3);

}
