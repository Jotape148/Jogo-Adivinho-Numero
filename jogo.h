#ifndef JOGO_H
#define JOGO_H

#include <windows.h>

// Número máximo de tentativas permitidas
#define MAX_TENTATIVAS 5

// Estrutura de dados para armazenar as informações necessárias para as threads
typedef struct {
    int numero_secreto;     // Número secreto a ser adivinhado
    int* tentativas;        // Contador de tentativas
    HANDLE semaforo;        // Semáforo para sincronização
} dados_thread_t;

// Declaração da função que será executada pela thread do jogo
DWORD WINAPI loop_jogo(LPVOID arg);

#endif // JOGO_H
