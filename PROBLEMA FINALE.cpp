#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Spesa {
    string data;
    string categoria;
    string descrizione;
    double importo;
};

const int MAX = 100;
Spesa spese[MAX];
int numeroSpese = 0;

void carica() {
    ifstream file("spese.txt");

    while (file >> spese[numeroSpese].data >> spese[numeroSpese].categoria >> spese[numeroSpese].descrizione >> spese[numeroSpese].importo) {
        numeroSpese++;
    }

    file.close();
}

void salva() {
    ofstream file("spese.txt");

    for (int i = 0; i < numeroSpese; i++) {
        file << spese[i].data << " " << spese[i].categoria << " " << spese[i].descrizione << " " << spese[i].importo << "\n";
    }

    file.close();
}

void aggiungi() {
    if (numeroSpese >= MAX) {
        cout << "Archivio pieno!\n";
        return;
    }

    string data;
    bool ok = false;

    while (!ok) {
        cout << "Data (AAAA-MM-GG): ";
        cin >> data;

        if (data.length() != 10) {
            cout << "Data non valida!\n";
            continue;
        }

        if (data[4] != '-' || data[7] != '-') {
            cout << "Formato errato! Usa AAAA-MM-GG\n";
            continue;
        }

        if (data < "1900-01-01" || data > "2026-12-31") {
            cout << "Data fuori range!\n";
            continue;
        }

        ok = true;
    }

    spese[numeroSpese].data = data;

    cout << "Categoria: ";
    cin >> spese[numeroSpese].categoria;

    cout << "Descrizione: ";
    cin >> spese[numeroSpese].descrizione;

    cout << "Importo: ";
    cin >> spese[numeroSpese].importo;

    numeroSpese++;
}

void visualizza() {
    if (numeroSpese == 0) {
        cout << "Nessuna spesa!\n";
        return;
    }

    for (int i = 0; i < numeroSpese; i++) {
        cout << i << ") " << spese[i].data << " | " << spese[i].categoria << " | " << spese[i].descrizione << " | " << spese[i].importo << " euro\n";
    }
}

void modifica() {
    int i;

    visualizza();

    cout << "Indice da modificare: ";
    cin >> i;

    if (i < 0 || i >= numeroSpese) {
        cout << "Indice non valido!\n";
        return;
    }

    cout << "Nuova categoria: ";
    cin >> spese[i].categoria;

    cout << "Nuova descrizione: ";
    cin >> spese[i].descrizione;

    cout << "Nuovo importo: ";
    cin >> spese[i].importo;
}

void elimina() {
    int i;

    visualizza();

    cout << "Indice da eliminare: ";
    cin >> i;

    if (i < 0 || i >= numeroSpese) {
        cout << "Indice non valido!\n";
        return;
    }

    for (int j = i; j < numeroSpese - 1; j++) {
        spese[j] = spese[j + 1];
    }

    numeroSpese--;
}

int main() {
    carica();

    int scelta;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Aggiungi\n";
        cout << "2. Visualizza\n";
        cout << "3. Modifica\n";
        cout << "4. Elimina\n";
        cout << "5. Esci\n";
        cout << "Scelta: ";
        cin >> scelta;

        switch (scelta) {
            case 1: 
				aggiungi(); 
				break;
            case 2: 
				visualizza(); 
				break;
            case 3: 
				modifica(); 
				break;
            case 4: 
				elimina(); 
				break;
            case 5: 
				salva(); 
				cout << "Dati salvati!\n"; 
				break;
            default: 
				cout << "Errore!\n";
        }

    } while (scelta != 5);

    return 0;
}