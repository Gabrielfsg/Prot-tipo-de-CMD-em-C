<h1 align="center">Protótipo de CMD em C</h1>

<p align="center">
  Shell minimalista escrito em C — projeto da disciplina de Sistemas Operacionais.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black"/>
  <img src="https://img.shields.io/badge/Make-A42E2B?style=for-the-badge&logo=gnu&logoColor=white"/>
</p>

## 📋 Sobre o projeto

Trabalho da disciplina de **Sistemas Operacionais** que implementa um **protótipo de interpretador de comandos (shell)** em linguagem C, simulando um CMD/terminal simples.

## 🛠️ Tecnologias

- **C**
- **Make** — automação da compilação
- Compatível com **MinGW (Windows)** e **GCC (Linux)**

## 📁 Estrutura

```
TrabalhoSO/
├── main.c           # Implementação do shell
├── Makefile         # Regras de build
├── nbproject/       # Configuração do NetBeans
└── dist/            # Binário compilado
```

## ✅ Pré-requisitos

- GCC ou MinGW
- Make

## 🚀 Como executar

```bash
cd TrabalhoSO

# Compilar
make

# Executar
./dist/Debug/MinGW-Windows/trabalhoso     # Windows
./dist/Debug/GNU-Linux/trabalhoso          # Linux
```

Ou compile manualmente:

```bash
gcc main.c -o trabalhoso
./trabalhoso
```

## 🎯 Conceitos aplicados

- Manipulação de processos (`fork`, `exec`)
- Parsing de entrada do usuário
- Loop interativo de leitura, parsing e execução de comandos
- Programação de baixo nível em C

---

Trabalho da disciplina de Sistemas Operacionais — [IFMG Formiga](https://www.formiga.ifmg.edu.br/).
