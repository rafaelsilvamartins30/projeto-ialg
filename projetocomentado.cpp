#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <locale>

using namespace std;

// Estrutura que representa um atleta
struct sportlist {
    char nome[30];           // Nome do jogador
    int idade;              // Idade do jogador
    char nacionalidade[20]; // Nacionalidade do jogador
    float altura;           // Altura do jogador
    int peso;               // Peso do jogador
    char modalidade[20];    // Modalidade esportiva do jogador

    // Método para imprimir os dados do jogador
    void imprime() {
        cout << "_____________________________________________" << endl;
        cout << " Nome do Jogador: " << nome << endl;
        cout << " Idade do Jogador: " << idade << endl;
        cout << " Nacionalidade do Jogador: " << nacionalidade << endl;
        cout << " Altura do Jogador: " << altura << endl;
        cout << " Peso do Jogador: " << peso << endl;
        cout << " Modalidade do Jogador: " << modalidade << endl;
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
    }
};

// Função para limpar a tela do console
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para outros sistemas operacionais
    #endif
}

// Função para ler uma única linha do arquivo e preencher os dados do atleta
bool lerUmaUnicaLinha(ifstream& entrada, sportlist& algumsportlist) {
    char virgula; // Variável para armazenar a vírgula
    return entrada.getline(algumsportlist.nome, 30, ',') // Lê o nome até a vírgula
           && (entrada >> algumsportlist.idade >> virgula) // Lê a idade
           && (entrada.getline(algumsportlist.nacionalidade, 20, ',')) // Lê a nacionalidade
           && (entrada >> algumsportlist.altura >> virgula) // Lê a altura
           && (entrada >> algumsportlist.peso >> virgula) // Lê o peso
           && (entrada.getline(algumsportlist.modalidade, 20)); // Lê a modalidade
}

// Função para ler os dados de um arquivo e armazená-los em um vetor de sportlist
sportlist* lerDados(const string& nomeArquivo, int& numRegistros, int& capacidade) {
    // Abre o arquivo para leitura
    ifstream entrada(nomeArquivo, nomeArquivo.find(".csv") != string::npos ? ios::in : ios::binary);
    if (!entrada) {
        return NULL; // Retorna NULL se o arquivo não puder ser aberto
    }

    // Aloca memória para o vetor de sportlist
    sportlist* vetorSportlist = new sportlist[capacidade];
    sportlist algumsportlist; // Variável temporária para armazenar os dados lidos

    // Se o arquivo for CSV, lê os dados linha por linha
    if (nomeArquivo.find(".csv") != string::npos) {
        string descArquivo;
        getline(entrada, descArquivo); // Lê a primeira linha (cabeçalho)
        while (lerUmaUnicaLinha(entrada, algumsportlist)) { // Lê os dados dos atletas
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
    } else { // Se o arquivo não for CSV, lê os dados binários
        while (entrada.read((char*)&algumsportlist, sizeof(sportlist))) { // Lê os dados dos atletas
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
    }

    return vetorSportlist; // Retorna o vetor de sportlist
}

// Função para converter uma string para minúsculas
std::string to_lower(const std::string& str) {
    std::string lower_str = str; // Cria uma cópia da string
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower); // Converte para minúsculas
    return lower_str; // Retorna a string em minúsculas
}

// Função para verificar se o nome contém a chave de busca
bool matches(const std::string& name, const std::string& search) {
    return to_lower(name).find(to_lower(search)) != std::string::npos; // Retorna true se a chave for encontrada
}

// Função para realizar busca binária na lista de atletas
void buscaBinaria(sportlist* lista, int numRegistros) {
    limparTela(); // Limpa a tela
    cout << " _______________ " << endl;
    cout << "| Busca Binaria |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " ________________________________________________________________ " << endl;
    cout << "| Digite 1 para buscar por nome ou 2 para buscar por modalidade: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao; // Lê a opção do usuário
    cin.ignore(); // Limpa o buffer

    if (opcao == 1 || opcao == 2) { // Se a opção for válida
        char chave[30]; // Variável para armazenar a chave de busca
        cout << " ____________________________ " << endl;
        cout << "| Digite o termo para busca: |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30); // Lê a chave de busca

        if (opcao == 1) { // Busca por nome
            bool encontrado = false; // Flag para verificar se encontrou
            for (int i = 0; i < numRegistros; i++) { // Percorre a lista
                if (matches(lista[i].nome, chave)) { // Verifica se o nome corresponde à chave
                    lista[i].imprime(); // Imprime os dados do jogador
                    encontrado = true; // Marca como encontrado
                }
            }
            if (!encontrado) { // Se não encontrou
                cout << " ____________________________ " << endl;
                cout << "| Nenhum jogador encontrado. |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            }
        } else if (opcao == 2) { // Busca por modalidade
            bool encontrado = false; // Flag para verificar se encontrou
            for (int i = 0; i < numRegistros; i++) { // Percorre a lista
                if (matches(lista[i].modalidade, chave)) { // Verifica se a modalidade corresponde à chave
                    lista[i].imprime(); // Imprime os dados do jogador
                    encontrado = true; // Marca como encontrado
                }
            }
            if (!encontrado) { // Se não encontrou
                cout << " ___________________________________________________________ " << endl;
                cout << "| Nenhum jogador encontrado para a modalidade especificada. |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            }
        }
    } else { // Se a opção for inválida
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

// Função para alterar a lista de atletas
void alterarLista(sportlist*& lista, int& numRegistros, int& capacidade) {
    limparTela(); // Limpa a tela
    cout << " ____________________ " << endl;
    cout << "| Alteracao na lista |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " ____________________________________________________________________________________________________ " << endl;
    cout << "| Digite 1 para alterar por nome, 2 para excluir por nome, 3 para adicionar e 4 para voltar ao menu: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao; // Lê a opção do usuário
    cin.ignore(); // Limpa o buffer

    if (opcao == 1) { // Alterar por nome
        char chave[30]; // Variável para armazenar o nome do jogador a ser alterado
        cout << " ___________________________________________________ " << endl;
        cout << "| Digite o nome completo do jogador a ser alterado: |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30); // Lê o nome do jogador

        int i = 0; // Índice para percorrer a lista
        while (i < numRegistros) { // Percorre a lista
            if (matches(lista[i].nome, chave)) { // Verifica se o nome corresponde à chave
                cout << " __________________________________________________________________________________________ " << endl;
                cout << "| Digite os novos dados do jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                cout << "_____________________________________________" << endl;
                cout << " Nome: "; cin.getline(lista[i].nome, 30); // Lê o novo nome
                cout << " Idade: "; cin >> lista[i].idade; cin.ignore(); // Lê a nova idade
                cout << " Nacionalidade: "; cin.getline(lista[i].nacionalidade, 20); // Lê a nova nacionalidade
                cout << " Altura: "; cin >> lista[i].altura; // Lê a nova altura
                cout << " Peso: "; cin >> lista[i].peso; cin.ignore(); // Lê o novo peso
                cout << " Modalidade: "; cin.getline(lista[i].modalidade, 20); // Lê a nova modalidade
                cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
                cout << " ______________________________ " << endl;
                cout << "| Dados alterados com sucesso! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                return; // Sai da função
            }
            i++; // Incrementa o índice
        }
        cout << " _________________________ " << endl;
        cout << "| Jogador nao encontrado! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 2) { // Excluir por nome
        char chave[30]; // Variável para armazenar o nome do jogador a ser excluído
        cout << " ___________________________________________________ " << endl;
        cout << "| Digite o nome completo do jogador a ser excluido: |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30); // Lê o nome do jogador

        int i = 0; // Índice para percorrer a lista
        while (i < numRegistros) { // Percorre a lista
            if (matches(lista[i].nome, chave)) { // Verifica se o nome corresponde à chave
                char confirmacao; // Variável para confirmação da exclusão
                cout << " _________________________________________ " << endl;
                cout << "| Você realmente deseja exclui-lo? (s/n): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                cin >> confirmacao; // Lê a confirmação
                cin.ignore(); // Limpa o buffer

                if (confirmacao == 's' || confirmacao == 'S') { // Se confirmado
                    for (int j = i; j < numRegistros - 1; j++) { // Move os elementos para excluir o jogador
                        lista[j] = lista[j + 1];
                    }
                    numRegistros--; // Decrementa o número de registros
                    cout << " _______________________________ " << endl;
                    cout << "| Jogador excluido com sucesso! |" << endl;
                    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                } else { // Se não confirmado
                    cout << " _____________________ " << endl;
                    cout << "| Exclusão cancelada. |" << endl;
                    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                }
                return; // Sai da função
            }
            i++; // Incrementa o índice
        }
        cout << " _________________________ " << endl;
        cout << "| Jogador nao encontrado! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 3) { // Adicionar novo jogador
        if (numRegistros >= capacidade) { // Verifica se é necessário aumentar a capacidade
            capacidade += 10; // Aumenta a capacidade
            sportlist* novo = new sportlist[capacidade]; // Aloca novo vetor
            memcpy(novo, lista, numRegistros * sizeof(sportlist)); // Copia os dados antigos
            delete[] lista; // Libera a memória do vetor antigo
            lista = novo; // Atualiza o ponteiro
        }
        cout << " _________________________________________________________________________________________ " << endl;
        cout << "| Digite os dados do novo jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cout << "_____________________________________________" << endl;
        cout << " Nome: "; cin.getline(lista[numRegistros].nome, 30); // Lê o nome do novo jogador
        cout << " Idade: "; cin >> lista[numRegistros].idade; cin.ignore(); // Lê a idade
        cout << " Nacionalidade: "; cin.getline(lista[numRegistros].nacionalidade, 20); // Lê a nacionalidade
        cout << " Altura: "; cin >> lista[numRegistros].altura; // Lê a altura
        cout << " Peso: "; cin >> lista[numRegistros].peso; cin.ignore(); // Lê o peso
        cout << " Modalidade: "; cin.getline(lista[numRegistros].modalidade, 20); // Lê a modalidade
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
        numRegistros++; // Incrementa o número de registros
        cout << " _________________________________ " << endl;
        cout << "| Jogador adicionado com sucesso! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if(opcao == 4) { //pergunta se quer voltar ao menu principal
        return;
    }else { // Se a opção for inválida
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

// Função para exportar os dados para um arquivo
void exportarArquivo(sportlist* lista, int numRegistros) {
    limparTela(); // Limpa a tela
    cout << " _______________________ " << endl;
    cout << "| Exportacao de Arquivo |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " ______________________________________ " << endl;
    cout << "| Digite 1 para CSV ou 2 para binario: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao; // Lê a opção do usuário

    if (opcao == 1) { // Exportar como CSV
        string nomeArquivo;
        cout << " _____________________________________________________________ " << endl;
        cout << "| Digite o nome do arquivo de exportacao (com extensao .csv): |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivo; // Lê o nome do arquivo
        ofstream saida(nomeArquivo); // Abre o arquivo para escrita
        saida << "Nome,Idade,Nacionalidade,Altura,Peso,Modalidade\n"; // Escreve o cabeçalho
        for (int i = 0; i < numRegistros; i++) { // Percorre a lista
            saida << lista[i].nome << ',' << lista[i].idade << ',' << lista[i].nacionalidade << ','
                  << lista[i].altura << ',' << lista[i].peso << ',' << lista[i].modalidade << '\n'; // Escreve os dados
        }
        saida.close(); // Fecha o arquivo
        cout << " _____________________________ " << endl;
        cout << "| Arquivo exportado como CSV! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 2) { // Exportar como binário
        string nomeArquivo;
        cout << " _____________________________________________________________ " << endl;
        cout << "| Digite o nome do arquivo de exportacao (com extensao .dat): |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivo; // Lê o nome do arquivo
        ofstream saida(nomeArquivo, ios::binary); // Abre o arquivo para escrita em binário
        saida.write((char*)lista, numRegistros * sizeof(sportlist)); // Escreve os dados
        saida.close(); // Fecha o arquivo
        cout << " _________________________________ " << endl;
        cout << "| Arquivo exportado como binario! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else { // Se a opção for inválida
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}
// Função para comparar dois atletas pelo nome (para ordenação)
bool comparaPorNome(const sportlist& a, const sportlist& b) {
    return strcmp(a.nome, b.nome) < 0; // Ordena em ordem alfabética
}

// Função para comparar dois atletas pela idade (para ordenação)
bool comparaPorIdade(const sportlist& a, const sportlist& b) {
    return a.idade < b.idade; // Ordena por idade
}

// Função para comparar dois atletas pela modalidade (para ordenação)
bool comparaPorModalidade(const sportlist& a, const sportlist& b) {
    return strcmp(a.modalidade, b.modalidade) < 0; // Ordena por modalidade
}

void imprimeordenado(sportlist* lista, int numRegistros) {
    for (int i = 0; i < numRegistros; i++) {
        lista[i].imprime(); // Imprime os dados de todos os jogadores
    }
}

// Função de Quick Sort
void quickSort(sportlist* lista, int esquerda, int direita, bool (*compara)(const sportlist&, const sportlist&)) {
    int i = esquerda, j = direita;
    sportlist pivo = lista[(esquerda + direita) / 2];

    while (i <= j) {
        while (compara(lista[i], pivo)) i++;
        while (compara(pivo, lista[j])) j--;
        if (i <= j) {
            swap(lista[i], lista[j]);
            i++;
            j--;
        }
    }

    if (esquerda < j) quickSort(lista, esquerda, j, compara);
    if (i < direita) quickSort(lista, i, direita, compara);
}

void escolhertipo(sportlist* lista, int numRegistros){
    limparTela(); // Limpa a tela
    int tipoOrdenacao;
    cout << " _____________________________________________________________________________________ " << endl;
    cout << "| Digite 1 para vizualizar por nome, 2 para idade, 3 para modalidade e 4 para voltar: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cin >> tipoOrdenacao;

    // Chama a função de ordenação correspondente
    if (tipoOrdenacao == 1) { 
        quickSort(lista, 0, numRegistros - 1, comparaPorNome);
                    
    }else if(tipoOrdenacao == 2){
        quickSort(lista, 0, numRegistros - 1, comparaPorIdade);
                   
    }else if(tipoOrdenacao == 3){
        quickSort(lista, 0, numRegistros - 1, comparaPorModalidade);
                  
    }else{
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }           
    // Imprime a lista ordenada
    imprimeordenado(lista, numRegistros);
}
void visualizarIntervalo(sportlist* lista, int numRegistros) {
    limparTela();
    int inicio, fim;
    cout << " __________________________ " << endl;
    cout << "| Digite o índice inicial: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cin >> inicio;
    cout << " ________________________ " << endl;
    cout << "| Digite o índice final: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cin >> fim;

    if (inicio < 0 || fim >= numRegistros || inicio > fim) {
        cout << " _____________________ " << endl
             << "| Intervalo inválido! |" << endl
             << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        return;
    }

    for (int i = inicio; i <= fim; i++) {
        lista[i].imprime(); // Imprime os dados do jogador
    }
}

// Função para salvar os dados em um arquivo binário
void salvarDados(const string& nomeArquivo, sportlist* lista, int numRegistros) {
    // Verifica a extensão do arquivo
    if (nomeArquivo.find(".csv") != string::npos) {
        // Se o arquivo for CSV, abre o arquivo para escrita em texto
        ofstream saida(nomeArquivo);
        if (!saida) { // Verifica se o arquivo foi aberto corretamente
            cout << " _____________________________________ " << endl;
            cout << "| Erro ao salvar os dados no arquivo! |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
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
        cout << " ____________________________________ " << endl;
        cout << "| Dados salvos como CSV com sucesso! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (nomeArquivo.find(".dat") != string::npos) {
        // Se o arquivo for binário, abre o arquivo para escrita em binário
        ofstream saida(nomeArquivo, ios::binary | ios::trunc);
        if (!saida) { // Verifica se o arquivo foi aberto corretamente
            cout << " _____________________________________ " << endl;
            cout << "| Erro ao salvar os dados no arquivo! |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            return; // Sai da função
        }
        for (int i = 0; i < numRegistros; i++) { // Percorre a lista
            saida.write((char*)&lista[i], sizeof(sportlist)); // Escreve os dados no arquivo
        }
        cout << " ________________________________________ " << endl;
        cout << "| Dados salvos como binário com sucesso! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else {
        cout << " _____________________________________ " << endl;
        cout << "| Erro: Extensao de arquivo invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

// Função para exibir o menu principal e gerenciar as opções do usuário
void exibirMenu(sportlist*& lista, int& numRegistros, int& capacidade, const string& nomeArquivo) {
    bool continuarMenu = true; // Flag para controlar o loop do menu
    while (continuarMenu) {
        limparTela(); // Limpa a tela
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

        int opcao;
        cin >> opcao; // Lê a opção do usuário
        cin.ignore(); // Limpa o buffer

        switch (opcao) {
            case 1:
                buscaBinaria(lista, numRegistros); // Chama a função de busca binária
                break;
            case 2:
                alterarLista(lista, numRegistros, capacidade); // Chama a função para alterar a lista
                break;
            case 3:
                exportarArquivo(lista, numRegistros); // Chama a função para exportar o arquivo
                break;
            case 4:
                escolhertipo(lista, numRegistros);
                break;
            case 5: 
                visualizarIntervalo(lista, numRegistros); 
                break;
            case 6:
                cout << " ___________________________________________________ " << endl;
                cout << "| Deseja salvar as alteracoes antes de sair? (s/n): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                char salvar;
                cin >> salvar; // Lê a confirmação para salvar
                if (salvar == 's' || salvar == 'S') {
                    salvarDados(nomeArquivo, lista, numRegistros); // Salva os dados se confirmado
                }
                cout << " _____________________ " << endl;
                cout << "| Programa encerrado! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                continuarMenu = false; // Sai do loop
                break;
            default:    
                cout << " _________________ " << endl;
                cout << "| Opcao invalida! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        }

        if (continuarMenu) { // Se o menu continuar
            cout << " _________________________________________ " << endl;
            cout << "| Deseja voltar ao menu principal? (s/n): |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            char continuar;
            cin >> continuar; // Lê a confirmação para voltar ao menu
            if (continuar != 's' && continuar != 'S') {
                cout << " ___________________________________________________ " << endl;
                cout << "| Deseja salvar as alteracoes antes de sair? (s/n): |"  << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                char salvar;
                cin >> salvar; // Lê a confirmação para salvar
                if (salvar == 's' || salvar == 'S') {
                    salvarDados(nomeArquivo, lista, numRegistros); // Salva os dados se confirmado
                }
                cout << " _____________________ " << endl;
                cout << "| Programa encerrado! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                continuarMenu = false; // Sai do loop
            }
        }
    }
}

// Função principal do programa
int main() {
    limparTela(); // Limpa a tela
    cout << " ___________________________________________________ " << endl;
    cout << "| Bem-vindo ao sistema de gerenciamento de atletas! |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

    string nomeArquivo; // Nome do arquivo a ser carregado
    int numRegistros = 0, capacidade = 40; // Inicializa o número de registros e a capacidade
    sportlist* lista = nullptr; // Ponteiro para a lista de atletas
    bool arquivoAberto = false; // Flag para controlar a abertura do arquivo

    while (!arquivoAberto) { // Loop para abrir o arquivo
        cout << " ___________________________________________________________________________ " << endl;
        cout << "| Digite o nome do arquivo que deseja carregar (com extensao .csv ou .dat): |"  << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivo; // Lê o nome do arquivo

        lista = lerDados(nomeArquivo, numRegistros, capacidade); // Lê os dados do arquivo

        if (lista) { // Se a leitura foi bem-sucedida
            arquivoAberto = true; // Marca que o arquivo foi aberto
        } else { // Se a leitura falhou
            limparTela(); // Limpa a tela
            cout << " ____________________________________________________________________________________________________________ " << endl;
            cout << "| Nao foi possivel abrir o arquivo especificado. Certifique-se de que o nome esta correto e tente novamente. |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

            char tentarNovamente; // Variável para tentar abrir outro arquivo
            cout << " ___________________________________________ " << endl;
            cout << "| Deseja tentar abrir outro arquivo? (s/n): |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            cin >> tentarNovamente; // Lê a confirmação

            if (tentarNovamente != 's' && tentarNovamente != 'S') { // Se não tentar novamente
                limparTela(); // Limpa a tela
                cout << " _____________________ " << endl;
                cout << "| Programa encerrado! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                return 0; // Encerra o programa
            } else {
                limparTela(); // Limpa a tela
            }
        }
    }

    exibirMenu(lista, numRegistros, capacidade, nomeArquivo); // Chama a função para exibir o menu

    delete[] lista; // Libera a memória alocada para a lista
    return 0; // Encerra o programa
}