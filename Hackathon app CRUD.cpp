#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Spesa
{
    string data;
    string categoria;
    string descrizione;
    int importo;
};


const int MAX_SPESE = 100;
const string NOME_FILE = "spese.txt";


bool dataValida(string data) 
{
    if (data.size() != 10) 
    {
        return false;
    }

    if (data[4] != '-' || data[7] != '-') 
    {
        return false;
    }

    for (int i = 0; i < data.size(); i++) 
    {
        if (i != 4 && i != 7) 
        {
            if (data[i] < '0' || data[i] > '9') 
            {
                return false;
            }
        }
    }

    int anno = stoi(data.substr(0, 4));
    int mese = stoi(data.substr(5, 2));
    int giorno = stoi(data.substr(8, 2));
    

    if (anno < 1900 || anno > 2100)
    {
    return false;
    }

    if (mese < 1 || mese > 12) 
    {
        return false;
    }    
    int giorniMese;

    if (mese == 2) 
    {
        giorniMese = 28; 
    } 
    else if (mese == 4 || mese == 6 || mese == 9 || mese == 11) 
    {
        giorniMese = 30;
    } 
    else 
    {
        giorniMese = 31;
    }

    if (giorno < 1 || giorno > giorniMese) 
    {
        return false;
    }    
    return true;
}


void salvaSuFile(Spesa spese[], int n) 
{
    ofstream file(NOME_FILE);

    if (!file) 
    {
        cout << "Errore apertura file." << endl;
        return;
    }

    file << "data;categoria;descrizione;importo" << endl;

    for (int i = 0; i < n; i++) 
    {
        file << spese[i].data << ";"
             << spese[i].categoria << ";"
             << spese[i].descrizione << ";"
             << spese[i].importo << endl;
    }

    file.close();
}




void caricaDaFile(Spesa spese[], int &n) 
{
    ifstream file(NOME_FILE);
    n = 0;

    if (!file) 
    {
        cout << "File non trovato. Verra' creato al primo salvataggio." << endl;
        return;
    }

    string riga;
    getline(file, riga); // salta header

    while (getline(file, riga) && n < MAX_SPESE) 
    {
        string data = "";
        string categoria = "";
        string descrizione = "";
        string importoStr = "";

        int i = 0;

        while (i < riga.size() && riga[i] != ';') 
        {
            data += riga[i];
            i++;
        }
        i++;

        while (i < riga.size() && riga[i] != ';') 
        {
            categoria += riga[i];
            i++;
        }
        i++;

        while (i < riga.size() && riga[i] != ';') 
        {
            descrizione += riga[i];
            i++;
        }
        i++;

        while (i < riga.size()) 
        {
            importoStr += riga[i];
            i++;
        }

        spese[n].data = data;
        spese[n].categoria = categoria;
        spese[n].descrizione = descrizione;
        spese[n].importo = stoi(importoStr);

        n++;
    }

    file.close();
}


void visualizzaSpese(Spesa spese[], int n) 
{
    if (n == 0) 
    {
        cout << "Nessuna spesa." << endl;
        return;
    }

    for (int i = 0; i < n; i++) 
    {
        cout << i + 1 << ". "
             << spese[i].data << " | "
             << spese[i].categoria << " | "
             << spese[i].descrizione << " | "
             << spese[i].importo << endl;
    }
}


void aggiungiSpesa(Spesa spese[], int &n)
{
    if (n >= MAX_SPESE) 
    {
        cout << "Archivio pieno." << endl;
        return;
    }

    do 
    {
        cout << "Inserisci data (AAAA-MM-DD): ";
        cin >> spese[n].data;

        if (!dataValida(spese[n].data)) 
        {
            cout << "Data non valida. Riprova." << endl;
        }

    } while (!dataValida(spese[n].data));

    cout << "Categoria: ";
    cin >> spese[n].categoria;

    cin.ignore();
    cout << "Descrizione: ";
    getline(cin, spese[n].descrizione);

    cout << "Importo: ";
    cin >> spese[n].importo;

    n++;
    salvaSuFile(spese, n);

    cout << "Spesa aggiunta correttamente." << endl;
}


void visualizzaPerCategoria(Spesa spese[], int n) 
{
    string cat;
    bool trovata = false;

    cout << "Categoria da cercare: ";
    cin >> cat;

    for (int i = 0; i < n; i++) 
    {
        if (spese[i].categoria == cat) 
        {
            cout << i + 1 << ". "
                 << spese[i].data << " | "
                 << spese[i].descrizione << " | "
                 << spese[i].importo << endl;
            trovata = true;
        }
    }

    if (!trovata) 
    {
        cout << "Nessuna spesa trovata." << endl;
    }
}

void modificaSpesa(Spesa spese[], int n) 
{
    if (n == 0) 
    {
        cout << "Nessuna spesa da modificare." << endl;
        return;
    }

    int scelta;
    visualizzaSpese(spese, n);

    cout << "Numero da modificare: ";
    cin >> scelta;

    if (scelta < 1 || scelta > n) 
    {
        cout << "Errore." << endl;
        return;
    }

    int i = scelta - 1;

    do 
    {
        cout << "Nuova data (AAAA-MM-DD): ";
        cin >> spese[i].data;

        if (!dataValida(spese[i].data)) 
        {
            cout << "Data non valida. Riprova." << endl;
        }

    } while (!dataValida(spese[i].data));

    cout << "Nuova categoria: ";
    cin >> spese[i].categoria;

    cin.ignore();
    cout << "Nuova descrizione: ";
    getline(cin, spese[i].descrizione);

    cout << "Nuovo importo: ";
    cin >> spese[i].importo;

    salvaSuFile(spese, n);

    cout << "Spesa modificata." << endl;
}

void eliminaSpesa(Spesa spese[], int &n) 
{
    if (n == 0) 
    {
        cout << "Nessuna spesa da eliminare." << endl;
        return;
    }

    int scelta;
    visualizzaSpese(spese, n);

    cout << "Numero da eliminare: ";
    cin >> scelta;

    if (scelta < 1 || scelta > n) 
    {
        cout << "Errore." << endl;
        return;
    }

    int pos = scelta - 1;

    for (int i = pos; i < n - 1; i++) 
    {
        spese[i] = spese[i + 1];
    }

    n--;
    salvaSuFile(spese, n);

    cout << "Spesa eliminata." << endl;
}

int menu() 
{
    int scelta;

    cout << endl;
    cout << "   __  ________  ____  __" << endl;
    cout << "  /  |/  / __/ |/ / / / /" << endl;
    cout << " / /|_/ / _//    / /_/ / " << endl;
    cout << "/_/  /_/___/_/|_/\\____/  " << endl;
    cout << endl;

    cout << "1. Aggiungi spesa" << endl;
    cout << "2. Visualizza tutte" << endl;
    cout << "3. Modifica" << endl;
    cout << "4. Elimina" << endl;
    cout << "5. Cerca per categoria" << endl;
    cout << "6. Salva" << endl;
    cout << "0. Esci" << endl;
    cout << "Scelta: ";

    cin >> scelta;
    return scelta;
}

int main() 
{
    Spesa spese[MAX_SPESE];
    int n=0;
    int scelta;

    caricaDaFile(spese, n);

    do 
    {
        scelta = menu();

        switch (scelta) 
        {
            case 1:
                aggiungiSpesa(spese, n);
                break;
            case 2:
                visualizzaSpese(spese, n);
                break;
            case 3:
                modificaSpesa(spese, n);
                break;
            case 4:
                eliminaSpesa(spese, n);
                break;
            case 5:
                visualizzaPerCategoria(spese, n);
                break;
            case 6:
                salvaSuFile(spese, n);
                cout << "Salvato!" << endl;
                break;
            case 0:
                salvaSuFile(spese, n);
                cout << "Uscita..." << endl;
                break;
            default:
                cout << "Scelta non valida." << endl;
        }

    } while (scelta != 0);

    return 0;
}