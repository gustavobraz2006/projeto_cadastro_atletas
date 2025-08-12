# Sistema de Cadastro de Jogadores em C

Este é um projeto simples em C que implementa um sistema de cadastro de jogadores, com funcionalidades para:

- Cadastrar novos jogadores (nome, idade, posição)
- Listar jogadores cadastrados
- Buscar jogador por nome (case insensitive)
- Apagar jogador
- Salvar e carregar os dados em arquivo CSV (`jogadores.csv`)


## Como compilar

No Linux/Mac:

```bash
gcc main.c -o cadastro

No Windows:

gcc main.c -o cadastro.exe

os dados serão armazenados em arquivo csv na pasta do programa.
o arquivo csv possui o seguinte formato: (nome,idade,posição)
