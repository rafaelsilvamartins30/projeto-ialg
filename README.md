# 🏅 Sistema de Cadastro de Atletas

Este é um sistema simples desenvolvido em **C++** para o cadastro de atletas profissionais. O programa lê um arquivo CSV contendo informações dos atletas, processa esses dados e abre um display para manipula-los.

## 🗂️ Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **`projeto-ialg.cpp`**: Código-fonte principal do sistema.
- **`data.csv`**: Arquivo CSV com os dados dos atletas (certifique-se de que está no mesmo diretório que o programa).
- **`data.dat`**: Mesmo arquivo so que em Binario (certifique-se de que está no mesmo diretório que o programa).

## ⚙️ Funcionalidades

- O sistema permite cadastrar atletas com os seguintes campos:
  - **Nome**: Nome completo do atleta.
  - **Idade**: Idade do atleta.
  - **Nacionalidade**: Nacionalidade do atleta.
  - **Altura**: Altura do atleta (em metros).
  - **Peso**: Peso do atleta (em kg).
  - **Modalidade**: Modalidade esportiva praticada pelo atleta.

- Ao rodar o programa, ele lê os dados do arquivo e exibe no console um display, onde você tem acesso a algumas funcionalidades:
  - **Busca Binaria por**:
    - **Nome**
    - **Idade**
  - **Alteração na lista**:
    - **Editar um atletaa**
    - **Excluir um atleta**
    - **Adicionar um atleta**
  - **Exportar arquivo escolhendo o nome em:**:
    - **.csv**
    - **.dat**
  - **Vizualizar a lista toda ordenada por:
    - **Nome**
    - **Idade**
  - **Vizualizar um trecho especifico da lista ordenada por:
    - **Nome**
    - **Idade**
  - **Sair do programa tendo a opção de salvar o arquivo atual com as mudanças que fez ou não**

## 📑 Formato do Arquivo 

O arquivo se for CSV tipo: `nomedoarquivo.csv` deve seguir o seguinte formato para garantir que o sistema funcione corretamente:

```csv
nome,idade,nacionalidade,altura,peso,modalidade
Lebron James,39,Americano,2.06,113,Basquete
Cristiano Ronaldo,39,Português,1.87,83,Futebol
```

Caso não seja CSV precisa ser um arquivo binario com extensão .dat tipo: `nomedoarquivo.dat`.

## 🚀 Como Executar o Projeto

Compile o código-fonte:
```
g++ main.cpp -o programa
```

Certifique-se de que o arquivo arquivo de entrada seja CSV ou Binario esteja no mesmo diretório que o programa.

Execute o programa:
```
./programa
```

## 🛠️ Tecnologias Utilizadas

C++: Linguagem de programação utilizada para o desenvolvimento.
CSV: Formato de arquivo usado para armazenar os dados dos atletas.
