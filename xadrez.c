#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char capturadas[32]; 
    char jogadas[100][5]; 
    int capturasCount;   
    int jogadasCount;    
} Jogador;

char** inicializarTabuleiro() {
    char **tabuleiro = (char**) malloc(8 * sizeof(char*)); 
    for (int i = 0; i < 8; i++) {
        tabuleiro[i] = (char*) malloc(8 * sizeof(char));   
    }
    
    tabuleiro[0][0] = 'T'; tabuleiro[0][1] = 'C'; tabuleiro[0][2] = 'B'; tabuleiro[0][3] = 'D';
    tabuleiro[0][4] = 'R'; tabuleiro[0][5] = 'B'; tabuleiro[0][6] = 'C'; tabuleiro[0][7] = 'T';
    for (int i = 0; i < 8; i++) tabuleiro[1][i] = '*';  
    
    tabuleiro[7][0] = 't'; tabuleiro[7][1] = 'c'; tabuleiro[7][2] = 'b'; tabuleiro[7][3] = 'd';
    tabuleiro[7][4] = 'r'; tabuleiro[7][5] = 'b'; tabuleiro[7][6] = 'c'; tabuleiro[7][7] = 't';
    for (int i = 0; i < 8; i++) tabuleiro[6][i] = '@';  
    
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
    
    return tabuleiro;
}

void exibirTabuleiro(char** tabuleiro) {
    printf("\n  A B C D E F G H\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf(" %d\n", 8 - i);
    }
    printf("  A B C D E F G H\n");
}

void traduzirNotacao(char* notacao, int* linha, int* coluna) {
    *coluna = notacao[0] - 'A';  // Traduz a coluna de A-H para 0-7
    *linha = 8 - (notacao[1] - '1') - 1;  // Traduz a linha de 1-8 para 0-7
}

bool validarEntrada(char* movimento) {
    if (movimento[0] < 'A' || movimento[0] > 'H') return false;
    if (movimento[1] < '1' || movimento[1] > '8') return false;
    if (movimento[2] < 'A' || movimento[2] > 'H') return false;
    if (movimento[3] < '1' || movimento[3] > '8') return false;
    return true;
}

void copiarJogada(char* destino, const char* origem) {
    for (int i = 0; i < 4; i++) {
        destino[i] = origem[i];
    }
    destino[4] = '\0';  
}

bool moverPeca(char** tabuleiro, char* movimento, Jogador* jogadorAtual, Jogador* oponente) {
    if (!validarEntrada(movimento)) {
        printf("Entrada inválida! Use o formato correto (ex: E2E4).\n");
        return false;
    }

    int linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;
    char pecaCapturada;
    
    traduzirNotacao(movimento, &linhaOrigem, &colunaOrigem);
    traduzirNotacao(movimento + 2, &linhaDestino, &colunaDestino);
    
    char peca = tabuleiro[linhaOrigem][colunaOrigem];
    if (peca == ' ') {
        printf("Movimento inválido! Nenhuma peça na posição de origem.\n");
        return false;
    }

    pecaCapturada = tabuleiro[linhaDestino][colunaDestino];
    if (pecaCapturada != ' ') {
        jogadorAtual->capturadas[jogadorAtual->capturasCount++] = pecaCapturada;
    }

    tabuleiro[linhaDestino][colunaDestino] = tabuleiro[linhaOrigem][colunaOrigem];
    tabuleiro[linhaOrigem][colunaOrigem] = ' ';

    copiarJogada(jogadorAtual->jogadas[jogadorAtual->jogadasCount++], movimento);

    return true;
}

bool verificarXequeMate(char** tabuleiro, char rei, int linhaRei, int colunaRei) {
    int direcoes[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    
    for (int i = 0; i < 8; i++) {
        int novaLinha = linhaRei + direcoes[i][0];
        int novaColuna = colunaRei + direcoes[i][1];

        if (novaLinha >= 0 && novaLinha < 8 && novaColuna >= 0 && novaColuna < 8) {
            if (tabuleiro[novaLinha][novaColuna] == ' ')
                return false; 
        }
    }
    return true; 
}

void exibirJogadasCapturas(Jogador* jogadorA, Jogador* jogadorB, char* nomeJogadorA, char* nomeJogadorB) {
    printf("\nJogador %s - Pecas capturadas: ", nomeJogadorA);
    for (int i = 0; i < jogadorA->capturasCount; i++) {
        printf("%c ", jogadorA->capturadas[i]);
    }
    printf("\nJogador %s - Pecas capturadas: ", nomeJogadorB);
    for (int i = 0; i < jogadorB->capturasCount; i++) {
        printf("%c ", jogadorB->capturadas[i]);
    }
    printf("\nJogadas ja feitas:\n");
    printf("A: ");
    for (int i = 0; i < jogadorA->jogadasCount; i++) {
        printf("%s ", jogadorA->jogadas[i]);
    }
    printf("\nB: ");
    for (int i = 0; i < jogadorB->jogadasCount; i++) {
        printf("%s ", jogadorB->jogadas[i]);
    }
    printf("\n");
}

void jogar(){
     char** tabuleiro = inicializarTabuleiro();
    Jogador jogadorA = {.capturasCount = 0, .jogadasCount = 0};
    Jogador jogadorB = {.capturasCount = 0, .jogadasCount = 0};
    bool xequeMate = false;
    char movimento[5];
    int turno = 1;
    int linhaReiA = 0, colunaReiA = 4;
    int linhaReiB = 7, colunaReiB = 4; 
    char nomeJogadorA[50], nomeJogadorB[50];

    printf("Digite o nome do jogador A: ");
    scanf("%s", nomeJogadorA);
    
    printf("Digite o nome do jogador B: ");
    scanf("%s", nomeJogadorB);

    while (!xequeMate) {
        exibirTabuleiro(tabuleiro);
        if (turno % 2 == 1) {
            printf("\nJogador %s, sua vez. Insira seu movimento: ", nomeJogadorA);
            scanf("%s", movimento);
            if (moverPeca(tabuleiro, movimento, &jogadorA, &jogadorB)) {
                xequeMate = verificarXequeMate(tabuleiro, 'R', linhaReiA, colunaReiA);
                if (xequeMate) {
                    printf("Parabéns, %s! Você venceu o jogo!\n", nomeJogadorA);
                    break;
                }
            }
        } else {
            printf("\nJogador %s, sua vez. Insira seu movimento: ", nomeJogadorB);
            scanf("%s", movimento);
            if (moverPeca(tabuleiro, movimento, &jogadorB, &jogadorA)) {
                xequeMate = verificarXequeMate(tabuleiro, 'r', linhaReiB, colunaReiB);
                if (xequeMate) {
                    printf("Parabéns, %s! Você venceu o jogo!\n", nomeJogadorB);
                    break;
                }
            }
        }
        turno++;
    }

    exibirJogadasCapturas(&jogadorA, &jogadorB, nomeJogadorA, nomeJogadorB);

}

int main() {
   jogar();
    
    return 0;
}
