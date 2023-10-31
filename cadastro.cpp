#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "myLibc++.cpp"
using namespace std;

/*
bool validEmail(string text)
{
    std::string charArrayString(text);

    size_t foundAt =  charArrayString.find("@");
    size_t foundCom =  charArrayString.find(".com");

    if (foundAt != std::string::npos && foundCom != std::string::npos){
            return true;
    }

    return false;
}
*/


struct Pessoa {
    int id;
    char nome[30];
    char rua[50];
    char bairro[50];
    char estado[50];
    char email[50];
    char cep[50];
    char celular[50];
    char cpf[50];
    char rg[50];
    char flag;
};

int getId() {
    Pessoa p;
    ifstream f("agenda2.dat", ios::in | ios::binary);

    if (!f.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        pausa();
        return -1;
    }

    f.seekg(0, ios::end);
    f.seekg(-(sizeof(Pessoa)), ios::cur);
    f.read((char *)(&p), sizeof(Pessoa));

    if (f) {
        return p.id;
    }

    else {
        return -1;
    }
}

void cadContato() {
    Pessoa p;
    char cont = 's';
    ofstream f;

    f.open("agenda2.dat", ios::app | ios::binary);
    if (!f.is_open()) {
        cout << "Erro de abertura de arquivo ";
        pausa();
        return;
    }

    p.id = getId();
    while (cont == 's') {
        clearscr();
        p.id++;
        cout << "Codigo: " << p.id << endl;
        cout << "Nome: ";
        leStr_c(p.nome, 30);
        cout << "Rua: ";
        leStr_c(p.rua, 50);
        cout << "Bairro: ";
        leStr_c(p.bairro, 50);
        cout << "Estado: ";
        leStr_c(p.estado, 50);
        
        do{
        cout << "E-mail: ";
        leStr_c(p.email, 50);
        }while(!validEmail(p.email));

        cout << "Cep: ";
        leStr_c(p.cep, 50);
        cout << "Celular: ";
        leStr_c(p.celular, 50);
        
        do{
        cout << "Cpf: ";
        leStr_c(p.cpf, 50);
        }while(!cpfTest(p.cpf));

        do{
        cout << "Rg: ";
        leStr_c(p.rg, 50);
        }while(!rgTest(p.rg));

        f.write((char *)&p, sizeof(Pessoa));
        cout << endl;
        cout << "Novo cadastro (s/n): ";
        cin >> cont;
        cont = tolower(cont);
    }
    cout << "Fim" << endl;
    pausa();
    f.close();
}

void leContato() {
    ifstream f;
    f.open("agenda2.dat", ios::in | ios::binary);
    Pessoa p;
    int linha = 0;

    while (f.read((char *)&p, sizeof(Pessoa))) {
        if (p.flag != '*') {
            cout << "\n---------------------------------------------------------";
            cout << '\n' << setw(30) << left << "ID: " << p.id << '\n'
                 << setw(30) << left <<"Nome: " <<  p.nome << '\n'
                 << setw(30) << left << "Rua: " << p.rua << '\n'
                 << setw(30) << left << "Bairro: " << p.bairro << '\n'
                 << setw(30) << left << "Estado: " <<p.estado << '\n'
                 << setw(30) << left << "E-mail: " << p.email << '\n'
                 << setw(30) << left << "Cep: " << p.cep << '\n'
                 << setw(30) << left << "Celular: " << p.celular << '\n'
                 << setw(30) << left << "Cpf: " << p.cpf << '\n'
                 << setw(30) << left << "Rg: " << p.rg << '\n';
                 cout << "---------------------------------------------------------\n";
            linha++;
            if (linha == 20) {
                pausa();
                linha = 0;
            }
        }
    }
    f.close();
    pausa();
}

    

void excluiContato() {
    fstream f;
    f.open("agenda2.dat", ios::in | ios::out | ios::binary);
    Pessoa p;
    int id, ultimoId;
    char confirma;
    clearscr();
    ultimoId = getId();

    while (true){

        cout << "Qual o codigo a ser excluido: (-1 listagem) ";
        cin >> id;

        if (id == -1) {
            leContato();
        }

        else if ((id > ultimoId) || (id < -1))
        {
            cout << "Id invalido";
            pausa();
        }

       else if ((id <= ultimoId) && (id >= 0) && (id != -1)){
            break;
        }
    }

    while (f.read((char *)&p, sizeof(Pessoa))) {
        if (p.id == id && p.flag == '*'){
            f.seekg(-1 * sizeof(Pessoa), ios::cur);
            cout << "Nome: " << p.nome << ", de id " << p.id << ", ja foi excluido";
            pausa();
            break;
        }
        else if (p.id == id && p.flag != '*') {
            f.seekg(-1 * sizeof(Pessoa), ios::cur);
            p.flag = '*';
            cout << "Nome: " << p.nome << ", sera excluido, confirma (s/n): ";
            cin >> confirma;
            confirma = tolower(confirma);
            if (confirma == 's') {
                f.write((char *)&p, sizeof(Pessoa));
                cout << p.nome << ", Excluido com sucesso " << endl;
                pausa();
            }
            else if (confirma == 'n'){
                pausa();
                break;
            }
        }
    }
    f.close();
}

void alteraContato() {
    fstream f;
    f.open("agenda2.dat", ios::in | ios::out | ios::binary);
    Pessoa p;
    int id, campo, ultimoId;
    char confirma;
    clearscr();
    ultimoId = getId();

    while (true){
        
        cout << "Qual o codigo a ser alterado: (-1 listagem) ";
        cin >> id;
        
        if (id == -1) {
            leContato();
        }

        else if ((id > ultimoId) || (id < -1))
        {
            cout << "Id invalido";
            pausa();
        }

       else if ((id <= ultimoId) && (id >= 0) && (id != -1)){
            break;
        }
    }

    while (f.read((char *)&p, sizeof(Pessoa))) {     
        if ((p.id == id && p.flag == '*')){
            cout << "Nao foi possivel achar os dados solicitados (ou foi excluido, ou ainda nao foi criado)";
            pausa();
            break;
        }

        else if (p.id == id && p.flag != '*') {
            f.seekg(-1 * sizeof(Pessoa), ios::cur);
            cout << "1) Nome:   " << p.nome << endl;
            cout << "2) Rua:    " << p.rua << endl;
            cout << "3) Bairro: " << p.bairro << endl;
            cout << "4) Estado: " << p.estado << endl;
            cout << "5) Email:  " << p.email << endl;
            cout << "6) CEP:    " << p.cep << endl;
            cout << "7) Celular: " << p.celular << endl;
            cout << "8) CPF:    " << p.cpf << endl;
            cout << "9) RG:     " << p.rg << endl;
            
            cout << "Digite o numero do campo a ser alterado (0 to exit): ";
            cin >> campo;

            if (campo == 0) {
                break;
            }

            switch (campo) {
                case 1:
                    cout << "Nome: ";
                    leStr_c(p.nome, 30);
                    break;

                case 2:
                    cout << "Rua: ";
                    leStr_c(p.rua, 50);
                    break;

                case 3:
                    cout << "Bairro: ";
                    leStr_c(p.bairro, 50);
                    break;

                case 4:
                    cout << "Estado: ";
                    leStr_c(p.estado, 50);
                    break;

                case 5:
                    cout << "Email: ";
                    leStr_c(p.email, 50);
                    break;

                case 6:
                    cout << "CEP: ";
                    leStr_c(p.cep, 50);
                    break;

                case 7:
                    cout << "Celular: ";
                    leStr_c(p.celular, 50);
                    break;

                case 8:
                    cout << "CPF: ";
                    leStr_c(p.cpf, 50);
                    break;

                case 9:
                    cout << "RG: ";
                    leStr_c(p.rg, 50);
                    break;

                default:
                    break;
            }

            cout << "Confirma alteracao (s/n): ";
            cin >> confirma;
            confirma = tolower(confirma);
            if (confirma == 's') {
                f.write((char *)&p, sizeof(Pessoa));
                cout << p.nome << ", alterado com sucesso " << endl;
                pausa();
            }
        }
    }

    f.close();
}

int main() {
    int op = 1;
    while (op) {
        clearscr();
        if (op > 4 || op < 0){
            cout << "Voce inseriu uma opcao invalida\n";
        }

        cout << "Data: " << dataHoje() << endl << endl;
        cout << "+---------------+" << endl;
        cout << "| 1 - Cadastro  |" << endl;
        cout << "| 2 - Relatorio |" << endl;
        cout << "| 3 - Excluir   |" << endl;
        cout << "| 4 - Alteracao |" << endl;
        cout << "| 0 - Fim       |" << endl;
        cout << "+---------------+" << endl;
        cout << "Opcao: ";
        cin >> op;
        switch (op) {
            case 1:
                cadContato();
                break;

            case 2:
                leContato();
                break;

            case 3:
                excluiContato();
                break;

            case 4:
                alteraContato();
                break;

            default:
                break;
        }
    }
    return 0;
}