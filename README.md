# 🏅 Sistema de Cadastro de Atletas

Este é um sistema simples desenvolvido em **C++** para o cadastro de atletas profissionais. O programa lê um arquivo CSV contendo informações dos atletas, processa esses dados e exibe um display para manipulá-los.

## 🗂️ Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **`projeto-ialg.cpp`**: Código-fonte principal do sistema.
- **`data.csv`**: Arquivo CSV com os dados dos atletas (certifique-se de que está no mesmo diretório que o programa).
- **`data.dat`**: Mesmo arquivo, porém em formato binário (certifique-se de que está no mesmo diretório que o programa).

## ⚙️ Funcionalidades

- O sistema permite cadastrar atletas com os seguintes campos:
  - **Nome**: Nome completo do atleta.
  - **Idade**: Idade do atleta.
  - **Nacionalidade**: Nacionalidade do atleta.
  - **Altura**: Altura do atleta (em metros).
  - **Peso**: Peso do atleta (em kg).
  - **Modalidade**: Modalidade esportiva praticada pelo atleta.

- Ao rodar o programa, ele lê os dados do arquivo e exibe no console um display, onde você tem acesso a algumas funcionalidades:
  - **Busca Binária por**:
    - **Nome.**
    - **Idade.**
  - **Alteração na lista**:
    - **Editar um atletaa.**
    - **Excluir um atleta.**
    - **Adicionar um atleta.**
  - **Exportar arquivo, escolhendo o nome e o formato**:
    - **.csv**
    - **.dat**
  - **Visualizar a lista completa ordenada por**:
    - **Nome.**
    - **Idade.**
  - **Visualizar um trecho específico da lista ordenada por**:
    - **Nome.**
    - **Idade.**
  - **Sair do programa, com a opção de salvar ou não as mudanças feitas no arquivo atual.**

## 📑 Formato do Arquivo 

Se o arquivo for CSV, como `nomedoarquivo.csv`, ele deve seguir o seguinte formato para garantir que o sistema funcione corretamente:

```csv
nome,idade,nacionalidade,altura,peso,modalidade
Lebron James,39,Americano,2.06,113,Basquete
Cristiano Ronaldo,39,Português,1.87,83,Futebol
```

Caso contrário, o arquivo deve ser binário, com a extensão `.dat`, como `nomedoarquivo.dat`.

## 🚀 Como Executar o Projeto

Compile o código-fonte:
```
g++ main.cpp -o programa
```

Certifique-se de que o arquivo arquivo de entrada seja CSV ou Binário esteja no mesmo diretório que o programa.

Execute o programa:
```
./programa
```

## 🛠️ Tecnologias Utilizadas

- ![C++](https://img.shields.io/badge/-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white&style=flat)

- ![Binary](https://img.shields.io/badge/-Binary%20%28.dat%29-9B4D4D?logo=java&logoColor=white&style=flat)

- ![CSV](https://img.shields.io/badge/-CSV-2E8B57?logo=csv&logoColor=white&style=flat)

![Gatinho Fofo](https://media.giphy.com/media/JIX9t2j0ZTN9S/giphy.gif)


