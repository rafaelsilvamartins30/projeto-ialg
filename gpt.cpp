#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>



using namespace std;

struct sportlist {
    char nome[30];
    int idade;
    char nacionalidade[20];
    float altura;
    int peso;
    char modalidade[20];

    void imprime() {
        const int largura = 45;
        
        // Convertendo a altura para string com precisão
        stringstream ss;
        ss << fixed << setprecision(2) << altura;
        string alturaStr = ss.str()+ " M";
        
        // Convertendo a idade e peso para string
        string idadeStr = to_string(idade) + " Anos";
        string pesoStr = to_string(peso) + " KG";

        // Calculando a largura dinamicamente para as strings
        cout << " _____________________________________________" << endl;
        cout << "| Nome do Jogador: " << left << setw(largura - 19) << nome << " |" << endl;
        cout << "| Idade do Jogador: " << left << setw(largura - 20) << idadeStr << " |" << endl;
        cout << "| Nacionalidade do Jogador: " << left << setw(largura - 28) << nacionalidade << " |" << endl;
        cout << "| Altura do Jogador: " << left << setw(largura - 21) << alturaStr << " |" << endl;
        cout << "| Peso do Jogador: " << left << setw(largura - 19) << pesoStr << " |" << endl;
        cout << "| Modalidade do Jogador: " << left << setw(largura - 25) << modalidade << " |" << endl;
        cout << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
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

void buscaBinaria(sportlist* lista, int numRegistros) {
    limparTela();
    cout << "Busca Binaria" << endl;
    cout << "Digite 1 para buscar por nome ou 2 para buscar por modalidade: ";
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1 || opcao == 2) {
        char chave[30];
        cout << "Digite o termo para busca: ";
        cin.getline(chave, 30);

        // Converter a chave para minúsculas para comparações insensíveis a caso
        auto toLowerCase = [](const char* str) -> string {
            string lowerStr;
            for (int i = 0; str[i] != '\0'; i++) {
                lowerStr += tolower(str[i]);
            }
            return lowerStr;
        };

        string chaveBusca = toLowerCase(chave);

        if (opcao == 1) {
            // Busca por nome (insensitive + substrings)
            bool encontrado = false;
            for (int i = 0; i < numRegistros; i++) {
                string nomeJogador = toLowerCase(lista[i].nome);
                if (nomeJogador.find(chaveBusca) != string::npos) {
                    lista[i].imprime();
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "Nenhum jogador encontrado." << endl;
            }
        } else if (opcao == 2) {
            // Busca por modalidade (insensitive + substrings)
            bool encontrado = false;
            for (int i = 0; i < numRegistros; i++) {
                string modalidadeJogador = toLowerCase(lista[i].modalidade);
                if (modalidadeJogador.find(chaveBusca) != string::npos) {
                    lista[i].imprime();
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "Nenhum jogador encontrado para a modalidade especificada." << endl;
            }
        }
    } else {
        cout << "Opcao invalida!" << endl;
    }
}




void alterarLista(sportlist*& lista, int& numRegistros, int& capacidade) {
    limparTela();
    cout << "Alteracao na lista" << endl;
    cout << "Digite 1 para alterar, 2 para excluir, 3 para adicionar: ";
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        char chave[30];
        cout << "Digite o nome do jogador a ser alterado: ";
        cin.getline(chave, 30);
        
        for (int i = 0; i < numRegistros; i++) {
            if (strcmp(lista[i].nome, chave) == 0) {
                cout << "Digite os novos dados do jogador (nome, idade, nacionalidade, altura, peso, modalidade):\n";
                cin.getline(lista[i].nome, 30, ',');
                cin >> lista[i].idade;
                cin.ignore();
                cin.getline(lista[i].nacionalidade, 20, ',');
                cin >> lista[i].altura >> lista[i].peso;
                cin.ignore();
                cin.getline(lista[i].modalidade, 20);
                cout << "Dados alterados com sucesso!" << endl;
                return;
            }
        }
        cout << "Jogador nao encontrado!" << endl;
    } else if (opcao == 2) {
        char chave[30];
        cout << "Digite o nome do jogador a ser excluido: ";
        cin.getline(chave, 30);

        for (int i = 0; i < numRegistros; i++) {
            if (strcmp(lista[i].nome, chave) == 0) {
                for (int j = i; j < numRegistros - 1; j++) {
                    lista[j] = lista[j + 1];
                }
                numRegistros--;
                cout << "Jogador excluido com sucesso!" << endl;
                return;
            }
        }
        cout << "Jogador nao encontrado!" << endl;
    } else if (opcao == 3) {
        if (numRegistros >= capacidade) {
            capacidade += 20;
            sportlist* novo = new sportlist[capacidade];
            memcpy(novo, lista, numRegistros * sizeof(sportlist));
            delete[] lista;
            lista = novo;
        }

        cout << "Digite os dados do novo jogador (nome, idade, nacionalidade, altura, peso, modalidade):\n";
        cin.getline(lista[numRegistros].nome, 30, ',');
        cin >> lista[numRegistros].idade;
        cin.ignore();
        cin.getline(lista[numRegistros].nacionalidade, 20, ',');
        cin >> lista[numRegistros].altura >> lista[numRegistros].peso;
        cin.ignore();
        cin.getline(lista[numRegistros].modalidade, 20);
        numRegistros++;
        cout << "Jogador adicionado com sucesso!" << endl;
    } else {
        cout << "Opcao invalida!" << endl;
    }
}

void exportarArquivo(sportlist* lista, int numRegistros) {
    limparTela();
    cout << "Exportacao de Arquivo" << endl;
    cout << "Digite 1 para CSV ou 2 para binario: ";
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
        cout << "Arquivo exportado como CSV!" << endl;
    } else if (opcao == 2) {
        ofstream saida("arquivo_exportado.dat", ios::binary);
        saida.write((char*)lista, numRegistros * sizeof(sportlist));
        saida.close();
        cout << "Arquivo exportado como binario!" << endl;
    } else {
        cout << "Opcao invalida!" << endl;
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
                cout << "Deseja salvar as alteracoes antes de sair? (s/n): ";
                char salvar;
                cin >> salvar;
                if (salvar == 's' || salvar == 'S') {
                    exportarArquivo(lista, numRegistros);
                }
                cout << "Programa encerrado!" << endl;
                return;
            default:
                cout << "Opcao invalida!" << endl;
        }

        cout << "Deseja voltar ao menu principal? (s/n): ";
        char continuar;
        cin >> continuar;
        if (continuar != 's' && continuar != 'S') {
            cout << "Deseja salvar as alteracoes antes de sair? (s/n): ";
            char salvar;
            cin >> salvar;
            if (salvar == 's' || salvar == 'S') {
                exportarArquivo(lista, numRegistros);
            }
            cout << "Programa encerrado!" << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    limparTela();
    cout << "Bem-vindo ao sistema de gerenciamento de atletas!" << endl;
    cout << "Digite o nome do arquivo que deseja carregar (com extensao .csv ou .dat): ";
    string nomeArquivo;
    cin >> nomeArquivo;

    int numRegistros = 0, capacidade = 50;
    sportlist* lista = lerDados(nomeArquivo, numRegistros, capacidade);

    if (!lista) {
        cout << "Nao foi possivel abrir o arquivo especificado. Certifique-se de que o nome esta correto e tente novamente." << endl;
        return 1;
    }

    exibirMenu(lista, numRegistros, capacidade);

    delete[] lista;
    return 0;
}