Este projeto foi desenvolvido como parte da disciplina de Laboratório de Programação II, do curso de Ciência da Computação da Universidade Federal de Santa Maria.
Descrição

O programa implementa um jogo de xadrez simplificado que permite aos jogadores realizar jogadas no tabuleiro e verificar se uma jogada resulta em xeque ou xeque-mate. Ele mantém o histórico de jogadas e peças capturadas durante a partida.

O tabuleiro é inicializado com as peças nas posições padrões do jogo de xadrez, e o programa oferece funcionalidades para movimentar as peças e capturar peças adversárias, além de verificar se o rei está em xeque ou se ocorreu um xeque-mate.
Funcionalidades:

  Inicialização do tabuleiro de xadrez com peças brancas e pretas;
  Validação de movimentos para peças como peões, torres, cavalos, bispos, rainhas e reis;
  Detecção de xeque e xeque-mate;
  Registro de jogadas e captura de peças;
  Exibição das jogadas realizadas e das peças capturadas.

### Estrutura

O código está organizado da seguinte forma:

  Peca: Estrutura que representa uma peça de xadrez, contendo o tipo e a cor da peça.
  Jogada: Estrutura que armazena uma jogada, contendo a descrição da jogada realizada.
  Tabuleiro: O tabuleiro de xadrez é representado por uma matriz 8x8 de ponteiros para peças.

### Como Jogar

  O programa exibe o tabuleiro e solicita que o jogador insira uma jogada no formato coluna linha coluna linha (exemplo: E2 E4).
  O jogador deve inserir jogadas válidas de acordo com as regras do xadrez.
  O jogo verifica se a jogada é válida e atualiza o tabuleiro.
  As capturas e jogadas são registradas, e o programa continua até que ocorra um xeque-mate.

### Requisitos

  Compilador compatível com C (por exemplo, gcc).

### Compilação

    gcc -o xadrez xadrez.c

### Execução

    ./xadrez

### Autor

  Lucas Blanger - Desenvolvido como parte da disciplina de Laboratório de Programação II na Universidade Federal de Santa Maria (UFSM).
