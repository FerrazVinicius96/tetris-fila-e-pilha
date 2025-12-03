#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 5

// -----------------------------
// Estruturas
// -----------------------------
typedef struct {
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca item[MAX_ITENS];
    int inicio;
    int fim;
    int total;
} Fila;

// Criacao da pilha itens_reserva

typedef struct{
    Peca itens_reserva[MAX_ITENS];
    int topo;
} Pilha;

// ----------------------------
// Controle da Pilha
// ----------------------------

void inicializarPilha(Pilha *pi){
    pi->topo = -1;
}

int pilhaCheia(Pilha *pi){
    return pi->topo == MAX_ITENS - 1;
}

int pilhaVazia(Pilha *pi){
    return pi->topo == -1;
}

void push(Pilha *pi, Peca p){
    if(pilhaCheia(pi)){
        printf("Pilha cheia.\n");
        return;
    }

    pi->topo++;
    pi->itens_reserva[pi->topo] = p;
}

void pop(Pilha *pi, Peca *removida){
    if(pilhaVazia(pi)){
        printf("Pilha reserva vazia.\n");
        return;
    }

    *removida = pi->itens_reserva[pi->topo];
    pi->topo--;
}

void mostrarPilha(Pilha *pi){
    printf("\nPilha reserva: \n");

    if(pilhaVazia(pi)){
        printf("Pilha reserva vazia.\n");
        return;
    }

    for(int i = pi->topo; i > -1; i--){
        printf("[%c %d] ", pi->itens_reserva[i].tipo, pi->itens_reserva[i].id);
    }

    printf("\n\n");


}

// -----------------------------
// Controle da Fila
// -----------------------------
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f){
    return f->total == MAX_ITENS;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

void inserir(Fila *f, Peca p){
    if(filaCheia(f)){
        printf("Fila cheia.\n");
        return;
    }

    f->item[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_ITENS;
    f->total++;
}

Peca remover(Fila *f){
    Peca removida = {-1, '?'};

    if(filaVazia(f)){
        printf("Fila vazia.\n");
        return removida;
    }

    removida = f->item[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_ITENS;
    f->total--;

    return removida;
}


void mostrar(Fila *f){
    printf("\nFila atual:\n");

    if (filaVazia(f)) {
        printf("[vazia]\n\n");
        return;
    }

    int idx = f->inicio;

    for (int i = 0; i < f->total; i++){
        printf("[%c %d] ", f->item[idx].tipo, f->item[idx].id);
        idx = (idx + 1) % MAX_ITENS;
    }

    printf("\n\n");
}


// -----------------------------
// Geração Aleatória de Peças
// -----------------------------

Peca gerarPeca(void){
    static int nextId = 0; // garante IDs únicos

    char tipos[] = {'O', 'I', 'T', 'L'};
    int r = rand() % 4; // sorteio entre 0 e 3

    Peca p;
    p.id = nextId++;
    p.tipo = tipos[r];

    return p;
}

/* Menu */

int menu() {
    char buffer[100];
    char *endptr;
    long opcao;

    printf("\n--- MENU INICIAL ---\n\n");
    printf("1 - Jogar peca (remover da fila)\n");
    printf("2 - Armazenar peca na pilha\n");
    printf("3 - Jogar peca do topo da pilha\n");
    printf("4 - Sair\n");
    printf("Opcao: ");

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return -1; // erro de leitura
    }

    opcao = strtol(buffer, &endptr, 10);

    return (int)opcao;
}

// -----------------------------
// MAIN
// -----------------------------
int main(void){
    int opcao;
    srand((unsigned)time(NULL)); // inicializa aleatoriedade

    Fila jogo; // Declara uma variavel para o jogo
    Pilha reserva; // Declara uma variavel para fila

    inicializarFila(&jogo);
    inicializarPilha(&reserva);

    // Inserindo 5 peças iniciais
    for(int i = 0; i < MAX_ITENS; i++){
        inserir(&jogo, gerarPeca());
    }

    mostrar(&jogo);
    mostrarPilha(&reserva);

    do{
        opcao = menu();
        switch(opcao){
            case 1: {
                // Jogar peça (remover da frente)
                Peca jogada = remover(&jogo);
                printf("Voce jogou a peca: [%c %d]\n", jogada.tipo, jogada.id);

                // Inserir nova peca aleatoria
                Peca nova = gerarPeca();
                inserir(&jogo, nova);
                printf("Peca inserida: [%c %d]\n", nova.tipo, nova.id);

                mostrar(&jogo);
                break;
            }
            case 2: {
                Peca proxima = remover(&jogo);
                inserir(&jogo, gerarPeca());

                push(&reserva, proxima);

                mostrar(&jogo);
                mostrarPilha(&reserva);
                break;
            }
            case 3:
                Peca removida;
                pop(&reserva, &removida);
                printf("Voce jogou a peca: [%c %d]\n", removida.tipo, removida.id);


                break;
            case 4:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while(opcao != 4);

    return 0;
}
