# 🧪 Trabalhos Práticos – Programação 1

Repositório contendo os cinco TPs desenvolvidos ao longo da disciplina de **Programação 1**, ministrada no curso de Ciência da Computação da **UFPR – DINF**.

## 📦 Trabalhos inclusos

### TP1 – TAD Racional (básico)
Implementação de um TAD para números racionais (`a/b`), com operações aritméticas básicas, detecção de inválidos e uso de múltiplos arquivos fonte (`.c`/`.h`).

### TP2 – Racional com parâmetros por endereço
Extensão do TP1: as funções passam a receber parâmetros por referência, retornando códigos de erro. Entrada de dados via redirecionamento de arquivos.

### TP3 – Vetor de Ponteiros para Racionais
Manipulação de vetor de ponteiros para racionais:
- Leitura, remoção de inválidos
- Ordenação sem mover os dados (apenas ponteiros)
- Soma total dos elementos
- Liberação completa da memória

### TP4 – TAD Lista Encadeada
Implementação completa de um TAD `lista`:
- Lista duplamente ligada com sentinelas
- Inserção, remoção, busca
- Respeito ao uso de `valgrind`, boa organização modular e makefile

### TP5 – TAD Fila de Prioridades
Implementação de uma fila de prioridades genérica com:
- Inserção ordenada por prioridade crescente
- Estabilidade (FIFO entre prioridades iguais)
- Ponteiro `void*` para dados genéricos + tipo inteiro associado

Cada TP contém:
- Código fonte em C (`.c`, `.h`)
- Makefile para compilação
- Comentários/documentação inline

## 🛠️ Como usar

1. Clone o repositório:

```bash
git clone git@github.com:rlimad/tps.git
cd tps
```

2. Extraia o TP desejado:

```bash
cd tp3
make
./tp3
```

## 🎓 Objetivo

Desenvolver e aplicar TADs fundamentais em C, com foco em:

  - Listas ligadas
  - Filas e filas de prioridade
  - Conjuntos e operações de conjunto
  - Simulação baseada em eventos
