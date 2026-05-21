# 🚦 Semáforos

Simulação de controle semafórico para interseção veicular e de pedestres, desenvolvida em linguagem **C** como desafio proposto pelo professor da disciplina. O programa implementa um sistema completo de semáforos com temporização realista, faixa de pedestres e alternância entre via principal e secundária, utilizando cores ANSI para representação visual no terminal.

---

## 🗂️ Estrutura do Repositório

- **Semaforos/**
  - `semaforos.c` — Código-fonte principal com a simulação completa do sistema semafórico
  - `semaforos.exe` — Executável compilado para Windows

---

## 🛠️ Tecnologias

- **Linguagem:** C (padrão ANSI/C99)
- **Compilação:** GCC / MinGW
- **Ambiente:** Windows / Linux / macOS (com suporte a cores ANSI via terminal)
- **Bibliotecas:** `stdio.h`, `stdlib.h`, `locale.h`, `wchar.h`, `windows.h` (Win) / `unistd.h` (Unix)

---

## 📖 Especificação do Sistema

### Regras do Desafio

| Requisito | Descrição |
|-----------|-----------|
| **Via Principal** | Deve permanecer fechada por no máximo 60 segundos |
| **Via Secundária** | Opera com tempos realistas durante o fechamento da via principal |
| **Faixa de Pedestres** | Sinalização integrada para travessia segura |
| **Interface Visual** | Cores reais de semáforo (vermelho, amarelo, verde) via ANSI no terminal |

### Funcionamento

O sistema simula um ciclo completo de semáforos em uma interseção:

1. **Via Principal** — Sinal verde para veículos; via secundária fechada
2. **Transição** — Amarelo na via principal, preparando para fechamento
3. **Via Principal Fechada** — Vermelho na via principal; via secundária abre
4. **Pedestres** — Sinal verde para travessia na faixa de pedestres
5. **Retorno ao Ciclo** — Via secundária fecha, via principal reabre

---

## 🚀 Como Compilar e Executar

### Requisitos
- Compilador C (GCC recomendado)
- Terminal com suporte a cores ANSI

### Compilação

```bash
gcc semaforos.c -o semaforo
./semaforo
```

O programa detecta automaticamente o sistema operacional:

- **Windows:** utiliza `Sleep()` para temporização e `system("cls")` para limpeza de tela
- **Linux/macOS:** utiliza `sleep()` para temporização e `system("clear")` para limpeza de tela

---

## 💡 Destaques de Implementação

- **Compatibilidade Cross-Platform:** Uso de diretivas `#ifdef _WIN32` para adaptar funções de temporização e limpeza de tela entre Windows e sistemas Unix
- **Cores ANSI:** Sequências de escape `\033[1;31m` (vermelho), `\033[1;32m` (verde) e `\033[1;33m` (amarelo) para representação visual realista
- **Suporte a UTF-8:** Configuração automática de locale para exibição correta de caracteres acentuados e símbolos no console
- **Temporização Realista:** Ciclos de tempo calibrados para simular o comportamento real de um sistema semafórico
- **Código Compacto:** Implementação em arquivo único, sem dependências externas além das bibliotecas padrão

---

## 📌 Observações

- O código foi desenvolvido na 1ª semana de contato com a linguagem C, representando um desafio significativo para o nível inicial do autor
- A execução em terminais Windows antigos (pré-Windows 10) pode não suportar cores ANSI; recomenda-se Windows Terminal ou PowerShell moderno
- O arquivo `.exe` é um artefato de compilação local e pode ser ignorado ou removido

---

## 👨‍💻 Autor

- **Matheus Souza Silva**
- Desafio acadêmico de programação em C — UCB

---

📅 Última atualização: 09/2025
