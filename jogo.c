#include <stdio.h>
#include "jogo.h"

// Função que será executada pela thread do jogo
DWORD WINAPI loop_jogo(LPVOID arg) {
    dados_thread_t* dados = (dados_thread_t*)arg;
    int palpite;

    while (*(dados->tentativas) < MAX_TENTATIVAS) {
        // Solicita ao jogador que insira um palpite
        printf("Digite sua tentativa: ");
        scanf("%d", &palpite);

        // Espera pelo semáforo
        WaitForSingleObject(dados->semaforo, INFINITE);

        // Verifica o palpite do jogador
        if (palpite == dados->numero_secreto) {
            printf("Parabens! Voce adivinhou o numero!\n");
            ReleaseSemaphore(dados->semaforo, 1, NULL);  // Libera o semáforo antes de sair do loop
            break;
        } else if (palpite < dados->numero_secreto) {
            printf("Tente um numero maior!\n");
        } else {
            printf("Tente um numero menor!\n");
        }
        
        // Incrementa o número de tentativas
        (*(dados->tentativas))++;

        // Libera o semáforo
        ReleaseSemaphore(dados->semaforo, 1, NULL);
    }

    // Se o jogador exceder o número máximo de tentativas, informa o número secreto
    if (*(dados->tentativas) >= MAX_TENTATIVAS) {
        printf("Voce excedeu o numero de tentativas! O numero era: %d.\n", dados->numero_secreto);
    }

    return 0;
}
