/*Membros da equipe (Grupo 9):
 * Alexandre Bortone
 * Rafael Silva Martins
 * Gabriel Freitas Lima
Tema: Dados de atletas profissionais*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <locale>
#include <cctype>
#include <string>
#include <limits>

using namespace std;

//struct dos itens que vamos trabalhar
struct sportlist {
    char nome[40];          // Nome do jogador
    int idade;              // Idade do jogador
    char nacionalidade[30]; // Nacionalidade do jogador
    float altura;           // Altura do jogador
    int peso;               // Peso do jogador
    char modalidade[30];    // Modalidade esportiva do jogador

    // Método para imprimir os dados do jogador formatado
    void imprime() {
        cout << "_____________________________________________" << endl
        	 << " Nome do Jogador: " << nome << endl
        	 << " Idade do Jogador: " << idade << endl
        	 << " Nacionalidade do Jogador: " << nacionalidade << endl
        	 << " Altura do Jogador: " << altura << endl
        	 << " Peso do Jogador: " << peso << endl
        	 << " Modalidade do Jogador: " << modalidade << endl
        	 << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
    }
};

// Função para limpar a tela do console
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // outros sistemas
    #endif
}

// Função para comparar duas strings ignorando maiúsculas e minúsculas
int comparaCaseInsensitive(const char* str1, const char* str2) {
    #ifdef _WIN32
        return _stricmp(str1, str2); // Windows
    #else
        return strcasecmp(str1, str2); // Unix/Linux
    #endif
}

//displays que se repetem ou que são muito grandes
void displaydeOpcaoInvalida(){
	cout << " _________________ " << endl
    	 << "| Opcao invalida! |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
}

void displayJogadorNaoEncontrado(){
	cout << " ____________________________ " << endl
   		 << "| Nenhum jogador encontrado. |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
}

void displayEncerrarPrograma(){
	cout << " _____________________ " << endl
    	 << "| Programa encerrado! |" << endl
         << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
}

void displayMenuPrincipal(){
	cout << " ________________________ " << endl
         << "|         Menu           |" << endl
         << "|       Principal        |" << endl
         << "|————————————————————————|" << endl
         << "| 1. Busca binaria       |" << endl
     	 << "|————————————————————————|" << endl
         << "| 2. Alteracao na lista  |" << endl
         << "|————————————————————————|" << endl
         << "| 3. Exportar arquivo    |" << endl
         << "|————————————————————————|" << endl
         << "| 4. Visualizar arquivo  |" << endl
         << "|————————————————————————|" << endl
         << "| 5. Vizualizar trecho   |" << endl
         << "|————————————————————————|" << endl
         << "| 6. Sair                |" << endl
         << "|————————————————————————|" << endl
         << "| Escolha uma opcao:     |" << endl
         << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
}

void displaySalvarAlterações(){
	cout << " ___________________________________________________ " << endl
    	 << "| Deseja salvar as alteracoes antes de sair? (s/n): |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
}

// Função para ler uma única linha do arquivo e preencher os dados do atleta
bool lerUmaUnicaLinha(ifstream& entrada, sportlist& algumsportlist) {
    char virgula; // Variável para armazenar a vírgula
    return entrada.getline(algumsportlist.nome, 40, ',') // Lê até a vírgula
           && (entrada >> algumsportlist.idade >> virgula) 
           && (entrada.getline(algumsportlist.nacionalidade, 30, ',')) 
           && (entrada >> algumsportlist.altura >> virgula) 
           && (entrada >> algumsportlist.peso >> virgula) 
           && (entrada.getline(algumsportlist.modalidade, 30)); 
}

// Função para ler os dados de um arquivo e armazená-los em um vetor de sportlist
sportlist* lerDados(const string& nomeArquivo, int& numRegistros, int& capacidade) {
    // Abre o arquivo para leitura
    ifstream entrada(nomeArquivo, nomeArquivo.find(".csv") != string::npos ? ios::in : ios::binary);
    if (!entrada) {
        return NULL; // Retorna NULL se o arquivo não puder ser aberto assim apresentando mensagem de erro na main
    }

    // Aloca memória para o vetor de sportlist
    sportlist* vetorSportlist = new sportlist[capacidade];
    sportlist algumsportlist; // Variável temporária para armazenar os dados lidos

    // Se o arquivo for CSV, lê os dados linha por linha
    if (nomeArquivo.find(".csv") != string::npos) {
        string descArquivo;
        getline(entrada, descArquivo); // Lê a primeira linha (cabeçalho)
        while (lerUmaUnicaLinha(entrada, algumsportlist)) { // Lê os dados dos atletas usando a função de ler uma linha 
            if (numRegistros >= capacidade) { // Verifica se é necessário aumentar a capacidade
                capacidade += 10; // Aumenta a capacidade
                sportlist* novo = new sportlist[capacidade]; // Aloca novo vetor
                memcpy(novo, vetorSportlist, numRegistros * sizeof(sportlist)); // Copia os dados antigos
                delete[] vetorSportlist; // Libera a memória do vetor antigo
                vetorSportlist = novo; // Atualiza o ponteiro
            }
            vetorSportlist[numRegistros] = algumsportlist; // Armazena os dados lidos
            numRegistros++; // Incrementa o número de registros
        }
    } else { // Se o arquivo não for CSV, lê os dados binários praticamente igual acima so que em binario
        while (entrada.read((char*)&algumsportlist, sizeof(sportlist))) { // faz a leitura do arquivo em binario
            if (numRegistros >= capacidade) { 
                capacidade += 10; 
                sportlist* novo = new sportlist[capacidade]; 
                memcpy(novo, vetorSportlist, numRegistros * sizeof(sportlist)); 
                delete[] vetorSportlist; 
                vetorSportlist = novo; 
            }
            vetorSportlist[numRegistros] = algumsportlist; 
            numRegistros++; 
        }
    }

    return vetorSportlist; // Retorna o vetor sportlist
}

// Função para comparar dois atletas pelo nome (para ordenação)
bool comparaPorNome(const sportlist& a, const sportlist& b) {
    return comparaCaseInsensitive(a.nome, b.nome) < 0; // Ordena em ordem alfabética (case-insensitive)
}

// Função para comparar dois atletas pela idade (para ordenação)
bool comparaPorIdade(const sportlist& a, const sportlist& b) {
    return a.idade < b.idade; // Ordena por idade
}

// Função de Quick Sort
void quickSort(sportlist* lista, int esquerdaquickSort, int direitaquickSort, bool (*compara)(const sportlist&, const sportlist&)) {
    // Inicializa os índices para percorrer a lista
    int iquickSort = esquerdaquickSort; // Índice que começa no início da lista
    int jquickSort = direitaquickSort;  // Índice que começa no final da lista

    sportlist pivo = lista[(esquerdaquickSort + direitaquickSort) / 2]; // Escolhe o pivô como o elemento do meio da lista

    while (iquickSort <= jquickSort) { // Enquanto os índices não se cruzarem
        while (compara(lista[iquickSort], pivo)) {  // Avança o índice 'iquickSort' enquanto o elemento for "menor" que o pivô (de acordo com a função 'compara')
            iquickSort++;
        }
        
        while (compara(pivo, lista[jquickSort])) { // Retrocede o índice 'jquickSort' enquanto o elemento for "maior" que o pivô (de acordo com a função 'compara')
            jquickSort--; 
        }

        if (iquickSort <= jquickSort) { // Se os índices não se cruzaram, troca os elementos nas posições 'iquickSort' e 'jquickSort'
            std::swap(lista[iquickSort], lista[jquickSort]); // Troca os elementos
            iquickSort++; // Avança o índice 'iquickSort'
            jquickSort--; // Retrocede o índice 'jquickSort'
        }
    }

    // Recursão para a parte esquerda da lista (elementos menores que o pivô)
    if (esquerdaquickSort < jquickSort) {
        quickSort(lista, esquerdaquickSort, jquickSort, compara);
    }

    // Recursão para a parte direita da lista (elementos maiores que o pivô)
    if (iquickSort < direitaquickSort) {
        quickSort(lista, iquickSort, direitaquickSort, compara);
    }
}

// Função de busca binária
int buscaBinariaFunction(sportlist* lista, int numRegistros, const std::string& chave, bool buscaPorNome) {
    int esquerda = 0; // Índice inicial da lista
    int direita = numRegistros - 1; // Índice final da lista

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2; // Calcula o índice do meio

        if (buscaPorNome) {
            // Busca por nome (ignorando maiúsculas e minúsculas)
            int comparacao = comparaCaseInsensitive(lista[meio].nome, chave.c_str());
            if (comparacao == 0) {
                return meio; // Retorna o índice do elemento encontrado
            } else if (comparacao < 0) {
                esquerda = meio + 1; // Busca na metade direita
            } else {
                direita = meio - 1; // Busca na metade esquerda
            }
        } else {
            // Busca por idade
            int idadeMeio = lista[meio].idade;
            int idadeChave = std::stoi(chave); // Converte a chave para inteiro

            if (idadeMeio == idadeChave) {
                return meio; // Retorna o índice do elemento encontrado
            } else if (idadeMeio < idadeChave) {
                esquerda = meio + 1; // Busca na metade direita
            } else {
                direita = meio - 1; // Busca na metade esquerda
            }
        }
    }

    return -1; // Retorna -1 se o elemento não for encontrado
}

// Função de escolha da busca binária
void buscaBinaria(sportlist* lista, int numRegistros) {
    limparTela();
    cout << " _______________ " << endl
         << "| Busca Binaria |" << endl
         << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl
         << " ___________________________________________________________ " << endl
         << "| Digite 1 para buscar por nome ou 2 para buscar por idade: |" << endl
         << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) { // Busca por nome
        string chave;
        cout << " ___________________________ " << endl
             << "| Digite o nome para busca: |" << endl
             << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        getline(cin, chave);

        // Ordena a lista por nome
        quickSort(lista, 0, numRegistros - 1, comparaPorNome);

        // Realiza a busca binária
        int indice = buscaBinariaFunction(lista, numRegistros, chave, true);

        if (indice != -1) {
            // Exibe o registro encontrado
            lista[indice].imprime();

            // Verifica registros à esquerda (caso haja duplicatas)
            int i = indice - 1;
            while (i >= 0 && lista[i].nome == chave) {
                lista[i].imprime();
                i--;
            }

            // Verifica registros à direita (caso haja duplicatas)
            int j = indice + 1;
            while (j < numRegistros && lista[j].nome == chave) {
                lista[j].imprime();
                j++;
            }
        } else {
            displayJogadorNaoEncontrado();
        }

    } else if (opcao == 2) { // Busca por idade
        int chave;
        cout << " ____________________________ " << endl
             << "| Digite a idade para busca: |" << endl
             << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> chave;

        // Ordena a lista por idade
        quickSort(lista, 0, numRegistros - 1, comparaPorIdade);

        // Realiza a busca binária
        int indice = buscaBinariaFunction(lista, numRegistros, std::to_string(chave), false);

        if (indice != -1) {
            // Exibe o registro encontrado
            lista[indice].imprime();

            // Verifica registros à esquerda (caso haja duplicatas)
            int i = indice - 1;
            while (i >= 0 && lista[i].idade == chave) {
                lista[i].imprime();
                i--;
            }

            // Verifica registros à direita (caso haja duplicatas)
            int j = indice + 1;
            while (j < numRegistros && lista[j].idade == chave) {
                lista[j].imprime();
                j++;
            }
        } else {
            displayJogadorNaoEncontrado();
        }
    } else {
        displaydeOpcaoInvalida();
    }
}

// Função para adicionar dados a lista
void adicionarLista(sportlist*& lista, int& numRegistros, int& capacidade){
	if (numRegistros >= capacidade) { // Verifica se é necessário aumentar a capacidade
            capacidade += 10; // Aumenta a capacidade
            sportlist* novo = new sportlist[capacidade]; // Aloca novo vetor
            memcpy(novo, lista, numRegistros * sizeof(sportlist)); // Copia os dados antigos
            delete[] lista; // Libera a memória do vetor antigo
            lista = novo; // Atualiza o ponteiro
        }
        cout << " _________________________________________________________________________________________ " << endl
        	 << "| Digite os dados do novo jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl
        	 << "_____________________________________________" << endl;
        cout << " Nome: "; cin.getline(lista[numRegistros].nome, 40); // Lê o nome do novo jogador
        cout << " Idade: "; cin >> lista[numRegistros].idade; cin.ignore(); // Lê a idade
        cout << " Nacionalidade: "; cin.getline(lista[numRegistros].nacionalidade, 30); // Lê a nacionalidade
        cout << " Altura: "; cin >> lista[numRegistros].altura; // Lê a altura
        cout << " Peso: "; cin >> lista[numRegistros].peso; cin.ignore(); // Lê o peso
        cout << " Modalidade: "; cin.getline(lista[numRegistros].modalidade, 30); // Lê a modalidade
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl
        	 << " _________________________________ " << endl
        	 << "| Jogador adicionado com sucesso! |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

		numRegistros++; // Incrementa o número de registros
}

// Função para remover dados a lista
void excluirLista(sportlist*& lista, int& numRegistros) {
    string chaveexcluirLista; // Variável para armazenar o nome do jogador a ser excluído
    cout << " ___________________________________________________ " << endl
         << "| Digite o nome completo do jogador a ser excluido: |" << endl
         << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    getline(cin, chaveexcluirLista); // Lê o nome do jogador

    // Ordena a lista por nome antes da busca
    quickSort(lista, 0, numRegistros - 1, comparaPorNome);

    // Busca o jogador na lista
    int indiceexcluirLista = buscaBinariaFunction(lista, numRegistros, chaveexcluirLista, true);

    if (indiceexcluirLista != -1) { // Jogador encontrado
        char confirmacaoexcluirLista;
        cout << " _________________________________________ " << endl
             << "| Você realmente deseja exclui-lo? (s/n): |" << endl
             << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> confirmacaoexcluirLista;
        cin.ignore();

        if (confirmacaoexcluirLista == 's' || confirmacaoexcluirLista == 'S') { // Se confirmado
            for (int j = indiceexcluirLista; j < numRegistros - 1; j++) { // Move os elementos para excluir o jogador
                lista[j] = lista[j + 1];
            }
            numRegistros--; // Decrementa o número de registros
            cout << " _______________________________ " << endl
                 << "| Jogador excluido com sucesso! |" << endl
                 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        } else { // Se não confirmado
            cout << " _____________________ " << endl
                 << "| Exclusão cancelada. |" << endl
                 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        }
    } else {
        displayJogadorNaoEncontrado();
    }
}

// Função para editar dados a lista
void editarLista(sportlist*& lista, int& numRegistros){
	char chaveeditarLista[40]; // Variável para armazenar o nome do jogador a ser alterado
    cout << " ___________________________________________________ " << endl
    	 << "| Digite o nome completo do jogador a ser alterado: |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cin.getline(chaveeditarLista, 40); // Lê o nome do jogador

    // Ordena a lista por nome antes da busca
    quickSort(lista, 0, numRegistros - 1, comparaPorNome);

    // Busca o jogador na lista
    int indiceeditarLista = buscaBinariaFunction(lista, numRegistros, chaveeditarLista, true);
        
    if (indiceeditarLista != -1) { // Verifica se o nome corresponde à chave
        cout << " __________________________________________________________________________________________ " << endl
        	 << "| Digite os novos dados do jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl
        	 << "_____________________________________________" << endl;
        cout << " Nome: "; cin.getline(lista[indiceeditarLista].nome, 40); // Lê o novo nome
        cout << " Idade: "; cin >> lista[indiceeditarLista].idade; cin.ignore(); // Lê a nova idade
        cout << " Nacionalidade: "; cin.getline(lista[indiceeditarLista].nacionalidade, 30); // Lê a nova nacionalidade
        cout << " Altura: "; cin >> lista[indiceeditarLista].altura; // Lê a nova altura
        cout << " Peso: "; cin >> lista[indiceeditarLista].peso; cin.ignore(); // Lê o novo peso
        cout << " Modalidade: "; cin.getline(lista[indiceeditarLista].modalidade, 30); // Lê a nova modalidade
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl
        	 << " ______________________________ " << endl
             << "| Dados alterados com sucesso! |" << endl
             << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;           
    } else {
        displayJogadorNaoEncontrado();
    }
}

// Função para escolher a aleteração de dados
void escolherAlteracao(sportlist*& lista, int& numRegistros, int& capacidade) {
    limparTela(); 
    cout << " ____________________ " << endl
    	 << "| Alteracao na lista |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl
    	 << " ____________________________________________________________________________________________________ " << endl
    	 << "| Digite 1 para alterar por nome, 2 para excluir por nome, 3 para adicionar e 4 para voltar ao menu: |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcaoescolherAlteracao;
    cin >> opcaoescolherAlteracao; // Lê a opção do usuário
    cin.ignore(); // Limpa o buffer

    if (opcaoescolherAlteracao == 1) { // Alterar por nome
        editarLista(lista, numRegistros);
    } else if (opcaoescolherAlteracao == 2) { // Excluir por nome
        excluirLista(lista, numRegistros);
    } else if (opcaoescolherAlteracao == 3) { // Adicionar novo jogador
        adicionarLista(lista, numRegistros, capacidade);
    } else if(opcaoescolherAlteracao == 4) { // Pergunta se quer voltar ao menu principal
        return; // Sai da função
    } else { // Se a opção for inválida
        displaydeOpcaoInvalida();
    }
}

// Função para exportar os dados para um arquivo
void exportarArquivo(sportlist* lista, int numRegistros) {
    limparTela();
    cout << " _______________________ " << endl
    	 << "| Exportacao de Arquivo |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl
    	 << " ______________________________________ " << endl
    	 << "| Digite 1 para CSV ou 2 para binario: |" << endl	
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcaoexportarArquivo;
    cin >> opcaoexportarArquivo; // Lê a opção do usuário

    if (opcaoexportarArquivo == 1) { // Exportar como CSV
        string nomeArquivoexportarArquivo;
        cout << " _____________________________________________________________ " << endl
        	 << "| Digite o nome do arquivo de exportacao (com extensao .csv): |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivoexportarArquivo; // Lê o nome do arquivo
        ofstream saida(nomeArquivoexportarArquivo); // Abre o arquivo para escrita
        saida << "Nome,Idade,Nacionalidade,Altura,Peso,Modalidade\n"; // Escreve o cabeçalho
        for (int i = 0; i < numRegistros; i++) { // Percorre a lista
            saida << lista[i].nome << ',' << lista[i].idade << ',' << lista[i].nacionalidade << ','
                  << lista[i].altura << ',' << lista[i].peso << ',' << lista[i].modalidade << '\n'; // Escreve os dados
        }
        saida.close(); // Fecha o arquivo
        cout << " _____________________________ " << endl
        	 << "| Arquivo exportado como CSV! |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcaoexportarArquivo == 2) { // Exportar como binário
        string nomeArquivoexportarArquivo;
        cout << " _____________________________________________________________ " << endl
        	 << "| Digite o nome do arquivo de exportacao (com extensao .dat): |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivoexportarArquivo; // Lê o nome do arquivo
        ofstream saida(nomeArquivoexportarArquivo, ios::binary); // Abre o arquivo para escrita em binário
        saida.write((char*)lista, numRegistros * sizeof(sportlist)); // Escreve os dados
        saida.close(); // Fecha o arquivo
        cout << " _________________________________ " << endl
        	 << "| Arquivo exportado como binario! |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else { // Se a opção for inválida
        displaydeOpcaoInvalida();
    }
}

// Função para imprimir ápos ordenar
void imprimeOrdenado(sportlist* lista, int numRegistros) {
    for (int i = 0; i < numRegistros; i++) {
        lista[i].imprime(); // Imprime os dados de todos os jogadores
    }
}

// Função para escolher o tipo de ordenação
bool escolherTipo(sportlist* lista, int numRegistros) {
    limparTela(); 
    int tipoOrdenacao;
	bool escolheuordenacao = true;
    cout << " ____________________________________________________ " << endl
    	 << "| Digite 1 para vizualizar por nome ou 2 para idade: |" << endl
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cin >> tipoOrdenacao;

    // Chama a função de ordenação correspondente
    if (tipoOrdenacao == 1) { 
        quickSort(lista, 0, numRegistros - 1, comparaPorNome); // Ordena por nome
    } else if(tipoOrdenacao == 2) {
        quickSort(lista, 0, numRegistros - 1, comparaPorIdade); // Ordena por idade
    } else {
		escolheuordenacao = false;
        displaydeOpcaoInvalida();
    }
	return escolheuordenacao;           
}

// Função para visualizar o arquivo todo por tipo de ordenação
void vizualizarPorOrde(sportlist* lista, int numRegistros) {
    if (escolherTipo(lista, numRegistros)){
    // Imprime a lista ordenada
    imprimeOrdenado(lista, numRegistros); // Chama a função para imprimir a lista ordenada
	}
}

// Função para visualizar um intervalo de atletas
void visualizarIntervalo(sportlist* lista, int numRegistros) {
    if (escolherTipo(lista, numRegistros)){
		limparTela(); 
		int inicio, fim;
		cout << " __________________________ " << endl
			 << "| Digite o índice inicial: |" << endl
			 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
		cin >> inicio; // Lê o índice inicial
		cout << " ________________________ " << endl
			 << "| Digite o índice final: |" << endl
			 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
		cin >> fim; // Lê o índice final

		// Verifica se o intervalo é válido
		if (inicio < 0 || fim >= numRegistros || inicio > fim) {
			cout << " _____________________ " << endl
				 << "| Intervalo inválido! |" << endl // Mensagem de erro para intervalo inválido
				 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
			return; // Sai da função
		}

		// Imprime os dados dos atletas no intervalo especificado
		for (int i = inicio; i <= fim; i++) {
			lista[i].imprime(); // Imprime os dados do jogador
		}
	}
}

// Função para salvar os dados em um arquivo binário ou CSV
void salvarDados(const string& nomeArquivo, sportlist* lista, int numRegistros) {
    // Verifica a extensão do arquivo
    if (nomeArquivo.find(".csv") != string::npos) {
        // Se o arquivo for CSV, abre o arquivo para escrita em texto
        ofstream saida(nomeArquivo);
        if (!saida) { // Verifica se o arquivo foi aberto corretamente
            cout << " _____________________________________ " << endl
            	 << "| Erro ao salvar os dados no arquivo! |" << endl 
            	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            return; // Sai da função
        }
        saida << "Nome,Idade,Nacionalidade,Altura,Peso,Modalidade\n"; // Escreve o cabeçalho
        for (int i = 0; i < numRegistros; i++) { // Percorre a lista
            saida << lista[i].nome << ',' 
                   << lista[i].idade << ',' 
                   << lista[i].nacionalidade << ',' 
                   << lista[i].altura << ',' 
                   << lista[i].peso << ',' 
                   << lista[i].modalidade << '\n'; // Escreve os dados
        }
        cout << " ____________________________________ " << endl 
        	 << "| Dados salvos como CSV com sucesso! |" << endl 
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (nomeArquivo.find(".dat") != string::npos) {
        // Se o arquivo for binário, abre o arquivo para escrita em binário
        ofstream saida(nomeArquivo, ios::binary | ios::trunc);
        if (!saida) { // Verifica se o arquivo foi aberto corretamente
            cout << " _____________________________________ " << endl
            	 << "| Erro ao salvar os dados no arquivo! |" << endl 
            	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            return; // Sai da função
        }
        for (int i = 0; i < numRegistros; i++) { // Percorre a lista
            saida.write((char*)&lista[i], sizeof(sportlist)); // Escreve os dados no arquivo
        }
        cout << " ________________________________________ " << endl
        	 << "| Dados salvos como binário com sucesso! |" << endl 
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else {
        cout << " _____________________________________ " << endl
        	 << "| Erro: Extensao de arquivo invalida! |" << endl 
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

// Função para exibir o menu principal e gerenciar as opções do usuário
void exibirMenu(sportlist*& lista, int& numRegistros, int& capacidade, const string& nomeArquivo) {
    bool continuarMenu = true; // Controle do loop do menu
    while (continuarMenu) {
        limparTela(); 
        displayMenuPrincipal();
        int opcaoexibirMenu;
        cin >> opcaoexibirMenu; 
        cin.ignore(); // Limpa o buffer

        switch (opcaoexibirMenu) { // Switch do menu
            case 1:
                buscaBinaria(lista, numRegistros); // Chama a função de busca binária
                break;
            case 2:
                escolherAlteracao(lista, numRegistros, capacidade); // Chama a função para alterar a lista
                break;
            case 3:
                exportarArquivo(lista, numRegistros); // Chama a função para exportar o arquivo
                break;
            case 4:
                vizualizarPorOrde(lista, numRegistros); // Chama a função para escolher o tipo de ordenação
                break;
            case 5: 
                visualizarIntervalo(lista, numRegistros); // Chama a função para visualizar um intervalo de atletas
                break;
            case 6:
                displaySalvarAlterações();
                char salvarAlterações;
                cin >> salvarAlterações; 
                if (salvarAlterações == 's' || salvarAlterações == 'S') {
                    salvarDados(nomeArquivo, lista, numRegistros); // Salva os dados se confirmado
                }
                displayEncerrarPrograma();
                continuarMenu = false; // Sai do loop
                break;
            default:    
				displaydeOpcaoInvalida();
        }

        if (continuarMenu) { // Se o menu continuar
            cout << " _________________________________________ " << endl
            	 << "| Deseja voltar ao menu principal? (s/n): |" << endl
            	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            char continuarExibirMenu;
            cin >> continuarExibirMenu; // Lê a confirmação para voltar ao menu
            if (continuarExibirMenu != 's' && continuarExibirMenu != 'S') {
                limparTela();
                displaySalvarAlterações();
                char salvarExibirMenu;
                cin >> salvarExibirMenu; // Lê a confirmação para salvar
                if (salvarExibirMenu == 's' || salvarExibirMenu == 'S') {
                    salvarDados(nomeArquivo, lista, numRegistros); // Salva os dados se confirmado
                }
                displayEncerrarPrograma();
                continuarMenu = false; // Sai do loop
            }
        }
    }
}

// Função principal do programa
int main() {
    limparTela(); 
    cout << " ___________________________________________________ " << endl
    	 << "| Bem-vindo ao sistema de gerenciamento de atletas! |" << endl 
    	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

    string nomeArquivo; // Variavel para o nome do arquivo 
    int numRegistros = 0, capacidade = 40; // Inicializa o número de registros e a capacidade
    sportlist* lista = nullptr; // Ponteiro para a lista de atletas
    bool arquivoAberto = false; // Controle da abertura do arquivo

    while (!arquivoAberto) { // Loop para abrir o arquivo
        cout << " ___________________________________________________________________________ " << endl
        	 << "| Digite o nome do arquivo que deseja carregar (com extensao .csv ou .dat): |" << endl
        	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivo; // Lê o nome do arquivo

        lista = lerDados(nomeArquivo, numRegistros, capacidade); // Lê os dados do arquivo

        if (lista) { // Verifica se a leitura foi bem-sucedida
            arquivoAberto = true; // Marca que o arquivo foi aberto
        } else { // Se a leitura falhou
            limparTela(); 
            cout << " ____________________________________________________________________________________________________________ " << endl
            	 << "| Nao foi possivel abrir o arquivo especificado. Certifique-se de que o nome esta correto e tente novamente. |" << endl
            	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

            char tentarNovamente; // Variável para tentar abrir outro arquivo
            cout << " ___________________________________________ " << endl
            	 << "| Deseja tentar abrir outro arquivo? (s/n): |" << endl
            	 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            cin >> tentarNovamente; // Lê a confirmação

            if (tentarNovamente != 's' && tentarNovamente != 'S') { // Se não tentar novamente
                limparTela();
                displayEncerrarPrograma(); // Encerra programa
                return 0; 
            } else {
                limparTela();
            }
        }
    }

    exibirMenu(lista, numRegistros, capacidade, nomeArquivo); // Chama a função do menu

    delete[] lista; // Libera a memória alocada para a lista
    return 0; 
}