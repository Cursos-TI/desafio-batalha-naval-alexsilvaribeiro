#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define TAM 10
#define VAZIO 0
#define NAVIO 3
#define ACERTO 1
#define ERRO -1

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = VAZIO;
        }
    }
}

void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n    ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d  ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == ACERTO)
                printf("💥  ");
            else if (tabuleiro[i][j] == ERRO)
                printf("🌊  ");
            else
                printf(".   ");  // Não revela navios ainda
        }
        printf("\n");
    }
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int tabuleiro[TAM][TAM];
    int mapaNavios[TAM][TAM];  // Local onde os navios estão escondidos

    inicializarTabuleiro(tabuleiro);
    inicializarTabuleiro(mapaNavios);

    // Posiciona um navio de 3 blocos em linha (horizontal)
    mapaNavios[2][3] = NAVIO;
    mapaNavios[2][4] = NAVIO;
    mapaNavios[2][5] = NAVIO;

    int linha, coluna;
    int acertos = 0;
    int tentativas = 0;
    const int maxTentativas = 10;

    while (tentativas < maxTentativas && acertos < 3) {
        mostrarTabuleiro(tabuleiro);

        printf("\nTentativa %d de %d\n", tentativas + 1, maxTentativas);
        printf("Digite linha e coluna (0-9): ");
        scanf("%d %d", &linha, &coluna);

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Coordenada inválida!\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == ACERTO || tabuleiro[linha][coluna] == ERRO) {
            printf("Você já atirou aqui!\n");
            continue;
        }

        if (mapaNavios[linha][coluna] == NAVIO) {
            printf("💥 Acertou um navio!\n");
            tabuleiro[linha][coluna] = ACERTO;
            acertos++;
        } else {
            printf("🌊 Errou! Só água aqui.\n");
            tabuleiro[linha][coluna] = ERRO;
        }

        tentativas++;
    }

    mostrarTabuleiro(tabuleiro);

    if (acertos == 3) {
        printf("\n🎉 Parabéns! Você afundou todos os navios!\n");
    } else {
        printf("\n😢 Fim de jogo! Você não conseguiu encontrar todos os navios.\n");
    }

    printf("\nObrigado por jogar!\n");
    return 0;
}
