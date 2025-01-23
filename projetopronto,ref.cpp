#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <locale>




using namespace std;

struct sportlist {
    char nome[30];
    int idade;
    char nacionalidade[20];
    float altura;
    int peso;
    char modalidade[20];

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

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool lerUmaUnicaLinha(ifstream& entrada, sportlist& algumsportlist) {
    char virgula;
    return entrada.getline(algumsportlist.nome, 30, ',')
           && (entrada >> algumsportlist.idade >> virgula)
           && (entrada.getline(algumsportlist.nacionalidade, 20, ','))
           && (entrada >> algumsportlist.altura >> virgula)
           && (entrada >> algumsportlist.peso >> virgula)
           && (entrada.getline(algumsportlist.modalidade, 20));
}

sportlist* lerDados(const string& nomeArquivo, int& numRegistros, int& capacidade) {
    ifstream entrada(nomeArquivo, nomeArquivo.find(".csv") != string::npos ? ios::in : ios::binary);
    if (!entrada) {
        return NULL;
    }

    sportlist* vetorSportlist = new sportlist[capacidade];
    sportlist algumsportlist;

    if (nomeArquivo.find(".csv") != string::npos) {
        string descArquivo;
        getline(entrada, descArquivo);
        while (lerUmaUnicaLinha(entrada, algumsportlist)) {
            if (numRegistros >= capacidade) {
                capacidade += 20;
                sportlist* novo = new sportlist[capacidade];
                memcpy(novo, vetorSportlist, numRegistros * sizeof(sportlist));
                delete[] vetorSportlist;
                vetorSportlist = novo;
            }
            vetorSportlist[numRegistros] = algumsportlist;
            numRegistros++;
        }
    } else {
        while (entrada.read((char*)&algumsportlist, sizeof(sportlist))) {
            if (numRegistros >= capacidade) {
                capacidade += 20;
                sportlist* novo = new sportlist[capacidade];
                memcpy(novo, vetorSportlist, numRegistros * sizeof(sportlist));
                delete[] vetorSportlist;
                vetorSportlist = novo;
            }
            vetorSportlist[numRegistros] = algumsportlist;
            numRegistros++;
        }
    }

    return vetorSportlist;
}

// Função para converter uma string para minúsculas
std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// Função para verificar se o nome contém a chave de busca
bool matches(const std::string& name, const std::string& search) {
    return to_lower(name).find(to_lower(search)) != std::string::npos;
}

void buscaBinaria(sportlist* lista, int numRegistros) {
    limparTela();
    cout << " _______________ " << endl;
    cout << "| Busca Binaria |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " ________________________________________________________________ " << endl;
    cout << "| Digite 1 para buscar por nome ou 2 para buscar por modalidade: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1 || opcao == 2) {
        char chave[30];
        cout << " ____________________________ " << endl;
        cout << "| Digite o termo para busca: |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30);

        if (opcao == 1) {
            // Busca por nome (insensitive + substrings)
            bool encontrado = false;
            for (int i = 0; i < numRegistros; i++) {
                if (matches(lista[i].nome, chave)) {
                    lista[i].imprime();
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << " ____________________________ " << endl;
                cout << "| Nenhum jogador encontrado. |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            }
        } else if (opcao == 2) {
            // Busca por modalidade (insensitive + substrings)
            bool encontrado = false;
            for (int i = 0; i < numRegistros; i++) {
                if (matches(lista[i].modalidade, chave)) {
                    lista[i].imprime();
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << " ___________________________________________________________ " << endl;
                cout << "| Nenhum jogador encontrado para a modalidade especificada. |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            }
        }
    } else {
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |"<< endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

void alterarLista(sportlist*& lista, int& numRegistros, int& capacidade) {
    limparTela();
    cout << " ____________________ " << endl;
    cout << "| Alteracao na lista |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " __________________________________________________________ " << endl;
    cout << "| Digite 1 para alterar, 2 para excluir, 3 para adicionar: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        char chave[30];
        cout << " __________________________________________ " << endl;
        cout << "| Digite o nome do jogador a ser alterado: |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30);
        
        for (int i = 0; i < numRegistros; i++) {
            if (matches(lista[i].nome, chave)) {
                cout << " __________________________________________________________________________________________ " << endl;
                cout << "| Digite os novos dados do jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                cout << "_____________________________________________" << endl;
                cout << " Nome: "; cin.getline(lista[i].nome, 30); // Nome
                cout << " Idade: "; cin >> lista[i].idade; cin.ignore(); // Idade
                cout << " Nacionalidade: "; cin.getline(lista[i].nacionalidade, 20); // Nacionalidade
                cout << " Altura: "; cin >> lista[i].altura; // Altura
                cout << " Peso: "; cin >> lista[i].peso; cin.ignore(); // Peso
                cout << " Modalidade: "; cin.getline(lista[i].modalidade, 20); // Modalidade
                cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
                cout << " ______________________________ " << endl;
                cout << "| Dados alterados com sucesso! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                return;
            }
        }
        cout << " _________________________ " << endl;
        cout << "| Jogador nao encontrado! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 2) {
        char chave[30];
        cout << " __________________________________________ " << endl;
        cout << "| Digite o nome do jogador a ser excluido: |"<< endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin.getline(chave, 30);

        for (int i = 0; i < numRegistros; i++) {
            if (matches(lista[i].nome, chave)) {
                char confirmacao;
                cout << " _________________________________________ " << endl;
                cout << "| Você realmente deseja exclui-lo? (s/n): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                cin >> confirmacao;
                cin.ignore(); // Limpa o buffer

                if (confirmacao == 's' || confirmacao == 'S') {
                    for (int j = i; j < numRegistros - 1; j++) {
                        lista[j] = lista[j + 1];
                    }
                    numRegistros--;
                    cout << " _______________________________ " << endl;
                    cout << "| Jogador excluido com sucesso! |" << endl;
                    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                } else {
                    cout << " _____________________ " << endl;
                    cout << "| Exclusão cancelada. |" << endl;
                    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                }
                return;
            }
        }
        cout << " _________________________ " << endl;
        cout << "| Jogador nao encontrado! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 3) {
        if (numRegistros >= capacidade) {
            capacidade += 20;
            sportlist* novo = new sportlist[capacidade];
            memcpy(novo, lista, numRegistros * sizeof(sportlist));
            delete[] lista;
            lista = novo;
        }
        cout << " _________________________________________________________________________________________ " << endl;
        cout << "| Digite os dados do novo jogador (nome, idade, nacionalidade, altura, peso, modalidade): |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cout << "_____________________________________________" << endl;
        cout << " Nome: "; cin.getline(lista[numRegistros].nome, 30); // Nome
        cout << " Idade: "; cin >> lista[numRegistros].idade; cin.ignore(); // Idade
        cout << " Nacionalidade: "; cin.getline(lista[numRegistros].nacionalidade, 20); // Nacionalidade
        cout << " Altura: "; cin >> lista[numRegistros].altura; // Altura
        cout << " Peso: "; cin >> lista[numRegistros].peso; cin.ignore(); // Peso
        cout << " Modalidade: "; cin.getline(lista[numRegistros].modalidade, 20); // Modalidade
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
        numRegistros++;
        cout << " _________________________________ " << endl;
        cout << "| Jogador adicionado com sucesso! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else {
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

void exportarArquivo(sportlist* lista, int numRegistros) {
    limparTela();
    cout << " _______________________ " << endl;
    cout << "| Exportacao de Arquivo |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    cout << " ______________________________________ " << endl;
    cout << "| Digite 1 para CSV ou 2 para binario: |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    int opcao;
    cin >> opcao;

    if (opcao == 1) {
        ofstream saida("arquivo_exportado.csv");
        saida << "Nome,Idade,Nacionalidade,Altura,Peso,Modalidade\n";
        for (int i = 0; i < numRegistros; i++) {
            saida << lista[i].nome << ',' << lista[i].idade << ',' << lista[i].nacionalidade << ','
                  << lista[i].altura << ',' << lista[i].peso << ',' << lista[i].modalidade << '\n';
        }
        saida.close();
        cout << " _____________________________ " << endl;
        cout << "| Arquivo exportado como CSV! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else if (opcao == 2) {
        ofstream saida("arquivo_exportado.dat", ios::binary);
        saida.write((char*)lista, numRegistros * sizeof(sportlist));
        saida.close();
        cout << " _________________________________ " << endl;
        cout << "| Arquivo exportado como binario! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    } else {
        cout << " _________________ " << endl;
        cout << "| Opcao invalida! |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
    }
}

void exibirMenu(sportlist*& lista, int& numRegistros, int& capacidade) {
    while (true) {
        limparTela();
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
             << "| 5. Sair                |" << endl
			 << "|————————————————————————|" << endl
			 << "| Escolha uma opcao:     |" << endl
			 << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

        int opcao;
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                buscaBinaria(lista, numRegistros);
                break;
            case 2:
                alterarLista(lista, numRegistros, capacidade);
                break;
            case 3:
                exportarArquivo(lista, numRegistros);
                break;
            case 4:
                limparTela();
                for (int i = 0; i < numRegistros; i++) {
                    lista[i].imprime();
                }
                break;
            case 5:
                cout << " ___________________________________________________ " << endl;
                cout << "| Deseja salvar as alteracoes antes de sair? (s/n): |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                char salvar;
                cin >> salvar;
                if (salvar == 's' || salvar == 'S') {
                    exportarArquivo(lista, numRegistros);
                }
                cout << " _____________________ " << endl;
                cout << "| Programa encerrado! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                return;
            default:    
                cout << " _________________ " << endl;
                cout << "| Opcao invalida! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        }

        cout << " _________________________________________ " << endl;
        cout << "| Deseja voltar ao menu principal? (s/n): |"  << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        char continuar;
        cin >> continuar;
        if (continuar != 's' && continuar != 'S') {
            cout << " ___________________________________________________ " << endl;
            cout << "| Deseja salvar as alteracoes antes de sair? (s/n): |"  << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            char salvar;
            cin >> salvar;
            if (salvar == 's' || salvar == 'S') {
                exportarArquivo(lista, numRegistros);
            }
            cout << " _____________________ " << endl;
            cout << "| Programa encerrado! |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            break;
        }
    }
}

int main() {
    limparTela();
    cout << " ___________________________________________________ " << endl;
    cout << "| Bem-vindo ao sistema de gerenciamento de atletas! |" << endl;
    cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

    string nomeArquivo;
    int numRegistros = 0, capacidade = 50;
    sportlist* lista = nullptr;
    bool arquivoAberto = false; // Variável de controle

    while (!arquivoAberto) {
        cout << " ___________________________________________________________________________ " << endl;
        cout << "| Digite o nome do arquivo que deseja carregar (com extensao .csv ou .dat): |"  << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
        cin >> nomeArquivo;

        lista = lerDados(nomeArquivo, numRegistros, capacidade);

        if (lista) {
            arquivoAberto = true; 
        } else {
            limparTela();
            cout << " ____________________________________________________________________________________________________________ " << endl;
            cout << "| Nao foi possivel abrir o arquivo especificado. Certifique-se de que o nome esta correto e tente novamente. |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;

            char tentarNovamente;
            cout << " ___________________________________________ " << endl;
            cout << "| Deseja tentar abrir outro arquivo? (s/n): |" << endl;
            cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
            cin >> tentarNovamente;
            cin.ignore(); 

            if (tentarNovamente != 's' && tentarNovamente != 'S') {
                limparTela();
                cout << " _____________________ " << endl;
                cout << "| Programa encerrado! |" << endl;
                cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << endl;
                return 0; 
            } else {
                limparTela();
            }
        }
    }

    exibirMenu(lista, numRegistros, capacidade);

    delete[] lista;
    return 0;
}