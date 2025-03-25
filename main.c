#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int numero_secreto = rand() % 100 + 1; // Gera um número secreto entre 1 e 100
    int tentativas = 0; // Inicializa o contador de tentativas
    HANDLE semaforo; // Declara o semáforo

    // Inicializa o semáforo com valor 1 (semáforo binário)
    semaforo = CreateSemaphore(NULL, 1, 1, NULL);

    // Cria a thread do jogo
    HANDLE thread_jogo;
    dados_thread_t dados;
    dados.numero_secreto = numero_secreto;
    dados.tentativas = &tentativas;
    dados.semaforo = semaforo;

    // Inicia a thread do jogo
    thread_jogo = CreateThread(NULL, 0, loop_jogo, &dados, 0, NULL);

    // Aguarda a conclusão da thread do jogo
    WaitForSingleObject(thread_jogo, INFINITE);

    // Fecha o handle da thread
    CloseHandle(thread_jogo);

    // Destroi o semáforo
    CloseHandle(semaforo);

    return 0;
}
