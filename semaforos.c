#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

// Detecta Windows ou Linux/Mac
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
    #define SLEEP(seconds) Sleep((seconds) * 1000)
    #define CLEAR() system("cls")
#else
    #include <unistd.h>
    #define SLEEP(seconds) sleep(seconds)
    #define CLEAR() system("clear")
#endif

// Códigos de cores ANSI (no Windows 10+ funciona no terminal padrão)
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

/*
Configura o console para suportar UTF-8 e cores ANSI

No Windows:
- Habilita suporte a UTF-8 no console
- Ativa sequências de escape ANSI para cores
- Configura locale para UTF-8

No Linux/Mac:
- Configura locale para UTF-8
*/
void configurarConsole() {
#ifdef _WIN32
    // Habilita suporte a UTF-8 no console do Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Habilita sequências de escape ANSI no Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    // Configura locale para UTF-8
    setlocale(LC_ALL, ".UTF8");
#else
    // Para Linux/Mac, configura locale para UTF-8
    setlocale(LC_ALL, "");
#endif
}

/*
Exibe uma barra de progresso visual com tempo restante

@param total Tempo total em segundos
@param restante Tempo restante em segundos

A barra é preenchida proporcionalmente ao progresso e mostra o tempo restante em segundos
*/
void barraProgresso(int total, int restante) {
    int tamanhoBarra = 20;
    int preenchidos = (total - restante) * tamanhoBarra / total;

    printf("[");
    for (int i = 0; i < preenchidos; i++) printf("█");
    for (int i = preenchidos; i < tamanhoBarra; i++) printf(" ");
    printf("] %2ds", restante);
    fflush(stdout);
}

/*
Exibe o estado atual do semáforo usando emojis coloridos

@param verde 1 se o sinal verde estiver ativo, 0 caso contrário
@param amarelo 1 se o sinal amarelo estiver ativo, 0 caso contrário
@param vermelho 1 se o sinal vermelho estiver ativo, 0 caso contrário

Usa códigos de cores ANSI para destacar os sinais ativos e emojis para representar visualmente o estado
*/
void mostrarSemaforo(int vermelho, int amarelo, int verde) {
    printf("Semáforo: ");
    printf(vermelho ? RED "🔴 " RESET : "⚪ ");
    printf(amarelo ? YELLOW "🟡 " RESET : "⚪ "); 
    printf(verde ? GREEN "🟢" RESET : "⚪");
    printf("\n");
}

/*
Função principal que executa a simulação do semáforo

O programa roda em loop infinito, alternando entre:
1. Via principal aberta (45s verde)
2. Primeira transição (5s amarelo piscando)
3. Fase de pedestres na via principal (10s - via principal fechada)
4. Via secundária aberta (35s verde)
5. Segunda transição (5s amarelo piscando)
6. Fase de pedestres na via secundária (10s - via secundária fechada)

Total: Via principal fica fechada por 50 segundos
 */
int main() {
    // Configura o console para suportar UTF-8 e cores
    configurarConsole();
    
    while (1) {
        CLEAR();
        printf("╔════════════════════════════════════════╗\n");
        printf("║     FASE 1: FLUXO NA VIA PRINCIPAL     ║\n");
        printf("╚════════════════════════════════════════╝\n");

        mostrarSemaforo(0, 0, 1); // Verde ativo, outros desligados

        // Conta regressiva de 45 segundos para via principal
        for (int i = 45; i > 0; i--) {
            printf("\rTempo para fechar via principal: ");
            barraProgresso(45, i);
            SLEEP(1);
        }

        // Pisca o amarelo por 5 segundos para alertar sobre mudança
        for (int t = 0; t < 5; t++) {
            CLEAR();
            printf("╔════════════════════════════════════════╗\n");
            printf("║      TRANSIÇÃO: AMARELO PISCANDO       ║\n");
            printf("╚════════════════════════════════════════╝\n");

            // Alterna entre amarelo ligado e desligado para efeito piscante
            if (t % 2 == 0)
                mostrarSemaforo(0, 1, 0); // Amarelo ligado
            else
                mostrarSemaforo(0, 0, 0); // Todos desligados

            // Mostra barra de progresso para a transição
            printf("\rTempo da transição: ");
            barraProgresso(5, 5 - t);
            SLEEP(1);
        }

        // Via principal fechada para permitir travessia de pedestres
        CLEAR();
        printf("╔════════════════════════════════════════╗\n");
        printf("║    FASE DE PEDESTRES (VIA PRINCIPAL)   ║\n");
        printf("╚════════════════════════════════════════╝\n");

        printf(RED "Carros da via principal: PARADOS\n" RESET);
        mostrarSemaforo(1, 0, 0); // Vermelho ativo para carros
        printf("\n");
        printf(GREEN "Pedestres da via principal: ATRAVESSANDO\n" RESET);
        mostrarSemaforo(0, 0, 1); // Verde ativo para pedestres

        // Contagem regressiva de 10 segundos para travessia de pedestres
        for (int i = 10; i > 0; i--) {
            printf("\rTempo para atravessar: ");
            barraProgresso(10, i);
            SLEEP(1);
        }

        // Via principal permanece fechada, via secundária recebe fluxo
        CLEAR();
        printf("╔════════════════════════════════════════╗\n");
        printf("║     FASE 2: FLUXO NA VIA SECUNDÁRIA    ║\n");
        printf("╚════════════════════════════════════════╝\n");

        mostrarSemaforo(0, 0, 1); // Verde ativo na via secundária

        // Contagem regressiva de 35 segundos para via secundária
        for (int i = 35; i > 0; i--) {
            printf("\rTempo para fechar via secundária: ");
            barraProgresso(35, i);
            SLEEP(1);
        }

        // Pisca o amarelo por 5 segundos para alertar sobre mudança
        for (int t = 0; t < 5; t++) {
            CLEAR();
            printf("╔════════════════════════════════════════╗\n");
            printf("║      TRANSIÇÃO: AMARELO PISCANDO       ║\n");
            printf("╚════════════════════════════════════════╝\n");

            // Alterna entre amarelo ligado e desligado para efeito piscante
            if (t % 2 == 0)
                mostrarSemaforo(0, 1, 0); // Amarelo ligado
            else
                mostrarSemaforo(0, 0, 0); // Todos desligados

            // Mostra barra de progresso para a transição
            printf("\rTempo da transição: ");
            barraProgresso(5, 5 - t);
            SLEEP(1);
        }

        // Via secundária fechada para permitir travessia de pedestres
        CLEAR();
        printf("╔════════════════════════════════════════╗\n");
        printf("║   FASE DE PEDESTRES (VIA SECUNDÁRIA)   ║\n");
        printf("╚════════════════════════════════════════╝\n");

        printf(RED "Carros da via secundária: PARADOS\n" RESET);
        mostrarSemaforo(1, 0, 0); // Vermelho ativo para carros
        printf("\n");
        printf(GREEN "Pedestres da via secundária: ATRAVESSANDO\n" RESET);
        mostrarSemaforo(0, 0, 1); // Verde ativo para pedestres

        // Contagem regressiva de 10 segundos para travessia de pedestres na via secundária
        for (int i = 10; i > 0; i--) {
            printf("\rTempo para atravessar: ");
            barraProgresso(10, i);
            SLEEP(1);
        }
    }

    return 0;
}