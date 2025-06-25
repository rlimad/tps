/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>  
#include "racional.h"
#include <time.h>


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  // inverte caso min > max
  if (min > max) {
    long tmp = min;
    min = max;
    max = tmp;
  }
  
  // gera o número aleatório
  return (rand() % (max - min + 1)) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
  // valores absolutos para que o MDC seja positivo.
  a = labs(a);
  b = labs(b);

  // caso base: se b é zero, o MDC é a.
  if (b == 0)
      return a;
  // chamada recursiva: MDC de (b, a % b)
  return mdc(b, a % b);

}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  if (a == 0 || b == 0)
  return 0;

  //  produto absoluto de a e b / MDC.
  return labs(a * b) / mdc(a, b);

}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  // verifica se o racional eh valido
  if (r.den == 0) {
    return r;
  }

  long divisor_comum = mdc(labs(r.num), labs(r.den));

  // simplifica o racional
  r.num /= divisor_comum;
  r.den /= divisor_comum;

  // se o denominador ficar negativo, transfere o sinal para o numerador
  if (r.den < 0) {
      r.num = -r.num;
      r.den = -r.den;
  }

  // representação de zero como 0/1
  if (r.num == 0) {
      r.den = 1;
  }

  return r;
  
}

struct racional cria_r (long numerador, long denominador) {
  
  struct racional r;
  r.num = numerador;
  r.den = denominador;

  return r;
}

int valido_r (struct racional r) {
  
  if (r.den == 0) {
    return 0;
  }
  return 1;

}

struct racional sorteia_r (long min, long max) {
  
  struct racional r;
  long numerador = aleat(min, max);
  long denominador = aleat(min, max);

  r = cria_r(numerador, denominador);

  return r;
}

void imprime_r (struct racional r) {
  
  if (valido_r(r) == 0) {
    printf("INVALIDO");
  } else {
    r = simplifica_r(r);
    if (r.num == 0) {
      printf("0");
    } else if (r.den == 1) {
      printf("%ld", r.num);
    } else if (r.num == r.den) {
      printf("1");
    } else if (r.den < 0) {
      printf("%ld/%ld", -r.num, -r.den);
    } else {
      printf("%ld/%ld", r.num, r.den);
    }
  }

}

struct racional soma_r (struct racional r1, struct racional r2) {

  struct racional r;
  long numerador, denominador;

  if (valido_r(r1) == 0 || valido_r(r2) == 0) {
    return cria_r(0, 0);
  }

  // simplifica os racionais
  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);

  // calcula o denominador
  denominador = mmc(r1.den, r2.den);

  // calcula o numerador
  numerador = (r1.num * (denominador / r1.den)) + (r2.num * (denominador / r2.den));

  r = cria_r(numerador, denominador);

  return r;
}

struct racional subtrai_r (struct racional r1, struct racional r2) {

  struct racional r;
  long numerador, denominador;

  if (valido_r(r1) == 0 || valido_r(r2) == 0) {
    return cria_r(0, 0);
  }

  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);

  denominador = mmc(r1.den, r2.den);

  numerador = (r1.num * (denominador / r1.den)) - (r2.num * (denominador / r2.den));

  r = cria_r(numerador, denominador);

  return r;
}

struct racional multiplica_r (struct racional r1, struct racional r2) {

  struct racional r;
  long numerador, denominador;

  if (valido_r(r1) == 0 || valido_r(r2) == 0) {
    return cria_r(0, 0);
  }

  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);

  numerador = r1.num * r2.num;
  denominador = r1.den * r2.den;

  r = cria_r(numerador, denominador);

  return r;
}

struct racional divide_r (struct racional r1, struct racional r2) {

  struct racional r;
  long numerador, denominador;

  if (valido_r(r1) == 0 || valido_r(r2) == 0) {
    return cria_r(0, 0);
  }

  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);

  // verifica se o denominador eh zero
  if (r2.num == 0) {
    return cria_r(0, 0);
  }

  numerador = r1.num * r2.den;
  denominador = r1.den * r2.num;

  r = cria_r(numerador, denominador);

  return r;
}

