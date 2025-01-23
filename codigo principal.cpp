#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

struct sportlist {
    char nome[30];
    int idade;
    char nacionalidade[20];
    float altura;
    int peso;
    char modalidade[20];

    void imprime() {
        cout << "-----------------------------------------" << endl
             << "Nome do Jogador: " << nome << endl
             << "Idade do Jogador: " << idade << " Anos" << endl
             << "Nacionalidade do Jogador: " << nacionalidade << endl
             << "Altura do Jogador: " << altura << " M" << endl
             << "Peso do Jogador: " << peso << " KG" << endl
             << "Modalidade do Jogador: " << modalidade << endl;
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

sportlist* lerDados(int& numRegistros, int& capacidade) {
    ifstream entrada("arquivoentrada.csv");
    if (!entrada) {
        return NULL;
    }

    string descArquivo;
    getline(entrada, descArquivo);

    sportlist* vetorSportlist = new sportlist[capacidade];
    sportlist algumsportlist;

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

        auto comp = [&](const sportlist& a, const sportlist& b) {
            return (opcao == 1) ? strcmp(a.nome, b.nome) < 0 : strcmp(a.modalidade, b.modalidade) < 0;
        };

        sort(lista, lista + numRegistros, comp);

        int inicio = 0, fim = numRegistros - 1;
        bool encontrado = false;
        while (inicio <= fim) {
            int meio = (inicio + fim) / 2;
            int cmp = (opcao == 1) ? strcmp(lista[meio].nome, chave) : strcmp(lista[meio].modalidade, chave);
            if (cmp == 0) {
                lista[meio].imprime();
                encontrado = true;
                break;
            } else if (cmp < 0) {
                inicio = meio + 1;
            } else {
                fim = meio - 1;
            }
        }

        if (!encontrado) {
            cout << "Nenhum registro encontrado." << endl;
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

void visualizarArquivo(sportlist* lista, int numRegistros) {
    limparTela();
    cout << "Visualizacao de Arquivo" << endl;
    for (int i = 0; i < numRegistros; i++) {
        lista[i].imprime();
    }
}

int main() {
    sportlist* lista;
    int numRegistros = 0, capacidade = 50;
    lista = lerDados(numRegistros, capacidade);

    if (!lista) {
        cout << "Erro ao ler o arquivo de entrada." << endl;
        return 1;
    }

    bool continuar = true;
    while (continuar) {
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
                visualizarArquivo(lista, numRegistros);
                break;
            case 5: {
                cout << "Deseja salvar as alteracoes antes de sair? (s/n): ";
                char salvar;
                cin >> salvar;
                if (salvar == 's' || salvar == 'S') {
                    ofstream saida("arquivoentrada.csv");
                    saida << "Nome,Idade,Nacionalidade,Altura,Peso,Modalidade\n";
                    for (int i = 0; i < numRegistros; i++) {
                        saida << lista[i].nome << ',' << lista[i].idade << ',' << lista[i].nacionalidade << ','
                              << lista[i].altura << ',' << lista[i].peso << ',' << lista[i].modalidade << '\n';
                    }
                    saida.close();
                }
                continuar = false;
                break;
            }
            default:
                cout << "Opcao invalida!" << endl;
        }

        if (continuar) {
            cout << "Deseja voltar ao menu principal? (s/n): ";
            char resposta;
            cin >> resposta;
            if (resposta != 's' && resposta != 'S') {
                continuar = false;
            }
        }
    }

    delete[] lista;
    return 0;
}
