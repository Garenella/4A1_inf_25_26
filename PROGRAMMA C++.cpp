#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

const int MAX = 100;

struct spesa
{
    string data;
    string categoria;
    string descrizione;
    int importo;
};

// MENU
int menu()
{
    int scelta;
    do
    {
    cout << "\n1. Inserisci spesa";
    cout << "\n2. Visualizza spese";
    cout << "\n3. Modifica spesa";
    cout << "\n4. Elimina spesa";
    cout << "\n5. Esci";
    cin >> scelta;
    } 
    while (scelta < 1 || scelta > 5);
    return scelta;
}

// CONTROLLO DATA
int controllo_data(string data)
{
    // Controllo formato base
    if (data.length() != 10) return -1;
    if (data[2] != '/' || data[5] != '/') return -1;

    // Controllo che siano numeri
    for (int i = 0; i < data.length(); i++)
    {
        if (i != 2 && i != 5 && !isdigit(data[i]))
            return -1;
    }

    // Estrazione valori
    int giorno = stoi(data.substr(0,2));
    int mese   = stoi(data.substr(3,2));
    int anno   = stoi(data.substr(6,4));

    // Controllo mese
    if (mese < 1 || mese > 12) return -1;

    // Giorni per ogni mese
    int giorni_mese;

    if (mese == 2) // FEBBRAIO
    {
        // Anno bisestile
        bool bisestile = (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);

        if (bisestile)
            giorni_mese = 29;
        else
            giorni_mese = 28;
    }
    else if (mese == 4 || mese == 6 || mese == 9 || mese == 11)
    {
        giorni_mese = 30;
    }
    else
    {
        giorni_mese = 31;
    }

    // Controllo giorno
    if (giorno < 1 || giorno > giorni_mese) return -1;

    return 0;
}
// CARICAMENTO
void carica()
{
    ofstream file("spese.txt", ios::app);

    string data, categoria, descrizione;
    int importo,i=0;
    if(i>=MAX)
    {
        cout<<"Limite massimo di spese raggiunto\n";
        return;
    }

    cin.ignore();

    cout << "DATA (gg/mm/aaaa): ";
    getline(cin, data);

    if (controllo_data(data) == -1)
    {
        cout << "Data non valida\n";
        return;
    }

    cout << "CATEGORIA: ";
    getline(cin, categoria);

    cout << "DESCRIZIONE: ";
    getline(cin, descrizione);

    cout << "IMPORTO: ";
    cin >> importo;

    if (importo <= 0)
    {
        cout << "Importo non valido\n";
        return;
    }

    file << data << "|"
         << categoria << "|"
         << descrizione << "|"
         << importo << endl;

    file.close();

    cout << "Spesa salvata!\n";
    i++;
}

// VISUALIZZAZIONE
void visualizza()
{
    ifstream file("spese.txt");

    string data, categoria, descrizione, importo;

    cout << "\n--- ELENCO SPESE ---\n";

    while (getline(file, data, '|') &&
           getline(file, categoria, '|') &&
           getline(file, descrizione, '|') &&
           getline(file, importo))
    {
        cout << "DATA: " << data << endl;
        cout << "CATEGORIA: " << categoria << endl;
        cout << "DESCRIZIONE: " << descrizione << endl;
        cout << "IMPORTO: " << importo << endl;
        cout << "----------------------\n";
    }

    file.close();
}

// MODIFICA
void modifica()
{
    ifstream file("spese.txt");
    ofstream temp("temp.txt");

    string data, categoria, descrizione, importo;
    string cerca;

    cin.ignore();
    cout << "Inserisci descrizione da modificare: ";
    getline(cin, cerca);

    while (getline(file, data, '|') &&
           getline(file, categoria, '|') &&
           getline(file, descrizione, '|') &&
           getline(file, importo))
    {
        if (descrizione == cerca)
        {
            cout << "Nuova data: ";
            getline(cin, data);

            cout << "Nuova categoria: ";
            getline(cin, categoria);

            cout << "Nuova descrizione: ";
            getline(cin, descrizione);

            cout << "Nuovo importo: ";
            getline(cin, importo);
        }

        temp << data << "|"
             << categoria << "|"
             << descrizione << "|"
             << importo << endl;
    }

    file.close();
    temp.close();

    remove("spese.txt");
    rename("temp.txt", "spese.txt");

    cout << "Modifica completata!\n";
}

// ELIMINAZIONE
void elimina()
{
    ifstream file("spese.txt");
    ofstream temp("temp.txt");

    string data, categoria, descrizione, importo;
    string cerca;

    cin.ignore();
    cout << "Inserisci descrizione da eliminare: ";
    getline(cin, cerca);

    while (getline(file, data, '|') &&
           getline(file, categoria, '|') &&
           getline(file, descrizione, '|') &&
           getline(file, importo))
    {
        if (descrizione != cerca)
        {
            temp << data << "|"
                 << categoria << "|"
                 << descrizione << "|"
                 << importo << endl;
        }
    }

    file.close();
    temp.close();

    remove("spese.txt");
    rename("temp.txt", "spese.txt");

    cout << "Eliminazione completata!\n";
}

// MAIN
int main()
{
    int scelta;
    bool flag=false;
    do
    {
        scelta = menu();

        switch (scelta)
        {
            case 1:
                carica();
                flag=true;
                break;

            case 2:
                if (flag)
                    visualizza();
                else
                    cout << "Nessuna spesa da visualizzare\n";
                break;

            case 3:
                if (flag)
                    modifica();
                else
                    cout << "Nessuna spesa da modificare\n";
                break;

            case 4:
                if (flag)
                    elimina();
                else
                    cout << "Nessuna spesa da eliminare\n";
                break;

            case 5:
                cout << "Uscita...\n";
                break;

            default:
                cout << "Scelta non valida\n";
        }

    } while (scelta != 5);

    return 0;
}