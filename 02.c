#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Elemento {
  int prioridade[MAX_SIZE];
  int dado[MAX_SIZE];
  struct Elemento *prox;
} Elemento;

typedef struct Fila {
  Elemento *inicio;
  Elemento *fim;
} Fila;

Fila *criaFila() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  if (fila != NULL) {
    fila->fim = NULL;
    fila->inicio = NULL;
  }
  return fila;
}

bool filacheia(Fila *fila) {
  return (fila->fim == MAX_SIZE - 1); // menos 1 pq ainda tem o /0
}

void inserefilacomprioridade(Fila *fila, int info, int prioridaden) {
  if (filacheia(fila)) // para saber se pode ou n inserir na fila de prioridade
  {
    printf("A fila esta cheiaa!!\n");
    return;
  }

  Elemento *novo = (Elemento *)malloc(
      sizeof(Elemento)); // aloca um espaço para um novo elemento
  if (novo == NULL)      // para saber se o espaço foi alocado
  {
    printf("Erro em alocar a memória!!\n");
    return;
  }
  int i = fila->fim; // apontando para o final porque é uma fila com prioridade
  while (
      i >= 0 &&
      prioridaden <
          novo->prioridade[i]) // i >= 0 porque se fosse igual a 0 não dava para
                               // inserir, visto que é uma fila com prioridade
  {
    novo->dado[i + 1] = novo->dado[i];
    novo->prioridade[i + 1] = novo->prioridade[i];
    i--; // diminuir pq o i aponta para o fim no começo no loop
  }
  novo->dado[i + 1] = info;
  novo->prioridade[i + 1] = prioridaden;

  fila->fim++;
}

bool filaVazia(Fila *fila) {
  if (fila->inicio == NULL) {
    return true;
  } else {
    return false;
  }
}

void removeFilacomprioridade(Fila *fila, int info) {
  if (filaVazia(fila)) {
    printf("Fila vazia!\n");
    return;
  }

  Elemento *auxi = fila->fim;
  Elemento *anterior = NULL;
  // para encontrar o elemento desejado
  while (auxi != NULL && *(auxi->dado) != info) {
    anterior = auxi;
    auxi = auxi->prox;
  }

  if (auxi == NULL) {
    printf("Elemento nao encontrado na fila!\n");
    return;
  }

  if (anterior == NULL) // quando o elemento é o primeiro da fila
  {
    fila->inicio = auxi->prox;
  } else // quando o elemento a ser removido esta no final ou no meio da fila
  {
    anterior->prox = auxi->prox;
  }

  free(auxi);
}
void imprimefila(Fila *fila) {
  if (filaVazia(fila)) {
    printf("Fila Vazia!\n");
    return;
  }
  Elemento *auxi = fila->inicio;
  while (auxi != NULL) {
    printf("dado: %d\n", *(auxi->dado));
    printf("prioridade: %d\n", *(auxi->prioridade));
    auxi = auxi->prox;
  }
}
int main() {
  Fila *fila = criaFila();

  int opcao, num, prio, numero;

  while (1) {
    printf("----- MENU DE OPCOES -----\n");
    printf("[1] insere\n");
    printf("[2] remove\n");
    printf("[3] imprime\n");
    printf("[4] sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o numero que quer inserir:\n");
      scanf("%d", &num);
      printf("Digite a prioridade que quer [1-10]:\n");
      scanf("%d", &prio);
      inserefilacomprioridade(fila, num, prio);
      break;
    case 2:
      imprimefila(fila);
      printf("Digite o numero que quer remover:\n");
      scanf("%d", &numero);
      removeFilacomprioridade(fila, numero);
      break;

    case 3:
      imprimefila(fila);
      break;
    default:
      printf("Saindo do programa...");
      break;
    }
  }
}