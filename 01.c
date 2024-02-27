#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Elemento{
    int prioridade;
    int dado;
    struct Elemento *prox;
}Elemento;

typedef struct Fila{
    Elemento *inicio;
    Elemento *fim;
}Fila;


Fila *criaFila(){
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    if (fila != NULL)
    {
        fila->fim = NULL;
        fila->inicio = NULL;
    }
    return fila;
}

void insereFilaPrioridade(Fila *fila,int idade, int prioridaden){
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    if (novo != NULL)// conseguiu alocar bem a memória
    {
        novo->dado = idade;
        novo->prioridade = prioridaden;
        novo->prox = NULL;

        if (fila->inicio == NULL)// ainda n tem nenhum dado na fila
        {
            fila->inicio = novo;
            fila->fim = novo;
        }else
        {
            Elemento *anterior = NULL;
            Elemento *auxi = fila->inicio;
            while (auxi != NULL && prioridaden >= auxi->prioridade)
            {
               anterior = auxi;
               auxi = auxi->prox; 
            }

            if (anterior == NULL)
            {
                novo->prox = fila->inicio;
                fila->inicio = novo;
            }else
            {
                anterior->prox = novo;
                novo->prox = auxi;

                if (auxi == NULL)
                {
                    fila->fim = novo;
                }
                
            }
              
        }

    }else
    {
        printf("Erro em alocar memória!");
    }
    
}
void removeFila(Fila *fila, int dadon){
    if (fila != NULL)
    {
        Elemento *auxi = fila->inicio;
        Elemento *anterior = NULL;
        while (auxi != NULL)
        {
            if (auxi->dado == dadon)
            {
               if (anterior == NULL)
               {
                fila->inicio = auxi->prox;
               }else
               {
                anterior->prox = auxi->prox;
               }
               
               if (auxi == fila->fim)
               {
                fila->fim = anterior;
               }
                free(auxi);
                return;
            }
               anterior =  auxi;
               auxi = auxi->prox;
            
        }
        printf("Elemento com idade %d não encontrado na fila!\n",dadon);
    }
    
}

void alterarprioridade(Fila *fila, int dadon, int novaPrioridade){
    Elemento *auxi = fila->inicio;
    while (auxi != NULL)
    {
        if (auxi->dado == dadon)
        {
            auxi->prioridade = novaPrioridade;
            removeFila(fila,dadon);
            insereFilaPrioridade(fila,dadon,novaPrioridade);
            return;
        }
        auxi = auxi->prox;
    }
    printf("Elemento com idade %d não encontrado!\n",dadon);

}
void imprimeFila(Fila *fila){
    int contador = 0;
    Elemento *auxi = fila->inicio;
    printf("-----Pessoas na fila-----\n");
    while (auxi != NULL)
    {
        contador++;
        printf("Idade: %d\n",auxi->dado);
        printf("Prioridade: %d\n",auxi->prioridade);
        auxi = auxi->prox;
    }
    printf("Tem %d pessoas na fila!\n",contador);
}



int main(){
    Fila *fila = criaFila();
    int opcao;
    int idade,prioridade = 0, idaden, prioridaden, idadenn;
    while (1)
    {
        printf("----------MENU DE OPCOES----------\n");
        printf("[1] inserir pessoa\n");
        printf("[2] imprimir pessoas\n");
        printf("[3] alterar prioridade\n");
        printf("[4] remover pessoa\n");
        printf("[5] sair\n");
        scanf("%d",&opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a idade da pessoa: \n");
            scanf("%d",&idade);
            printf("Digite a prioridade[1-10]:\n");
            scanf("%d",&prioridade);
            insereFilaPrioridade(fila,idade,prioridade);
            break;
        
        case 2:
            imprimeFila(fila);
            break;
        case 3:
            imprimeFila(fila);
            printf("Digite a idade que quer alterar a prioridade:\n");
            scanf("%d",&idaden);
            printf("Agora digite a nova prioridade da pessoa[1-10]:\n");
            scanf("%d",&prioridaden);
            alterarprioridade(fila,idaden,prioridaden);
            break;
        case 4:
            imprimeFila(fila);
            printf("Digite a idade da pessoa que quer remover:\n");
            scanf("%d",&idadenn);
            removeFila(fila,idadenn);
            break;
        case 5:
            printf("Saindo do programa....");
            break;
        default:
            printf("Insercao invalida! Por favor inserir novamente!\n");
            break;
        }
    }
    
}