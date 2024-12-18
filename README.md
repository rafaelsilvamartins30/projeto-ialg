
# Sistema de Cadastro de Atletas

Este projeto é um sistema simples de cadastro de atletas profissionais, desenvolvido em C++. O programa realiza a leitura de um arquivo CSV com informações dos atletas, processa os dados e os exibe no console.

## Estrutura do Projeto

- **main.cpp**: Código-fonte principal do sistema.
- **arquivoentrada.csv**: Arquivo de entrada com os dados dos atletas.

## Como Executar

1. Compile o código-fonte:
   ```bash
   g++ main.cpp -o programa
   ```
2. Certifique-se de que o arquivo `arquivoentrada.csv` está no mesmo diretório do programa.
3. Execute o programa:
   ```bash
   ./programa
   ```

## Formato do Arquivo CSV

O arquivo CSV deve seguir o seguinte formato:

```csv
nome,idade,nacionalidade,altura,peso,modalidade
Lebron James,39,Americano,2.06,113,Basquete
...
```

## Observações

- Este projeto foi criado para fins acadêmicos.
- Modifique e adapte conforme necessário para atender aos requisitos do seu professor.

