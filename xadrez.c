#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO 8

// Estrutura para representar uma peça
typedef struct {
    char tipo;    // Símbolo da peça
    char cor;     // 'B' para brancas, 'P' para pretas
} Peca;

// Função para inicializar o tabuleiro
Peca** inicializa_tabuleiro() {
    Peca **tabuleiro = (Peca**)malloc(TAMANHO * sizeof(Peca*));
    for (int i = 0; i < TAMANHO; i++) {
        tabuleiro[i] = (Peca*)malloc(TAMANHO * sizeof(Peca));
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j].tipo = ' '; // Casa vazia
            tabuleiro[i][j].cor = ' ';
        }
    }
    
    // Posicionar as peças brancas e pretas
    // Peões
    for (int j = 0; j < TAMANHO; j++) {
        tabuleiro[1][j].tipo = '@'; // Peão preto
        tabuleiro[1][j].cor = 'P';
        tabuleiro[6][j].tipo = '*'; // Peão branco
        tabuleiro[6][j].cor = 'B';
    }
    
    // Torres
    tabuleiro[0][0].tipo = tabuleiro[0][7].tipo = 't';
    tabuleiro[0][0].cor = tabuleiro[0][7].cor = 'P';
    tabuleiro[7][0].tipo = tabuleiro[7][7].tipo = 'T';
    tabuleiro[7][0].cor = tabuleiro[7][7].cor = 'B';

    // Cavalos
    tabuleiro[0][1].tipo = tabuleiro[0][6].tipo = 'c';
    tabuleiro[0][1].cor = tabuleiro[0][6].cor = 'P';
    tabuleiro[7][1].tipo = tabuleiro[7][6].tipo = 'C';
    tabuleiro[7][1].cor = tabuleiro[7][6].cor = 'B';

    // Bispos
    tabuleiro[0][2].tipo = tabuleiro[0][5].tipo = 'b';
    tabuleiro[0][2].cor = tabuleiro[0][5].cor = 'P';
    tabuleiro[7][2].tipo = tabuleiro[7][5].tipo = 'B';
    tabuleiro[7][2].cor = tabuleiro[7][5].cor = 'B';

    // Damas
    tabuleiro[0][3].tipo = 'd';
    tabuleiro[0][3].cor = 'P';
    tabuleiro[7][3].tipo = 'D';
    tabuleiro[7][3].cor = 'B';

    // Reis
    tabuleiro[0][4].tipo = 'r';
    tabuleiro[0][4].cor = 'P';
    tabuleiro[7][4].tipo = 'R';
    tabuleiro[7][4].cor = 'B';

    return tabuleiro;
}

// Função para desenhar o tabuleiro
void desenha_tabuleiro(Peca **tabuleiro) {
    printf("  A B C D E F G H\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", TAMANHO - i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j].tipo);
        }
        printf("%d\n", TAMANHO - i);
    }
    printf("  A B C D E F G H\n");
}

// Função para converter a notação algébrica em coordenadas
void converte_posicao(char coluna, int linha, int *x, int *y) {
    *y = coluna - 'A';  // Coluna A-H para índice 0-7
    *x = TAMANHO - linha;  // Linha 1-8 para índice 7-0
}

bool movimento_peao(Peca **tabuleiro, int x_inicial, int y_inicial, int x_final, int y_final) {
    Peca peca = tabuleiro[x_inicial][y_inicial];
    int direcao = (peca.cor == 'B') ? -1 : 1;  // Peões brancos sobem, pretos descem
    
    // Movendo para frente
    if (y_inicial == y_final) {
        if (x_final == x_inicial + direcao && tabuleiro[x_final][y_final].tipo == ' ') {
            return true;
        }
        if ((x_inicial == 1 && peca.cor == 'P') || (x_inicial == 6 && peca.cor == 'B')) {
            if (x_final == x_inicial + 2 * direcao && tabuleiro[x_final][y_final].tipo == ' ' && tabuleiro[x_inicial + direcao][y_inicial].tipo == ' ') {
                return true;
            }
        }
    }
    
    // Captura diagonal
    if (abs(y_inicial - y_final) == 1 && x_final == x_inicial + direcao && tabuleiro[x_final][y_final].tipo != ' ' && tabuleiro[x_final][y_final].cor != peca.cor) {
        return true;
    }

    return false;
}

bool movimento_torre(Peca **tabuleiro, int x_inicial, int y_inicial, int x_final, int y_final) {
    if (x_inicial != x_final && y_inicial != y_final) {
        return false; // Movimentos diagonais não são permitidos
    }
    
    // Verificar se há peças no caminho
    if (x_inicial == x_final) {
        int delta = (y_final > y_inicial) ? 1 : -1;
        for (int j = y_inicial + delta; j != y_final; j += delta) {
            if (tabuleiro[x_inicial][j].tipo != ' ') {
                return false;
            }
        }
    } else {
        int delta = (x_final > x_inicial) ? 1 : -1;
        for (int i = x_inicial + delta; i != x_final; i += delta) {
            if (tabuleiro[i][y_inicial].tipo != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool movimento_cavalo(int x_inicial, int y_inicial, int x_final, int y_final) {
    return (abs(x_inicial - x_final) == 2 && abs(y_inicial - y_final) == 1) || 
           (abs(x_inicial - x_final) == 1 && abs(y_inicial - y_final) == 2);
}

bool movimento_bispo(Peca **tabuleiro, int x_inicial, int y_inicial, int x_final, int y_final) {
    if (abs(x_inicial - x_final) != abs(y_inicial - y_final)) {
        return false;
    }

    int delta_x = (x_final > x_inicial) ? 1 : -1;
    int delta_y = (y_final > y_inicial) ? 1 : -1;
    for (int i = x_inicial + delta_x, j = y_inicial + delta_y; i != x_final; i += delta_x, j += delta_y) {
        if (tabuleiro[i][j].tipo != ' ') {
            return false;
        }
    }

    return true;
}

bool movimento_rainha(Peca **tabuleiro, int x_inicial, int y_inicial, int x_final, int y_final) {
    return movimento_torre(tabuleiro, x_inicial, y_inicial, x_final, y_final) || 
           movimento_bispo(tabuleiro, x_inicial, y_inicial, x_final, y_final);
}

bool movimento_rei(int x_inicial, int y_inicial, int x_final, int y_final) {
    return abs(x_inicial - x_final) <= 1 && abs(y_inicial - y_final) <= 1;
}

// Função para mover uma peça
bool mover_peca(Peca **tabuleiro, char col_inicial, int lin_inicial, char col_final, int lin_final) {
    int x_inicial, y_inicial, x_final, y_final;
    converte_posicao(col_inicial, lin_inicial, &x_inicial, &y_inicial);
    converte_posicao(col_final, lin_final, &x_final, &y_final);
    
    Peca peca = tabuleiro[x_inicial][y_inicial];

    if (peca.tipo == ' ') {
        printf("Não há peça na posição de origem.\n");
        return false;
    }

    // Validação dos movimentos de acordo com o tipo de peça
    bool movimento_valido = false;
    switch (peca.tipo) {
        case '@':
        case '*': movimento_valido = movimento_peao(tabuleiro, x_inicial, y_inicial, x_final, y_final); break;
        case 't':
        case 'T': movimento_valido = movimento_torre(tabuleiro, x_inicial, y_inicial, x_final, y_final); break;
        case 'c':
        case 'C': movimento_valido = movimento_cavalo(x_inicial, y_inicial, x_final, y_final); break;
        case 'b':
        case 'B': movimento_valido = movimento_bispo(tabuleiro, x_inicial, y_inicial, x_final, y_final); break;
        case 'd':
        case 'D': movimento_valido = movimento_rainha(tabuleiro, x_inicial, y_inicial, x_final, y_final); break;
        case 'r':
        case 'R': movimento_valido = movimento_rei(x_inicial, y_inicial, x_final, y_final); break;
        default: return false;
    }

    if (movimento_valido) {
        tabuleiro[x_final][y_final] = peca;
        tabuleiro[x_inicial][y_inicial].tipo = ' ';
        tabuleiro[x_inicial][y_inicial].cor = ' ';
        return true;
    } else {
        printf("Movimento inválido.\n");
        return false;
    }
}

int main() {
    Peca **tabuleiro = inicializa_tabuleiro();
    
    char col_inicial, col_final;
    int lin_inicial, lin_final;
    bool jogo_continua = true;

    while (jogo_continua) {
        desenha_tabuleiro(tabuleiro);
        
        printf("Informe a jogada (e.g., E2 E4): ");
        scanf(" %c%d %c%d", &col_inicial, &lin_inicial, &col_final, &lin_final);
        
        if (!mover_peca(tabuleiro, col_inicial, lin_inicial, col_final, lin_final)) {
            printf("Jogada inválida. Tente novamente.\n");
        }
    }
    
    for (int i = 0; i < TAMANHO; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}
