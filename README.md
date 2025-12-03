TETRIS MODULAR – ESTRUTURAS DE DADOS (README)

🎮 Tetris Modular – Estruturas de Dados (Fila + Pilha)
Projeto acadêmico – Disciplina de Estrutura de Dados (2º Período)

Este repositório contém a implementação modular de um protótipo de jogo inspirado no Tetris, focado no uso e aplicação prática de Estruturas de Dados Lineares — especificamente Fila (Queue) e Pilha (Stack). O objetivo principal do projeto é demonstrar, em um contexto real, a manipulação dessas estruturas utilizando circular queue, controle de overflow/underflow, modularização em C e boas práticas de organização de código.

SUMÁRIO
- Visão Geral
- Objetivos Acadêmicos
- Estruturas de Dados Utilizadas
- Arquitetura do Projeto
- Compilação e Execução
- Fluxo Lógico das Peças
- Trechos de Código Importantes
- Melhorias Futuras
- Autor

VISÃO GERAL
O protótipo implementa um sistema básico de gerenciamento de peças no estilo Tetris, utilizando:
- Fila circular → para armazenar as próximas peças.
- Pilha → para armazenar a peça de reserva.

OBJETIVOS ACADÊMICOS
✔ Implementação de Fila Circular Estática  
✔ Implementação de Pilha Estática  
✔ Modularização em C  
✔ Boas práticas de ADTs  
✔ Prototipação funcional usando Estruturas de Dados reais

ESTRUTURAS DE DADOS UTILIZADAS

FILA CIRCULAR
A fila armazena sequencialmente as próximas peças. Usa índices circulares:
fim = (fim + 1) % MAX_ITENS

PILHA DE RESERVA
A pilha representa a peça guardada. Opera com topo++, topo--.

ARQUITETURA DO PROJETO
/include  
/src  
Makefile  
README.md

COMPILAÇÃO
gcc -Wall -Wextra -std=c11 src/*.c -Iinclude -o tetris  
ou apenas: make  
Execução: ./tetris

FLUXO LÓGICO
1. Peças são inseridas na fila.  
2. A atual é removida e usada.  
3. Jogador pode guardar na pilha.  
4. Recuperação via pop.  
5. Overflow/Underflow tratados.

TRECHOS DE CÓDIGO IMPORTANTES
typedef struct { int id; char tipo; } Peca;

Inserção:
f->item[f->fim] = p;
f->fim = (f->fim + 1) % MAX_ITENS;
f->total++;

Remoção:
Peca p = f->item[f->inicio];
f->inicio = (f->inicio + 1) % MAX_ITENS;
f->total--;

Pilha:
pi->itens_reserva[++pi->topo] = p;

MELHORIAS FUTURAS
- Interface visual com ncurses  
- Tetris completo  
- Bag randomization  
- Testes automatizados

AUTOR
Vinícius Ferraz – GitHub: @FerrazVinicius96
